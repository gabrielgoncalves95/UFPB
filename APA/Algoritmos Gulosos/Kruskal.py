import fileLoaderK


class Grafo:

    def __init__(self):
        self.no, self.grafo = fileLoaderK.carrega_lista()
        self.no = int(self.no)

    # Union - Find Algorithm (INICIO)

    # A função union une dois subsets de árvore em um processo chamado união por rank (semelhante a altura) utilizando
    # a função find move o nó x (e sua sub-árvore) tornando o nó x filho do nó raíz, então o caminho para encontrar os demais
    # nós é reduzido.
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    def union(self, parent, rank, x, y):
        raiz_x = self.find(parent, x)
        raiz_y = self.find(parent, y)

        if rank[raiz_x] < rank[raiz_y]:
            parent[raiz_x] = raiz_y
        elif rank[raiz_x] > rank[raiz_y]:
            parent[raiz_y] = raiz_x

        else:
            parent[raiz_y] = raiz_x
            rank[raiz_x] += 1

    # Union - Find Algorithm (FIM)

    def kruskal(self):

        mst_final = []  # Array que guarda a mst final

        lista_de_ligacoes = 0  # Index usado para percorrer todas as ligações do grafo ordenado
        nos_da_mst = 0  # Index usado para saber quando a mst foi preenchida completamente (todos os nós)

        # Ordena o grafo em ordem crescente de peso das arestas
        self.grafo = sorted(self.grafo, key=lambda item: item[2])

        conjunto_nos = [];
        altura = []

        # Preenche a variável conjunto_nos com todos os nós do grafo (cada um representa uma árvore de altura 0)
        for no in range(self.no):
            conjunto_nos.append(no)
            altura.append(0)

        # Número de arestas que a mst deve possuir (quantidade de nós do grafo - 1)
        while nos_da_mst < self.no - 1:

            # Escolhe o primeiro nó e incrementa
            u, v, w = self.grafo[lista_de_ligacoes]
            lista_de_ligacoes = lista_de_ligacoes + 1

            # retorna o nó pai da sub-árvore correspondente dos nós x e y
            x = self.find(conjunto_nos, u)
            y = self.find(conjunto_nos, v)

            # verifica se o nó pai das sub-árvores é o mesmo (se for igual, a união das árvores gera um ciclo)
            if x != y:
                nos_da_mst = nos_da_mst + 1
                mst_final.append([u, v, w])
                self.union(conjunto_nos, altura, x, y)

        resultado = 0
        for u, v, custo in mst_final:
            resultado = resultado + custo

        print("Resultado: " + str(resultado))


g = Grafo()
g.kruskal()

