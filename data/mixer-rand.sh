#!/bin/sh

R=${1:-1}

OFNAME=history_mix_1to${R}.csv

{ head -n 1 history.csv ; { grep ",1$" history.csv | head -n 120148 ; \
                            grep ",0$" history.csv | shuf | head -n $(( $R * 120148 )) ; } | shuf ; \
} > "${OFNAME}"
