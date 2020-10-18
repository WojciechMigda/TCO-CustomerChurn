#pragma once

#ifndef APP_SRC_COLUMNS_HPP_
#define APP_SRC_COLUMNS_HPP_

#include <optional>


#define __LIST_OF_CAT_ENUMS \
    X(md5_cust_party_key), \
           X(province_cd), \
             X(Gender_CD), \
      X(prod_monodual_cd), \
     X(customer_value_cd)


#define X(val) val
enum Cat
{
    __LIST_OF_CAT_ENUMS
};
#undef X


#define __LIST_OF_NUM_ENUMS \
            X(report_period_m_cd), \
                         X(z_age), \
     X(z_census_household_1p_pct), \
   X(z_census_education_high_pct), \
   X(z_census_purchase_household), \
      X(z_census_purchase_capita), \
        X(z_census_household_cnt), \
                 X(multiplay_cnt), \
                    X(z_line_cnt), \
                     X(z_sim_cnt), \
           X(fixed_prod_cat1_ind), \
            X(tenure_fixed_month), \
           X(tenure_mobile_month), \
         X(z_line_voice_cat1_cnt), \
           X(fixed_data_cat1_ind), \
           X(fixed_data_cat2_ind), \
         X(z_fixed_prod_cat2_cnt), \
         X(z_fixed_prod_cat1_cnt), \
         X(z_fixed_data_cat3_cnt), \
           X(fixed_prod_cat3_cnt), \
         X(device_smartphone_cnt), \
       X(z_mobile_voice_cat1_cnt), \
        X(z_mobile_data_cat1_cnt), \
          X(mobile_data_cat2_cnt), \
       X(z_mobile_voice_cat3_cnt), \
        X(z_mobile_data_cat3_cnt), \
               X(z_usg_fv_3m_avg), \
            X(z_usg_fd_mb_1m_sum), \
            X(z_usg_fd_mb_3m_avg), \
          X(z_usg_mv_ib_a_3m_avg), \
      X(z_usg_md_sms_ib_a_3m_avg), \
         X(z_usg_md_ib_mb_3m_avg), \
       X(payment_method_cash_cnt), \
                  X(z_rev_1m_sum), \
          X(z_device_netcube_cnt), \
          X(z_tariff_netcube_cnt), \
        X(z_min_Prog_Max_BB_Down), \
              X(z_line_Fib2h_CNT), \
      X(z_min_Speed_Product_KBit), \
      X(z_Max_Speed_Missing_KBit), \
      X(z_Min_Speed_Reserve_KBit), \
             X(z_Max_DSL_OOS_PCT), \
           X(z_PR_Relocation_CNT), \
          X(z_PR_Relocation_Days), \
 X(z_PR_ActivationSupportOpt_CNT), \
X(z_PR_ActivationSupportOpt_Days), \
   X(z_PR_DeactivationThreat_CNT), \
  X(z_PR_DeactivationSupport_CNT), \
  X(z_PR_DeactivationProdOpt_CNT), \
 X(z_PR_DeactivationProdOpt_Days), \
         X(z_PR_OtherWOTopic_CNT), \
        X(z_PR_OtherWOTopic_Days), \
        X(z_PR_AddressChange_CNT), \
       X(z_PR_AddressChange_Days), \
    X(z_PR_ServiceDisruption_CNT), \
   X(z_PR_ServiceDisruption_Days), \
        X(z_PR_BasketSupport_CNT), \
       X(z_PR_BasketSupport_Days), \
  X(z_PR_SellingSalesSupport_CNT), \
 X(z_PR_SellingSalesSupport_Days), \
         X(z_PR_DigitalUsage_CNT), \
        X(z_PR_DigitalUsage_Days), \
              X(z_TNPS_Last_Days), \
              X(z_TNPS_Score_Avg), \
                    X(target_ind)

#define X(val) val
enum Num
{
    __LIST_OF_NUM_ENUMS
};
#undef X


std::optional<enum Cat> Cat_from_string(std::string const & str);
std::optional<enum Num> Num_from_string(std::string const & str);


#endif /* APP_SRC_COLUMNS_HPP_ */
