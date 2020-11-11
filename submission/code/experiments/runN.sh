#!/bin/sh


# 1:3 s:20  MAE 201906 C4k e20
cd regr34 && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20  MAE 201906 C4k e32
cd regr35 && unbuffer ./run.sh 3 | tee run.log
cd -
