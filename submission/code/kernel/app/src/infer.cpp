#include "read_csv.hpp"
#include "json_io.hpp"
#include "data_tools.hpp"

#include "json/json.hpp"
#include "spdlog/spdlog.h"

#include <string>


void infer(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname)
{
    auto encoding = read_json(encoder_ifname);

    if (encoding.empty())
    {
        spdlog::error("JSON: encoding read from {} failed.", encoder_ifname);

        return;
    }

    auto [cat_rows, num_rows] = read_csv(csv_ifname);

    if (cat_rows.empty() or num_rows.empty())
    {
        spdlog::error("CSV: read from {} failed.", csv_ifname);

        return;
    }

    spdlog::info("CSV: read {} rows with categorical features and {} rows with numerical ones.",
        cat_rows.size(), num_rows.size());

    auto X_train = encode_features(cat_rows, num_rows, encoding);
}
