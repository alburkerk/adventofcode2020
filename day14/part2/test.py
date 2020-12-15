import numpy as np
import pandas as pd
import itertools

data = np.loadtxt('input.txt',dtype=str,delimiter=' = ')


#Part 2: Applying masks to the memory instead, what is the sum of the values stored in memory?

memory = {}

for i in data:
    if i[0] == 'mask':
        mask = np.array(list(i[1]))
        num_X = np.count_nonzero(mask == 'X')
        perms = ["".join(seq) for seq in itertools.product("01", repeat=num_X)]
    else:
        binnum = np.array(list(bin(int(i[0][4:-1]))[2:].zfill(36)))
        binnum[np.where(mask == '1')] = '1'
        binnum[np.where(mask == 'X')] = 'X'
        for j in perms:
            new_num = np.array([i for i in binnum])
            new_num[np.where(new_num == 'X')] = np.array(list(j))
            memory[''.join(list(new_num))] = int(i[1])

print(sum(memory.values()))
