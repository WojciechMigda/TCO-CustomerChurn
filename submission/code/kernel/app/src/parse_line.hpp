#pragma once

#ifndef APP_SRC_PARSE_LINE_HPP_
#define APP_SRC_PARSE_LINE_HPP_

#include <string>
#include <vector>
#include <utility>
#include <cstddef>


std::pair<bool, std::size_t> parse_line(
    std::vector<std::string> & cats,
    std::vector<float> & vals,
    std::string const & line
);


#endif /* APP_SRC_PARSE_LINE_HPP_ */
