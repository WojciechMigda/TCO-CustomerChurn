#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""

Requires raw inference results generated with main infer

"""

import plac
import json
import pandas as pd
import numpy as np


def main(
#        threshold : ('Threshold', 'option', "T", int),
        threshold : ('Threshold', 'positional', None, int),
        ifname: ("Input raw inference file", 'positional'),
    ):

    print(locals())

    scores = pd.read_csv(ifname, header=None, index_col=0, names=['n', 'p'])
    means = (scores['n'] + scores['p']) / 2
    probas = (scores['p'] - means + threshold) / (2 * threshold)

    assert(sum(probas < 0) == 0)

    sorted_indices = probas.values.argsort()[::-1]
    churned = scores.index[sorted_indices]

    np.savetxt("submission.txt", churned, fmt="%s")

    return


if __name__ == "__main__":
    plac.call(main)
