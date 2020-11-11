#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""

Extract negative mismatched samples

"""

import os
import sys
import plac
import random


def main(
        ifname_csv: ("Training CSV data, with target column.", 'positional'),
        ifname_score: ("File with cores for samples. Two columns: cust_id, score", 'positional'),
        ofname_csv: ("Output CSV file.", 'positional'),
        nsamples: ("Number of samples to output", 'positional', None, int),
    ):

    with open(ifname_csv) as ifile_csv, open(ifname_score) as ifile_score, open(ofname_csv, 'wt') as ofile_csv:

        header = ifile_csv.readline()

        lines = []
        positives = []

        for (iline_csv, iline_score) in zip(ifile_csv.readlines(), ifile_score.readlines()):
            sample, target = iline_csv.rsplit(',', 1)
            cust_id, score = iline_score.split(',', 1)

            target = int(target)
            score = float(score)

            if target == 1:
                positives.append(iline_csv.strip())
                continue

            lines.append(tuple([sample, score]))
            pass

        sorted_by_score = sorted(lines, key=lambda t: t[1], reverse=True)[:nsamples]

        most_mismatched = [','.join((t[0], '0')) for t in sorted_by_score]
        most_mismatched.extend(positives)

        random.shuffle(most_mismatched)

        ofile_csv.write(header)
        ofile_csv.write('\n'.join(most_mismatched))

        pass


if __name__ == "__main__":
    plac.call(main)
