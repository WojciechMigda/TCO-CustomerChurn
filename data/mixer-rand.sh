#!/bin/sh

R=${1:-1}
HISTORY=${2:-history.csv}
NPOS=${3:-120148}

OFNAME=history_mix_1to${R}.csv

{ head -n 1 "${HISTORY}" ; { grep ",1$" "${HISTORY}" | head -n ${NPOS} ; \
                             grep ",0$" "${HISTORY}" | shuf | head -n $(( $R * ${NPOS} )) ; } | shuf ; \
} > "${OFNAME}"
