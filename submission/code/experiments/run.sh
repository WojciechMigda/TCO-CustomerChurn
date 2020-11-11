#!/bin/sh

cd regr1 && unbuffer ./run.sh | tee run1.log
cd -

# MSE
cd regr2 && unbuffer ./run.sh | tee run2.log
cd -

# enc 32
cd regr3 && unbuffer ./run.sh | tee run3.log
cd -

# T=32000
cd regr4 && unbuffer ./run.sh | tee run4.log
cd -

# Ratio 1:2
cd regr5 && unbuffer ./run.sh 2 | tee run5.log
cd -

# boost = off
cd regr6 && unbuffer ./run.sh | tee run6.log
cd -

# s=12.0
cd regr7 && unbuffer ./run.sh | tee run7.log
cd -

# C=3000 T=12000
cd regr8 && unbuffer ./run.sh | tee run8.log
cd -
