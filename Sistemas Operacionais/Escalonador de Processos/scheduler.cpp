#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/**Vetores Globais para carregamento dos dados dos processos*/
vector <int> t_chegada;
vector <int> t_duracao;


/**Fun��o para carregar o arquivo no vetor */
void carrega_arquivo(){
    ifstream infile ("input.txt");
    int a, b;
    while (infile >> a >> b){
        t_chegada.push_back(a);
        t_duracao.push_back(b);
    }
}


/** FCFS
    1)Define os vetores e vari�veis acumuladoras
    2)Define o inicio do primeiro processo = ao seu tempo de chegada
    3) O tempo de in�cio de cada processo � calculado (tempo de inicio do anterior + dura��o)
    4) Calcula a espera (tempo de chegada - tempo de inicio)
    5) Calcula o retorno (tempo de in�cio do pr�ximo - chegada)
    6) Calcula e exibe a m�dia dos tempos
*/
void FCFS (){
    int aux = t_chegada.size();
    int t_inicio [aux];
    int t_espera [aux];
    int t_retorno [aux];

    float m_espera = 0;
    float m_retorno = 0;

    t_inicio[0] = t_chegada [0];
    for (int i=0; i < aux; i++){
            t_inicio[i+1] = t_inicio[i] + t_duracao[i];
            t_espera [i] = t_inicio[i] - t_chegada[i];
            m_espera += t_espera[i];
            t_retorno[i] = t_inicio[i+1] - t_chegada[i];
            m_retorno += t_retorno[i];
    }

    m_espera = m_espera/aux;
    m_retorno = m_retorno/aux;

    cout.unsetf (ios::floatfield);
    cout.precision(3);
    cout << "FCFS " << m_retorno << " " << m_espera << " " << m_espera << endl;
}


/**SJF
    1) Ordena fila de processos do menor para o maior e verifica se a ordem ficou correta
    2) Verifica se a fila de processos n�o est� vazia e se os processos em execu��o j� atingiram o tempo esperado
    3) Verifica se os processos em execu��o foram conclu�dos
    4) Calcula os tempos e exibe
*/
void SJF (){
    int aux = t_chegada.size();
    int fila [aux], t_inicio[aux], t_fim[aux];
    int tempo = 0, toRun = 0, Running = -1;
    float m_retorno = 0, m_resposta = 0;

    for (int i = 0; i < aux; i++){
        fila[i] = -1;
        t_fim[i] = -1;
        t_inicio[i] = -1;
    }

    while (toRun >= 0){
        for (int i=0; i < aux; i++){
            if(t_chegada[i]==tempo){
                fila[toRun] = i;
                for (int j=0; j < toRun; j++){
                    if (t_duracao[fila[j]] > t_duracao[i]){
                        for (int k = toRun; k>j; k--){
                            fila[k] = fila [k-1];
                        }
                        fila [j] = i;
                        break;

                    }
                }
                toRun++;
            }
        }


        if ((Running == -1 && fila[0] != -1) || ((tempo - t_inicio[Running]) == t_duracao[Running])){
            if (Running != -1){
                t_fim[Running] = tempo;
            }
            Running=fila[0];
            for (int i=0; i<toRun; i++){
                fila[i] = fila[i+1];
            }
            if (Running != -1){
                fila[toRun] = -1;
            }
            toRun--;
            t_inicio[Running] = tempo;
        }
        tempo++;
    }
for (int i=0; i<aux; i++){
    m_retorno += t_fim[i] - t_chegada[i];
    m_resposta += t_inicio[i] - t_chegada[i];
}

m_retorno = m_retorno/aux;
m_resposta = m_resposta/aux;
cout << "SJF " << m_retorno << " " << m_resposta << " " << m_resposta << endl;

}

/**Round Robin
    1) O quantum foi definido como 2 no in�cio da fun��o como foi pedido
    2) Define a fila e as vari�veis de execu��o
    3) O primeiro for reseta as vari�veis
    4) Depois ordena a fila
    5) Verifica se h� processos em execu��o e incrementa o tempo
    6) Verifica se o processoa atual atingiu tempo limite
    7) Verifica se os processos atingiram o limite quantum e/ou foram finalizados
    8) Se terminar antes do quantum, guarda tempo do t�rmino do processo, caso n�o tenha terminado, move para o fim da fila
    9) Calcula os tempos e exibe.
*/
void RR()
{
    int quantum = 2;
    int aux = t_chegada.size();
    int fila[aux], t_inicio[aux], t_fim[aux];
    int t_run[aux];
    int i, tempo = 0, c_running = 0, running = -1, t_espera[aux], fim = 0;
    float m_retorno = 0, m_resposta = 0, m_espera = 0;

    for (i = 0; i < aux; i++){
		fila[i] = -1;
		t_run[i] = 0;
		t_espera[i] = 0;
		t_fim[i] = -1;
		t_inicio[i] = -1;
	}
	while (running != 0){
		for (i = 0; i < aux; i++){
			if (t_chegada[i] == tempo)
			{
                if (running == -1)
                {
                        t_inicio[i] = tempo;
                        running++;
                }
                fila[running] = i;
                running++;
			}
		}
		if (tempo != t_chegada[0] || fila[0] == -1)
		{
			if (t_inicio[fila[0]] != -1 && t_fim[fila[0]] == -1)
				t_run[fila[0]]++;
		}
		if (t_run[fila[0]] == t_duracao[fila[0]])
            fim = 1;
		if (fim || c_running == quantum)
		{
			c_running = 0;
			int wait = 0;
			if (!fim) wait = fila[0];
			else
			{
				t_fim[fila[0]] = tempo;
				for (i = 0; i < aux; i++)
				{
					if (i != fila[0]) t_espera[fila[0]] += t_run[i];
				}
			}
			for (i = 0; i < running - 1; i++)
				fila[i] = fila[i + 1];
            if (!fim) fila[running - 1] = wait;
			else {
				fila[running - 1] = -1;
				running--;
			}
			if (t_inicio[fila[0]] == -1)
				t_inicio[fila[0]] = tempo;
			fim = 0;
        }
        if (fila[0] != -1)
            c_running++;
        tempo++;
    }
    for (i = 0; i < aux; i++)
    {
        m_retorno += t_fim[i] - t_chegada[i];
        m_resposta += t_inicio[i] - t_chegada[i];
        m_espera += t_espera[i] - t_chegada[i] + t_chegada[0];
    }

    m_retorno = m_retorno / aux;
    m_resposta = m_resposta / aux;
    m_espera = m_espera / aux;
    cout << "RR " << m_retorno << " " << m_resposta << " " << m_espera << endl;
}



int main()
{
    carrega_arquivo();
    FCFS();
    SJF();
    RR();
    return 0;
}
