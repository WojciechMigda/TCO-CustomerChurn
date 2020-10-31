#!/bin/bash

# takes history.csv and extracts each month's data into separate input_YYYYMM.csv / ground_truth_YYYYMM.json pair


#for ym in 201801 201802 201803 201804 201805 201806 201807 201808 201809 201810 201811 201812 201901 201902 201903 201904 201905 201906 201907; do

for ym in 201801 201802 201803 201804 201805 201806 201807 201808 201809 201810 201811 201812 201901 201902 201903 201904 201905 201906; do

  echo $ym
  ../submission/code/extract_gt.py $ym history.csv input_$ym.csv ground_truth_$ym.json

done
