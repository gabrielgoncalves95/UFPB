# Gabriel Goncalves Barreto dos Santos
# -*- coding: utf-8 -*-
import numpy as np


def mochila_dinamic(p:list, v:list, n:int, M:int):
    memo_array = [[0 for i in range(M+1)] for j in range(n)]
    for i in range(0, n):
        for j in range(1, M+1):
            if p[i] > j:
                memo_array[i][j] = memo_array[i - 1][j]
            else:
                memo_array[i][j] = max(memo_array[i - 1][j], v[i] + memo_array[i - 1][(j) - p[i]])

    return memo_array


f = open('entrada.txt', 'r')

entrada = f.readlines()

n, M = entrada[0].split()
p = [-1]*int(n)
v = [-1]*int(n)

for i in range(0, 4):
    p[i], v[i] = entrada[i+1].split()


n = int(n)
M = int(M)
print(n, M)
for i in range(0, n):
    p[i] = int(p[i])
    v[i] = int(v[i])
    print(p[i], v[i])

memo = mochila_dinamic(p, v, n, M)
print("\n")
print(np.matrix(memo))
print("\nO melhor custo é:")
print(memo[n-1][M])
