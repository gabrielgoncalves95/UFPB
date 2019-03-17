#include <iostream>
#include <fstream>
#include <vector>


using namespace std;



/**Vetores e vari�veis Globais para carregamento dos dados*/
vector <int> seq_ref;
vector <int> mem_quadros;
int n_pages = 0, n_quadros = 0;

/**Carrega o arquivo para as vari�veis numero de quadros (n_quadros) e sequencias de referencias (seq_ref)*/
void carrega_arquivo (){
    ifstream infile ("input.txt");
    int a, ciclo = 0;
    while (infile >> a){
        if (ciclo==0) n_quadros = a;
        else seq_ref.push_back(a);
        ciclo++;
    }
    n_pages = ciclo-1;
}


/**Fun��es que os algoritmos usar�o*/
//Especifica um valor pra ser buscado na lista de quadros
int busca_quadros (int a){
    int n = seq_ref[a];
    for (int i=0; i < n_quadros; i++){
        if (n == mem_quadros[i]) return 1;
    }
return 0;
}


//Faz o mesmo que a busca_quadros por�m salva a coordenada em um ponteiro
int busca_retorna (int *ponteiro, int a){
    int n = seq_ref[a];
    for (int i=0; i<n_quadros; i++){
        if (n == mem_quadros[i]){
            *ponteiro=i;
            return 1;
        }
    }
return 0;
}

//Inicia vector de quadros para ser usado pelos algoritmos
void inicia_quadros (){
    for (int i=0; i<n_quadros; i++){
        mem_quadros.push_back(-1);
    }
}

//Limpa vetor de quadros antes de executar os algoritmos de substitui��o
void limpa_quadros (){
    for (int i=0; i<n_quadros; i++){
        mem_quadros[i]=-1;
    }
}

void FIFO (){
    int faltas=0, aux=0;
    limpa_quadros();
    for (int i=0; i<n_pages; i++){
        /**Verifica se est� faltando no vetor de quadros o valor dessa posi��o*/
        if(!(busca_quadros(i))){
            mem_quadros[aux]=seq_ref[i];
            faltas++; //Incrementa a quantidade de faltas
            aux++;
            if(aux==n_quadros) aux=0;
        }
    }
cout << "FIFO " << faltas << endl;
}


void OTM (){
    int faltas=0, tempo=0, maior=0, coord_maior=0, aux=0;
    limpa_quadros();
    for (int i=0; i<n_pages-1;i++){
        maior=0;
        //maior tempo
        for(int j=0; j<n_quadros; j++){
            tempo=0;
            for (int k=0; k<n_pages;k++){
                if(seq_ref[k]!=mem_quadros[j])tempo++;
                else break;
            }
            //intervalo maior que o registrado
            if (tempo > maior){
                maior=tempo;
                coord_maior=j;
            }
            aux = j;
        }
        //se o maior tempo for 0, todos os intervalos tamb�m ser�o
        if (maior==0){
            coord_maior=aux++;
            if (coord_maior==n_quadros) coord_maior=0;
        }

        //Se o valor da sequencia nao estiver no vetor, incrementa-se as faltas
        if (!busca_quadros(i)){
            mem_quadros[coord_maior]=seq_ref[i];
            faltas++;
        }
    }
cout << "OTM " << faltas << endl;
}


void LRU (){
    int faltas=0, menos=0, coord_menos=0, aux=0;
    int tempo[n_quadros];
    limpa_quadros();
    for (int i=0; i<n_pages;i++){
        //Busca o valor da posi��o i na lista de quadros e salva no ponteiro
        if (busca_retorna(&coord_menos, i))
            tempo[coord_menos]=0;
        else {
            menos=0;
            //Verifica se todos os quadros foram preenchidos por um valor da sequencia e pega o maior
            if (i>=n_quadros){
                for (int j=0; j<n_quadros;j++){
                    if (tempo[j]>menos){
                        menos=tempo[j];
                        coord_menos=j;
                    }
                aux=j;
                }
            }
            //Se o maior tempo for zero, os demais tamb�m ser�o
            if (menos==0){
                coord_menos=aux++;
                if(coord_menos==n_quadros) coord_menos=0;
            }
            tempo[coord_menos]=0;
            mem_quadros[coord_menos]=seq_ref[i];
            faltas++;
        }
        //Incrementa os contadores de tempo se j for menor que faltas e numero de quadros
        for(int j=0; j<n_quadros && j<faltas; j++){
            tempo[j]++;
        }
    }
cout << "LRU " << faltas << endl;
}


int main()
{
    carrega_arquivo();
    inicia_quadros();
    FIFO();
    OTM();
    LRU();
    return 0;
}
