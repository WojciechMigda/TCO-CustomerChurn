#!/bin/sh

# 1:3 s:20  MAE 201906  extended history
cd clas8 && unbuffer ./run.sh 3 | tee run.log
cd -

