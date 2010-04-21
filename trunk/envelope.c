#include "envelope.h"
#include "languages.h"

/* envelope.c - conjunto de fun��es envelopadoras */



FILE * Fopen(char *arg1, char *arg2){
/* Abre um arquivo. Em caso de erro, imprime mensagem de erro e finaliza
   a execu��o do programa */
     
     FILE *f;
     f = fopen(arg1, arg2);
     
     if(f == NULL) {
          fprintf(stderr, MSG_ERRO_ABERTURA_ARQUIVO);
          system("pause");
          exit (0);
     }
     
     return f;
     
} /* Fopen */


void * Malloc(int tamanho){
/* Aloca e retorna um espa�o de mem�ria de 'tamanho' bytes. Caso n�o haja
   mem�ria suficiente, imprime mensagem de erro e finaliza a execu��o do
   programa */
     
     void * ptr;
     ptr = malloc(tamanho);
     
     if(ptr == NULL) {
            fprintf(stderr, MSG_ERRO_MEMORIA);
            system("pause");
            exit (0);
     }
     
     return ptr;
     
} /* Malloc */
