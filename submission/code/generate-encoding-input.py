#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Creates default encoding input descriptor and saves it into encoding-in.json

The output is a json dictionary, with each ordinal column being paired with specified bin size,
e.g.
{'z_age': 10, 'z_census_household_1p_pct': 10, ...and so on}


This is the first script to be run. With encoding-in.json present, either generated or hand-modified,
the next step is to create proper encoding data, which specifies actual bin sizes and bin definitions.

"""

import plac
import json


"""
            report_period_m_cd    int64           19   201801   201907 
            md5_cust_party_key   object       478152      ---      --- 4EA2C1D617DDBC0C9382,A7C64347F331C9A0D2A6,9FBB78546D12A1D3696D,D9D13703C1D7FD0440C5,55330BB52BEE462CA3C5,84D5E3930A0FF428928A,7490E63D90F90CCDF9F2,7FF85D111C27FC11E890,5CDE645B286C9CE6A5A7,3C343BECC3195B7FCB95
                   province_cd   object NaN        9      ---      --- G,D,E,B,H,A,C,F,I
                     Gender_CD   object NaN        2      ---      --- F,M
              prod_monodual_cd   object            2      ---      --- F,D
             customer_value_cd   object NaN        5      ---      --- HIGHEST,HIGH,MEDIUM,NEW,LOW

                    target_ind    int64            2        0        1 

Full TRAIN shape: (6421184, 70)
                         z_age  float64 NaN      111  -3.1244   4.1774 
     z_census_household_1p_pct  float64         1327  -2.9141   2.5672 
   z_census_education_high_pct  float64          757  -1.4181   4.7594 
   z_census_purchase_household  float64         1707  -3.4114   7.5813 
      z_census_purchase_capita  float64 NaN     1518  -1.5554   3.5881 
        z_census_household_cnt  float64          800  -0.5714   4.0065 
                 multiplay_cnt    int64            5        1        5 
                    z_line_cnt  float64 NaN        3  -0.1555    9.009 
                     z_sim_cnt  float64 NaN       10  -0.6735   9.5165 
           fixed_prod_cat1_ind    int64            2        0        1 
            tenure_fixed_month    int64          424        0      426 
           tenure_mobile_month    int64          316        0      315 
         z_line_voice_cat1_cnt  float64 NaN        1  -0.0658  -0.0658 
           fixed_data_cat1_ind    int64            2        0        1 
           fixed_data_cat2_ind    int64            2        0        1 
         z_fixed_prod_cat2_cnt  float64 NaN        6  -1.0954   8.7088 
         z_fixed_prod_cat1_cnt  float64 NaN        2   -0.159   6.2408 
         z_fixed_data_cat3_cnt  float64 NaN        3  -0.2875   7.1015 
           fixed_prod_cat3_cnt    int64            3        0        2 
         device_smartphone_cnt  float64 NaN       10      0.0      9.0 
       z_mobile_voice_cat1_cnt  float64 NaN        5  -0.3024   8.1186 
        z_mobile_data_cat1_cnt  float64 NaN        3   -0.155    7.968 
          mobile_data_cat2_cnt    int64            5        0        4 
       z_mobile_voice_cat3_cnt  float64 NaN        3  -0.1979   7.8533 
        z_mobile_data_cat3_cnt  float64 NaN        1  -0.0628  -0.0628 
               z_usg_fv_3m_avg  float64 NaN     2208   -0.301   9.9991 
            z_usg_fd_mb_1m_sum  float64 NaN    78443  -0.5597   9.9999 
            z_usg_fd_mb_3m_avg  float64 NaN    78931  -0.5818   9.9998 
          z_usg_mv_ib_a_3m_avg  float64 NaN     2755  -0.3814   9.9965 
      z_usg_md_sms_ib_a_3m_avg  float64 NaN      812   -0.088   9.9913 
         z_usg_md_ib_mb_3m_avg  float64 NaN    50923  -0.1015   9.9991 
       payment_method_cash_cnt    int64           22        0      329 
                  z_rev_1m_sum  float64 NaN   105429  -9.9998    9.998 
          z_device_netcube_cnt  float64 NaN        2  -0.0912   9.3162 
          z_tariff_netcube_cnt  float64 NaN        2  -0.0799    6.383 
        z_min_Prog_Max_BB_Down  float64        23055  -0.5219   7.3425 
              z_line_Fib2h_CNT  float64 NaN        2  -0.1374   7.1899 
      z_min_Speed_Product_KBit  float64 NaN       25  -0.9427   6.3676 
      z_Max_Speed_Missing_KBit  float64 NaN    71894  -0.2854   9.9978 
      z_Min_Speed_Reserve_KBit  float64        21400  -0.3636   6.9381 
             z_Max_DSL_OOS_PCT  float64          309  -0.3743   3.6245 
           z_PR_Relocation_CNT  float64 NaN        2  -0.0981   5.5339 
          z_PR_Relocation_Days  float64 NaN      238  -0.0973   9.9589 
 z_PR_ActivationSupportOpt_CNT  float64 NaN       10   -0.235   9.4548 
