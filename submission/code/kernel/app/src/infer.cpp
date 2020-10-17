#include "read_csv.hpp"

#include "json/json.hpp"
#include "spdlog/spdlog.h"

#include <string>


void infer(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname)
{
    auto [cat_rows, num_rows] = read_csv(csv_ifname);

    spdlog::info("CSV: read {} rows with categorical features and {} rows with numerical ones.",
        cat_rows.size(), num_rows.size());
}
