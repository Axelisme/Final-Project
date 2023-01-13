# %%
import numpy as np
import json
from json import JSONEncoder
M = np.zeros([10,24]).astype(int)
M[1:4,16] = 1
M[6,9:23] = 1; M[6,13:16] = 0
M[4,3] = 1
M[9,23] = 1
M[5,0:12] = 1; M[5,5:7] = 0; M[5,10] = 0
M[2,8:13] = 1; M[2,10] = 0
M[3,[8,11]] = 1 ;M[4,11] = 1
M[0,16] = 2
M[3,9] = 3; M[3,17] = 3; M[7,18] = -1
ML = M.tolist()
MS = [''.join('▓▓' if j == 1 else '  ' if j==0 else '░░' if j==2 else  ' ⋄' if j==3 else ' ⭓' for j in i) + '\n' for i in ML]
with open('../data/level/L1','w') as fh:
    fh.writelines(MS)