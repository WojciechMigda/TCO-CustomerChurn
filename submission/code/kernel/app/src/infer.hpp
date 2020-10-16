#pragma once

#ifndef APP_SRC_INFER_HPP_
#define APP_SRC_INFER_HPP_

#include <string>


void infer(
    std::string const & csv_ifname,
    std::string const & encoder_ifname,
    std::string const & model_ifname);


#endif /* APP_SRC_INFER_HPP_ */
