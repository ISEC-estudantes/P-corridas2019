/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/
#include "menus.h"
#include "carros.h"
#include "corrida.h"
#include "pilotos.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

int mainmenu(psS saveS)
{
  int escolha, erro = -1, help = 0;
  char test;
  do
  {

    printf("\n--------Main Menu--------\n"
           "Digite um numero para escolher(Mostrar opções-5)\n ");
    printf("\n=> ");

    // scanf da escolha
    escolha = -1;
    if (scanf(" %d", &escolha) != 1)
      scanf(" %*[^\n]");

    switch (escolha)
    {

    case 5:
      printf("\n---Opções---\n"
             "Mostras pilotos - 1\n"
             "Mostrar carros - 2\n"
             "Fazer Corrida - 3\n"
             "Fazer Campionato - 4\n"
             "Salvar e sair - 0\n"
             "-----------\n\n");
      break;
    case 1:
      printPi(saveS);
      break;
    case 2:
      printCar(saveS);
      break;

    case 3:
      //falta corrigir a parte do menu final e a parte de não amostrar aqueles pilotos e carros que estao disponiveis para correr mas não tinham vagas
      corridamenu(saveS, -1, -1, -1);
      break;

    case 4:
      campeonatomenu(saveS);
      break;

    case 0:
      printf("A salvar...\n");
      erro = salvaC(saveS);
      if (erro != 0)
      {
        printf("erro a salvar carros");
        return erro;
      }
      erro = -1;
      erro = salvaP(saveS);
      if (erro != 0)
      {
        printf("erro a salvar pilotos");
        return erro;
      }
      freeall(saveS);
      break;

    default:
      help++;
      if (help == 3)
      {
        printf("\nPara escolher digite o numero respectivo para a sua resposta e clique enter para continuar.\n\n");
        help = 0;
      }
      break;
    }
  } while (escolha != 0);

  return 0;
}

int corridamenu(psS saveS, int voltas, int comp, int MaxAll)
{

  /****OBETER VALORES********/

  int nMaxP = MaxAll, erro = -1;

  if (voltas == -1 && voltas == -1 && comp == -1)
  {
    // voltas -- voltas entre 5- 10
    // comp ---- comprimento da pista entre 500 - 1000
    // nCpart -- numero de maximo de carros que pode participar
    printf("\n---------- Corrida \\ treino ----------\n\n");
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
  }

  pCon combina = selCarPil(nMaxP, saveS);
  if (combina == NULL)
  {
    printf("Falta de memoria no computador.\n");
    return -1;
  }

  combina = fazercorrida(saveS, combina, voltas, comp, nMaxP, NULL);

  printf("\nA CORRIDA TERMINOU!\n");
  //menu para ver os tempos
  menufinalcor(saveS, combina, voltas, nMaxP);
  //limpar memoria dinamica
  freecorr(combina);

  return 0;
}

pCon adicionaCon(pCon inicio, int piloto, int carro)
{
  pCon aux = NULL;
  if (inicio == NULL)
  {
    aux = malloc(sizeof(Con));
    if (!aux)
    {
      printf("Falta de memoria.\n");
      return NULL;
    }

    // guardar indexes
    aux->piloto = piloto;
    aux->carro = carro;
    aux->tempo = NULL;
    aux->total = 0;
    aux->des = 0;
    aux->gainexp = 0;
    aux->ant = NULL;
    aux->prox = NULL;
    return aux;
  }
  aux = malloc(sizeof(Con));
  if (!aux)
  {
    printf("Falta de memoria.\n");
    return inicio;
  }
  pCon finder = inicio;
  while (finder->prox != NULL)
  {
    finder = finder->prox;
  }

  // guardar indexes
  aux->ant = finder;
  aux->prox = NULL;
  aux->piloto = piloto;
  aux->carro = carro;
  aux->des = 0;
  aux->gainexp = 0;
  finder->prox = aux;
  return inicio;
}

int menufinalcor(psS saveS, pCon combina, int nMaxP, int voltas)
{
  int escolha = -1, help = -1;
  while (escolha != 0)
  {

    printf("\nDeseja ver com detanhe a corrida(1), ver os pilotos e carros que correram(2) ou deseja ir para o menu principal(0)?\n=> ");
    if (scanf("%d", &escolha) != 1)
      scanf(" %*[^\n]");
    switch (escolha)
    {
    case 1:
      vercorrida(saveS, combina, nMaxP, voltas);
      break;

    case 0:
      return 0;
      break;

    case 2:
      printf("\n\tPilotos e carros que participaram:\n");
      for (pCon aux = combina; aux != NULL; aux = aux->prox)
        printf("O pilotx %s(Id=%d) correu com o carro %d.\n", saveS->pPilotos[aux->piloto].nome, saveS->pPilotos[aux->piloto].Id, saveS->pCarros[aux->carro].Id);
      printf("\n");
      break;

    default:
      help++;
      if (help == 3)
      {
        printf("\nPara escolher digite o numero respectivo para a sua resposta e clique enter para continuar.\n\n");
        help = 0;
      }
    }
  }
  return 0;
}

void freeall(psS saveS)
{
  free(saveS->pPilotos);
  free(saveS->pCarros);
  free(saveS);
}

int vercorrida(psS saveS, pCon combina, int nMaxP, int voltas)
{
  int escolha = -1, help = 0;
  while (escolha != 0)
  {
    pCon aux;
    int numero, i, total;
    char output[200];
    printf("\n\tVisualisação de Corrida com detanhe.\nDeseja ver uma volta com detalhe(1) ou a performance de um piloto(2)?(Para sair use 0)\n"
           "=> ");
    if (scanf("%d", &escolha) != 1)
      scanf(" %*[^\n]");

    switch (escolha)
    {
    case 1:
      verPos(combina, saveS, voltas, voltas, 0);
      break;
    case 2:
      do
      {
        printf("\nDigite o numero(Id) do piloto que quer ver o historico da corrida com detalhe, pode tambem digitar 0 para sair.\n=>");
        if (scanf(" %d", &numero) != 1)
          scanf(" %*[^\n]");
        if (numero < 0)
          printf("\nPor favor meta um numero posito para o Id ou 0 para sair.\n");
      } while (numero < 0);
      if (numero != 0)
        for (aux = combina; aux != NULL; aux = aux->prox)
        {
          if (saveS->pPilotos[aux->piloto].Id == numero)
          {
            sprintf(output, "\n%s (Id:%d)/Carro %d:", saveS->pPilotos[aux->piloto].nome, saveS->pPilotos[aux->piloto].Id, saveS->pCarros[aux->carro].Id);
            total = 0;
            for (i = 0; i <= voltas; i++)
            {

              if (i != 0)
                sprintf(output, "%s + ", output);

              sprintf(output, "%s%d", output, aux->tempo[i]);
              total += aux->tempo[i];
            }

            sprintf(output, "%s = %d segundos", output, total);

            printf("%s\n", output);
          }
        }
      break;
    case 3:
      break;

    case 0:
      break;

    default:
      help++;
      if (help == 3)
      {
        printf("\nPara escolher digite o numero respectivo para a sua resposta e clique enter para continuar.\n\n");
        help = 0;
      }
      break;
    }
  }
  return 0;
}
