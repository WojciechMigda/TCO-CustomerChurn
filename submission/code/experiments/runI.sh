#!/bin/sh

# 1:3 s:20 C16k  MAE  limited history e20 no-seasonal
cd regr33 && unbuffer ./run.sh 3 | tee run.log
cd -
