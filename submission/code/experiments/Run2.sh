#!/bin/sh

# Uczenie clas4, 1:3 s=12
cd Clas1 && unbuffer ./run.sh 3 | tee run.log
cd -
