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

psS makegeral(pPi pilotos, int npilotos, pCar carros, int ncarros)
{
  psS saveS = malloc(sizeof(sS));
  if (saveS == NULL)
  {
    printf("Erro a allocar de memoria.\n");
    return NULL;
  }
  saveS->pPilotos = pilotos;
  saveS->nPilotos = npilotos;
  saveS->pCarros = carros;
  saveS->nCarros = ncarros;
  return saveS;
}

int calIda(psS saveS, int indexpiloto)
{

  // dia de nascimento;
  int ndia = saveS->pPilotos[indexpiloto].Dnas;
  int nmes = saveS->pPilotos[indexpiloto].Mnas;
  int nano = saveS->pPilotos[indexpiloto].Anas;

  // dia actual
  int adia, ames, aano, lixo;

  // obtem a data actual
  obtemData(&adia, &ames, &aano, &lixo, &lixo, &lixo);

  // diferença do dia de nascimento ao dia actual
  int ddia, dmes, dano;

  // calculo da idade
  if (adia < ndia)
  {
    if (aano % 4 == 0 && ames == 2)
    {
      adia += 29;
    }
    else if (ames == 2)
    {
      adia += 28;
    }
    else if (ames == 4 || ames == 6 || ames == 9 || ames == 11)
    {
      adia += 31;
    }
    else
    {
      adia += 30;
    }
    ames--;
    if (ames == 0)
    {
      ames = 12;
      aano--;
    }
  }
  ddia = adia - ndia;

  if (ames < nmes)
  {
    aano--;
    ames += 12;
  }

  dmes = ames - nmes;
  dano = aano - nano;
  int idade = dano;
  return idade;
}

pCon selCarPil(int nMaxP, psS saveS)
{
  /****************************************/

  /******ASSOCIAR CARROS E PILOTOS*******/

  // ncp - numero de carros possiveis de correr
  int ncp = 0;

  // npp - numero de pilotos possiveis de correr
  int npp = 0;

  // pcp - array das posicões dos carros possiveis de correr
  int *pcp = NULL;

  // ppp - array das posicões dos pilotos possiveis de correr
  int *ppp = NULL;

  // c -count / contar
  int c;

  for (c = 0; c < saveS->nCarros; c++)
  {
    // verficar se o carro esta avariado
    if (saveS->pCarros[c].avar == 0)
    {
      ncp++;
      if (c == 1)
        pcp = malloc(sizeof(int));
      else
        pcp = realloc(pcp, sizeof(int) * ncp);
      if (pcp == NULL)
      {
        printf("Falta de memoria.\n");
        return NULL;
      }
      pcp[ncp - 1] = c;
    }
    else
    {

      // se estiver avariado dizer qual
      printf("Este carro(Id=%d) está avariado.\n", saveS->pCarros[c].Id);
    }
  }

  // verifar se existem carros para correr
  if (ncp == 0)
  {
    fprintf(stderr, "Não existem carros possiveis de correr.\n");
    return NULL;
  }
  for (c = 0; c < saveS->nPilotos; c++)
  {
    // ver se não está impedido
    if (saveS->pPilotos[c].imp == 0)
    {
      npp++;
      if (c == 1)
        ppp = malloc(sizeof(int));
      else
        ppp = realloc(ppp, sizeof(int) * ncp);
      if (ppp == NULL)
      {
        printf("Falta de memoria.\n");
        return NULL;
      }
      ppp[npp - 1] = c;
    }
    else
    {
      // dizer o porque do piloto c não pode correr
      printf("Piloto %s(Id=%d) está impedido de correr.\n",
             saveS->pPilotos[c].nome, saveS->pPilotos[c].Id);
    }
  }

  // verifar se existem pilotos para correr
  if (npp == 0)
  {
    fprintf(stderr, "Não existem pilotos possiveis de correr.\n");
    return NULL;
  }

  if (npp < ncp)
    nMaxP = npp;
  else
    nMaxP = ncp;

  // ponteiro para a primeira estrutura da lista ligada das combinações dos
  // participantes
  pCon combina = NULL;
  int value, piloto = -1, carro = -1;
  for (c = 0; c < nMaxP; c++)
  {
    // buscar randow piloto
    do
    {
      value = intUniformRnd(0, npp - 1);
      if (ppp[value] == -1)
      {
        continue;
      }
      piloto = value;
      ppp[value] = -1;
      break;
    } while (ppp[value] == -1);
    // buscar randow carro
    do
    {
      // buscar um numero aleatorio
      value = intUniformRnd(0, npp - 1);
      if (pcp[value] == -1)
      {
        continue;
      }
      carro = value;
      pcp[value] = -1;
      break;
    } while (pcp[value] == -1);
    // printar resultados das combinações
    printf("Corredor %d:\n\tNome do piloto:%s\n\tId do carro:%d\n\n", c + 1,
           saveS->pPilotos[piloto].nome, saveS->pCarros[carro].Id);
    // gravar as coisas numa lista ligada
    printf("problemas a refazer o adicionaCon\n");
    combina = adicionaCon(combina, piloto, carro);
    printf(" NOPE\n");
    if (combina == NULL)
    {
      printf("fazer free\n");
      free(ppp);
      free(pcp);
      return NULL;
    }
  }
  printf("sem problemas a fazer return\n");
  return combina;
}

