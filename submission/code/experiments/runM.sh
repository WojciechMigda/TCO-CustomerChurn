#!/bin/sh

# 1:3 s:20 C16k  MAE  e32 f201906
cd clasH && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20 C16k  MAE  e32 f201906 no-seasonal
cd clasI && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20  MAE 201906 C3.9k
cd clasJ && unbuffer ./run.sh 3 | tee run.log
cd -

# 1:3 s:19  MAE 201906 C4.1k
cd clasK && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:2 s:18  MAE 201906 C4k
cd clasL && unbuffer ./run.sh 3 | tee run.log
cd -
