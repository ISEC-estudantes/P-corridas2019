/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/
#include <stdio.h>
#include <stdlib.h>
#include "pilotos.h"
#include "carros.h"
#include "corrida.h"
#include "utils.h"
#include "menus.h"
#include "campeonato.h"

//funcção inicial do programa
psS inicializa()
{
  

  // ler ficheiros de texto dos pilotos e carros e guardar as suas variaveis
  //ler pilotos
  pPi pPilotos = NULL;
  int nPilotos = 0, erro = 0;
  erro = readPilotos(PILOTOS, &pPilotos, &nPilotos);
  if (erro != 0)
    return NULL;

  pCar pCarros;
  int nCarros;
  erro = readCar(CARROS, &pCarros, &nCarros);
  if (erro != 0)
  {
    free(pPilotos);
    return NULL;
  }

  //criar estrutura para gerir tudo
  psS saveS = makegeral(pPilotos, nPilotos, pCarros, nCarros);
  if (saveS == NULL)
  {
    free(pPilotos);
    free(pCarros);
    return NULL;
  }
  return saveS;
}


int main(int argc, char **argv)
{
  initRandom();
  psS saveS = inicializa();
  if (saveS == NULL)
    return 1;

  mainmenu(saveS);

  return 0;
}

