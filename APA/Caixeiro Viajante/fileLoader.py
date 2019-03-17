import numpy as np


def carrega_matriz():
    
    f = None
    while f is None:
        #entry = input("Digite o nome do arquivo com a extensão: ")
        entry = 'pcv04.txt'
        try:
            f = open(entry, 'r')
        except FileNotFoundError:
            print("Arquivo não encontrado!")

    entrada = f.readlines()

    num_nos = entrada[0]
    num_nos = int(num_nos)
    matriz_adj = [[0]]*(int(num_nos))

    # quebra a string de entrada em uma lista de numeros
    for i in range(0, int(num_nos)):
        matriz_adj[i] = entrada[i+1].split()
        matriz_adj[i] = list(map(int, matriz_adj[i]))

    print(np.matrix(matriz_adj))

    return num_nos, matriz_adj.copy()
