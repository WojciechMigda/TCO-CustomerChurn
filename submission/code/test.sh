#!/bin/bash

DATA_DIR="${1}"
OUT_DIR="${2}"

#./infer.sh "${DATA_DIR}" "${OUT_DIR}" _regr_17_18.model regr1.scores

./infer.sh "${DATA_DIR}" "${OUT_DIR}" _clas_F_17.model clas1.scores


./merge_scores.sh "${OUT_DIR}"/clas1.scores > "${OUT_DIR}"/scores.txt

./make_submission_txt.sh "${OUT_DIR}"/scores.txt > "${OUT_DIR}"/solution.txt
