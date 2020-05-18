from sys import *
import pandas as pd
from itertools import groupby
import re

if len(argv) != 3:
    print("missing command-line argument")
    exit(1)

var_1 = argv[1]
var_2 = argv[2]

s = pd.read_csv(var_1)
q = pd.read_csv(var_2)

#print(s.head())

pattern_names = list(s.columns)
pattern_names = pattern_names[1:]

sequence_names = list(q.columns)
sequence_names = str(sequence_names[0])

#print(pattern_names)

#print(sequence_names)

counts = []

for i in pattern_names:
    pat = '('
    patt = ')+'
    tt = ')'
    patt2 = pat+i+pat+i+patt+tt
    patt3 = str(patt2)
    results = re.findall(patt2,sequence_names)
    if results:
                longest_sequence = sorted(results, reverse=True)[0]
                count = len(longest_sequence[0]) / len(i) # count the number of ocurrences
    else:
            count = 1
    counts.append(count)
#print(counts)


counts2 = str(counts)

t = s.iloc[:,1:][s.iloc[:,1:].isin(counts)].dropna()

#print(t.empty)

if t.empty == True:
    print("No Match")
else:
    print(s.iloc[t.index[0],0])
