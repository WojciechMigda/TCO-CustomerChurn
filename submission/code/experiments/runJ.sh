#!/bin/sh

# 1:3 s:20 C6k  MAE  limited history e32 no-seasonal
cd clasE && unbuffer ./run.sh 3 | tee run.log
cd -

