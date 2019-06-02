/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/

#ifndef MENUS_H
#define MENUS_H

#define ACIDENTE 0.05

typedef struct piloto Pi, *pPi;
typedef struct carro Car, *pCar;
typedef struct saverS sS, *psS;
typedef struct pilcam Cam, *pCam;


typedef struct conbinacao Con, *pCon;

struct conbinacao{
    //index de onde esta localizado o piloto na estrutura dos pilotos
    int piloto;

    //idade do piloto
    int idade;

    //index de onde esta localizado o carro na estrutura dos carros
    int carro;


    //segundos que o piloto demora a percorrer a cada voltal(ponteiro para array de inteiros)
    int *tempo;

    //tempo tomado para acavar a corrida
    int total;

    //regista se desistiu ou não da corrida
    int des;

    //volta de desistencia
    int voltades;

    //o ganho de experiencia durante a corrida
    float gainexp;

    //posição da combinação
    int pos;

    //ponteiro para proximo
    pCon prox;

    //ponteiro para anterior 
    pCon ant;
};


//menu principal do programa
int mainmenu(psS saveS);

//menu inicial para uma corrida
int corridamenu(psS saveS, int voltas, int comp, int MaxAll);

//adiciona uma estrutura na lista ligada de competidor de uma corrida
pCon adicionaCon(pCon inicio, int piloto, int carro);

//ajustar incrementa o numero de 


//menu para ver as pontuações ou sair
int menufinalcor(psS saveS, pCon combina, int nMaxP, int voltas);

//apaga as estruturas principais do saveS e das estruturas dos pilotos e carros
void freeall(psS saveS);

//ver as pontoações com detalhe
int vercorrida(psS saveS,pCon combina, int nMaxP, int voltas);

#endif


