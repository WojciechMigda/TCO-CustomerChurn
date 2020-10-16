#include "parse_line.hpp"

#include <string>
#include <vector>
#include <utility>
#include <fstream>


std::pair<std::vector<std::string>, std::vector<float>> read_csv(std::string const & ifname, bool const for_inference)
{
    std::vector<std::string> cats;
    std::vector<float> vals;

    std::ifstream fcsv(ifname);

    std::string line;

    if (std::getline(fcsv, line)) // header
    {
        while (std::getline(fcsv, line))
        {
            auto ok = parse_line(for_inference, cats, vals, line);

            if (not ok)
            {
                break;
            }
        }
    }

    fcsv.close();

    return {cats, vals};
}
