/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laborat�rio    02A - Programa para leitura de dados de arquivo em formato  */
/*                      de campo fixo, convers�o para formato delimitado e    */
/*                      impress�o nos dois formatos                           */
/******************************************************************************/
/*
   1a vers�o de principal.c
   N�o implementa menus, apenas executa em sequencia 
   as tarefas das op��es 1, 2 e 3
   Para testes
              */
              
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "languages.h"
#include "envelope.h"

/* o programa recebe os nomes dos arquivos de entrada e sa�da */
#define QTE_ARGUMENTOS 3


void Erro(char * msgErro) {
     printf("%s\n",msgErro); 
     system("pause");
     exit(0);
}


int main(int argc, char *argv[]) {
    /* vari�veis */
    char lingua[5];
    char separador;
    char fimRegistro;
    FILE* arqFix, * arqDlm, * arqCfg;
    char* delim;
    Header* head;
    int i, numcampos;
    Record registro;
    
    /* checa linha de comando */
    if(argc != QTE_ARGUMENTOS)
       Erro(MSG_ERRO_NUM_ARGUMENTOS);

    /* arquivo de configura��o */
    if(!LeConfig(&separador, lingua))
       Erro(MSG_ERRO_CONFIG); 

    /* defini��o da lingua de interface */
    Linguagem(lingua);

    /* abertura dos arquivos */
    arqFix = Fopen(argv[1], "r");
    arqCfg = Fopen("header.cfg", "r");
    
    /* leitura dos campos */                        
    CarregaHeader(&head, &numcampos, arqCfg);
    

    //impress�o dos campos do arquivo de tamanho fixo
    while(!feof(arqFix)) {
          registro = LeRegistroFixo(arqFix, numcampos, head);
          for(i=0; i<numcampos; i++)
                   fprintf(stdout, "%s ", registro[i]);
          printf("\n");
          //LiberaRegistro(registro); ??
          }

    //cria��o do arquivo delimitado
    arqDlm = ConverteFixoDelim(argv[2], arqFix, separador);
    
    //impress�o dos campos do arquivo delimitados
    while(!feof(arqDlm)) {
          registro = LeRegistroDelim(arqDlm, numcampos);
          for(i=0; i<numcampos; i++)
                   fprintf(stdout, "%s ", registro[i]);
          printf("\n");
          //LiberaRegistro(registro); ??
          }
    
    
    fclose(arqFix);
    fclose(arqDlm);
    fclose(arqCfg);
    free(head);
//    free(???); LiberaRegistro(????);
    
    system("pause");
    return 0;

} /* main */
