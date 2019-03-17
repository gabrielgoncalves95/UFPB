from operator import itemgetter


def carrega_matriz():
    f = None
    while f is None:
        entry = input("Digite o nome do arquivo com a extensão: ")
        try:
            f = open(entry, 'r')
        except FileNotFoundError:
            print("Arquivo não encontrado!")

    entrada = f.readlines()

    num_nos = entrada[0]
    lista_loaded = [[0]]*(int(num_nos))
    lista_adj = [[0]]*(int(num_nos))
    matriz_adj = [[0]]*(int(num_nos))

    # quebra a string de entrada em uma lista de numeros
    for i in range(0, int(num_nos)-1):
        lista_loaded[i] = entrada[i+1].split()

    aux = []
    for i in range(0, int(num_nos)):
        aux.clear()
        n = i

        for j in range(0, len(lista_loaded[i])):
            if j == 0:
                aux.append([n + 1, 0])
            if lista_loaded[i][j] != 0:
                aux.append([n+2, int(lista_loaded[i][j])])
                n = n+1
        lista_adj[i] = aux.copy()


    # completa listas (forma matriz quadrada)
    for i in range(0, int(num_nos)):
        for j in range(0, len(lista_adj[i])):
            if lista_adj[i][j][1] == 0:
                continue
            if (lista_adj[i][j][0] - 1) < i:
                continue
            lista_adj[(lista_adj[i][j][0] - 1)].append([i+1, lista_adj[i][j][1]])

    for i in range(0, len(lista_adj)):
        lista_adj[i] = sorted(lista_adj[i], key=itemgetter(0)).copy()

    # cria matriz de adjacências
    for i in range(0, len(lista_adj)):
        aux.clear()
        for j in range(0, len(lista_adj)):
            aux.append(lista_adj[i][j][1])
        matriz_adj[i] = aux.copy()

    return num_nos, matriz_adj.copy()

