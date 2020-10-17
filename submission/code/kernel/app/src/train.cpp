#include "model_params.hpp"
#include "read_csv.hpp"

#include "json/json.hpp"
#include "spdlog/spdlog.h"

#include <string>


void train(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname,
    model_params_t const & model_params)
{
    read_csv(csv_ifname);
}
