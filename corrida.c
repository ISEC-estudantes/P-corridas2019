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

  int selec;
  if (npp < ncp)
    selec = npp;
  else
    selec = ncp;
  printf("npp %d ncp %d selec %d nmaxp %d\n", npp, ncp, selec, nMaxP);
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
    value = intUniformRnd(0, npp - 1);

    piloto = ppp[value];
    if (npp > 1)
    {
      for (i = value; i < npp - 1; i++)
        ppp[i] = ppp[i + 1];

      ppp = realloc(pcp, (npp - 1) * sizeof(int));
    }
    if (ppp == NULL)
    {
      free(ppp);
      free(pcp);
      printf("erro a alucar memoria.\n");
      return NULL;
    }
    npp--;

    // buscar randow carro
    // buscar um numero aleatorio
    value = intUniformRnd(0, ncp - 1);

    carro = pcp[value];
    if (ncp > 1)
    {
      for (i = value; i < ncp - 1; i++)
        pcp[i] = pcp[i + 1];

      pcp = realloc(pcp, (ncp - 1) * sizeof(int));
    }
    if (pcp == NULL)
    {
      free(ppp);
      free(pcp);
      printf("erro a alucar memoria.\n");
      return NULL;
    }
    ncp--;

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
      printf("O carro com Id %d não foi selecionado para a corrida nao ter vaga para correr.", saveS->pCarros[pcp[i]].Id);

  free(ppp);
  free(pcp);
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
        saveS->pPilotos[aux->piloto].exp -= 1;
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
  printf("ele entra aqui\n");
  pCon finder, finder2;
  int idade, ordenado = 0, *aux, i, ndes = 0;

  int prob, c;
  // loop de voltas
  for (c = 0; c < voltas; c++)
  {
    // loop para passar por todas as combinações
    for (finder = combina; finder != NULL; finder = finder->prox)
    {
      printf("isto é um loop\n");
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
        // printf("finder->des==%d de %s\n", finder->des,
        // saveS->pPilotos[finder->piloto].nome);
        prob = probEvento(ACIDENTE);
        if (prob == 1)
        {
          // printf("probablidade ficou a 1 para a combinação do piloto
          // %s\n",
          //        saveS->pPilotos[finder->piloto].nome);
          finder->des = 1;
          saveS->pPilotos[finder->piloto].imp = 3;
          saveS->pCarros[finder->carro].avar = 1;
          finder->gainexp = -1;
          if (saveS->pPilotos[finder->piloto].exp < 1)
            saveS->pPilotos[finder->piloto].exp = 0;
          else
          {
            saveS->pPilotos[finder->piloto].exp -= 1;
          }

          finder->voltades = c;
          ndes++;
        }
      }
      printf("ele saiu\n");
      if (ndes == nMaxP)
      {
        printf("Todos os pilotos tiveram acidentes!\n");
        break;
      }
      if (finder->des == 0)
      {
        finder->tempo[c] = calculaSegundos(finder->idade, saveS->pPilotos[finder->piloto].peso, saveS->pPilotos[finder->piloto].exp, saveS->pCarros[finder->carro].pot, comp);
        finder->total += finder->tempo[c];
      }
      if (finder->des == 1)
        finder->tempo[c] = -1;
    }
    //organiza a lista ligada
    //combina = ordTem(combina); antigo organizador
    printf("entrou no ord\n");
    combina = ordterm2(combina); //novo organizador
    printf("saiu do ord\n");
    if (ndes == nMaxP)
      break;

    //printa as posições
    verPos(combina, saveS, voltas, c, 1);
    if (part != NULL)
    {
    }
  }

  calPontos(saveS, combina);
  rempen(saveS);
  return combina;
}

pCon ordterm2(pCon combina)
{

  pCon paux, inicio = combina;
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
      inicio->ant = inicio->prox;
      inicio->prox = NULL;
      inicio->ant->ant = NULL;
      inicio->ant->prox = inicio;
      paux = inicio->ant;
      inicio = paux;
      return inicio;
    }

  // para ordenar aquele que esta em primeiro, mete se o que estiver em
  // primeiro na lista ligada
  // verficar se o segunte mais pequeno do que o actual

  pCon finder;
  //andar para a direita
  for (finder = inicio; finder != NULL;
       finder = finder->prox)
    //ve se o actual não esta a null só porque sim
    if (finder != NULL)
      // ve se o proximo esta a null para não morrer
      if (finder->prox != NULL)
        //compara os tempos
        if (finder->total > finder->prox->total)
          //entra num ciclo qu vai levar o finder(actual) para o inicio
          do
          {
            //compara outra vez para os casos dentro do loop a andar para tras e transportar o que tiver um menor numero
            if (finder->prox == NULL && finder->ant != NULL)
              finder = finder->ant;
            if (finder->total > finder->prox->total && finder->prox != NULL)
            {
              //se não for null vai pegar no anterior, pegar no seu ponteiro para o seguinte e trucar para o que esta a frente do actual
              if (finder->ant != NULL)
                finder->ant->prox = finder->prox;
              //auxiliar para não perdero que esta no anterior para depois substituir para o ponteiro a apontar para o anterior do finder para apontar para o que estava aseguinte
              paux = finder->ant;
              finder->ant = finder->prox;

              finder->ant->ant = paux;

              paux = finder->prox;
              finder->prox = paux->prox;
              if (paux->prox != NULL)
                paux->prox->ant = finder;

              paux->prox = finder;
              if (finder == inicio)
                inicio = paux;

              printf("loop lol\n");
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
      saveS->pPilotos[i].imp -= 1;
    }
  for (i = 0; i < saveS->nCarros; i++)
    if (saveS->pCarros[i].avar != 0)
    {
      saveS->pCarros[i].avar = 0;
    }
}
pCon ordterm(pCon combina)
{
  pCon next, last, center;

  for (center = combina; center->prox != NULL; center = center->prox)
  {
    if (center->total > center->prox->total)
    {
      printf("espaço giro\n");
    }
  }
}