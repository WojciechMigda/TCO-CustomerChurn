#!/bin/bash

DATA_DIR="${1}"
OUT_DIR="${2}"

./train.sh "${DATA_DIR}" "${OUT_DIR}" 3 32 _clas_X.model

./infer.sh "${DATA_DIR}" "${OUT_DIR}" _clas_X.model clasX.scores 32

./infer.sh "${DATA_DIR}" "${OUT_DIR}" _clas_6_1.model clas1.scores 20
./infer.sh "${DATA_DIR}" "${OUT_DIR}" _clas_J_1.model clas2.scores 20
./infer.sh "${DATA_DIR}" "${OUT_DIR}" _clas_K_1.model clas3.scores 20
./infer.sh "${DATA_DIR}" "${OUT_DIR}" _clas_L_1.model clas4.scores 20
./infer.sh "${DATA_DIR}" "${OUT_DIR}" _clas_O_1.model clas5.scores 64


./merge_scores.sh \
  "${OUT_DIR}"/clasX.scores \
  "${OUT_DIR}"/clas1.scores \
  "${OUT_DIR}"/clas2.scores \
  "${OUT_DIR}"/clas3.scores \
  "${OUT_DIR}"/clas4.scores \
  "${OUT_DIR}"/clas5.scores \
  > "${OUT_DIR}"/scores.txt

./make_submission_txt.sh "${OUT_DIR}"/scores.txt > "${OUT_DIR}"/solution.txt
