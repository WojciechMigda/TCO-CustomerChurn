#!/bin/sh

# clf 1:3 s=20
cd clas5 && unbuffer ./run.sh 3 | tee run.log
cd -

