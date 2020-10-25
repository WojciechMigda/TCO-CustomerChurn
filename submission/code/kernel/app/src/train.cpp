#include "model_params.hpp"
#include "read_csv.hpp"
#include "columns.hpp"
#include "data_tools.hpp"
#include "json_io.hpp"
#include "filesystem.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include "tsetlini/tsetlini_status_code.hpp"
#include "tsetlini/tsetlini.hpp"
#include "tsetlini/tsetlini_state_json.hpp"

#include <string>
#include <cstdlib>
#include <fstream>


static
auto error_printer = [](Tsetlini::status_message_t && msg)
{
    spdlog::error("{}", msg.second);

    std::exit(1);

    return msg;
};


namespace params
{

unsigned int threshold(model_params_t const & params)
{
    return std::get<unsigned int>(params.at("threshold"));
}


unsigned int clauses(model_params_t const & params)
{
    return std::get<unsigned int>(params.at("clauses"));
}


int max_weight(model_params_t const & params)
{
    return std::get<int>(params.at("max_weight"));
}


int n_jobs(model_params_t const & params)
{
    return std::get<int>(params.at("n_jobs"));
}


float s(model_params_t const & params)
{
    return std::get<float>(params.at("s"));
}


unsigned int nepochs(model_params_t const & params)
{
    return std::get<unsigned int>(params.at("nepochs"));
}


bool boost_tpf(model_params_t const & params)
{
    return std::get<bool>(params.at("boost_tpf"));
}


bool regression(model_params_t const & params)
{
    return std::get<bool>(params.at("regression"));
}


}  // namespace params


auto partial_fit(
    Tsetlini::ClassifierBitwise & clf,
    std::vector<Tsetlini::bit_vector_uint64> const & X_train,
    Tsetlini::label_vector_type const & target,
    unsigned int NEPOCHS)
{
    return clf.partial_fit(X_train, target, 2, NEPOCHS);
}

auto partial_fit(
    Tsetlini::RegressorBitwise & clf,
    std::vector<Tsetlini::bit_vector_uint64> const & X_train,
    Tsetlini::response_vector_type const & target,
    unsigned int NEPOCHS)
{
    return clf.partial_fit(X_train, target, NEPOCHS);
}


