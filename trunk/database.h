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
 * database.h - conjunto de fun��es para manipula��o de banco de dados
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define branco ' '
#define tamPrimCampoHd 20
#define tamUltCampoHd 40

/*** Estruturas de dados ******************************************************/

/* Defini��o de tipo booleano */
typedef enum {false, true} Boolean;


/* Defini��o de um vetor de ponteiros para caractere. Uma vez inicializados,
   cada um dos ponteiros do vetor ir� apontar para a posi��o inicial do
   conte�do do campo[i] do registro correspondente. Caso seja necess�rio
   carregar mais de um registro do banco de dados na mem�ria, cada um de seus 
   campos poder� ser acessado por: registro[m].campo[n]   */
typedef char** Record;


/* Defini��o de estrutura que armazena as caracter�sticas de um campo de um
   arquivo de dados. Estas caracter�sticas devem ser extra�das de um arquivo de
   configura��o ou de uma se��o espec�fica do arquivo de dados */
typedef struct {
        char nome[tamPrimCampoHd+1];
        char tipo;
        int inicio;
        int tamanho;
        Boolean obrig;
        char msg[tamUltCampoHd+1];
        } Header;


/*** Fun��es ******************************************************************/

Boolean VerificaDigitos(char *string);
/* Retorna "true" se a string s� cont�m digitos de 0-9
   ou retorna "false" caso contr�rio */

Boolean LeConfig(char* sep, char* lingua);
/* Procura o arquivo Config.l1b e carrega em sep o caractere que deve separar 
   os dados no arquivo de entrada e em lingua o identificador da linua de 
   interface. Retorna erro se n�o encontrar o arquivo ou se o conte�do 
   for inv�lido */
   
void CarregaHeader(Header** h, int* numcampos, FILE* arqCfg);
/* Carrega o vetor head com os campos do banco de dados definido por arqCfg */

Record LeRegistroFixo(FILE* arq, int n, Header* h);
/* Aloca a mem�ria din�mica necess�ria e carrega na mesma o conte�do dos n 
   campos do registro corrente de um arquivo de dados em formato de campo fixo
   (arq). Carrega Record com os endere�os do conte�do de cada campo. 
   Deixa o ponteiro de arqFix na posi��o apropriada para a pr�xima leitura */
   
FILE* ConverteFixoDelim(char* nome, FILE* arq, char c);
/* Retorna o ponteiro para um arquivo de "nome.dlm", com os mesmos registros de 
   arq, separados pelo delimitador c. Para tanto, invoca RemoveBrancos para
   compactar os campos que n�o preenchem todo o espa�o do campo fixo */
   
Record LeRegistroDelim(FILE* arq, int n);
/* Aloca a mem�ria din�mica necess�ria e carrega na mesma o conte�do dos n 
   campos do registro corrente de um arquivo de dados em formato delimitado
   (arq). Carrega Record com os endere�os do conte�do de cada campo. 
   Deixa o ponteiro de arqFix na posi��o apropriada para a pr�xima leitura */
   
