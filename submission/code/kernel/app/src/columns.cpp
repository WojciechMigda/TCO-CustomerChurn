#include "columns.hpp"

#include <optional>
#include <unordered_map>
#include <string>


#define X(val) {#val, Cat::val}
std::unordered_map<std::string, enum Cat> const Cat_to_string_map  =
{
    __LIST_OF_CAT_ENUMS
};
#undef X


#define X(val) {#val, Num::val}
std::unordered_map<std::string, enum Num> const Num_to_string_map  =
{
    __LIST_OF_NUM_ENUMS
};
#undef X


std::optional<enum Cat> Cat_from_string(std::string const & str)
{
    if (Cat_to_string_map.count(str) != 0)
    {
        return Cat_to_string_map.at(str);
    }
    else
    {
        return {};
    }
}


std::optional<enum Num> Num_from_string(std::string const & str)
{
    if (Num_to_string_map.count(str) != 0)
    {
        return Num_to_string_map.at(str);
    }
    else
    {
        return {};
    }
}
