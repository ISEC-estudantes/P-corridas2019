/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/
#include "menus.h"
#include "carros.h"
#include "leitura.h"
#include "pilotos.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mainmenu(psS saveS)
{
  int escolha, erro = -1, help = 0;
  char test;
  do
  {

    printf("--------Main Menu--------\n"
           "Digite um numero para escolher(Mostrar opções-5)\n ");
    printf("\n=> ");

    // scanf da escolha
    escolha = -1;
    if (scanf(" %d", &escolha) != 1)
      scanf(" %*[^\n]");

    /*

       if (escolha > 4 || escolha < 0)
         printf("Escolha um numero entre 0 e 4\n=> ");

     */
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
      // place holder
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
  /*
  voltas = 5;
  comp = 500;
  nMaxP = 3;*/
  // cerificar o numero de carros e pilotos
  // nMaxP - numero maximo de participantes posiveis seja pelo numero limitado
  // de carro ou pilotos
  if ((nMaxP > saveS->nPilotos) || (nMaxP > saveS->nCarros))
  {
    if (saveS->nPilotos < saveS->nCarros)
      nMaxP = saveS->nPilotos;
    else
      nMaxP = saveS->nCarros;
  }

  pCon combina = selCarPil(nMaxP, saveS);
  if (combina==NULL)
  {
    printf("Falta de memoria no computador.\n");
    return -1;
  }
  pCon finder, finder2;
  int idade, ordenado = 0, *aux, i, ndes = 0;
  Car scarro;
  Pi spiloto;
  int prob, c;
  // loop de voltas
  for (c = 0; c < voltas; c++)
  {
    printf("volta %d\n", c+1);
    // loop para passar por todas as combinações
    for (finder = combina; finder != NULL; finder = finder->prox)
    {
      // estruturas dos carros e pilotos desta combinação
      spiloto = saveS->pPilotos[finder->piloto];
      scarro = saveS->pCarros[finder->carro];

      // criar vetor dos resultdos das voltas
      if (c == 0)
      {
        finder->idade = calIda(saveS, finder->piloto);
        aux = malloc(sizeof(int) * voltas);
        if (!aux)
        {
          printf("Erro na alocação de memoria.\n");
          return -1;
        }
        finder->tempo = aux;
        // limpar o array de tempos para 0
        for (i = 0; i < voltas; i++)
          finder->tempo[i] = 0;
      }
      // verificar a probablidade de haver acidente caso n tennha desistido
      if (finder->des == 0)
      {
        // printf("finder->des==%d de %s\n", finder->des,
        // saveS->pPilotos[finder->piloto].nome);
        prob = probEvento(ACIDENTE);
        if (prob == 1)
        {
          // printf("probablidade ficou a 1 para a combinação do piloto
          // %s\n",
          //        saveS->pPilotos[finder->piloto].nome);
          finder->des = 1;
          spiloto.imp = 2;
          scarro.avar = 1;
          finder->gainexp = -1;
          if (spiloto.exp < 1)
            spiloto.exp = 0;
          else
          {
            spiloto.exp -= 1;
          }

          finder->voltades = c;
          ndes++;
        }
      }
      if (ndes == nMaxP)
      {
        printf("Todos os pilotos tiveram acidentes!\n");
        break;
      }
      if (finder->des == 0)
      {
        finder->tempo[c] = calculaSegundos(finder->idade, spiloto.peso,
                                           spiloto.exp, scarro.pot, comp);
        finder->total += finder->tempo[c];
      }
      if (finder->des == 1)
        finder->tempo[c] = -1;
    }
    printf("ordenar as merdas\n");
    //organiza a lista ligada
    //combina = ordTem(combina); antigo organizador
    combina = novoord(saveS, combina, c); //novo organizador
    printf("nope\n");
    if (ndes == nMaxP)
      break;          
                      
    //printa as posições
    verPos(combina, saveS, voltas, c, 1);

  }

  calPontos(saveS, combina);
  printf("\nA CORRIDA TERMINOU!\n");
  //menu para ver os tempos
  menufinalcor(saveS, combina, voltas, nMaxP);
  printf("test\n");
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
  int escolha = 0, help = 0;
  while (escolha != 2)
  {
    printf("Deseja ver com detanhe a corrida(1), ver os pilotos e carros que correram(2) ou deseja ir para o menu principal(0)?\n=>");
    if (scanf(" %d", escolha) != 1)
      scanf(" %*[^\n]");
    switch (escolha)
    {
    case 1:
      vercorrida(saveS, combina, nMaxP, voltas);
      break;

    case 0:
      printf("a returnar");
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
      break;
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
  int escolha = 0, sair, help = 0;
  while (escolha == 0)
  {
    printf("\n\tVisualisação de Corrida com detanhe.\nDeseja ver uma volta com detalhe(1) ou a performance de um piloto(2)?(Para sair use 0)\n");
    if (scanf(" %d", escolha) != 1)
      scanf(" %*[^\n]");

    switch (escolha)
    {
    case 1:
      verPos(combina, saveS, voltas, voltas, 0);
      break;
    case 2:

      printf("Digite o numero do piloto que quer ver o historico da corrida com detalhe, pode tambem digitar 0 para sair.\n");
      if (scanf(" %d", escolha) != 1)
        scanf(" %*[^\n]", escolha);

      switch (escolha)
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
