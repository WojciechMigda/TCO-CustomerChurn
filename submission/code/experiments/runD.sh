#!/bin/sh

# 1:3 s:20  MAE 201906  extended history encoding32
cd clas9 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20  MAE 201906  extended history
cd regr29 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20  MAE 201906  extended history encoding32
cd regr30 && unbuffer ./run.sh 3 | tee run.log
cd -

