#ifndef CONJUNTO_H
#define CONJUNTO_H

//Classe que contém todos os pontos que se deseja cobrir e que podem virar facilidades
class Conjunto
{
    public:
        //Contrutor padrão
        Conjunto();

        //Destrutor virtual padrão
        virtual ~Conjunto();

        int coord_x;
        int coord_y;
        bool facilidade;
        bool visitado;
};

#endif // CONJUNTO_H
