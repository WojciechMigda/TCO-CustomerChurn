#!/bin/sh


# 1:4 s:12  MAE
cd regr21 && unbuffer ./run.sh 4 | tee run.log
cd -
