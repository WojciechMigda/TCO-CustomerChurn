#!/bin/sh

# C=8000, T=32000, MAE
#cd regr15 && unbuffer ./run.sh | tee run.log
#cd -

# C=6000, T=24000, MAE
cd regr15a && unbuffer ./run.sh | tee run.log
cd -