z_PR_ActivationSupportOpt_Days  float64          365  -0.2652   6.0011 
   z_PR_DeactivationThreat_CNT  float64 NaN        1  -0.0429  -0.0429 
  z_PR_DeactivationSupport_CNT  float64 NaN        1  -0.0738  -0.0738 
  z_PR_DeactivationProdOpt_CNT  float64 NaN        5   -0.198   8.4468 
 z_PR_DeactivationProdOpt_Days  float64          365   -0.204   7.3956 
         z_PR_OtherWOTopic_CNT  float64 NaN        3  -0.1146   8.5269 
        z_PR_OtherWOTopic_Days  float64 NaN      290  -0.1216   9.9887 
        z_PR_AddressChange_CNT  float64 NaN        3  -0.0909   8.0832 
       z_PR_AddressChange_Days  float64 NaN      245  -0.1009   9.9798 
    z_PR_ServiceDisruption_CNT  float64 NaN       10  -0.3854   9.0622 
   z_PR_ServiceDisruption_Days  float64          365  -0.4208    3.857 
        z_PR_BasketSupport_CNT  float64 NaN        2  -0.0926   4.9671 
       z_PR_BasketSupport_Days  float64 NaN      236  -0.1012   9.9706 
  z_PR_SellingSalesSupport_CNT  float64 NaN       21  -0.2405     9.68 
 z_PR_SellingSalesSupport_Days  float64          365    -0.26    6.862 
         z_PR_DigitalUsage_CNT  float64 NaN      737   -0.181   9.9904 
        z_PR_DigitalUsage_Days  float64          365  -0.5878   3.7003 
              z_TNPS_Last_Days  float64          365  -0.3377   4.8627 
              z_TNPS_Score_Avg  float64          475  -0.3868    2.843 


"""


def main(bin_size : ('Bin size in bits', 'option', "W", int)=10):
    print(locals())

    ordinal_columns = """
                         z_age
     z_census_household_1p_pct
   z_census_education_high_pct
   z_census_purchase_household
      z_census_purchase_capita
        z_census_household_cnt
                 multiplay_cnt
                    z_line_cnt
                     z_sim_cnt
           fixed_prod_cat1_ind
            tenure_fixed_month
           tenure_mobile_month
         z_line_voice_cat1_cnt
           fixed_data_cat1_ind
           fixed_data_cat2_ind
         z_fixed_prod_cat2_cnt
         z_fixed_prod_cat1_cnt
         z_fixed_data_cat3_cnt
           fixed_prod_cat3_cnt
         device_smartphone_cnt
       z_mobile_voice_cat1_cnt
        z_mobile_data_cat1_cnt
          mobile_data_cat2_cnt
       z_mobile_voice_cat3_cnt
        z_mobile_data_cat3_cnt
               z_usg_fv_3m_avg
            z_usg_fd_mb_1m_sum
            z_usg_fd_mb_3m_avg
          z_usg_mv_ib_a_3m_avg
      z_usg_md_sms_ib_a_3m_avg
         z_usg_md_ib_mb_3m_avg
       payment_method_cash_cnt
                  z_rev_1m_sum
          z_device_netcube_cnt
          z_tariff_netcube_cnt
        z_min_Prog_Max_BB_Down
              z_line_Fib2h_CNT
      z_min_Speed_Product_KBit
      z_Max_Speed_Missing_KBit
      z_Min_Speed_Reserve_KBit
             z_Max_DSL_OOS_PCT
           z_PR_Relocation_CNT
          z_PR_Relocation_Days
 z_PR_ActivationSupportOpt_CNT
z_PR_ActivationSupportOpt_Days
   z_PR_DeactivationThreat_CNT
  z_PR_DeactivationSupport_CNT
  z_PR_DeactivationProdOpt_CNT
 z_PR_DeactivationProdOpt_Days
         z_PR_OtherWOTopic_CNT
        z_PR_OtherWOTopic_Days
        z_PR_AddressChange_CNT
       z_PR_AddressChange_Days
    z_PR_ServiceDisruption_CNT
   z_PR_ServiceDisruption_Days
        z_PR_BasketSupport_CNT
       z_PR_BasketSupport_Days
  z_PR_SellingSalesSupport_CNT
 z_PR_SellingSalesSupport_Days
         z_PR_DigitalUsage_CNT
        z_PR_DigitalUsage_Days
              z_TNPS_Last_Days
              z_TNPS_Score_Avg
""".split()

    dictionary = dict((col, bin_size) for col in ordinal_columns)
    #print(dictionary)

    with open('encoding-in.json', "w", encoding="utf8") as ofile:
        json.dump(dictionary, ofile, indent=2)

    pass


if __name__ == "__main__":
    plac.call(main)
