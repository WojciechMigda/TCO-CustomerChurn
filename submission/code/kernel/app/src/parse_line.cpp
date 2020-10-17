#include "boost/spirit/home/x3.hpp"

#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <cstddef>
#include <cmath>


#if 0
report_period_m_cd,md5_cust_party_key,province_cd,z_age,Gender_CD,z_census_household_1p_pct,z_census_education_high_pct,z_census_purchase_household,z_census_purchase_capita,z_census_household_cnt,prod_monodual_cd,multiplay_cnt,z_line_cnt,z_sim_cnt,fixed_prod_cat1_ind,tenure_fixed_month,tenure_mobile_month,z_line_voice_cat1_cnt,fixed_data_cat1_ind,fixed_data_cat2_ind,z_fixed_prod_cat2_cnt,z_fixed_prod_cat1_cnt,z_fixed_data_cat3_cnt,fixed_prod_cat3_cnt,device_smartphone_cnt,z_mobile_voice_cat1_cnt,z_mobile_data_cat1_cnt,mobile_data_cat2_cnt,z_mobile_voice_cat3_cnt,z_mobile_data_cat3_cnt,z_usg_fv_3m_avg,z_usg_fd_mb_1m_sum,z_usg_fd_mb_3m_avg,z_usg_mv_ib_a_3m_avg,z_usg_md_sms_ib_a_3m_avg,z_usg_md_ib_mb_3m_avg,payment_method_cash_cnt,customer_value_cd,z_rev_1m_sum,z_device_netcube_cnt,z_tariff_netcube_cnt,z_min_Prog_Max_BB_Down,z_line_Fib2h_CNT,z_min_Speed_Product_KBit,z_Max_Speed_Missing_KBit,z_Min_Speed_Reserve_KBit,z_Max_DSL_OOS_PCT,z_PR_Relocation_CNT,z_PR_Relocation_Days,z_PR_ActivationSupportOpt_CNT,z_PR_ActivationSupportOpt_Days,z_PR_DeactivationThreat_CNT,z_PR_DeactivationSupport_CNT,z_PR_DeactivationProdOpt_CNT,z_PR_DeactivationProdOpt_Days,z_PR_OtherWOTopic_CNT,z_PR_OtherWOTopic_Days,z_PR_AddressChange_CNT,z_PR_AddressChange_Days,z_PR_ServiceDisruption_CNT,z_PR_ServiceDisruption_Days,z_PR_BasketSupport_CNT,z_PR_BasketSupport_Days,z_PR_SellingSalesSupport_CNT,z_PR_SellingSalesSupport_Days,z_PR_DigitalUsage_CNT,z_PR_DigitalUsage_Days,z_TNPS_Last_Days,z_TNPS_Score_Avg,target_ind
201810,3E04B4AE041ADB76C059,D,1.4077,F,0.4236,0.4746,0.4081,-0.2102,-0.3446,F,2,-0.1555,-0.6735,0,213,0,-0.0658,0,1,0.8654,-0.1590,-0.2875,0,0.0000,-0.3024,-0.1550,0,-0.1979,-0.0628,-0.0550,-0.5597,-0.5818,-0.3814,-0.0880,-0.1015,0,MEDIUM,0.0148,-0.0912,-0.0799,0.4407,-0.1374,0.0320,-0.2854,0.3807,3.6245,-0.0981,-0.0973,-0.2350,-0.2652,-0.0429,-0.0738,-0.1980,-0.2040,-0.1146,-0.1216,-0.0909,-0.1009,-0.3854,-0.4208,-0.0926,-0.1012,-0.2405,-0.2600,-0.1672,0.9908,-0.3377,-0.3868,0

