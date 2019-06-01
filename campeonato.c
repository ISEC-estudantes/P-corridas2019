/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/

#include "leitura.h"
#include "carros.h"
#include "menus.h"
#include "pilotos.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

int campeonato(psS saveS)
{
  int corridas = 0, voltas-1, comp = -1, nMaxP = -1;

  printf("\n\tCAMPEONATO\n\n");
  while (corridas < 1)
  {
    printf("Quantas corridas serão o campeonato?[3-8](para sair prima 0)\n");
    if (scanf(" %d", corridas) != 1)
      scanf(" %*[^\n]");
  }

  while (voltas < 5 || voltas > 10)
  {
    printf("\nQuantas voltas tem a corrida?[5-10]\n=> ");

    if (scanf("%d", &voltas) != 1)
      scanf(" %*[^\n]");
  }
  while (comp < 500 || comp > 1000)
  {
    printf("\nQual o comprimento da pista?[500-1000]\n=> ");
    if (scanf("%d", &comp) != 1)
      scanf(" %*[^\n]");
  }
  while (nMaxP < 0)
  {
    printf("\nQuantos carros poderam correr nesta pista?\n=> ");
    if (scanf("%d", &nMaxP) != 1)
      scanf(" %*[^\n]");
  }

  corridamenu(saveS,voltas,comp,nMaxP)


}