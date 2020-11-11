#!/bin/sh

# C=6000, T=16000, MAE
cd regr19 && unbuffer ./run.sh | tee run.log
cd -

# clf 1:3 s=12
cd clas4 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:12 C=6000, T=16000, MAE
cd regr20 && unbuffer ./run.sh 3 | tee run.log
cd -
