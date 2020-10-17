#include "parse_line.hpp"

#include "spdlog/spdlog.h"

#include <string>
#include <vector>
#include <utility>
#include <fstream>


std::pair<
    std::vector<std::vector<std::string>>,
    std::vector<std::vector<float>>>
read_csv(std::string const & ifname)
{
    std::ifstream fcsv(ifname);

    std::string line;

    std::vector<std::vector<std::string>> cat_rows;
    std::vector<std::vector<float>> num_rows;

    if (std::getline(fcsv, line)) // header
    {
        while (std::getline(fcsv, line))
        {
            std::vector<std::string> cats;
            std::vector<float> nums;

            // reserve empirically determined number of elements
            cats.reserve(5);
            nums.reserve(65);

            auto const [ok, pos] = parse_line(cats, nums, line);

            if (not ok)
            {
                spdlog::error("CSV: Parsing failed for line {} at position {}", line, pos);
                break;
            }

            cat_rows.push_back(cats);
            num_rows.push_back(nums);
//            spdlog::info("CSV: Read {} features ({} categorical and {} numerical)",
//                cats.size() + nums.size(), cats.size(), nums.size());
        }
    }
    else
    {
        spdlog::error("Missing header line in read CSV file {}", ifname);
    }

    return {cat_rows, num_rows};
}
