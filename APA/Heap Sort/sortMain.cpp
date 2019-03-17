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


//Max Heap
void buildMaxH(std::vector<long int> &vec, int start , int end){
    int max = 2 * start + 1;

    if(max < end){
       if((max+1) < end && vec.at(max) < vec.at(max+1))++max;

       if(vec.at(max) > vec.at(start)){
          std::swap(vec[max], vec[start]);
          buildMaxH(vec, max, end);
       }
    }
}


//HeapSort
void heapSort(std::vector<long int> &vec){
    int tam = static_cast<long int>(vec.size()), i;

    for(i=tam/2-1; i>=0; --i)
       buildMaxH(vec, i , tam );

    std::vector<long int>::reverse_iterator elem;

    for(elem=vec.rbegin(); elem!=vec.rend(); elem++){
       std::iter_swap( elem, vec.begin() );
       buildMaxH(vec,0,--tam);
    }
}


int main(int argc, char const *argv[]) {
    std::vector<long int> v1 = readFile();
    heapSort(v1);
    writeFile(v1, "heapSort");
    return 0;
}
