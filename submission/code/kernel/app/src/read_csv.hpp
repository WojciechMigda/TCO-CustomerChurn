#pragma once

#ifndef APP_SRC_READ_CSV_HPP_
#define APP_SRC_READ_CSV_HPP_

#include <string>
#include <vector>
#include <utility>


std::pair<std::vector<std::string>, std::vector<float>> read_csv(std::string const & ifname);


#endif /* APP_SRC_READ_CSV_HPP_ */
