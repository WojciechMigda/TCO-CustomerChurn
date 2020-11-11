#!/bin/sh

# clf 1:1
cd clas1 && unbuffer ./run.sh | tee run.log
cd -

# clf 1:2
cd clas2 && unbuffer ./run.sh 2 | tee run.log
cd -

# regr
# Ratio 1:10 MAE
cd regr16 && unbuffer ./run.sh 10 | tee run.log
cd -

# regr
# Ratio 1:3 s=12 MAE
cd regr17 && unbuffer ./run.sh 3 | tee run.log
cd -

# TODO clas 1:3 ?
