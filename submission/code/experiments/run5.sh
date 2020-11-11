#!/bin/sh

# regr
# Ratio 1:4 MAE
cd regr18 && unbuffer ./run.sh 4 | tee run.log
cd -

# clf 1:3
cd clas3 && unbuffer ./run.sh 3 | tee run.log
cd -

