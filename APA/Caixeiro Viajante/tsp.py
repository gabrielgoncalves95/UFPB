import sys
import copy
import fileLoader

n, matrix = fileLoader.carrega_matriz()

all_sets = []
g = {}
p = []


def main():
    for x in range(1, n):
        g[x + 1, ()] = matrix[x][0]

    get_minimum(1, tuple(range(2, n+1)))
    solution = p.pop()

    result_list = [1, solution[1][0]]
    result = 0
    result = result + matrix[result_list[0]-1][result_list[1]-1]
    i = 2


    for x in range(n - 2):
        for new_solution in p:
            if tuple(solution[1]) == new_solution[0]:
                solution = new_solution
                result_list.append(solution[1][0])
                result = result + matrix[result_list[i-1]-1][result_list[i]-1]
                i = i+1
                break
    result_list.append(1)
    result = result + matrix[result_list[i-1] - 1][result_list[i] - 1]
    print("\n\n\nSolução do Caixeiro Viajante: " + str(result_list))
    print("Custo: " + str(result) + "\n\n")
    return


def get_minimum(k, a):
    if (k, a) in g:
        return g[k, a]

    values = []
    all_min = []
    for j in a:
        set_a = copy.deepcopy(list(a))
        set_a.remove(j)
        all_min.append([j, tuple(set_a)])
        result = get_minimum(j, tuple(set_a))
        values.append(matrix[k-1][j-1] + result)

    g[k, a] = min(values)
    p.append(((k, a), all_min[values.index(g[k, a])]))

    return g[k, a]


if __name__ == '__main__':
    main()
    sys.exit(0)
