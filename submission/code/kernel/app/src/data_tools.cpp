#include "columns.hpp"

#include "tsetlini/tsetlini_types.hpp"
#include "json/json.hpp"
#include "spdlog/spdlog.h"

#include <vector>
#include <string>
#include <utility>
#include <array>


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


unsigned int bin_ordinal(float x, std::vector<float> const & bin_edges)
{
    // TODO
    return 0;
}


unsigned int total_kbd_bits(nlohmann::json const & encoding)
{
    /*
     * Example
     * =======
     *
     * bin_edges_ = array([-2.3061, -1.4878, -1.1731, -0.8583, -0.5436, -0.2289, -0.04  ,
     *   0.2118,  0.4635,  0.7783,  1.156 ,  2.9814])
     *
     * len(bin_edges_) = 12
     *
     * n_bins_ = 11
     *
     * min/max = 0 / 10
     *
     * So, for a bin_edges of size N it corresponds to N-1 bins, and yields
     * ordinals between 0 and N-2.
     *
     * Encoding values between 0 and N-2 requires N-2 bits, but with NaN it
     * becomes N-1:
     *   0 -> 0000
     *   1 -> 1000
     *   2 -> 1100
     *   3 -> 1110
     * NaN -> 0001
     */
    unsigned int rv = 0;

    for (auto const it : encoding.items())
    {
        if (not it.value().is_null())
        {
            // Add 1 for a NaN column
            rv += it.value().size() - 2 + 1;
        }
    }

    return rv;
}


std::array<std::string, 9> const cat_province = {"G", "D", "E", "B", "H", "A", "C", "F", "I"};
std::array<std::string, 2> const cat_gender = {"M", "F"};
std::array<std::string, 2> const cat_prod_monodual = {"F", "D"};
std::array<std::string, 5> const cat_customer_value = {"HIGHEST", "HIGH", "MEDIUM", "NEW", "LOW"};


template<std::size_t N>
unsigned int encode_cat(
    unsigned int pos,
    std::array<std::string, N> desc,
    std::string const & val,
    Tsetlini::bit_vector_uint64 & bv)
{
    // One-hot encoding + NaN bit (why NaN bit is the last see below)
    //
    // N = 5
    //
    // 0 1 2 3 4 5
    // x x x x x NaN

    if (val.empty())
    {
        bv.set(pos + N);
    }
    else
    {
        auto const cat_idx = std::distance(desc.cbegin(), std::find(desc.cbegin(), desc.cend(), val));

        // with unknown category std::find will return cend(), which through
        // std::distance will yield cat_idx equal to position of NaN bit.
        // Convenient, huh?
        bv.set(pos + cat_idx);
    }

    return N + 1;
}


std::vector<Tsetlini::bit_vector_uint64> encode_features(
    std::vector<std::vector<std::string>> & cat_rows,
    std::vector<std::vector<float>> & num_rows,
    nlohmann::json const & encoding
)
{
    auto const F_SEASONAL_SZ = 12u;

    unsigned int const NROWS = cat_rows.size();
    unsigned int const NCOLS =
        total_kbd_bits(encoding) +
        F_SEASONAL_SZ +
        (cat_province.size() + 1) +
        (cat_gender.size() + 1) +
        (cat_prod_monodual.size() + 1) +
        (cat_customer_value.size() + 1);

    std::vector<Tsetlini::bit_vector_uint64> df;
    df.reserve(NROWS);


    for (auto rix = 0u; rix < NROWS; ++rix)
    {
        unsigned int cpos = 0u;

        auto const & cat_row = cat_rows[rix];
        auto const & num_row = num_rows[rix];

        Tsetlini::bit_vector_uint64 bv(NCOLS);

        // encoding starts here
        cpos += encode_cat(cpos, cat_province, cat_row[Cat::province_cd], bv);
        cpos += encode_cat(cpos, cat_gender, cat_row[Cat::Gender_CD], bv);
        cpos += encode_cat(cpos, cat_prod_monodual, cat_row[Cat::prod_monodual_cd], bv);
        cpos += encode_cat(cpos, cat_customer_value, cat_row[Cat::customer_value_cd], bv);

        (void)num_row;

        df.push_back(std::move(bv));

        // release memory
        cat_rows[rix].clear();
        num_rows[rix].clear();
    }

    return df;
}