Full TRAIN shape: (6421184, 70)
            report_period_m_cd    int64                    19   201801   201907
            md5_cust_party_key   object                478152      ---      --- 660BAC09719FF5458119,EE80FCCE1BFF8F2F3A23,65A55D249940AB05E1B5,8DB5FF6937B6199AC289,93D946A4DD634ADA13C7,EB747946DF467107460B,30EBD3EA1765AA40FF38,32C912B9243F26FEC3F1,96BE6403850C91D11F5A,1BBFBBB20E0BB89C4CD2
                   province_cd   object NaN (2321)          9      ---      --- B,F,H,C,E,D,G,I,A
                         z_age  float64 NaN (76035)       111  -3.1244   4.1774
                     Gender_CD   object NaN (67982)         2      ---      --- M,F
     z_census_household_1p_pct  float64                  1327  -2.9141   2.5672
   z_census_education_high_pct  float64                   757  -1.4181   4.7594
   z_census_purchase_household  float64                  1707  -3.4114   7.5813
      z_census_purchase_capita  float64 NaN (15896)      1518  -1.5554   3.5881
        z_census_household_cnt  float64                   800  -0.5714   4.0065
              prod_monodual_cd   object                     2      ---      --- D,F
                 multiplay_cnt    int64                     5        1        5
                    z_line_cnt  float64 NaN (4358)          3  -0.1555    9.009
                     z_sim_cnt  float64 NaN (1196)         10  -0.6735   9.5165
           fixed_prod_cat1_ind    int64                     2        0        1
            tenure_fixed_month    int64                   424        0      426
           tenure_mobile_month    int64                   316        0      315
         z_line_voice_cat1_cnt  float64 NaN (29195)         1  -0.0658  -0.0658
           fixed_data_cat1_ind    int64                     2        0        1
           fixed_data_cat2_ind    int64                     2        0        1
         z_fixed_prod_cat2_cnt  float64 NaN (59)            6  -1.0954   8.7088
         z_fixed_prod_cat1_cnt  float64 NaN (612)           2   -0.159   6.2408
         z_fixed_data_cat3_cnt  float64 NaN (161)           3  -0.2875   7.1015
           fixed_prod_cat3_cnt    int64                     3        0        2
         device_smartphone_cnt  float64 NaN (278)          10      0.0      9.0
       z_mobile_voice_cat1_cnt  float64 NaN (726)           5  -0.3024   8.1186
        z_mobile_data_cat1_cnt  float64 NaN (3300)          3   -0.155    7.968
          mobile_data_cat2_cnt    int64                     5        0        4
       z_mobile_voice_cat3_cnt  float64 NaN (5487)          3  -0.1979   7.8533
        z_mobile_data_cat3_cnt  float64 NaN (32166)         1  -0.0628  -0.0628
               z_usg_fv_3m_avg  float64 NaN (5810)       2208   -0.301   9.9991
            z_usg_fd_mb_1m_sum  float64 NaN (4742)      78443  -0.5597   9.9999
            z_usg_fd_mb_3m_avg  float64 NaN (4738)      78931  -0.5818   9.9998
          z_usg_mv_ib_a_3m_avg  float64 NaN (9564)       2755  -0.3814   9.9965
      z_usg_md_sms_ib_a_3m_avg  float64 NaN (4386)        812   -0.088   9.9913
         z_usg_md_ib_mb_3m_avg  float64 NaN (13438)     50923  -0.1015   9.9991
       payment_method_cash_cnt    int64                    22        0      329
             customer_value_cd   object NaN (27)            5      ---      --- HIGHEST,HIGH,MEDIUM,LOW,NEW
                  z_rev_1m_sum  float64 NaN (11387)    105429  -9.9998    9.998
          z_device_netcube_cnt  float64 NaN (3326)          2  -0.0912   9.3162
          z_tariff_netcube_cnt  float64 NaN (5450)          2  -0.0799    6.383
        z_min_Prog_Max_BB_Down  float64                 23055  -0.5219   7.3425
              z_line_Fib2h_CNT  float64 NaN (546)           2  -0.1374   7.1899
      z_min_Speed_Product_KBit  float64 NaN (1499)         25  -0.9427   6.3676
      z_Max_Speed_Missing_KBit  float64 NaN (7392)      71894  -0.2854   9.9978
      z_Min_Speed_Reserve_KBit  float64                 21400  -0.3636   6.9381
             z_Max_DSL_OOS_PCT  float64                   309  -0.3743   3.6245
           z_PR_Relocation_CNT  float64 NaN (29301)         2  -0.0981   5.5339
          z_PR_Relocation_Days  float64 NaN (33591)       238  -0.0973   9.9589
 z_PR_ActivationSupportOpt_CNT  float64 NaN (8514)         10   -0.235   9.4548
