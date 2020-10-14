#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
Creates encoding descriptor file and saves it into encoding.json

The output is a json dictionary, with each ordinal column being paired with respective bin definition.
Exceptions are columns which are to be skipped, e.g. because they have just 1 value, and they will
be assigned null output.

"""

import plac
import json
import pandas as pd
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import KBinsDiscretizer

def work(df, binsz_dict):

    imp = SimpleImputer(strategy='median')

    rv = {}

    for colname, bin_bits in binsz_dict.items():
        col = df[colname]

        # N bits can represent N+1 values
        """
        4 values -- 3 bits:
            111
            110
            100
            000
        """
        bin_vals = bin_bits + 1

        # count unique values
        nunique = col.nunique(dropna=True)

        if nunique == 1:
            # no encoding, mark the column to be skipped
            rv[colname] = None
            continue

        # drop NaNs because KBinsDiscretizer cannot work with NaNs
        col = col.dropna().values.reshape(-1, 1)

        # bin_edges returned by KBinsDiscretizer are constructed so that
        # the first element is col.min(), and the last is col.max()

        if nunique < bin_vals:
            # Less actual values than allocated bits in the bin
            kbd = KBinsDiscretizer(n_bins=nunique, encode='ordinal', strategy='uniform')
            print(colname)
            kbd.fit(col)
            rv[colname] = kbd.bin_edges_[0].tolist()
            pass
        else:
            kbd = KBinsDiscretizer(n_bins=bin_vals, encode='ordinal', strategy='quantile')
            print(colname)
            kbd.fit(col)
            rv[colname] = kbd.bin_edges_[0].tolist()
            pass
        pass

    return rv


def main(
        ifname: ("Input CSV file", 'positional'),
        nrows : ('Number of rows to read, default(-1)=ALL', 'option', "R", int)=-1,
    ):
    with open('encoding-in.json') as ifile:
        binsz_dict = json.load(ifile)

        nrows = None if nrows == -1 else nrows
        df = pd.read_csv(ifname, na_values='*******', nrows=nrows)

        dictionary = work(df, binsz_dict)
        with open('encoding.json', "w", encoding="utf8") as ofile:
            json.dump(dictionary, ofile, indent=2)

    pass


if __name__ == "__main__":
    plac.call(main)
