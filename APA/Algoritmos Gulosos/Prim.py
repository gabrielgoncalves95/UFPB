import sys
import fileLoader


class Grafo():

    def __init__(self):
        self.no, self.grafo = fileLoader.carrega_matriz()
        self.no = int(self.no)

    def prim(self):

        distancias = [sys.maxsize] * self.no    # array de distâncias do nó x para o nó origem
        arvore = [None] * self.no               # array que vai guardar a árvore de espelhamento mínimo (mst)
        distancias[0] = 0                       # nó inicial
        adicionado = [False] * self.no          # marca nós adicionados e não adicionados na mst

        for i in range(self.no):                          # varre todos os nós do grafo
            u = self.minDistancia(distancias, adicionado) # retorna distância mínima dos nós ainda não inclusos na mst
            adicionado[u] = True                          # marca o nó com a distância mínima encontrada como adicionado

            # atualiza a árvore se a distância atual for maior que a distância nova
            # e se o nó em questão não tiver sido marcado previamente como adicionado
            for v in range(self.no):
                if self.grafo[u][v] > 0 and adicionado[v] == False and distancias[v] > self.grafo[u][v]:
                    distancias[v] = self.grafo[u][v]
                    arvore[v] = u

        self.printResultado(arvore)

    def printResultado(self, arvore):
        result = 0
        for i in range(1, self.no):
            result = result + self.grafo[i][arvore[i]]
        print ("Resultado: " + str(result))

    def minDistancia(self, distancias, adicionado):
        min = sys.maxsize   # inicializa variável com o maior valor possível para busca da menor distância

        for v in range(self.no):    # procura os nós com a menor distância que ainda não adicionados à MST
            if distancias[v] < min and adicionado[v] == False:
                min = distancias[v]
                min_index = v

        return min_index


g = Grafo()
g.prim();