#include <iostream>
#include <vector>
#include <fstream>
#include <string>

//Lê vetor do artigo para efetuar ordenação
std::vector<long int> readFile (){
    std::vector<long int> v;
    std::ifstream file("couting.txt");
    std::string str;
    while (std::getline(file, str))
    {
        v.push_back(std::stol(str));
    }
    return v;
}

//Salva vetor de volta no arquivo
void writeFile(std::vector<long int> v, std::string file){
    std::ofstream fout;
    fout.open(file+".txt");
    for (int i = 0; i < v.size(); i++){
        fout << v[i] << std::endl;
    }
    fout.close();
}

//Função que junta as partes no vetor final (faz o merge)
std::vector<long int> merge(std::vector<long int> vetor, int inicio, int meio, int fim, long int vetAux[]) {

    int esq = inicio;
    int dir = meio;
    for (int i = inicio; i < fim; ++i) {
        if ((esq < meio) and ((dir >= fim) or (vetor[esq] < vetor[dir]))) {
            vetAux[i] = vetor[esq];
            ++esq;
        }
        else {
            vetAux[i] = vetor[dir];
            ++dir;
        }
    }
    for (int i = inicio; i < fim; ++i) {
       vetor[i] = vetAux[i];
    }
    return vetor;
}

//Função realmente implementada de MergeSort
void mergeSort(std::vector<long int> *vetor, int inicio, int fim, long int vetorAux[]) {

    if ((fim - inicio) < 2) return;

    int meio = ((inicio + fim)/2);

    mergeSort(vetor, inicio, meio, vetorAux);

    mergeSort(vetor, meio, fim, vetorAux);

    (*vetor) = merge((*vetor), inicio, meio, fim, vetorAux);

}

//Sobrecarga de função que será chamado pelo usuário
void mergeSort(std::vector<long int> *vetor, int tamanho) {

    long int vetorAux[tamanho];

    mergeSort(vetor, 0, tamanho, vetorAux);

}

//Função de quicksort que faz o particionamento e ordena
void quick (std::vector<long int> *vetor, int esq, int dir){
    int pivo = esq, k, j;
    for (int i = esq + 1; i <= dir; i++){
        j = i;
        if ((*vetor)[j] < (*vetor)[pivo]){
            k = (*vetor)[j];

            while (j > pivo){
                (*vetor)[j] = (*vetor)[j-1];
                j--;
            }
            (*vetor)[j] = k;
            pivo++;
        }
    }
    if (pivo-1 >= esq){
        quick(vetor, esq, pivo - 1);
    }
    if (pivo+1 <= dir){
        quick(vetor, pivo + 1, dir);
    }
}

//Função de quick chamada pelo usuário
void quickSort(std::vector <long int> *vetor){
    quick(vetor, 0, vetor->size() - 1);
}



int main(int argc, char const *argv[]) {
    std::vector<long int> v1 = readFile();
    std::vector<long int> v2 = readFile();
    mergeSort(&v1, v1.size());
    writeFile(v1, "mergeSort");
    quickSort(&v2);
    writeFile(v2, "quickSort");
    return 0;
}