z_PR_ActivationSupportOpt_Days  float64                   365  -0.2652   6.0011
   z_PR_DeactivationThreat_CNT  float64 NaN (18176)         1  -0.0429  -0.0429
  z_PR_DeactivationSupport_CNT  float64 NaN (52173)         1  -0.0738  -0.0738
  z_PR_DeactivationProdOpt_CNT  float64 NaN (11172)         5   -0.198   8.4468
 z_PR_DeactivationProdOpt_Days  float64                   365   -0.204   7.3956
         z_PR_OtherWOTopic_CNT  float64 NaN (10342)         3  -0.1146   8.5269
        z_PR_OtherWOTopic_Days  float64 NaN (35685)       290  -0.1216   9.9887
        z_PR_AddressChange_CNT  float64 NaN (17474)         3  -0.0909   8.0832
       z_PR_AddressChange_Days  float64 NaN (39522)       245  -0.1009   9.9798
    z_PR_ServiceDisruption_CNT  float64 NaN (5581)         10  -0.3854   9.0622
   z_PR_ServiceDisruption_Days  float64                   365  -0.4208    3.857
        z_PR_BasketSupport_CNT  float64 NaN (33015)         2  -0.0926   4.9671
       z_PR_BasketSupport_Days  float64 NaN (54837)       236  -0.1012   9.9706
  z_PR_SellingSalesSupport_CNT  float64 NaN (9029)         21  -0.2405     9.68
 z_PR_SellingSalesSupport_Days  float64                   365    -0.26    6.862
         z_PR_DigitalUsage_CNT  float64 NaN (14462)       737   -0.181   9.9904
        z_PR_DigitalUsage_Days  float64                   365  -0.5878   3.7003
              z_TNPS_Last_Days  float64                   365  -0.3377   4.8627
              z_TNPS_Score_Avg  float64                   475  -0.3868    2.843
                    target_ind    int64                     2        0        1

#endif


