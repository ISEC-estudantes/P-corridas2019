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

#define bin "campeonato.bin"

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

  campeonato(saveS, parti, 0, corridas, voltas, comp, nMaxP);

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

    aux->acidente = 0;
    aux->gainpts = 0;
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
  int erro;
  for (int i = numdone; i <= numall; i++)
  {
    combina = selCarPil(maxpart, saveS);
    printf("isto é um loop\n");
    if (combina == NULL)
    {
      printf("Falta de memoria no computador.\n");
      return -1;
    }
    printf("\n CARRIDA %d\n\n", i + 1);
    combina = fazercorrida(saveS, combina, voltas, comp, maxpart, part);
    freecorr(combina);

    erro = gravaBi(part, i, numall, voltas, comp, maxpart);
    if (erro != 0)
      return erro;
  }
  return 0;
}

int gravaBi(pCam part, int numdone, int numall, int voltas, int comp, int maxpart)
{
  FILE *f = fopen("campeonato.bin", "wb");
  if (f == NULL)
  {
    printf("Erro a ler ter permições de escrita no ficheiro campeonato.bin\n");
    return 1;
  }
  pCam aux;
  int n = 0;
  //numero de corridas feitas
  fwrite(&numdone, sizeof(int), 1, f);
  fwrite(&voltas, sizeof(int), 1, f);
  fwrite(&comp, sizeof(int), 1, f);
  fwrite(&maxpart, sizeof(int), 1, f);
  for (aux = part; aux != NULL; aux = aux->prox)
    n++;
  fwrite(&maxpart, sizeof(int), 1, f);
  for (aux = part; aux != NULL; aux = aux->prox)
  {
    fwrite(&aux->piloto, sizeof(int), 1, f);
    fwrite(&aux->nCorridas, sizeof(int), 1, f);
    fwrite(&aux->pontos, sizeof(float), 1, f);
  }
  return 0;
}

int lerBi(psS saveS)
{

  FILE *f = fopen("campeonato.bin", "rb");
  if (f == NULL)
  {

    printf("Erro a ler ter permições de escrita no ficheiro campeonato.bin\n");
    return 1;
  }
  pCam inicio = NULL, aux = NULL, antaux = NULL;

  int n = 0, i, gainpts, acidente, nCorridas, correr, pontos, piloto, numdone, voltas, comp, maxpart;
  //numero de corridas feitas
  if ((fread(&numdone, sizeof(int), 1, f) != 1) || (fread(&voltas, sizeof(int), 1, f) != 1) ||
      (fread(&comp, sizeof(int), 1, f) != 1) || (fread(&maxpart, sizeof(int), 1, f) != 1) ||
      (fread(&maxpart, sizeof(int), 1, f) != 1))
  {
    fprintf(stderr, "Erro a criar o ficheiro %s\n", bin);
    return -1;
  }
  for (i = 0; i < maxpart; i++)
  {
    if ((fread(&piloto, sizeof(int), 1, f) != 1) ||
        (fread(&nCorridas, sizeof(int), 1, f) != 1) ||
        (fread(&pontos, sizeof(float), 1, f)))
    {
      fprintf(stderr, "Erro a criar o ficheiro %s\n", bin);
      return -1;
    }

    aux = malloc(sizeof(Cam));
    if (aux == NULL)
    {
      printf("erro alocar memoria.\n");
      return 1;
    }

    aux->piloto = piloto;
    aux->nCorridas = nCorridas;
    aux->pontos = pontos;
    aux->correr = 0;
    aux->acidente = 0;
    aux->gainpts = 0;
    if (inicio == NULL)
      aux->ant = NULL;
    else
    {
      antaux->prox = aux;
      aux->ant = antaux;
    }
    aux->prox = NULL;
    antaux = aux;
  }
  return campeonato(saveS, inicio, numdone, voltas, voltas, comp, maxpart);
}
