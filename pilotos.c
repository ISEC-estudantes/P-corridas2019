/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/
#include <stdio.h>
#include <stdlib.h>
#include "pilotos.h"
#include "corrida.h"


int readPilotos(char *file, pPi *pPilotos, int *nPilotos) {
    FILE *f = fopen(file, "rt");
    //printf("opening file ...\n");

    //printf("verifing file ...\n");
    if (f == NULL) {
        printf("Erro a abrir ficheiro %s.\n", file);

        return 5;
    }
    int npilotos = 0;
    int i;

    // le o numer de paragrafos que existem e se pedido printa os paragrafos no
    // ecra
    //printf("File opened successively.\n\nReading file ...\n");
    Pi piloto;
    //printf("\n######### TEXT FILE - START ##########\n\n");
     while (fscanf(f," %99[^\n] %d %d %d %d %d %f %d", piloto.nome,
            &piloto.Id, &piloto.Dnas, &piloto.Mnas,
            &piloto.Anas, &piloto.peso, &piloto.exp,
            &piloto.imp) == 8){
            npilotos++;
          /*
            printf("%s\n%d %d %d %d %d %f %d\n\n", piloto.nome,
            piloto.Id, piloto.Dnas, piloto.Mnas,
            piloto.Anas, piloto.peso, piloto.exp,
            piloto.impedido);           
          */
        }

    //printf("######### TEXT FILE - END ###########\n\n");

    // calcula o numero de pilotos
    

    if (npilotos <= 0) {
        printf("Não existem carros.\n");
        fclose(f);
        return 1;
    }
  //  printf("numero de carros » %d\n", npilotos);
    int piId[npilotos];
    pPi pilotos = malloc(npilotos * sizeof (Pi));

    if (pilotos == NULL) {
        printf("errro a acumolar memoria\n");
        fclose(f);
        return 1;
    }

    for (i = 0; i < npilotos; i++)
        piId[i] = -1;

    int erros = 0;
    int c = 0;
    //printf("a verficar as variaveis...\n");

    // volta ao inicio do ficheiro
    rewind(f);

    while (fscanf(f, " %99[^\n] %d %d %d %d %d %f %d", pilotos[c].nome,
            &pilotos[c].Id, &pilotos[c].Dnas, &pilotos[c].Mnas,
            &pilotos[c].Anas, &pilotos[c].peso, &pilotos[c].exp,
            &pilotos[c].imp) == 8) {
              
        // verificar se os valores estao degitados como foram especificados
        erros = verificaPiloto(pilotos[c], npilotos, piId);
        if (erros != 0) {
            fclose(f);
            return erros;
        }
        
        c++;
    }
    
    //printf("ficheiro lido e variaveis verificadas com sucesso.\n");
    fclose(f);

    // passar variaveis para a main function
    *pPilotos = pilotos;
    *nPilotos = npilotos;

    return erros;
}

int verificaPiloto(Pi piloto, int n, int piId[]) {
    int i = 0;
    while (piId[i] != -1 && i < n) {

        i++;
        if (piId[i] == piloto.Id) {
            printf("Erro: Id do piloto %s já existe\n", piloto.nome);
            // Erro 1 - o Id já existe, corrigir o problema no ficheiro de texto e
            // verificar o valor do Id
            return 1;
        }
    }
    piId[i] = piloto.Id;

    // verficar data de aniversario
    if (piloto.Dnas > 28 && (piloto.Mnas == (2))) {
        printf("Erro: Data de nascimento impossivel.\n");
        return 2;
    }
    if (piloto.Dnas > 31 && (piloto.Mnas == 4 || piloto.Mnas == 6 ||
            piloto.Mnas == 9 || piloto.Mnas == 11)) {

        printf("Erro: Data de nascimento impossivel.\n");
        return 2;
    }
    if (piloto.Dnas > 30) {
        printf("Erro: Data de nascimento impossivel.\n");
        return 2;
    }
    if (piloto.Mnas > 12) {
        printf("Erro: Data de nascimento impossivel.\n");
        return 2;
    }

    // verficar caracteristicas do piloto
    if (piloto.exp < 0.0) {
        printf("Erro: Experiencia menor que 0\n");
        return 3;
    }

  //  printf("%s\n%d %d %d %d %d %f %d\n\n", piloto.nome, piloto.Id, piloto.Dnas,piloto.Mnas, piloto.Anas, piloto.peso, piloto.exp, piloto.impedido);
    return 0;
}


int salvaP(psS saveS) {
  FILE *f = fopen(PILOTOS, "wt");
//  printf("A Abrir Ficheiro...\n");
  if (f == NULL) {
    printf("Erro a salvar o ficheiro.\n");
    fclose(f);
    return 1;
  }
 // printf("ficheiro aberto com sucesso\n");
  pPi pilotos = saveS->pPilotos;
  int c;
  for (c = 0; c < (saveS->nPilotos); c++)
    fprintf(f,"%s\n%d %d %d %d %d %.2f %d\n\n", pilotos[c].nome, pilotos[c].Id,
            pilotos[c].Dnas, pilotos[c].Mnas, pilotos[c].Anas,
            pilotos[c].peso, pilotos[c].exp, pilotos[c].imp);

  fclose(f);
  return 0;
}


void printPi(psS saveS) {
    pPi pilotos = saveS->pPilotos;
    int n = saveS->nPilotos;    
  printf("\n\n----Pilotos----\n\n");
  for (int i = 0; i < n; ++i)
    printf("%s\n %d %d %d %d %d %.2f %d\n\n", pilotos[i].nome, pilotos[i].Id,
           pilotos[i].Dnas, pilotos[i].Mnas, pilotos[i].Anas, pilotos[i].peso,
           pilotos[i].exp, pilotos[i].imp);
  printf("---------------\n");
  printf("numero de pilotos » %d\n\n", n);
}
