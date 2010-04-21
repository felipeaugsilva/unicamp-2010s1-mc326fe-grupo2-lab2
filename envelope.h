/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/

/* envelope.h - conjunto de fun��es envelopadoras */

#include <stdio.h>
#include <stdlib.h>



FILE * Fopen(char *arg1, char *arg2);
/* Abre um arquivo. Em caso de erro, imprime mensagem de erro e finaliza
   a execu��o do programa */

void * Malloc(int tamanho);
/* Aloca e retorna um espa�o de mem�ria de 'tamanho' bytes. Caso n�o haja
   mem�ria suficiente, imprime mensagem de erro e finaliza a execu��o do
   programa */
