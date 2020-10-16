#pragma once

#ifndef APP_SRC_MODEL_PARAMS_HPP_
#define APP_SRC_MODEL_PARAMS_HPP_

#include <unordered_map>
#include <string>
#include <variant>
#include <string>


using model_param_value_t = std::variant<unsigned int, int, float, std::string, bool>;

using model_params_t = std::unordered_map<std::string, model_param_value_t>;


#endif /* APP_SRC_MODEL_PARAMS_HPP_ */
