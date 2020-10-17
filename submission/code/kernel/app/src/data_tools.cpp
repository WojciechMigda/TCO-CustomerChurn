#include "columns.hpp"

#include "tsetlini/tsetlini_types.hpp"
#include "json/json.hpp"

#include <vector>
#include <string>
#include <utility>


std::vector<std::string> extract_cust_id(std::vector<std::vector<std::string>> & cat_rows)
{
    std::vector<std::string> rv;

    rv.reserve(cat_rows.size());

    for (auto & row : cat_rows)
    {
        auto id = std::move(row[Cat::md5_cust_party_key]);
        rv.push_back(id);
    }

    return rv;
}


std::vector<int> extract_target(std::vector<std::vector<float>> & num_rows)
{
    std::vector<int> rv;

    rv.reserve(num_rows.size());

    for (auto & row : num_rows)
    {
        auto target = std::move(row[Num::target_ind]);
        rv.push_back(target);
    }

    return rv;
}


std::vector<Tsetlini::bit_matrix_uint64> encode_features(
    std::vector<std::vector<std::string>> & cat_rows,
    std::vector<std::vector<float>> & num_rows,
    nlohmann::json const & encoding
)
{
    std::vector<Tsetlini::bit_matrix_uint64> bm;

    return bm;
}
