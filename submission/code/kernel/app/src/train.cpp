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
    auto [cat_rows, num_rows] = read_csv(csv_ifname);

    spdlog::info("CSV: read {} rows with categorical features and {} rows with numerical ones.",
        cat_rows.size(), num_rows.size());

    /*
     * cat_rows:
     *      md5_cust_party_key
     *      province_cd
     *      Gender_CD
     *      prod_monodual_cd
     *      customer_value_cd
     */
}
