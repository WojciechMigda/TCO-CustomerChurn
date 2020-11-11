#!/bin/sh

# 1:3 s:20 C=8000, T=16000, MAE
cd regr25 && unbuffer ./run.sh 3 | tee run.log
cd -
