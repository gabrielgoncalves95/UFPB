
def carrega_lista():
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

    # quebra a string de entrada em uma lista de numeros
    for i in range(0, int(num_nos)-1):
        lista_loaded[i] = entrada[i+1].split()

    aux = []
    for i in range(0, int(num_nos) - 1):
        aux.clear()
        n = i
        for j in range(0, len(lista_loaded[i])):
            aux.append([i ,n + 1, int(lista_loaded[i][j])])
            n = n+1
        lista_adj[i] = aux.copy()

    lista_final = []
    for i in range(0, len(lista_adj) - 1):
        for j in range(0, len(lista_adj[i])):
            lista_final.append(lista_adj[i][j])

    return num_nos, lista_final.copy()
