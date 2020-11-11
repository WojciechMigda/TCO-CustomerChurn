#!/bin/sh

# 1:3 s:20 C4k  e120 f201906
cd clasM && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20 C4k  e100 f201906
cd clasN && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20 C4k  e64 f201906
cd clasO && unbuffer ./run.sh 3 | tee run.log
cd -
