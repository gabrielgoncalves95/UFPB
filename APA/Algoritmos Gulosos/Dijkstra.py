import fileLoader
import sys


class Grafo():

    def __init__(self):
        self.no, self.grafo = fileLoader.carrega_matriz()
        self.no = int(self.no)

    def dijkstra(self, origem):

        distancias = [sys.maxsize] * self.no  # array de distâncias do nó x para o nó origem
        distancias[origem] = 0                # da origem para origem a distância é zero
        visitado = [False] * self.no          # cria um array de nós visitados que auxilia na criação dos caminhos

        for i in range(self.no):                        # varre todos os nós do grafo
            u = self.minDistancia(distancias, visitado) # retorna a distância mínima dos nós ainda não visitados
            visitado[u] = True                          # e marca o nó com a distância mínima encontrada como visitado

            # atualiza a distância dos nós adjacentes sequenciais se a distância atual for maior que a distância nova
            # e se o nó em questão não tiver sido marcado previamente como visitado
            for v in range(self.no):
                if self.grafo[u][v] > 0 and visitado[v] == False and distancias[v] > distancias[u] + self.grafo[u][v]:
                    distancias[v] = distancias[u] + self.grafo[u][v]

        self.printResultado(distancias[9])

    def printResultado(self, distancia):
        print("Resultado: " + str(distancia))

    def minDistancia(self, distancias, visitado):
        min = sys.maxsize   # inicializa variável com o maior valor possível para busca da menor distância

        for v in range(self.no):   # procura os nós com a menor distância que ainda não foram visitados
            if distancias[v] < min and visitado[v] == False:
                min = distancias[v]
                min_index = v

        return min_index


g = Grafo()
g.dijkstra(0)
