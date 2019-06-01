/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/
#ifndef LEIRUTORA_H
#define LEIRUTORA_H

typedef struct piloto Pi, *pPi;
typedef struct carro Car, *pCar;
typedef struct saverS sS, *psS;
typedef struct conbinacao Con, *pCon;

// saverS -é uma estrutura para guardar os ponteiros e valores para todas as
// variaveis importantes do programa, assim em vez de se passar todos os valores
// como argumentos passa se como uma unica estrutura para simplificar o numero
// de argumentos que as funçoes tem e poder se buscar o que seja necessario para
// cada função

struct saverS
{
  pPi pPilotos; // ponteiro para os pilotos
  int nPilotos; // numero de pilotos

  pCar pCarros; // ponteiro para os carros
  int nCarros;  // numero de carros
};

//faz a estrutura geral
psS makegeral(pPi pilotos, int npilotos, pCar carros, int ncarros);

// calcular idade
// indexpiloto- index de onde esta o piloto no array dos pilotos
int calIda(psS saveS, int indexpiloto);

//seleciona os Carros e os pilotos de forma aleatoria
pCon selCarPil(int nMaxP, psS saveS);

//apaga um membro da lista ligada combina(Con)
pCon delCon(pCon dels);

//gotohead vai para a cabeça(inicio) da lista
pCon gth(pCon combina);

//printa a posição de que os pilotos estao diacordo com a lista ligada
//espera - esta variavel só deve ser metida no final da corrida para fazer esperar e calcular o XP
void verPos(pCon combina, psS saveS, int voltastotal, int voltaact, int esperar);

//ordenar pelo tempo
pCon ordTem(pCon combina);

//função para limpar a memoria
void freecorr(pCon combina);

//muda a experiencia nos corredores
void calPontos(psS saveS, pCon combina);

//ordena as posicões nas estruturas
pCon novoord(psS saveS, pCon combina, int volta);

//substitui o "total" em todos os constintuintes da lista ligada "combina" pelo tempo total que fizeram ate a "volta" x
pCon totalde(pCon combina,int volta);

//algoritmo para ordenar(deve ser repetido quando returna 1 e acaba quando return 0)
int algord(pCon combina, psS saveS);

//troca 2 pilotos de lugar
int trocaPon(pCon *combina, pCon *aux, pCon *antaux);

//algoritmo da corrida
pCon fazercorrida(psS saveS, pCon combina, int voltas, int comp,int nMaxP);

#endif
