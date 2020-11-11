#!/bin/sh

# 1:3 s:20 C8k  MAE  limited history e32 no-seasonal
cd clasF && unbuffer ./run.sh 3 | tee run.log
cd -

