#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""

Extract new CSV/ Ground Truth datafiles pair from input training CSV

"""

import os
import sys
import plac
import json



def main(
        yyyymm: ("Date/month in YYYYMM format (e.g. 201907) to filter on and create output data", 'positional'),
        ifname: ("Input CSV data, with target column.", 'positional'),
        ofname_csv: ("Output CSV file.", 'positional'),
        ofname_json: ("Output ground truth file.", 'positional'),
    ):

    with open(ifname) as ifile, open(ofname_csv, 'wt') as ofile_csv, open(ofname_json, 'wt') as ofile_json:

        gt = {"nonChurned" : [], "churned": []}

        for iline in ifile.readlines():
            if iline.startswith('report'):
                ofile_csv.write(iline)
            if iline[:6] == yyyymm:
                target = iline[-2]
                custid = iline[7:27]
                if target == '0':
                    gt["nonChurned"].append(custid)
                    pass
                else:
                    gt["churned"].append(custid)
                    pass
                ofile_csv.write(iline)

        ofile_json.write(json.dumps(gt, indent=2))

        pass


if __name__ == "__main__":
    plac.call(main)
