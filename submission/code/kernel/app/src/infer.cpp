#include "read_csv.hpp"
#include "json_io.hpp"
#include "data_tools.hpp"
#include "filesystem.hpp"

#include "json/json.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

#include "tsetlini/tsetlini_status_code.hpp"
#include "tsetlini/tsetlini.hpp"
#include "tsetlini/tsetlini_state_json.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include <iterator>


static
auto error_printer = [](Tsetlini::status_message_t && msg)
{
    spdlog::error("{}", msg.second);

    std::exit(1);

    return msg;
};


void infer(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname,
    std::string const & infer_ofname)
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

    std::vector<std::string> const customers = extract_cust_id(cat_rows);

    spdlog::info("Encoding features...");
    spdlog::stopwatch sw_enc;
    auto const X_test = encode_features(cat_rows, num_rows, encoding);
    spdlog::info("...completed in {:.1f} secs", sw_enc);

    std::ifstream ifile(model_ifname);
    std::string const str_state((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());

    nlohmann::json jparams = nlohmann::json::parse(str_state);
    bool const do_regression = jparams["estimator"] == "regressor";
    spdlog::info("{} inference", do_regression ? "Regression" : "Classification");


    auto save_probas = [&](std::vector<double> const & probas)
    {
        std::ofstream ofile(infer_ofname);

        for (auto ix = 0u; ix < customers.size(); ++ix)
        {
            //ofile << fmt::format("{},{},{}\n", customers[ix], scores[ix][0], scores[ix][1]);
            ofile << fmt::format("{},{:.8f}\n", customers[ix], probas[ix]);
        }
    };

    if (do_regression)
    {
        Tsetlini::RegressorStateBitwise state(Tsetlini::params_t{});
        Tsetlini::from_json_string(state, str_state);

        Tsetlini::RegressorBitwise clf(state);

        auto const params = clf.read_params();
        double const T = std::get<int>(params.at("threshold"));

        spdlog::info("Predicting...");
        spdlog::stopwatch sw_pred;
        clf.predict(X_test)
            .leftMap(error_printer)
            .rightMap([&](Tsetlini::response_vector_type && y_hat)
            {
                spdlog::info("...completed in {:.1f} secs", sw_pred);

                std::vector<double> probas;
                probas.reserve(y_hat.size());
                std::transform(y_hat.cbegin(), y_hat.cend(), std::back_inserter(probas),
                    [T](Tsetlini::response_type const & resp)
                    {
                        double rv = (double)resp / T;

                        return rv;
                    }
                );

                spdlog::info("scores {}", y_hat.size());
                spdlog::info("[35] {},{:.5f}", y_hat[35], probas[35]);
                spdlog::info("[36] {},{:.5f}", y_hat[36], probas[36]);
                spdlog::info("[37] {},{:.5f}", y_hat[37], probas[37]);
                spdlog::info("[73] {},{:.5f}", y_hat[73], probas[73]);
                spdlog::info("[74] {},{:.5f}", y_hat[74], probas[74]);
                spdlog::info("[75] {},{:.5f}", y_hat[75], probas[75]);
                spdlog::info("[208] {},{:.5f}", y_hat[208], probas[208]);
                spdlog::info("[265] {},{:.5f}", y_hat[265], probas[265]);

                save_probas(probas);

                return y_hat;
            });
    }
    else
    {
        Tsetlini::ClassifierStateBitwise state(Tsetlini::params_t{});
        Tsetlini::from_json_string(state, str_state);

        Tsetlini::ClassifierBitwise clf(state);

        auto const params = clf.read_params();
        double const T = std::get<int>(params.at("threshold"));

        spdlog::info("Predicting...");
        spdlog::stopwatch sw_pred;
        clf.predict_raw(X_test)
            .leftMap(error_printer)
            .rightMap([&](std::vector<Tsetlini::aligned_vector_int> && scores)
            {
                spdlog::info("...completed in {:.1f} secs", sw_pred);

                std::vector<double> probas;
                probas.reserve(scores.size());
                std::transform(scores.cbegin(), scores.cend(), std::back_inserter(probas),
                    [T](Tsetlini::aligned_vector_int const & sc)
                    {
                        double rv = 0.5 + (sc[1] - sc[0]) / (4 * T);

                        return rv;
                    }
                );

                spdlog::info("scores {}", scores.size());
                spdlog::info("[35] {},{},{:.5f}", scores[35][0], scores[35][1], probas[35]);
                spdlog::info("[36] {},{},{:.5f}", scores[36][0], scores[36][1], probas[36]);
                spdlog::info("[37] {},{},{:.5f}", scores[37][0], scores[37][1], probas[37]);
                spdlog::info("[73] {},{},{:.5f}", scores[73][0], scores[73][1], probas[73]);
                spdlog::info("[74] {},{},{:.5f}", scores[74][0], scores[74][1], probas[74]);
                spdlog::info("[75] {},{},{:.5f}", scores[75][0], scores[75][1], probas[75]);
                spdlog::info("[208] {},{},{:.5f}", scores[208][0], scores[208][1], probas[208]);
                spdlog::info("[265] {},{},{:.5f}", scores[265][0], scores[265][1], probas[265]);

                save_probas(probas);

                return scores;
            });
    }
}
