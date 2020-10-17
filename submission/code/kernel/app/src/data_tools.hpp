#pragma once

#ifndef APP_SRC_DATA_TOOLS_HPP_
#define APP_SRC_DATA_TOOLS_HPP_

#include "tsetlini/tsetlini_types.hpp"

#include "json/json.hpp"

#include <vector>
#include <string>


std::vector<std::string> extract_cust_id(std::vector<std::vector<std::string>> & cat_rows);
std::vector<int> extract_target(std::vector<std::vector<float>> & num_rows);

std::vector<Tsetlini::bit_vector_uint64> encode_features(
    std::vector<std::vector<std::string>> & cat_rows,
    std::vector<std::vector<float>> & num_rows,
    nlohmann::json const & encoding
);


#endif /* APP_SRC_DATA_TOOLS_HPP_ */
