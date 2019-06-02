/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/

#include "corrida.h"
#include "carros.h"
#include "menus.h"
#include "pilotos.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

int campeonatomenu(psS saveS)
{

  int corridas = 0, voltas = -1, comp = -1, nMaxP = -1;

  printf("\n\tCAMPEONATO\n\n");
  do
  {
    printf("Quantas corridas serão o campeonato?[3-8](para sair prima 0)\n=> ");
    if (scanf(" %d", &corridas) != 1)
      scanf(" %*[^\n]");
  } while ((corridas < 3 || corridas > 8) && corridas != 0);
  if (corridas == 0)
    return 0;

  do
  {
    printf("\nQuantas voltas tem a corrida?[5-10]\n=> ");

    if (scanf("%d", &voltas) != 1)
      scanf(" %*[^\n]");
  } while (voltas != 0 && (voltas < 5 || voltas > 10));
  if (voltas == 0)
    return 0;

  do
  {
    printf("\nQual o comprimento da pista?[500-1000]\n=> ");
    if (scanf("%d", &comp) != 1)
      scanf(" %*[^\n]");
  } while (comp != 0 && (comp < 500 || comp > 1000));
  if (comp == 0)
    return 0;

  do
  {
    printf("\nQuantos carros poderam correr nesta pista?\n=> ");
    if (scanf("%d", &nMaxP) != 1)
      scanf(" %*[^\n]");
  } while (nMaxP < 0);
  if (nMaxP == 0)
    return 0;

  //cria uma lista ligada para os registos dos pilotos para o campeonato
  pCam parti = selectPil(saveS);

  campeonato(saveS, parti, 0, corridas,voltas,comp,nMaxP);

  return 0;
}

pCam selectPil(psS saveS)
{
  //neste campeonato esta como predefenido que todos os pilotos entram e que dependendo se eles estao disponiveis ou não é que correm

  pCam ant = NULL, aux = NULL, inicio = NULL;
  for (int i = 0; i < saveS->nPilotos; i++)
  {

    aux = malloc(sizeof(Cam));
    if (!aux)
    {
      printf("Falta de memoria.\n");
      return NULL;
    }

    // guardar indexes
    aux->piloto = i;
    aux->nCorridas = 0;
    aux->pontos = 0;
    //verificar se já foi criado um elemento
    if (inicio == NULL)
    {
      aux->ant = NULL;
      inicio = aux;
      ant = aux;
    }
    else
    {
      ant->prox = aux;
      ant = aux;
      aux->ant = ant;
    }
    aux->prox = NULL;
  }
  return inicio;
}

int campeonato(psS saveS, pCam part, int numdone, int numall, int voltas, int comp, int maxpart)
{
  pCon combina;
  for (int i = numdone; i < numall; i++)
  {
    combina = selCarPil(maxpart, saveS);
    printf("isto é um loop\n");
    if (combina == NULL)
    {
      printf("Falta de memoria no computador.\n");
      return -1;
    }
    
    combina = fazercorrida(saveS, combina, voltas, comp, maxpart, part);
    
    freecorr(combina);
  }
}
