/******************************/
/*          OnikenX           */
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
  int c, i;

  for (c = 0; c < saveS->nCarros; c++)
  {
    // verficar se o carro esta avariado
    if (saveS->pCarros[c].avar == 0)
    {
      ncp++;
      if (ncp == 1)
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
      if (npp == 1)
        ppp = malloc(sizeof(int));
      else
        ppp = realloc(ppp, sizeof(int) * npp);
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

  int selec;
  if (npp < ncp)
    selec = npp;
  else
    selec = ncp;
  if (selec < nMaxP)
    nMaxP = selec;

  // ponteiro para a primeira estrutura da lista ligada das combinações dos
  // participantes
  pCon combina = NULL;
  int value, piloto = -1, carro = -1;
  for (c = 0; c < nMaxP; c++)
  {
    if (npp == 0 || ncp == 0)
      break;
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
      value = intUniformRnd(0, ncp - 1);
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
    combina = adicionaCon(combina, piloto, carro);
    if (combina == NULL)
    {

      free(ppp);
      free(pcp);

      return NULL;
    }
  }
  for (i = 0; i < npp; i++)
    if (ppp[i] != -1)
      printf("O piloto %s não foi selecionado para a corrida por nao ter vaga para correr.\n", saveS->pPilotos[ppp[i]].nome);

  for (i = 0; i < ncp; i++)
    if (pcp[i] != -1)
      printf("O carro com Id %d não foi selecionado para a corrida nao ter vaga para correr.\n", saveS->pCarros[pcp[i]].Id);
  free(pcp);
  free(ppp);

  return combina;
}

int *movete(int *array, int value, int max)
{
  for (int i = value; i < max - 1; i++)
    array[i] = array[i + 1];
  if (max - 1 < 1)
    return NULL;

  array = realloc(array, (max - 1) * sizeof(int));
  return array;
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
      printf("%s (Id: %d) / Carro %d desistiu na volta %d.\n", saveS->pPilotos[aux->piloto].nome, saveS->pPilotos[aux->piloto].Id, saveS->pCarros[aux->carro].Id, aux->voltades);

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

        if (aux->tempo[i] > -1)
          sprintf(output, "%s%d", output, aux->tempo[i]);
        total += aux->tempo[i];
      }

      sprintf(output, "%s = %d segundos", output, total);

      printf("%s\n", output);
    }
  }
  printf("\t-------------\n\n");
  if (esperar == 1)
    espera(5);
}

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

