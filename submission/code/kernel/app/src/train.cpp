#include "model_params.hpp"
#include "read_csv.hpp"
#include "columns.hpp"
#include "data_tools.hpp"
#include "json_io.hpp"

#include "spdlog/spdlog.h"

#include <string>


void train(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname,
    model_params_t const & model_params)
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

    if (num_rows[0].size() < (Num::target_ind + 1))
    {
        spdlog::error("CSV: number of features is too small. 'target_ind' column is missing?");

        return;
    }

    auto const target = extract_target(num_rows);

    auto X_train = encode_features(cat_rows, num_rows, encoding);
}
