#!/bin/sh

# 1:3 s:20 C4k  e32 f201906
cd clasP && unbuffer ./run.sh 3 | tee run.log
cd -