pCon delCon(pCon dels)
{
  pCon aux;

  if (dels->ant == NULL && dels->prox == NULL)
  {
    free(dels);
    return NULL;
  }
  else if (dels->ant == NULL)
  {
    aux = dels->prox;
    aux->ant = NULL;
    free(dels);
    return gth(aux);
  }
  else if (dels->prox == NULL)
  {
    dels->ant->prox == NULL;
    free(dels);
    return gth(aux);
  }
  else
  {
    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
    return gth(aux);
  }
}

pCon gth(pCon combina)
{
  while (combina->ant != NULL)
    combina = combina->ant;
  return combina;
}

void verPos(pCon combina, psS saveS, int voltastotal, int voltaact, int esperar)
{
  if (esperar == 1)
    printf("\n\tClassificação na volta %d\n", voltaact + 1);
  if (esperar == 0)
    printf("\n\tClassificação de todas as voltas\n");

  int spot = 0, i, total, pos = 0;
  char output[200];
  for (pCon aux = combina; aux != NULL; aux = aux->prox)
  {

    if (aux->tempo[voltaact] == -1)
      printf("%s (Id: %d) / Carro %d desistiu na volta %d.\n", saveS->pPilotos[aux->piloto].nome, saveS->pPilotos[aux->piloto].Id, saveS->pCarros[aux->carro].Id, aux->voltades + 1);

    if (aux->tempo[voltaact] != -1)
    {
      pos++;
      if (pos == 1)
        aux->gainexp += 0.5;
      sprintf(output, "%dº:%s (Id:%d)/Carro %d:", pos, saveS->pPilotos[aux->piloto].nome, saveS->pPilotos[aux->piloto].Id, saveS->pCarros[aux->carro].Id);
      total = 0;
      for (i = 0; i <= voltaact; i++)
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
  printf("\t-------------\n\n");
  if (esperar == 1)
    if (voltastotal != voltaact)
      printf("a esperar\n"); //espera(1);
}

pCon ordTem(pCon inicio)
{
  int i = 0, f = 0;
  if (inicio == NULL || inicio->prox == NULL)
    return inicio;

  // para ordenar aquele que esta em primeiro, mete se o que estiver em
  // primeiro na lista ligada
  // verficar se o segunte mais pequeno do que o actual
  pCon auxfinder, finder, paux;
  //andar para a direita
  for (auxfinder = inicio->prox; auxfinder->prox != NULL;
       auxfinder = auxfinder->prox)
  {

    if (auxfinder->total >
        auxfinder->prox->total)
    {
      // se n for começa a andar para tras a trocar
      for (finder = auxfinder; finder->ant != NULL; finder->ant)
        if (finder->total > finder->prox->total)
        {

          // ver se existe algo antes do finder
          if (finder->ant != NULL)
            finder->prox = finder->ant->prox;

          if (finder->prox->prox != NULL)
            finder->prox->prox->ant = finder;

          paux = finder->ant;
          finder->ant = finder->prox;
          finder->prox->ant = paux;

          paux = finder->ant->prox;
          finder->ant->prox = finder;
          finder->prox = paux;
          finder = finder->prox;
        }
    }
  }
  while (inicio->ant != NULL)
    inicio = inicio->ant;
  return inicio;
}

//novo orenador

void freecorr(pCon combina)
{
  pCon aux = combina, paux;

  while (aux != NULL)
  {

    paux = aux->prox;
    free(aux->tempo);
    free(aux);
    aux = paux;
  }
}

void calPontos(psS saveS, pCon combina)
{
  pCon aux;
  for (aux = combina; aux != NULL; aux = aux->prox)
  {
    if (aux->gainexp == -1)
      if (saveS->pPilotos[aux->piloto].exp < 1)
        saveS->pPilotos[aux->piloto].exp = 0;
      else
        saveS->pPilotos[aux->piloto].exp -= 1;
    else
      saveS->pPilotos[aux->piloto].exp += aux->gainexp;
  }
}

pCon novoord(psS saveS, pCon combina, int volta)
{
  pCon aux, antaux, paux;
  int renova;
  totalde(combina, volta);
  int loop = 0;
  //loop de reorganização
  for (int i = 0; i < 2; i++)
    while (loop == 1)
      loop = algord(combina, saveS);

  return combina;
}

pCon totalde(pCon combina, int volta)
{
  pCon aux;
  int i;
  for (aux = combina; aux != NULL; aux = aux->prox)
  {
    aux->total = 0;
    for (i = 0; i < volta; i++)
    {
      if (aux->tempo[i] != -1)
        aux->total += aux->tempo[i];
    }
  }
}

int algord(pCon combina, psS saveS)
{
  pCon aux, antaux;
  int renova = 0;
  for (aux = combina; aux->prox != NULL; aux = aux->prox)
  {
    if (aux->total = aux->prox->total)
      if (saveS->pCarros[aux->carro].pot > saveS->pCarros[aux->prox->carro].pot)
        renova = trocaPon(&combina, &aux, &antaux);
      else if (saveS->pCarros[aux->carro].pot = saveS->pCarros[aux->prox->carro].pot)
        if (saveS->pPilotos[aux->piloto].exp > saveS->pPilotos[aux->prox->piloto].exp)
          renova = trocaPon(&combina, &aux, &antaux);
        else if (aux->total > aux->prox->total)
          renova = trocaPon(&combina, &aux, &antaux);

    if (renova == 1)
      return 1;
    antaux = aux;
  }
  return 0;
}

int trocaPon(pCon *combina, pCon *aux, pCon *antaux)
{
  pCon paux;

  //verificar os casos do que pode estar no inicio
  if ((*aux) == (*combina))
    (*combina) = (*aux)->prox;
  else
    (*antaux)->prox = (*aux)->prox;

  //fazer o geral
  paux = (*aux)->prox;
  (*aux)->prox = (*aux)->prox->prox;
  paux->prox = (*aux);

  return 1;
}

pCon fazercorrida(psS saveS, pCon combina, int voltas, int comp, int nMaxP)
{

  pCon finder, finder2;
  int idade, ordenado = 0, *aux, i, ndes = 0;
  Car scarro;
  Pi spiloto;
  int prob, c;
  // loop de voltas
  for (c = 0; c < voltas; c++)
  {
    printf("volta %d\n", c + 1);
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
          return NULL;
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

  return combina;
}
