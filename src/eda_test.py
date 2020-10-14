#!/usr/bin/python3
# -*- coding: utf-8 -*-


# A1 Austria


def read_train():
    import pandas as pd

    df = pd.read_csv('../data/input.csv', na_values='*******',
#            nrows=100000
        )
    print('Full TEST shape: {}'.format(df.shape))

    return df


def main():
    import pandas as pd

    df = read_train()


    # iterate over columns
    for colname in df:
        col = df[colname]
        isnull = col.isnull().values
        has_nans = 'NaN ({})'.format(isnull.sum()) if isnull.any() else ''
        uniq_vals = col.nunique(dropna=True)

        min_ = col.min() if col.dtype.name != 'object' else '---'
        max_ = col.max() if col.dtype.name != 'object' else '---'

        obj_vals = ','.join( list(set(col.dropna().values))[:10] ) if col.dtype.name == 'object' else ''

        print('{:>30s} {:>8s} {:<12s} {:>8d} {:>8s} {:>8s} {}'.format(colname, col.dtype.name, has_nans, uniq_vals, str(min_), str(max_), obj_vals))

    return


if __name__ == "__main__":
    main()
