#include "read_csv.hpp"
#include "json_io.hpp"
#include "data_tools.hpp"

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

    spdlog::info("Reading CSV...");
    spdlog::stopwatch sw_csv;
    auto [cat_rows, num_rows] = read_csv(csv_ifname);
    spdlog::info("...completed in {:.1} secs", sw_csv);

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
    spdlog::info("...completed in {:.1} secs", sw_enc);

    std::ifstream ifile(model_ifname);
    std::string const str_state((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());
    Tsetlini::ClassifierStateBitwise state(Tsetlini::params_t{});
    Tsetlini::from_json_string(state, str_state);

    Tsetlini::ClassifierBitwise clf(state);

    spdlog::info("Predicting...");
    spdlog::stopwatch sw_pred;
    clf.predict_raw(X_test)
        .leftMap(error_printer)
        .rightMap([&](std::vector<Tsetlini::aligned_vector_int> && scores)
        {
            spdlog::info("...completed in {:.1f} secs", sw_pred);

            spdlog::info("scores {}", scores.size());
            spdlog::info("[35] {},{}", scores[35][0], scores[35][1]);
            spdlog::info("[36] {},{}", scores[36][0], scores[36][1]);
            spdlog::info("[37] {},{}", scores[37][0], scores[37][1]);
            spdlog::info("[73] {},{}", scores[73][0], scores[73][1]);
            spdlog::info("[74] {},{}", scores[74][0], scores[74][1]);
            spdlog::info("[75] {},{}", scores[75][0], scores[75][1]);
            spdlog::info("[208] {},{}", scores[208][0], scores[208][1]);
            spdlog::info("[265] {},{}", scores[265][0], scores[265][1]);

            std::ofstream ofile(infer_ofname);

            for (auto ix = 0u; ix < customers.size(); ++ix)
            {
                ofile << fmt::format("{},{},{}\n", customers[ix], scores[ix][0], scores[ix][1]);
            }

            return scores;
        });
}
