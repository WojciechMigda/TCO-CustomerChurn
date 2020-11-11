#!/bin/sh

#cd regr1 && unbuffer ./run.sh | tee run1.log
#cd -

# MSE
#cd regr2 && unbuffer ./run.sh | tee run2.log
#cd -

# enc 32 MAE
cd regr9 && unbuffer ./run.sh | tee run.log
cd -

# T=32000 MAE
cd regr10 && unbuffer ./run.sh | tee run.log
cd -

# Ratio 1:2 MAE
cd regr11 && unbuffer ./run.sh 2 | tee run.log
cd -

# boost = off
#cd regr6 && unbuffer ./run.sh | tee run6.log
#cd -

# s=12.0 MAE
cd regr12 && unbuffer ./run.sh | tee run.log
cd -

# C=3000 T=12000
#cd regr8 && unbuffer ./run.sh | tee run8.log
#cd -

# Ratio 1:3 MAE
cd regr13 && unbuffer ./run.sh 3 | tee run.log
cd -

# s=20.0 MAE
cd regr14 && unbuffer ./run.sh | tee run.log
cd -
