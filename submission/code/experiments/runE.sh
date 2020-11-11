#!/bin/sh

# 1:3 s:20  MAE  limited history
cd clasB && unbuffer ./run.sh 3 | tee run.log
cd -

