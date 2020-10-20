#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""

Python version of scorer index.js

"""

import os
import sys
import plac
import json



def main(
        scored_file: ("Inference result", 'positional'),
        gt_file: ("Ground truth file", 'positional'),
        out_dir: ("Destination folder", 'positional'),
    ):

    RESULT_FILENAME = os.path.join(out_dir, 'result.txt')
    DETAILS_FILENAME = os.path.join(out_dir, 'details.txt')

    with open(scored_file) as ifile:
        scored = [line.strip() for line in ifile.readlines()]

    with open(gt_file) as ifile:
        gt = json.load(ifile)

    gt['churned'] = set(gt['churned'])
    gt['nonChurned'] = set(gt['nonChurned'])

    numChurned = len(gt['churned'])
    numAll = numChurned + len(gt['nonChurned'])

    averageChurn = numChurned / numAll

    print('Num. customers: {}'.format(numAll))
    print('Average churn: {:.2f}'.format(100. * averageChurn))

    def at(percent):
        return percent * numAll // 100

    reports = []
    reportStops = set([at(1), at(5), at(10), at(20), at(60), at(100)])

    def bail(reason):
        print('Bailing out with zero score:', reason)
        with open(RESULT_FILENAME, 'w') as ofile:
            ofile.write('0.0')
        with open(DETAILS_FILENAME, 'w') as ofile:
            ofile.write(reason)
        sys.exit(1)

    churnedCount = 0

    for i in range(1, len(scored) + 1):
        Id = scored[i - 1]
        if Id in gt['churned']:
            gt['churned'].remove(Id)
            churnedCount += 1
        elif Id in gt['nonChurned']:
            gt['nonChurned'].remove(Id)
        else:
            bail('Unknown customer ID')
        if i in reportStops:
            reports.append(dict(at=i / numAll, lift=churnedCount / i))

    if len(gt['churned']) or len(gt['nonChurned']):
        bail('Some customer IDs are missing')

    def toScore(at, lift):
        numItems = at * numAll
        maxPossibleChurn = min(numItems, numChurned) / numItems
        return 100 * lift / (maxPossibleChurn / averageChurn)

    result = None
    details = "% Group\tChurn\tLift\tScore\n"
    for item in reports:
        item['lift'] /= averageChurn
        if round(100 * item['at']) == 10:
            result = toScore(item['at'], item['lift'])
        details += "{:.2f}\t".format(100. * item['at'])
        details += "{:.4f}\t".format(item['lift'] * averageChurn)
        details += "{:.4f}\t".format(item['lift'])
        details += "{:.4f}\t\n".format(toScore(item['at'], item['lift']))

    print('result:  {:.5f}'.format(result))
    with open(RESULT_FILENAME, 'w') as ofile:
        ofile.write(str(result))

    with open(DETAILS_FILENAME, 'w') as ofile:
        ofile.write(details)

    pass


if __name__ == "__main__":
    plac.call(main)
