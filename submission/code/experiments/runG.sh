#!/bin/sh

# 1:3 s:20  MAE  limited history e20 no-seasonal
cd regr31 && unbuffer ./run.sh 3 | tee run.log
cd -
