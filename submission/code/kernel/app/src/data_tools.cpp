#include "columns.hpp"

#include "tsetlini/tsetlini_types.hpp"
#include "json/json.hpp"
#include "spdlog/spdlog.h"

#include <vector>
#include <string>
#include <utility>
#include <array>
#include <cmath>


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


template<typename Iterator>
unsigned int digitize(float const v, Iterator first, Iterator last)
{
    // from
    //  https://github.com/numpy/numpy/blob/v1.19.0/numpy/lib/function_base.py#L4678-L4786
    //  https://github.com/numpy/numpy/blob/v1.19.0/numpy/core/fromnumeric.py#L1276-L1343

    /*
     * numpy.searchsorted:
     * ===================
     * side     returned index i satisfies
     * ----     --------------------------
     * left     a[i-1] < v <= a[i]
     * right    a[i-1] <= v < a[i]
     *
      *================
     * KBinsDiscretizer calls np.digitize(Xt[:, jj] + eps, bin_edges[jj][1:]) with default `right=False`
     *
     * This leads to a call to searchsorted with `side=right` (https://github.com/numpy/numpy/blob/v1.19.0/numpy/lib/function_base.py#L4781)
     */

    auto const it = std::find_if(first, last, [v](float a){ return v < a;});

    auto rv = std::distance(first, it);

    return rv;
}


unsigned int bin_ordinal(float const x, std::vector<float> const & bin_edges)
{
    /*
     * From sklearn github:
     *
     * # Values which are close to a bin edge are susceptible to numeric
     * # instability. Add eps to X so these values are binned correctly
     * # with respect to their decimal truncation. See documentation of
     * # numpy.isclose for an explanation of ``rtol`` and ``atol``.
     */
    static auto constexpr rtol = 1.e-5;
    static auto constexpr atol = 1.e-8;

    auto const eps = atol + rtol * std::abs(x);

    auto rv = digitize(x + eps, std::next(bin_edges.cbegin()), bin_edges.cend());

    return std::clamp<unsigned int>(rv, 0, bin_edges.size() - 2);
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
     * min <--> max = 0 <--> 10
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


unsigned int encode_num(
    unsigned int const pos,
    std::string const & name,
    nlohmann::json const & desc,
    std::vector<float> const & num_rows,
    Tsetlini::bit_vector_uint64 & bv)
{
    unsigned int rv = 0;

    if (not desc.is_null())
    {
        rv = desc.size() - 1;

        auto const maybe_enum = Num_from_string(name);

        if (maybe_enum.has_value())
        {
            auto const feature_idx = maybe_enum.value();
            auto const val = num_rows[feature_idx];

            if (std::isnan(val))
            {
                // set the NaN bit
                bv.set(rv);
            }
            else
            {
                auto const to_set = bin_ordinal(val, desc);

                for (auto it = 0u; it < to_set; ++it)
                {
                    bv.set(pos + it);
                }
            }
        }
        else
        {
            spdlog::warn("Encoding specification has unknown numerical feature {}", name);
        }
    }

    return rv;
}


unsigned int encode_month(
    unsigned int const pos,
    float const f_report_period,
    Tsetlini::bit_vector_uint64 & bv)
{
    unsigned int report_period = std::round(f_report_period);
    unsigned int month = report_period % 13;

    bv.set(pos + month - 1);

    return 12;
}


unsigned int encode_201906(
    unsigned int const pos,
    float const f_report_period,
    Tsetlini::bit_vector_uint64 & bv)
{
    unsigned int const report_period = std::round(f_report_period);
    bool const flag = report_period >= 201906;

    bv.assign(pos, flag);

    return 1;
}


std::vector<Tsetlini::bit_vector_uint64> encode_features(
    std::vector<std::vector<std::string>> & cat_rows,
    std::vector<std::vector<float>> & num_rows,
    nlohmann::json const & encoding,
    bool const f201906
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
        (cat_customer_value.size() + 1) +
        (f201906 == true);

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

        for (auto const it : encoding.items())
        {
            cpos += encode_num(cpos, it.key(), it.value(), num_row, bv);
        }

        cpos += encode_month(cpos, num_row[Num::report_period_m_cd], bv);

        if (true == f201906)
        {
            cpos += encode_201906(cpos, num_row[Num::report_period_m_cd], bv);
        }

        // encoding ends here

        if (cpos != NCOLS)
        {
            spdlog::warn("Encoding resulted in mismatch between number of encoded bits {} and bit vector size {}", cpos, bv.size());
        }

        df.push_back(std::move(bv));

        // release memory
        cat_rows[rix].clear();
        num_rows[rix].clear();
    }

    return df;
}
