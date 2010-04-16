#include <stdio.h>
#include <stdlib.h>

/* envelope.h - conjunto de fun��es envelopadoras */



typedef enum {false, true} Boolean;


FILE * Fopen(char *arg1, char *arg2);
/* Abre um arquivo. Em caso de erro, imprime mensagem de erro e finaliza
   a execu��o do programa */

void * Malloc(int tamanho);
/* Aloca e retorna um espa�o de mem�ria de 'tamanho' bytes. Caso n�o haja
   mem�ria suficiente, imprime mensagem de erro e finaliza a execu��o do
   programa */
