#pragma once

#ifndef APP_SRC_TRAIN_HPP_
#define APP_SRC_TRAIN_HPP_

#include "model_params.hpp"

#include <string>


void train(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname,
    std::string const & model_ofname,
    model_params_t const & model_params,
    bool const f201906,
    bool const fseasonal);


#endif /* APP_SRC_TRAIN_HPP_ */
