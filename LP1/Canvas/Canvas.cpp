/*Primeiro trabalho da disciplina de Linguagem de Programacao 1
Aluno: Gabriel Goncalves Barreto dos Santos
*/




#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

class canvas
{
    private:
        int pixelsize[2];
        int tipo[100];
/*tipo 0=sem poligono tipo 2 = retangulo, tipo 3= circulo, tipo 4= triandulo, tipo 5 = hexagono */

    public:
    canvas (int x, int y)
    {
        pixelsize[0]=x;
        pixelsize[1]=y;
    }
    int gettipo (int i)
    {
       return tipo[i];
    }
    void settipo (int i,int x)
    {
        tipo[i]=x;
    }
       int altura ()
        {
           return pixelsize[0];
        }
        int largura ()
       {
            return pixelsize[1];
        }
        int retornapoligonos (int coord)
        {
            return tipo[coord];
        }
        void verpoligonos (int contador)
        {
            int retangulo=0, circulo=0, triangulo=0, hexagono=0;
            for (int i=0; i<contador;i++)
            {
                switch (tipo[i])
                {
                    case 2:
                        retangulo++;
                        break;
                    case 3:
                        circulo++;
                        break;
                    case 4:
                        triangulo++;
                        break;
                    case 5:
                        hexagono++;
                        break;
                }
            }

            cout << "Retangulos: " << retangulo <<endl;
            cout << "Circulos: " << circulo << endl;
            cout << "Triangulos: " << triangulo << endl;
            cout << "Hexagonos: " << hexagono << endl;

        }
};

class poligono
{
    private:
        int coordcentro [2];
        int Zindex;
        string cor;

    public:
        void setcentro (int x, int y)
        {
            coordcentro[0]=x;
            coordcentro[1]=y;
        }
        int centrox ()
        {
            return coordcentro[0];
        }
        int centroy ()
        {
            return coordcentro[1];
        }
        void setcor (string collor)
        {
            cor=collor;
        }
        void setZ (int z)
        {
            Zindex=z;
        }
        void retornarcentro (int *x ,int *y)
        {
            *x=coordcentro[0];
            *y=coordcentro[1];
        }
        string retornacor ()
        {
            return cor;
        }

};

class retangulo:public poligono
{
   private:
    int base, altura;

   public:
    retangulo ()
    {}
    int getaltura ()
    {
        return altura;
    }
    int getbase ()
    {
        return base;
    }
    void setbase (int x)
    {
        base=x;
    }
    void setaltura(int y)
    {
        altura=y;
    }
    int retornaarea ()
    {
        return base*altura;
    }

    int retornaperimetro ()
    {
        return (2*base)+(2*altura);
    }
};

class circulo:public poligono
{
    private:
        int raio;

    public:
        circulo ()
        {}
        int getraio()
        {
            return raio;
        }
        void setraio (int r)
        {
            raio=r;
        }
        int retornaarea ()
        {
        return raio*raio*3.14;
        }
        int retornaperimetro ()
        {
            return 2*3.14*raio;
        }

};

class triangulo:public poligono
{
    private:
        int base, altura;

    public:
        triangulo ()
        {}
        void setbase(int x)
        {
            base=x;
        }
        void setaltura (int y)
        {
            altura=y;
        }
        int getaltura ()
        {
            return altura;
        }
        int getbase ()
        {
            return base;
        }
        int retornaarea ()
        {
            return base*altura;
        }
        int retornaperimetro ()
        {
            return base*3;
        }

};

class hexagono:public poligono
{
    private:
        int lado;

    public:
        void setlado (int l)
        {
            lado=l;
        }
        int getlado ()
        {
            return lado;
        }
        int retornaarea ()
        {
            return (6*lado*lado*(sqrt(3)))/4;

        }
        int retornaperimetro ()
        {
            return lado*6;
        }
};

void infocanvas (canvas a,int x)
{
    int altura, largura;
    altura=a.altura();
    largura=a.largura();
    cout << "============================INFORMACOES DO CANVAS==============================="<<endl;
    cout << "ALTURA DO CANVAS: "<<altura << "\t\tLARGURA DO CANVAS: " << largura <<endl<<endl;
    a.verpoligonos(x);
    cout << "\n================================================================================"<<endl;
}

