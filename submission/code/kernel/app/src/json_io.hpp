#pragma once

#ifndef APP_SRC_JSON_IO_HPP_
#define APP_SRC_JSON_IO_HPP_

#include "json/json.hpp"

#include <string>


nlohmann::json read_json(std::string const & ifname);


#endif /* APP_SRC_JSON_IO_HPP_ */
