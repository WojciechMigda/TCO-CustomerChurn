#!/bin/sh

N=1
R=2

OFNAME=history_mix_1to${R}_${N}.csv

{ head -n 1 history.csv ; { grep ",1$" history.csv | head -n 120148 ; \
                            grep ",0$" history.csv | tail -n +$(( $R * ($N - 1) * 120148 )) | head -n $(( $R * 120148 )) ; \
                          } | shuf ; \
} > "${OFNAME}"

#{ head -n 1 history.csv ; { grep ",1$" history.csv | head -n 120148 ; grep ",0$" history.csv | shuf | head -n $(( 1 * 120148 )) ; } | shuf ; } > "${OFNAME}"