void inserirretangulo (retangulo *p, canvas t)
{
    int a, b, opcao, centrox, centroy, restoaltura, restobase;
    cout << "-------------------------------INSERIR RETANGULO--------------------------------"<<endl;
    cout << "Digite o comprimento base do retangulo: ";
    cin >> a;
    cout <<endl;
    do{
    if (a>=t.largura())
    {
        cout << "Grande demais, defina um tamanho menor para a base: ";
        cin >> a;
        cout<<endl;
    }
    }while(a>=t.largura());
    cout << "Digite a altura do retangulo: ";
    cin >> b;
    cout <<endl;
    do{
    if (b>=t.altura())
    {
        cout<<"Grande demais, defina um tamanho menor para a altura: ";
        cin >>b;
        cout<<endl;
    }
    }while(a>=t.altura());

    p->setbase(a);
    p->setaltura(b);
    cout <<"Quais as coordenadas do centro do retangulo? \n";
    cout<<"A coordenada x: ";
    cin>>centrox;
    cout<<endl;
    cout<<"A coordenada y: ";
    cin >>centroy;
    cout<<endl;
    do{
    restoaltura=t.altura()-p->getaltura()/2;
    restobase=t.largura()-p->getbase()/2;
    if ((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy)
    {
        cout<<"O retangulo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;


    }
    }while((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy);
    p->setcentro(centrox,centroy);
    cout << "Este poligono esta sobreposto a algum outro? 1=sim 2=nao ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao==1)
        {   int z;
            cout << "Esta sobreposto a quantos poligonos? ";
            cin >> z;
            cout<<endl;
            p->setZ(z);
            break;
        }
    else if (opcao==2)
        {
        p->setZ(0);
        break;
        }
    else {cout <<"OPCAO INVALIDA, DIGITE UMA OPCAO VALIDA!"<<endl; cin>>opcao; continue;}
    }while(opcao!=1&&opcao!=2);
    cout << "Qual a cor do poligono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------RETANGULO ADICIONADO COM SUCESSO--------------------------"<<endl;

}

void inserircirculo (circulo *p, canvas t)
{
    int r, centrox, centroy,opcao, restoraio1, restoraio2;
    string cor;
   cout << "--------------------------------INSERIR CIRCULO---------------------------------"<<endl;
    cout<<"Qual o comprimento do raio? ";
    cin>>r;
    cout<<endl;
    do{
    if(2*r>t.altura() || 2*r>t.altura())
    {
        cout << "O raio eh muito grande, digite um valor menor: ";
        cin>> r;
        cout<<endl;
    }
    }while(2*r>t.altura() || 2*r>t.altura());
    p->setraio(r);
    cout <<"Quais as coordenadas do centro do circulo? \n";
    cout<<"A coordenada x: ";
    cin>>centrox;
    cout<<endl;
    cout<<"A coordenada y: ";
    cin >>centroy;
    cout<<endl;
    do{
    restoraio1=t.altura()-p->getraio();
    restoraio2=t.largura()-p->getraio();
    if (p->getraio()>=centrox || p->getraio()>=centroy || restoraio1<=centrox || restoraio2<=centroy)
    {
        cout<<"O circulo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;
}
}while(p->getraio()>=centrox || p->getraio()>=centroy || restoraio1<=centrox || restoraio2<=centroy);
p->setcentro(centrox,centroy);
cout << "Este poligono esta sobreposto a algum outro? 1=sim 2=nao ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao==1)
        {   int z;
            cout << "Esta sobreposto a quantos poligonos? ";
            cin >> z;
            cout<<endl;
            p->setZ(z);
            break;
        }
    else if (opcao==2)
        {
        p->setZ(0);
        break;
        }
    else {cout <<"OPCAO INVALIDA, DIGITE UMA OPCAO VALIDA!"<<endl; cin>>opcao; continue;}
    }while(opcao!=1&&opcao!=2);
    cout << "Qual a cor do poligono? ";
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
     cout << "-----------------------CIRCULO ADICIONADO COM SUCESSO---------------------------"<<endl;
}