//isto na verdade define a experiencia ( ^ _ ^ ')
void calPontos(psS saveS, pCon combina)
{
  pCon aux;
  for (aux = combina; aux != NULL; aux = aux->prox)
  {
    if (aux->gainexp == -1)
      if (saveS->pPilotos[aux->piloto].exp < 1)
        saveS->pPilotos[aux->piloto].exp = 0;
      else
        saveS->pPilotos[aux->piloto].exp += -1;
    else
      saveS->pPilotos[aux->piloto].exp += aux->gainexp;
  }
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

pCon fazercorrida(psS saveS, pCon combina, int voltas, int comp, int nMaxP, pCam part)
{
  pCon finder, finder2;
  int idade, ordenado = 0, *aux, i, ndes = 0;
  if (part != NULL)
  {
    pCam camp = NULL;
  }

  int prob, c, erro;
  // loop de voltas
  for (c = 0; c < voltas; c++)
  {
    // loop para passar por todas as combinações
    for (finder = combina; finder != NULL; finder = finder->prox)
    {
      // estruturas dos carros e pilotos desta combinação

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

        prob = probEvento(ACIDENTE);
        if (prob == 1)
        {

          finder->des = 1;
          saveS->pPilotos[finder->piloto].imp = 3;
          saveS->pCarros[finder->carro].avar = 1;
          finder->gainexp = -1;
          if (part != NULL)
          {
            for (pCam camp; camp != NULL; camp->prox)
              if (camp->piloto == finder->piloto)
              {
                camp->acidente = 1;
              }
          }
          if (saveS->pPilotos[finder->piloto].exp < 1)
            saveS->pPilotos[finder->piloto].exp = 0;
          else
          {
            saveS->pPilotos[finder->piloto].exp = saveS->pPilotos[finder->piloto].exp - 1;
          }

          finder->voltades = c + 1;
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
        erro = 0;
        do
        {
          finder->tempo[c] = calculaSegundos(finder->idade, saveS->pPilotos[finder->piloto].peso, saveS->pPilotos[finder->piloto].exp, saveS->pCarros[finder->carro].pot, comp);
          erro++;
          if (erro == 3)
          {
            printf("algo está mal com os tempos\n"
                   "\targumentos:\n"
                   "finder->idade=%d\n saveS->pPilotos[finder->piloto].peso=%d\n saveS->pPilotos[finder->piloto].exp=%d\n saveS->pCarros[finder->carro].pot=%d\n comp=%d\n",
                   finder->idade, saveS->pPilotos[finder->piloto].peso, saveS->pPilotos[finder->piloto].exp, saveS->pCarros[finder->carro].pot, comp);

            return NULL;
          }
        } while (finder->tempo[c] < 0 || finder->tempo[c] > 1000);

        finder->total += finder->tempo[c];
      }
      if (finder->des == 1)
        finder->tempo[c] = -1;
    }
    //organiza a lista ligada
    //combina = ordTem(combina); antigo organizador
    combina = ordterm2(combina);
    if (ndes == nMaxP)
      break;
    //printa as posições
    verPos(combina, saveS, voltas, c, 1);
    if (part != NULL)
    {
      for (pCam camp = part; camp != NULL; camp = camp->prox)
        if (combina->piloto == part->piloto)
          part->pontos += 0.5;
    }
  }
  if (part != NULL)
  {
    for (pCam camp = part; camp != NULL; camp = camp->prox)
      if (part->acidente == 1)
        part->pontos = 0;
      else
        adicionapontos(combina, part);
  }

  calPontos(saveS, combina);
  rempen(saveS);

  return combina;
}

void adicionapontos(pCon combina, pCam part)
{
  int pontos = 5;
  for (pCon finder2 = combina; finder2 != NULL; finder2 = finder2->prox)
    for (pCam camp = part; camp != NULL; camp = camp->prox)
      if (combina->piloto == part->piloto && finder2->voltades == 0)
      {
        part->pontos += pontos--;
        if (pontos == 0)
          return;
      }
}

pCon ordterm2(pCon combina)
{
  pCon paux, inicio = combina;
  int num, *pnum;
  float flotua;
  pCon finder;
  //caso o inicio seja null ele retorna null
  if (inicio == NULL)
    return NULL;

  //caso o seja anterior seja null e o seguinte tambem para
  if (inicio->ant == NULL && inicio->prox == NULL)
    return inicio;

  //caso sejam so 2
  if (inicio->prox->prox == NULL)
    if (inicio->total > inicio->prox->total)
    {
      swap(inicio);
      return inicio;
    }

  // para ordenar aquele que esta em primeiro, mete se o que estiver em
  // primeiro na lista ligada
  // verficar se o segunte mais pequeno do que o actual

  //andar para a direita
  for (finder = inicio; finder->prox != NULL;
       finder = finder->prox)
    //ve se o actual não esta a null só porque sim
    // ve se o proximo esta a null para não morrer
    //compara os tempos
    if (finder->total > finder->prox->total)
      //entra num ciclo qu vai levar o finder(actual) para o inicio
      do
      {
        if (finder->total > finder->prox->total && finder->prox != NULL)
        {
          swap(finder);
        }
        //para que não ande para NULL
        if (finder->ant != NULL)
          finder = finder->ant;
      } while (finder->ant != NULL);

  return inicio;
}

void rempen(psS saveS)
{
  int i;
  for (i = 0; i < saveS->nPilotos; i++)
    if (saveS->pPilotos[i].imp != 0)
    {
      saveS->pPilotos[i].imp += -1;
    }

  for (i = 0; i < saveS->nCarros; i++)
    if (saveS->pCarros[i].avar != 0)
    {
      saveS->pCarros[i].avar = 0;
    }
}

pCon bubbleSort(pCon start)
{
  int swapped, i;
  pCon finder;
  pCon lptr = NULL;

  int num, *pnum;
  float flotua;

  /* Checking for empty list */
  if (start == NULL)
    return NULL;

  do
  {
    swapped = 0;
    finder = start;

    while (finder->prox != lptr)
    {
      if (finder->total > finder->prox->total)
      {
        num = finder->total;
        finder->total = finder->prox->total;
        finder->prox->total = num;

        num = finder->piloto;
        finder->piloto = finder->prox->piloto;
        finder->prox->piloto = num;

        num = finder->idade;
        finder->idade = finder->prox->idade;
        finder->prox->idade = num;

        num = finder->carro;
        finder->carro = finder->prox->carro;
        finder->prox->carro = num;

        pnum = finder->tempo;
        finder->tempo = finder->prox->tempo;
        finder->prox->tempo = pnum;

        num = finder->des;
        finder->des = finder->prox->des;
        finder->prox->des = num;

        num = finder->voltades;
        finder->voltades = finder->prox->voltades;
        finder->prox->voltades = num;

        flotua = finder->gainexp;
        finder->gainexp = finder->prox->gainexp;
        finder->prox->gainexp = flotua;

        num = finder->pos;
        finder->pos = finder->prox->pos;
        finder->prox->pos = num;

        swapped = 1;
      }
      finder = finder->prox;
    }
    lptr = finder;
  } while (swapped);
  return start;
}

void swap(pCon finder)
{

  int num, *pnum;
  float flotua;

  num = finder->total;
  finder->total = finder->prox->total;
  finder->prox->total = num;

  num = finder->piloto;
  finder->piloto = finder->prox->piloto;
  finder->prox->piloto = num;

  num = finder->idade;
  finder->idade = finder->prox->idade;
  finder->prox->idade = num;

  num = finder->carro;
  finder->carro = finder->prox->carro;
  finder->prox->carro = num;

  pnum = finder->tempo;
  finder->tempo = finder->prox->tempo;
  finder->prox->tempo = pnum;

  num = finder->des;
  finder->des = finder->prox->des;
  finder->prox->des = num;

  num = finder->voltades;
  finder->voltades = finder->prox->voltades;
  finder->prox->voltades = num;

  flotua = finder->gainexp;
  finder->gainexp = finder->prox->gainexp;
  finder->prox->gainexp = flotua;

  num = finder->pos;
  finder->pos = finder->prox->pos;
  finder->prox->pos = num;
}

void fixant(pCon start)
{
  pCon antaux;
  start->ant = NULL;
  antaux = NULL;
  for (pCon aux = start; aux != NULL; aux = aux->prox)
  {
    if (aux != NULL)
    {
      if (antaux != NULL)
        aux->ant = antaux;
      antaux = aux;
    }
  }
}