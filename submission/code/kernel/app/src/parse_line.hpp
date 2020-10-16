#pragma once

#ifndef APP_SRC_PARSE_LINE_HPP_
#define APP_SRC_PARSE_LINE_HPP_

#include <string>
#include <vector>


bool parse_line(
    bool const for_inference,
    std::vector<std::string> & cats,
    std::vector<float> & vals,
    std::string const & line
);


#endif /* APP_SRC_PARSE_LINE_HPP_ */
