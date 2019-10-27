// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2018-2019

/******************************/
/*          OnikenX           */
/******************************/


#ifndef UTILS_H
#define UTILS_H

#define min(A,B)    ((A)<(B)?(A):(B))
#define max(A,B)    ((A)>(B)?(A):(B))

// Inicializa o gerador de numeros aleatorios. 
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

// Demora aproximadamente seg segundos a executar
void espera(unsigned int seg);

// Obtem e devolve o dia e hora atuais 
void obtemData(int *dia, int *mes, int *ano, int *h, int *m, int *s);

// Calcula e devolve o numero de segundos por volta 
// de acordo com as informacoes recebidas por parametro
int calculaSegundos(int idadeP, int pesoP, float expP, int PotC, int metros);

#endif /* UTILS_H */

