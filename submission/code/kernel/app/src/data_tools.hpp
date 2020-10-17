#pragma once

#ifndef APP_SRC_DATA_TOOLS_HPP_
#define APP_SRC_DATA_TOOLS_HPP_

#include <vector>
#include <string>


std::vector<std::string> extract_cust_id(std::vector<std::vector<std::string>> & cat_rows);
std::vector<int> extract_target(std::vector<std::vector<float>> & num_rows);


#endif /* APP_SRC_DATA_TOOLS_HPP_ */
