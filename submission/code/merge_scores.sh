#!/bin/sh

awk -F, '{a[FNR]=$1; s[FNR]+=$2} END{for (i=1; i<=FNR; i++) print a[i] "," s[i]}' "${@}"
