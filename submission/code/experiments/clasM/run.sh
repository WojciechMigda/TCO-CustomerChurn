#!/bin/bash

REP=1
ENC=120

# pos/neg ration, default 1
RATIO=${1:-1}

EXE=../../kernel/.build/app/main

DATA_DIR=../../../../data

for N in `seq ${REP}`; do

  echo "${N}"

  # generate input
  pushd ${DATA_DIR}
  ./mixer-rand.sh ${RATIO}
  popd

  SAVED_MODEL=trained_$(( ${N} - 1 )).model
  if [ ${N} -eq 1 ]; then
    SAVED_MODEL_ARG=
  else
    SAVED_MODEL_ARG="-m ${SAVED_MODEL}"
  fi

  ${EXE} train \
      -c \
      -d ${DATA_DIR}/history_mix_1to${RATIO}.csv \
      -e ../../encoding-${ENC}.json \
      -o trained_${N}.model \
      -C 4000 -T 16000 -s 20 -w -1 -j 6 --nepochs 1 \
      --f201906 \
      ${SAVED_MODEL_ARG}

  ${EXE} infer \
      -d ${DATA_DIR}/input.csv \
      -e ../../encoding-${ENC}.json \
      -m trained_${N}.model \
      --f201906 \
      -o scores.txt

  # compress past model file in background
  gzip -9 ${SAVED_MODEL} &

  ../../make_submission_txt.sh scores.txt > submission.txt
  ../../scorer.py submission.txt ${DATA_DIR}/ground_truth.json .

done
