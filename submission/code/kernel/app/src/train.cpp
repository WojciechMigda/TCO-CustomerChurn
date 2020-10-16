#include "model_params.hpp"
#include "read_csv.hpp"

#include "json/json.hpp"

#include <string>


void train(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname,
    model_params_t const & model_params)
{
    //auto const [cat_vec, num_vec] =
        read_csv(csv_ifname, false);
}
