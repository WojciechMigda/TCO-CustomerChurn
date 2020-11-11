#!/bin/sh

# 1:3 s:20  MAE
cd regr22 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:32  MAE
cd regr23 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:4 s:20  MAE
cd regr24 && unbuffer ./run.sh 4 | tee run.log
cd -
