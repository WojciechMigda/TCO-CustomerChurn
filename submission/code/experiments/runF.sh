#!/bin/sh

# 1:3 s:20  MAE  limited history e20 no-seasonal
cd clasC && unbuffer ./run.sh 3 | tee run.log
cd -


# 1:3 s:20  MAE  limited history e32 no-seasonal
cd clasD && unbuffer ./run.sh 3 | tee run.log
cd -

