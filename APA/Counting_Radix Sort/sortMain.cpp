#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <map>


//Le vetor do arquivo para efetuar ordenacao
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

//Counting Sort
void coutingSort(std::vector<long int> *v){

    //Salva o valor maximo e minimo
    int min = *std::min_element( v->begin(), v->end());
    int max = *std::max_element( v->begin(), v->end());

    std::cout << max << std::endl;
    std::cout << min << std::endl;

    //Cria o vetor de contagem utilizando o maximo e minimo encontrado
    std::vector<long int> contagem(max - min + 1, 0); //inicializa um vetor de contagem completamente preenchido por zeros

    //Salva em cada coordenada
    for (auto i = v->begin(); i != v->end(); i++)
    ++contagem[*i - min];//incrementa o valor de determinada coordenada conforme o valor aparece no vetor

    std::partial_sum( contagem.begin(), contagem.end(), contagem.begin()); //gera o vetor de incrementos do couting sort, sempre somando com o proximo e salva em contagem

    std::vector<long int>ordem(v->size());
    for (auto i = v->rbegin(); i != v->rend(); i++)//Utiliza um iterador reverso para salvar o vetor ordenado
        ordem[--contagem[*i - min]] = *i;//salva do fim para o comeco em ordem, isso resulta no vetor ordenado

    for (int i = 0; i < v->size(); i++)
        (*v)[i] = ordem[i]; //copia o vetor ordem em v para retornar atraves do endereco
    
}


void radixSort(std::vector<long int> *v){

    //salva maximo elemento
    int max = *std::max_element( v->begin(), v->end());
    int divide = 1;//cria a variavel de divisao que sera usada para selecionar a casa da unidade, dezena ou centena
    std::vector<long int>ordem(v->size());

    while (max/divide > 0){
        std::vector<long int> aux(10, 0); //Preenche vetor auxiliar com 0

        //implementacao usando map para fazer a chamada do countingSort ja implementado e nao implementar novamente dentro do Radix

        /*std::map<long int,long int> relation;

        for (int i = 0; i < v->size(); i++){
            aux[i] = (*v)[i]/divide % 10;
            relation[aux[i]] = (*v)[i];
        }

        coutingSort(&aux);
        */

        //Utiliza o operador mod para pegar apenas o valor que se deseja ordenar (0-9), por ex.: 554%10 = 4, 53%10 = 3, etc
        for (int i = 0; i < v->size(); i++)
            aux[(*v)[i]/divide % 10]++; //e incrementa as ocorrencias para ordenar
        
        for (int i = 1; i < 10; i++)
            aux[i] += aux[i - 1]; //incrementa o valor de determinada coordenada conforme o valor aparece no vetor

        for (int i = v->size() - 1; i >= 0; i--)
            ordem[--aux[((*v)[i] / divide) % 10]] = (*v)[i]; //atribui a ordenacao da casa decimal de ordem n ao vetor ordem

        for (int i = 0; i < aux.size(); i++)
            (*v)[i] = ordem[i]; //salva o vetor ordem ordenado ate a iteracao i no vetor de saida

        divide *= 10;   //multiplica por 10 o valor do divide para pegar o valor de outra casa decimal na proxima iteracao
    }
}


int main(int argc, char const *argv[]) {
    std::vector<long int> v1 = readFile();
    std::vector<long int> v2 = readFile();
    coutingSort(&v1);
    writeFile(v1, "coutingSort");
    radixSort(&v2);
    writeFile(v2, "radixSort");
    return 0;
}
