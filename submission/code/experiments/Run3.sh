#!/bin/sh

# Uczenie clas6, 1:3 s=20 f201906
cd Clas2 && unbuffer ./run.sh 3 | tee run.log
cd -