void inserirtriangulo (triangulo *p, canvas t)
{
    int a, b, opcao, centrox, centroy,restoaltura, restobase;;
     cout << "-------------------------------INSERIR TRIANGULO--------------------------------"<<endl;
    cout << "Digite a base do triangulo: ";
    cin >> a;
    cout <<endl;
    do{
    if (a>t.largura())
    {
        cout << "Grande demais, defina um tamanho menor para a base: ";
        cin >> a;
        cout<<endl;
    }
    }while(a>t.largura());
    cout << "Digite a altura do triangulo: ";
    cin >> b;
    cout <<endl;
    do{
    if (b>t.altura())
    {
        cout<<"Grande demais, defina um tamanho menor para a altura: ";
        cin >>b;
        cout<<endl;
    }
    }while(a>t.altura());

    p->setbase(a);
    p->setaltura(b);
    cout <<"Quais as coordenadas do centro do retangulo? \n";
    cout<<"A coordenada x: ";
    cin>>centrox;
    cout<<endl;
    cout<<"A coordenada y: ";
    cin >>centroy;
    cout<<endl;
    do{
    restoaltura=t.altura()-p->getaltura()/2;
    restobase=t.largura()-p->getbase()/2;
    if ((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy)
    {
        cout<<"O triangulo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;

    }
    }while((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy);
    p->setcentro(centrox,centroy);
    cout << "Este poligono esta sobreposto a algum outro? 1=sim 2=nao ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao==1)
        {   int z;
            cout << "Esta sobreposto a quantos poligonos? ";
            cin >> z;
            cout<<endl;
            p->setZ(z);
        }
    else if (opcao==2)
        {
        p->setZ(0);
        }
    else {cout <<"OPCAO INVALIDA, DIGITE UMA OPCAO VALIDA!"<<endl; cin>>opcao; continue;}
    }while(opcao!=1&&opcao!=2);
    cout << "Qual a cor do poligono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------TRIANGULO ADICIONADO COM SUCESSO-------------------------"<<endl;


}

void inserirhexagono (hexagono *p, canvas t)
{
    int l, opcao, centrox, centroy, restolado1, restolado2;
     cout << "-------------------------------INSERIR HEXAGONO---------------------------------"<<endl;
    cout << "Digite o comprimento de um dos lado do hexagono: ";
    cin >> l;
    cout <<endl;
    do{
    if ((l*2)>t.largura())
    {
        cout << "Grande demais, defina um comprimento menor para o lado: ";
        cin >> l;
        cout<<endl;
    }
    }while((l*2)>t.largura());
    p->setlado(l);

    cout <<"Quais as coordenadas do centro do hexagono? \n";
    cout<<"A coordenada x: ";
    cin>>centrox;
    cout<<endl;
    cout<<"A coordenada y: ";
    cin >>centroy;
    cout<<endl;
    do{
    restolado1=t.altura()-p->getlado();
    restolado2=t.largura()-p->getlado();
    if (p->getlado()>=centrox || p->getlado()>=centroy || restolado1<=centrox || restolado2<=centroy)
    {
        cout<<"O hexagono ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;

    }
    }while(p->getlado()>=centrox || p->getlado()>=centroy || restolado1<=centrox || restolado2<=centroy);
    p->setcentro(centrox,centroy);
    cout << "Este poligono esta sobreposto a algum outro? 1=sim 2=nao ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao==1)
        {   int z;
            cout << "Esta sobreposto a quantos poligonos? ";
            cin >> z;
            cout<<endl;
            p->setZ(z);
        }
    else if (opcao==2)
        {
        p->setZ(0);
        }
    else {cout <<"OPCAO INVALIDA, DIGITE UMA OPCAO VALIDA!"<<endl; cin>>opcao; continue;}
    }while(opcao!=1&&opcao!=2);
    cout << "Qual a cor do poligono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------HEXAGONO ADICIONADO COM SUCESSO------------------------"<<endl;

}

