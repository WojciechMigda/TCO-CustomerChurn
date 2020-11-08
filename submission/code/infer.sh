#!/bin/bash

EXE=kernel/.build/app/main
DATA_DIR="${1}"
OUT_DIR="${2}"
MODEL="${3}"
OUT_SCORES="${4}"
ENC=${5:-20}

${EXE} infer \
      -d "${DATA_DIR}"/input.csv \
      -e encoding-${ENC}.json \
      -m models/"${MODEL}" \
      -o "${OUT_DIR}"/"${OUT_SCORES}" \
      --f201906 --fseasonal
