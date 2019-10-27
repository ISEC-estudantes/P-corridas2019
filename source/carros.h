/******************************/
/*          OnikenX           */
/******************************/

#ifndef CARROS_H
#define CARROS_H

#define CARROS "carros.txt"

typedef struct carro Car, *pCar;
typedef struct saverS sS, *psS;


typedef struct piloto Pi, *pPi;
// defenição do carro
struct carro {
  int Id;  // id do carro;valor inteiro positivo que deve ser único entre todos
           // os carros
           
  int pot; // potencia do carro; valor inteiro positivo

  int avar; // se o carro estiver variado 1, se nao 0; um carro pode ou não
            // estar avariado. Um carro fica avariado quando está envolvido num
            // acidente. Depois disso fica 1 corrida sem poder participar
};



//le o ficheiro dos carros e mete los numa estrutura
int readCar(char *file, pCar *pCarros, int *nCarros);

//verifica os valoros na estrutura dos carros
int verificaCarro(Car carro, int n, int carId[]);

//salva a estrutura num ficheiro apropriado
int salvaC(psS saveS);

//printa a estrura inteira dos carros
void printCar(psS saveS) ;

#endif /* CARROS_H */

