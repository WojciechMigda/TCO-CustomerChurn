#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""

Merges input.csv with ground_truth.json

Run this script in the same folder as these two files.

Successful execution yields input_gt.csv

"""

import plac
import json
import pandas as pd



def main():

    with open('input.csv') as csv_ifile, open('ground_truth.json') as gt_file, open('input_gt.csv', "w") as ofile:
        gt = json.load(gt_file)
        gt_true = set(gt["churned"])

        lines = csv_ifile.readlines()


        for ix, line in enumerate(lines):
            if ix == 0:
                # skip header line
                continue

            custid = line[7:27]

            if custid in gt_true:
                lines[ix] = lines[ix][:-1] + ",1" + lines[ix][-1]
            else:
                lines[ix] = lines[ix][:-1] + ",0" + lines[ix][-1]

        ofile.writelines(lines)
    pass


if __name__ == "__main__":
    plac.call(main)