void infopoligono (retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{

    switch (p->gettipo(i))
    {
    case 0:
        break;
    case 2:
        cout<<"Retangulo\t"<<"Centro: "<<a->centrox()<<", "<<a->centroy()<<"\t"<<"Cor: "<<a->retornacor()<<"\t"<<"Area: "<<a->retornaarea()<<"\t"<<"Perimetro: "<<a->retornaperimetro()<<endl;
        break;
    case 3:
        cout<<"Circulo\t"<<"Centro: "<<b->centrox()<<", "<<b->centroy()<<"\t"<<"Cor: "<<b->retornacor()<<"\t"<<"Area: "<<b->retornaarea()<<"\t"<<"Perimetro: "<<b->retornaperimetro()<<endl;
        break;
    case 4:
        cout<<"Triangulo\t"<<"Centro: "<<c->centrox()<<", "<<c->centroy()<<"\t"<<"Cor: "<<c->retornacor()<<"\t"<<"Area: "<<c->retornaarea()<<"\t"<<"Perimetro: "<<c->retornaperimetro()<<endl;
        break;
    case 5:
        cout<<"Hexagono\t"<<"Centro: "<<d->centrox()<<", "<<d->centroy()<<"\t"<<"Cor: "<<d->retornacor()<<"\t"<<"Area: "<<d->retornaarea()<<"\t"<<"Perimetro: "<<d->retornaperimetro()<<endl;
        break;
    default: cout << "\n\nPoligono nao identificado!\n"<<endl;
    }
}

void excluirpoligono (retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{

    int opcao;
    if (p->gettipo(i)==2)
    {
        cout<<"Retangulo\t"<<"Centro: "<<a->centrox()<<", "<<a->centroy()<<"\t"<<"Cor: "<<a->retornacor()<<"\t"<<"Area: "<<a->retornaarea()<<"\t"<<"Perimetro: "<<a->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse poligono? 1=sim  2=nao   ";
        cin>>opcao;
        if (opcao==1) {p->settipo(i,0);}
    }
    else if (p->gettipo(i)==3)
    {
        cout<<"Circulo\t"<<"Centro: "<<b->centrox()<<", "<<b->centroy()<<"\t"<<"Cor: "<<b->retornacor()<<"\t"<<"Area: "<<b->retornaarea()<<"\t"<<"Perimetro: "<<b->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse poligono? 1=sim  2=nao   ";
        cin>>opcao;
        if (opcao==1) {p->settipo(i,0);}
    }
    else if (p->gettipo(i)==4)
    {
        cout<<"Triangulo\t"<<"Centro: "<<c->centrox()<<", "<<c->centroy()<<"\t"<<"Cor: "<<c->retornacor()<<"\t"<<"Area: "<<c->retornaarea()<<"\t"<<"Perimetro: "<<c->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse poligono? 1=sim  2=nao   ";
        cin>>opcao;
        if (opcao==1) {p->settipo(i,0);}
    }
    else if (p->gettipo(i)==5)
    {
        cout<<"Hexagono\t"<<"Centro: "<<d->centrox()<<", "<<d->centroy()<<"\t"<<"Cor: "<<d->retornacor()<<"\t"<<"Area: "<<d->retornaarea()<<"\t"<<"Perimetro: "<<d->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse poligono? 1=sim  2=nao   ";
        cin>>opcao;
        if (opcao==1) {p->settipo(i,0);}

    }


}

int somaarea (retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{
    switch (p->gettipo(i))
    {
    case 0:
        break;
    case 2:
        return a->retornaarea();
        break;
    case 3:
        return b->retornaarea();
        break;
    case 4:
        return c->retornaarea();
        break;
    case 5:
        return d->retornaarea();
        break;
}
}

int somaperimetro(retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{
    switch (p->gettipo(i))
    {
    case 0:
        break;
    case 2:
        return a->retornaperimetro();
        break;
    case 3:
        return b->retornaperimetro();
        break;
    case 4:
        return c->retornaperimetro();
        break;
    case 5:
        return d->retornaperimetro();
        break;
}
}

int main ()
{
    int opcao1, continuador;
    retangulo r[1000];
    circulo c[1000];
    triangulo t[1000];
    hexagono h[1000];
    do{
    system("cls");
    int contapoligonos=0, opcao;;
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XX                                                                            XX";
    cout << "XX   BEM VINDO AO CANVAS - PROGRAMA PARA CRIACAO E MANIPULACAO DE POLIGONOS   XX";
    cout << "XX                                                                            XX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" << endl;
    int x,y;
    cout<<"\n1. CONFIGURAR O CANVAS\t\t\t2.SAIR\n";
    do{
    cin>>opcao1;
    if (opcao1==1){
    cout << "================================================================================"<<endl;
    cout << "PARA COMECAR EH PRECISO CRIAR UM CANVAS (TELA) DE DESENHO PARA OS POLIGONOS,\nAPOS CRIADO O CANVAS O USUARIO TERA ACESSO AO MENU PRINCIPAL\n"<<endl;
    cout << "================================================================================"<<endl;
    cout << "DIGITE A ALTURA EM PIXELS DESEJADA PARA O CANVAS: ";
    cin >> x;
    cout <<endl;
    cout << "DIGITE A LARGURA EM PIXELS DESEJADA PARA O CANVAS: ";
    cin >> y;
    cout<<endl;
    }
    else if(opcao1==2){break;}
    else {cout <<"Opcao invalida! Digite uma opcao valida!\n"; continue; }
    }while(opcao1!=1 && opcao1!=2);
    canvas b (x, y);
    do{
    if (opcao1==2){break;}
    system("cls");
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XX                                                                            XX";
    cout << "XX   BEM VINDO AO CANVAS - PROGRAMA PARA CRIACAO E MANIPULACAO DE POLIGONOS   XX";
    cout << "XX                                                                            XX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" << endl;
    cout << "=================================MENU PRINCIPAL================================="<<endl;
    cout << "1. Exibir informacoes do Canvas\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "2. Inserir Retangulo\t\t\t";
    cout << "3. Inserir Circulo\n"<<endl;
    cout << "4. Inserir Triangulo\t\t\t";
    cout << "5. Inserir Hexagono\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "6. Listar Poligonos (com informacoes)\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "7. Excluir Poligono\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "8. Soma das areas dos poligonos do Canvas\n"<<endl;
    cout << "9. Soma dos perimetros dos poligonos do Canvas\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "10. Sair do Menu\n"<<endl;
    cout << "================================================================================"<<endl;
    do{
    if (opcao1==2){break;}
    cin >> opcao;
    if (opcao==1)
    {
        infocanvas(b,contapoligonos);
        system("pause");
        break;
    }
    if (opcao==2)
    {
        inserirretangulo(&r[contapoligonos],b);
        b.settipo(contapoligonos,opcao);
        contapoligonos++;
        system("pause");
        break;
    }
    else if (opcao==3)
    {
        inserircirculo(&c[contapoligonos],b);
        b.settipo(contapoligonos,opcao);
        contapoligonos++;
        system("pause");
        break;
    }
    else if (opcao==4)
    {
        inserirtriangulo(&t[contapoligonos],b);
        b.settipo(contapoligonos,opcao);
        contapoligonos++;
        system("pause");
        break;
    }
    else if (opcao==5)
    {
        inserirhexagono(&h[contapoligonos],b);
        b.settipo(contapoligonos,opcao);
        contapoligonos++;
        system("pause");
        break;
    }
    else if (opcao==6)
    {
        cout << "============================DETALHES DOS POLIGONOS=============================="<<endl;
        if (contapoligonos==0){cout<<"SEM INFORMACOES... ADICIONE PELO MENOS UM POLIGONO ANTES!\n"<<endl;}
        for(int i=0;i<contapoligonos;i++)
        {
            infopoligono(&r[i],&c[i],&t[i],&h[i],&b,i);
        }
    cout << "================================================================================"<<endl;
    system("pause");
    break;
    }
    else if (opcao==7)
    {
        cout << "=============================EXCLUIR DOS POLIGONOS=============================="<<endl;
        if (contapoligonos==0){cout<<"\nVOCE AINDA NAO ADICIONOU NENHUM POLIGONO\n\n";  cout << "================================================================================"<<endl; system("pause");  break;}
        cout << "Qual poligono de acordo com a ordem de insercao voce deseja excluir?"<<endl;
        cout<<"Voce possui "<<contapoligonos<<" poligonos adicionados.\n\n"<<endl;
        int e;
        cin>>e;
        excluirpoligono(&r[e-1],&c[e-1],&t[e-1],&h[e-1],&b,e-1);
        cout << "\n==============================EXCLUIDO COM SUCESSO============================="<<endl;
        system("pause");
        break;
    }
    else if(opcao==8)
    {
        int somadasareas=0;
        for(int i=0; i<contapoligonos;i++)
        {
            somadasareas+=somaarea(&r[i],&c[i],&t[i],&h[i],&b,i);
        }
    cout << "=========================SOMA DAS AREAS DOS POLIGONOS==========================="<<endl;
        cout << "A Soma das Areas dos poligonos contidos no Canvas eh: "<<somadasareas<<endl<<endl;
    cout << "================================================================================"<<endl;
        system("pause");
        break;
    }
    else if(opcao==9)
    {
        int somadosperimetros=0;
        for (int i=0; i<contapoligonos;i++)
        {
            somadosperimetros+=somaperimetro(&r[i],&c[i],&t[i],&h[i],&b,i);
        }
        cout << "=======================SOMA DOS PERIMETROS DOS POLIGONOS========================"<<endl;
        cout << "A Soma dos Perimetros dos poligonos contidos no Canvas eh: "<<somadosperimetros<<endl<<endl;
        cout << "================================================================================"<<endl;
        system("pause");
        break;
    }
    else if(opcao==10)
    {
        break;
    }
    else {cout<<"Opcao invalida! Digite uma opcao valida!\n"; continue;}
    }while(opcao!=10);
     if (opcao1==2){break;}
    }while(opcao!=10);
     if (opcao1==2){break;}
    }while (opcao1!=0);

}
