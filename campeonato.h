
#ifndef CAMPEONATO_H
#define CAMPEONATO_H


typedef struct saverS sS, *psS;
typedef struct pilcam Cam, *pCam;

struct pilcam{

    int piloto;//index do piloto
    int nCorridas;//numero de corridas em que correu
    
    float pontos;//pontos acumulados
    
    int correr; //esta a correr, 1 se esta a correr na corrida actual ou 0 se não estiver a correr
    int acidente;//se ouve acidente durane a corrida
    float gainpts;//pontos ganhos numa corrida por volta

    pCam prox;//ponteiro para o anterior 
    pCam ant;//ponteiro para o seguinte
};


//função docampeonato
int campeonatomenu(psS saveS);

//corre para selecionar os participantes
pCam selectPil(psS saveS);

//o campeonato recebe como input o saveS(já explicado), part(a lista ligada os pilotos participantes),numdone(numero de corridas já corridas),numall(numero de todas as corridas), voltas por corrida, comprimento da pista, e quantos participantes podem correr
int campeonato(psS saveS, pCam part, int numdone, int numall, int voltas, int comp, int maxpart);

//meter os participantes no ficheiro binario
int gravaBi(pCam part, int numdone, int numall, int voltas, int comp, int maxpart);

//ler o ficheiro binario
int lerBi(psS saveS);
#endif