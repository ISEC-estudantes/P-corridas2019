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
  int corridas = 0;

  printf("\n\tCAMPEONATO\n\n");
  while (corridas < 1)
  {
    printf("Quantas corridas serão o campeonato?[3-8](para sair prima 0)\n");
    if (scanf(" %d", corridas) != 1)
      scanf(" %*[^\n]");
  }
  


  
}