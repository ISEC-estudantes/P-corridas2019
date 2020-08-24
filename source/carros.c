/******************************/
/*          OnikenX           */
/******************************/

#include "carros.h"
#include "corrida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 100

int readCar(char *file, pCar *pCarros, int *nCarros) {
  FILE *f = fopen(file, "r");
  if (f == NULL) {
    printf("Erro a abrir ficheiro %s.\n", file);

    // erro 5 - erro a abrir o ficheiro
    return 5;
  }
  int ncarros = 0;
  int i;
  

  Car carro;


  while (fscanf(f, "%d %d %d", &carro.Id, &carro.pot, &carro.avar) == 3) {
    ncarros++;

  }

 

  if (ncarros <= 0) {
    printf("Não existem carros.\n");
    fclose(f);
    return 1;
  }

  int carId[ncarros];
  pCar carros = malloc(ncarros * sizeof(Car));

  if (carros == NULL) {
    printf("errro a acumolar memoria\n");
    fclose(f);
    return 1;
  }
  for (i = 0; i < ncarros; i++)
    carId[i] = -1;

  int erros = 0;
  int c = 0;
 

 
  rewind(f);
 
  while (fscanf(f, "%d %d %d", &carros[c].Id, &carros[c].pot,
                &carros[c].avar) == 3) {
    // verificar se os valores estao degitados como foram especificados
    erros = verificaCarro(carros[c], ncarros, carId);
    if (erros != 0) {
      fclose(f);
      return erros;
    }
    c++;
  }

  fclose(f);

  // passar variaveis para a main function
  *pCarros = carros;
  *nCarros = ncarros;

  return erros;
}

int verificaCarro(Car carro, int n, int carId[]) {
  int i = 0;
  while (carId[i] != -1 && i < n) {
    if (carId[i] == carro.Id) {
      printf("Erro: Id do carro já existe\n");
      // Erro 1 - o Id já existe, corrigir o problema no ficheiro de texto e
      // verificar o valor do Id
      return 1;
    }
    ++i;
  }
  if (i == n) {
    printf(
        "todos os ids estao ocupados, problemas a calcular o numero existente "
        "de pilotos, o codigo tem de ser revisto para a contagem de pilotos\n");
    // erro 6, erro a ler o numero de pilotos por razao que seja
    return 6;
  }
  carId[i] = carro.Id;

  return 0;
}

int salvaC(psS saveS) {
  FILE *f = fopen(CARROS, "wt");
 
  if (f == NULL) {
    printf("Erro a salvar o ficheiro.\n");
    fclose(f);
    return 1;
  }

  pCar carros = saveS->pCarros;
  int c;
  for (c = 0; c < (saveS->nCarros); c++)
    fprintf(f, "%d %d %d\n\n", carros[c].Id, carros[c].pot, carros[c].avar);

  fclose(f);

  return 0;
}




void printCar(psS saveS) {
  pCar carros = saveS->pCarros;
  int n = saveS->nCarros;
  printf("\n\n----Carros----\n\n");
  for (int i = 0; i < n; ++i)
    printf("%d %d %d\n\n", carros[i].Id, carros[i].pot, carros[i].avar);
  printf("--------------\n");
  printf("numero de carros » %d\n\n", n);
}

int carDis(psS saveS, int *max, int **carL) {
  int c, ncars = 0;
  int *diCars = NULL, *aux;

  pCar carros = saveS->pCarros;

  for (c = 0; c < saveS->nCarros; c++) {
    if (carros[0].avar = 0) {
      ncars++;
      aux = (int*)realloc(diCars, ((ncars) * sizeof(int)));
      if (aux == NULL)
        return 1;
      diCars = aux;
      diCars[ncars - 1] = c;
      if ((ncars) == *max)
        break;
    }
  }
  diCars[ncars]=-1;
  *max = ncars;
  *carL = diCars;
  return 0;
}

