/******************************/
/* João Pedro Neves Gonçalves */
/* Nº 21280302                */
/******************************/

#ifndef PILOTOS_H
#define PILOTOS_H

#define PILOTOS "pilotos.txt"



typedef struct piloto Pi, *pPi;
typedef struct carro Car, *pCar;
typedef struct saverS sS, *psS;

// defenição do piloto
struct piloto {
  // identificação basica
  char nome[100]; // Sequência com tamanho máximo de 100 caracteres
  int Id; // valor inteiro positivo que deve ser único entre todos os pilotos

  // data de nascimento
  int Dnas; // dia de nascimento
  int Mnas; // mes de nascimento
  int Anas; // ano de nascimento

  // caracteristicas
  int peso; // peso do piloto;valor positivo
  float
      exp; // experiencia do piloto; valor real superior ou igual a 0.0.
           // Quando um novo piloto é criado, a sua experiência tem o valor 0.0
  int imp; // Impedimento: um piloto pode estar impedido de participar em
                // corridas devido a lesão ou penalização. Um piloto fica
                // magoado quando tem um acidente. Nessa altura deverá 1 ficar 2
                // corridas sem competir (podem ser corridas individuais ou
                // parte de campeonato).  Pode, além disso, ser castigado devido
                // a comportamento incorreto. A penalização varia entre 1 e 3
                // corridas sem competir
};




//le o os pilotos no ficheiro
int readPilotos(char *file, pPi *pPilotos, int *nPilotos) ;

//verifica os pilotos do ficheiro
int verificaPiloto(Pi piloto, int n, int piId[]);

//sala a struct de pilotos no ficheiro apropriado
int salvaP(psS saveS) ;

//printa a estrura inteira dos pilotos
void printPi(psS saveS);

#endif /* PILOTOS_H */

