#!/bin/bash

mixer() {
  R=${1:-1}
  HISTORY=${2:-history.csv}
  NPOS=${3:-120148}

  OFNAME=${4}



  { head -n 1 "${HISTORY}" ; { grep ",1$" "${HISTORY}" | head -n ${NPOS} ; \
                             grep ",0$" "${HISTORY}" | shuf | head -n $(( $R * ${NPOS} )) ; } | shuf ; \
  } > "${OFNAME}"

}


DATA_DIR="${1}"
OUT_DIR="${2}"


RATIO=${3:-3}
ENC=${4:-32}
SAVED_MODEL="${5:-trained.model}"


EXE=kernel/.build/app/main

NPOS=$( grep ",1$" ${DATA_DIR}/history.csv | wc -l )

mixer ${RATIO} ${DATA_DIR}/history.csv ${NPOS} ${OUT_DIR}/history_mix_1to${RATIO}.csv

${EXE} train \
  -c \
  -d ${OUT_DIR}/history_mix_1to${RATIO}.csv \
  -e encoding-${ENC}.json \
  -o models/${SAVED_MODEL} \
  -C 4000 -T 16000 -s 20 -w -1 -j 8 --nepochs 1 \
  --f201906 \
  #