std::pair<bool, std::size_t> parse_line(
    std::vector<std::string> & cats,
    std::vector<float> & vals,
    std::string const & line
)
{
    namespace x3 = boost::spirit::x3;
    namespace ascii = boost::spirit::x3::ascii;
    using x3::lit;
    using x3::eps;
    using x3::float_;
    using x3::int_;
    using x3::char_;
    using x3::phrase_parse;
    using ascii::space;

    auto first = line.c_str();
    auto const last = line.c_str() + line.size();


    auto fsave = [&](auto & ctx){ vals.push_back(_attr(ctx)); };
    auto fsave_null = [&](auto & ctx){ vals.push_back(NAN); };

    auto ssave = [&](auto & ctx){ cats.push_back(_attr(ctx)); };
    auto ssave_null = [&](auto & ctx){ cats.push_back(std::string()); };


    auto const MISSING = lit("*******");

    auto const str = *(char_ - ',');

    /*
     *  eps[fsave_null] is to handle case of an empty entry, like in ',,'
     */
    auto const maybe_int = (MISSING[fsave_null] | int_[fsave] | eps[fsave_null]);
    auto const maybe_int_and = maybe_int >> ',';

    auto const maybe_str = (MISSING[ssave_null] | str[ssave]);
    auto const maybe_str_and = maybe_str >> ',';

    auto const maybe_float = (MISSING[fsave_null] | float_[fsave] | eps[fsave_null]);
    auto const maybe_float_and = maybe_float >> ',';

    bool rv = phrase_parse(
        first,
        last,
        //  Begin grammar
        (
               maybe_int_and            //            report_period_m_cd    int64
            >> str[ssave] >> ','        //            md5_cust_party_key   object
            >> maybe_str_and            //                   province_cd   object NaN
            >> maybe_float_and          //                         z_age  float64 NaN
            >> maybe_str_and            //                     Gender_CD   object NaN
            >> maybe_float_and          //     z_census_household_1p_pct  float64
            >> maybe_float_and          //   z_census_education_high_pct  float64
            >> maybe_float_and          //   z_census_purchase_household  float64
            >> maybe_float_and          //      z_census_purchase_capita  float64 NaN
            >> maybe_float_and          //        z_census_household_cnt  float64
            >> maybe_str_and            //              prod_monodual_cd   object
            >> maybe_int_and            //                 multiplay_cnt    int64
            >> maybe_float_and          //                    z_line_cnt  float64 NaN
            >> maybe_float_and          //                     z_sim_cnt  float64 NaN
            >> maybe_int_and            //           fixed_prod_cat1_ind    int64
            >> maybe_int_and            //            tenure_fixed_month    int64
            >> maybe_int_and            //           tenure_mobile_month    int64
            >> maybe_float_and          //         z_line_voice_cat1_cnt  float64 NaN
            >> maybe_int_and            //           fixed_data_cat1_ind    int64
            >> maybe_int_and            //           fixed_data_cat2_ind    int64
            >> maybe_float_and          //         z_fixed_prod_cat2_cnt  float64 NaN
            >> maybe_float_and          //         z_fixed_prod_cat1_cnt  float64 NaN
            >> maybe_float_and          //         z_fixed_data_cat3_cnt  float64 NaN
            >> maybe_int_and            //           fixed_prod_cat3_cnt    int64
            >> maybe_float_and          //         device_smartphone_cnt  float64 NaN
            >> maybe_float_and          //       z_mobile_voice_cat1_cnt  float64 NaN
            >> maybe_float_and          //        z_mobile_data_cat1_cnt  float64 NaN
            >> maybe_int_and            //          mobile_data_cat2_cnt    int64
            >> maybe_float_and          //       z_mobile_voice_cat3_cnt  float64 NaN
            >> maybe_float_and          //        z_mobile_data_cat3_cnt  float64 NaN
            >> maybe_float_and          //               z_usg_fv_3m_avg  float64 NaN
            >> maybe_float_and          //            z_usg_fd_mb_1m_sum  float64 NaN
            >> maybe_float_and          //            z_usg_fd_mb_3m_avg  float64 NaN
            >> maybe_float_and          //          z_usg_mv_ib_a_3m_avg  float64 NaN
            >> maybe_float_and          //      z_usg_md_sms_ib_a_3m_avg  float64 NaN
            >> maybe_float_and          //         z_usg_md_ib_mb_3m_avg  float64 NaN
            >> maybe_int_and            //       payment_method_cash_cnt    int64
            >> maybe_str_and            //             customer_value_cd   object NaN
            >> maybe_float_and          //                  z_rev_1m_sum  float64 NaN
            >> maybe_float_and          //          z_device_netcube_cnt  float64 NaN
            >> maybe_float_and          //          z_tariff_netcube_cnt  float64 NaN
            >> maybe_float_and          //        z_min_Prog_Max_BB_Down  float64
            >> maybe_float_and          //              z_line_Fib2h_CNT  float64 NaN
            >> maybe_float_and          //      z_min_Speed_Product_KBit  float64 NaN
            >> maybe_float_and          //      z_Max_Speed_Missing_KBit  float64 NaN
            >> maybe_float_and          //      z_Min_Speed_Reserve_KBit  float64
            >> maybe_float_and          //             z_Max_DSL_OOS_PCT  float64
            >> maybe_float_and          //           z_PR_Relocation_CNT  float64 NaN
            >> maybe_float_and          //          z_PR_Relocation_Days  float64 NaN
            >> maybe_float_and          // z_PR_ActivationSupportOpt_CNT  float64 NaN
            >> maybe_float_and          //z_PR_ActivationSupportOpt_Days  float64
            >> maybe_float_and          //   z_PR_DeactivationThreat_CNT  float64 NaN
            >> maybe_float_and          //  z_PR_DeactivationSupport_CNT  float64 NaN
            >> maybe_float_and          //  z_PR_DeactivationProdOpt_CNT  float64 NaN
            >> maybe_float_and          // z_PR_DeactivationProdOpt_Days  float64
            >> maybe_float_and          //         z_PR_OtherWOTopic_CNT  float64 NaN
            >> maybe_float_and          //        z_PR_OtherWOTopic_Days  float64 NaN
            >> maybe_float_and          //        z_PR_AddressChange_CNT  float64 NaN
            >> maybe_float_and          //       z_PR_AddressChange_Days  float64 NaN
            >> maybe_float_and          //    z_PR_ServiceDisruption_CNT  float64 NaN
            >> maybe_float_and          //   z_PR_ServiceDisruption_Days  float64
            >> maybe_float_and          //        z_PR_BasketSupport_CNT  float64 NaN
            >> maybe_float_and          //       z_PR_BasketSupport_Days  float64 NaN
            >> maybe_float_and          //  z_PR_SellingSalesSupport_CNT  float64 NaN
            >> maybe_float_and          // z_PR_SellingSalesSupport_Days  float64
            >> maybe_float_and          //         z_PR_DigitalUsage_CNT  float64 NaN
            >> maybe_float_and          //        z_PR_DigitalUsage_Days  float64
            >> maybe_float_and          //              z_TNPS_Last_Days  float64
            >> maybe_float              //              z_TNPS_Score_Avg  float64

            // optional
            >> -(',' >> int_[fsave])    //                    target_ind    int64
        )
        ,
        //  End grammar

        space);

    return {rv, std::distance(line.c_str(), first)};
}
