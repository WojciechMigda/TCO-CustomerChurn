#!/bin/bash

#
# This one uses input which contains churning probability
# and outputs sorted customer ids. Ties are randomized

shuf ${1:-scores.txt} | sort --field-separator=, --key=2 -r -s | cut --delimiter=, -f 1
