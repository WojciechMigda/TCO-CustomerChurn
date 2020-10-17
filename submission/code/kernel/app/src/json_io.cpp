#include "json/json.hpp"

#include <string>
#include <fstream>

nlohmann::json read_json(std::string const & ifname)
{
    std::ifstream ifile(ifname);

    return nlohmann::json::parse(ifile);
}
