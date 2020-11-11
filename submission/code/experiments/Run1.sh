#!/bin/sh

# Uczenie regr17, 1:3 s=12
cd Regr1 && unbuffer ./run.sh 3 | tee run.log
cd -
