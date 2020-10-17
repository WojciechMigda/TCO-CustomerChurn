#pragma once

#ifndef APP_SRC_COLUMNS_HPP_
#define APP_SRC_COLUMNS_HPP_


enum class Cat
{
    md5_cust_party_key,
           province_cd,
             Gender_CD,
      prod_monodual_cd,
     customer_value_cd
};

enum class Num
{
            report_period_m_cd,
                         z_age,
     z_census_household_1p_pct,
   z_census_education_high_pct,
   z_census_purchase_household,
      z_census_purchase_capita,
        z_census_household_cnt,
                 multiplay_cnt,
                    z_line_cnt,
                     z_sim_cnt,
           fixed_prod_cat1_ind,
            tenure_fixed_month,
           tenure_mobile_month,
         z_line_voice_cat1_cnt,
           fixed_data_cat1_ind,
           fixed_data_cat2_ind,
         z_fixed_prod_cat2_cnt,
         z_fixed_prod_cat1_cnt,
         z_fixed_data_cat3_cnt,
           fixed_prod_cat3_cnt,
         device_smartphone_cnt,
       z_mobile_voice_cat1_cnt,
        z_mobile_data_cat1_cnt,
          mobile_data_cat2_cnt,
       z_mobile_voice_cat3_cnt,
        z_mobile_data_cat3_cnt,
               z_usg_fv_3m_avg,
            z_usg_fd_mb_1m_sum,
            z_usg_fd_mb_3m_avg,
          z_usg_mv_ib_a_3m_avg,
      z_usg_md_sms_ib_a_3m_avg,
         z_usg_md_ib_mb_3m_avg,
       payment_method_cash_cnt,
                  z_rev_1m_sum,
          z_device_netcube_cnt,
          z_tariff_netcube_cnt,
        z_min_Prog_Max_BB_Down,
              z_line_Fib2h_CNT,
      z_min_Speed_Product_KBit,
      z_Max_Speed_Missing_KBit,
      z_Min_Speed_Reserve_KBit,
             z_Max_DSL_OOS_PCT,
           z_PR_Relocation_CNT,
          z_PR_Relocation_Days,
 z_PR_ActivationSupportOpt_CNT,
z_PR_ActivationSupportOpt_Days,
   z_PR_DeactivationThreat_CNT,
  z_PR_DeactivationSupport_CNT,
  z_PR_DeactivationProdOpt_CNT,
 z_PR_DeactivationProdOpt_Days,
         z_PR_OtherWOTopic_CNT,
        z_PR_OtherWOTopic_Days,
        z_PR_AddressChange_CNT,
       z_PR_AddressChange_Days,
    z_PR_ServiceDisruption_CNT,
   z_PR_ServiceDisruption_Days,
        z_PR_BasketSupport_CNT,
       z_PR_BasketSupport_Days,
  z_PR_SellingSalesSupport_CNT,
 z_PR_SellingSalesSupport_Days,
         z_PR_DigitalUsage_CNT,
        z_PR_DigitalUsage_Days,
              z_TNPS_Last_Days,
              z_TNPS_Score_Avg,
                    target_ind
};


#endif /* APP_SRC_COLUMNS_HPP_ */
