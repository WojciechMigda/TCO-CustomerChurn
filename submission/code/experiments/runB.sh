#!/bin/sh

# 1:3 s:20  MAE 201906
cd regr26 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:4 s:20  MAE 201906
cd regr27 && unbuffer ./run.sh 4 | tee run.log
cd -


# 1:3 s:32  MAE 201906
cd regr28 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20  MAE 201906
cd clas6 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:12  MAE 201906
cd clas7 && unbuffer ./run.sh 3 | tee run.log
cd -

