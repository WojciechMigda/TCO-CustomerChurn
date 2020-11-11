#!/bin/sh

# 1:3 s:20 C16k  MAE  limited history e32 no-seasonal
cd clasG && unbuffer ./run.sh 3 | tee run.log
cd -