void train(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname,
    std::string const & model_ofname,
    model_params_t const & model_params)
{
    auto encoding = read_json(encoder_ifname);

    if (encoding.empty())
    {
        spdlog::error("JSON: encoding read from {} failed.", encoder_ifname);

        return;
    }
    else
    {
        spdlog::info("JSON: read encodings from {}", filename(encoder_ifname));
    }

    spdlog::info("CSV: reading {} ...", filename(csv_ifname));
    spdlog::stopwatch sw_csv;
    auto [cat_rows, num_rows] = read_csv(csv_ifname);
    spdlog::info("...completed in {:.1f} secs", sw_csv);

    if (cat_rows.empty() or num_rows.empty())
    {
        spdlog::error("CSV: read from {} failed.", csv_ifname);

        return;
    }

    spdlog::info("CSV: read {} rows with categorical features and {} rows with numerical ones.",
        cat_rows.size(), num_rows.size());

    if (num_rows[0].size() < (Num::target_ind + 1))
    {
        spdlog::error("CSV: number of features is too small. 'target_ind' column is missing?");

        return;
    }

    auto const target = extract_target(num_rows);

    spdlog::info("Encoding features...");
    spdlog::stopwatch sw_enc;
    auto X_train = encode_features(cat_rows, num_rows, encoding);
    spdlog::info("...completed in {:.1f} secs", sw_enc);


    auto const NEPOCHS = params::nepochs(model_params);

    auto train_model = [&](auto & clf, auto const & target)
    {
        spdlog::stopwatch sw;
        spdlog::info("Partial fit initiated for {} epoch(s)...", NEPOCHS);

        auto status = partial_fit(clf, X_train, target, NEPOCHS);

        spdlog::info("...completed in {:.1f} secs.", sw);

        if (status.first == Tsetlini::S_OK)
        {
            std::string const js_state = Tsetlini::to_json_string(clf.read_state());

            std::ofstream ofile(model_ofname);

            ofile << js_state;
            ofile.close();

            spdlog::info("Model saved into {}", filename(model_ofname));
        }
        else
        {
            spdlog::error("Partial fit completed with an error: {}", status.first);
        }
    };


    auto params_to_string = [](auto const & clf, unsigned int const NEPOCHS, bool do_regression) -> std::string
    {
        Tsetlini::params_t const p = clf.read_params();

        auto const C = do_regression ?
            std::get<int>(p.at("number_of_regressor_clauses"))
            :
            std::get<int>(p.at("number_of_pos_neg_clauses_per_label"));
        auto const T = std::get<int>(p.at("threshold"));
        auto const s = std::get<Tsetlini::real_type>(p.at("s"));
        auto const w = std::get<int>(p.at("max_weight"));
        auto const btpf = std::get<int>(p.at("boost_true_positive_feedback"));

        std::string rv = fmt::format("C {} T {} s {:.1f} w {} boost-tpf {} nepochs {}",
            C, T, s, w == std::numeric_limits<int>::max() ? -1 : w, btpf, NEPOCHS);

        return rv;
    };


    auto make_regression_target = [&]()
    {
        Tsetlini::response_vector_type y;
        y.resize(target.size());
        auto const T = params::threshold(model_params);

        std::transform(target.cbegin(), target.cend(), y.begin(),
            [T](int t)
            {
                return t == 0 ? 0 : T;
            }
        );

        return y;
    };

    if (not model_ifname.empty())
    {
        std::ifstream ifile(model_ifname);
        std::string const str_state((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());

        nlohmann::json jparams = nlohmann::json::parse(str_state);
        bool const do_regression = jparams["estimator"] == "regressor";
        spdlog::info("{} requested", do_regression ? "Regression" : "Classification");

        if (do_regression)
        {
            Tsetlini::RegressorStateBitwise state(Tsetlini::params_t{});
            Tsetlini::from_json_string(state, str_state);
            spdlog::info("Model restored from {}", filename(model_ifname));

            Tsetlini::RegressorBitwise clf(state);

            spdlog::info("{}", params_to_string(clf, NEPOCHS, do_regression));

            auto const y = make_regression_target();

            train_model(clf, y);
        }
        else
        {
            Tsetlini::ClassifierStateBitwise state(Tsetlini::params_t{});
            Tsetlini::from_json_string(state, str_state);
            spdlog::info("Model restored from {}", filename(model_ifname));

            Tsetlini::ClassifierBitwise clf(state);

            spdlog::info("{}", params_to_string(clf, NEPOCHS, do_regression));

            train_model(clf, target);
        }
    }
    else
    {
        bool const do_regression = params::regression(model_params);
        spdlog::info("{} requested", do_regression ? "Regression" : "Classification");

        std::string const j_params = do_regression ?
            R"({
                "threshold": )" + std::to_string(params::threshold(model_params)) + R"(,
                "s": )" + std::to_string(params::s(model_params)) + R"(,
                "number_of_regressor_clauses": )" + std::to_string(params::clauses(model_params)) + R"(,
                "number_of_states": 127,
                "boost_true_positive_feedback": )" + std::to_string(params::boost_tpf(model_params)) + R"(,
                "loss_fn": "MSE",
                "random_state": 1,
                "n_jobs": )" + std::to_string(params::n_jobs(model_params)) + R"(,
                "clause_output_tile_size": 16,
                "weighted": true,
                "max_weight": )" + std::to_string(params::max_weight(model_params)) + R"(,
                "verbose": false
                })"
            :
            R"({
                "threshold": )" + std::to_string(params::threshold(model_params)) + R"(,
                "s": )" + std::to_string(params::s(model_params)) + R"(,
                "number_of_pos_neg_clauses_per_label": )" + std::to_string(params::clauses(model_params)) + R"(,
                "number_of_states": 127,
                "boost_true_positive_feedback": )" + std::to_string(params::boost_tpf(model_params)) + R"(,
                "random_state": 1,
                "n_jobs": )" + std::to_string(params::n_jobs(model_params)) + R"(,
                "clause_output_tile_size": 16,
                "weighted": true,
                "max_weight": )" + std::to_string(params::max_weight(model_params)) + R"(,
                "verbose": false
                })"
            ;

        if (do_regression)
        {
            auto const y = make_regression_target();

            Tsetlini::make_regressor_bitwise(j_params)
                .leftMap(error_printer)
                .rightMap([&](Tsetlini::RegressorBitwise && clf)
                {
                    spdlog::info("{}", params_to_string(clf, NEPOCHS, do_regression));

                    train_model(clf, y);

                    return clf;
                });
        }
        else
        {
            Tsetlini::make_classifier_bitwise(j_params)
                .leftMap(error_printer)
                .rightMap([&](Tsetlini::ClassifierBitwise && clf)
                {
                    spdlog::info("{}", params_to_string(clf, NEPOCHS, do_regression));

                    train_model(clf, target);

                    return clf;
                });
        }
    }
}
