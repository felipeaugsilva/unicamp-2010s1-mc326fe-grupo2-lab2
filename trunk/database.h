/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laborat�rio    02 
   - Manipulacao de arquivos com registros de tamanho fixo, campos de tamanho
     fixo e campos de tamanho variavel.
   - Construcao de uma biblioteca de funcoes que permitam realizar as operacoes
     de pesquisa, alteracao, remocao e insercao de registros e campos em um
     arquivo.
     - Construcao de funcoes para criacao e pesquisa de indices;
/******************************************************************************/

/* database.h - conjunto de fun��es para manipula��o de banco de dados */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "languages.h"
#include "envelope.h"
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

Boolean VerificaStringNumericaNaoNula(char *string, int nDig);
/* Verifica se string s� cont�m n�meros, se os n�meros n�o s�o todos 0 e
   se string tem nDig. */

Boolean VerificaDigitos(char *string);
/* Retorna "true" se a string s� cont�m digitos de 0-9
   ou retorna "false" caso contr�rio */

Boolean LeConfig(char *sep);
/* Procura o arquivo Config.l1b e carrega em lang e sep a lingua de interface 
   do programa e o caractere que deve separar os dados no arquivo de entrada. 
   Retorna erro se n�o encontrar o arquivo ou se o conte�do for inv�lido */
     
void AbreArquivoFixo(char* nome, FILE** arqFix, FILE** arqCfg);
/* Abre o arquivo de entrada (.fix com registros de tamanho fixo) e
   seu respectivo arquivo de configura��o (.cfg) */

void CarregaHeader(Header** h, int* numcampos, FILE* arqCfg);
/* Carrega o vetor head com os campos do banco de dados definido por arqCfg */

Record LeRegistroFixo(char* linha, int n, Header* h);
/* Aloca a mem�ria din�mica necess�ria e carrega na mesma o conte�do dos n 
   campos do registro corrente de um arquivo de dados em formato de campo fixo
   (arq). Carrega Record com os endere�os do conte�do de cada campo. 
   Deixa o ponteiro de arqFix na posi��o apropriada para a pr�xima leitura.
   Retorna NULL se houver algum erro no registro. */
   
FILE* ConverteFixoDelim(char* nome, FILE* arqFix, char sep, Header* head, int numcampos);
/* Converte um arquivo de campos de tamanho fixo em outro de campos de tamanho variavel.
   Despreza registros invalidos */   
 
void ImprimeArquivoFixo(FILE* arqFix, int numcampos, Header* head);
/* Imprime os dados de um arquivo de campos de tamanho fixo. Nao imprime
   registros invalidos */

void ImprimeArquivoDelim(FILE* arqDel, int numcampos, Header* head, char c);
/* Imprime os dados de um arquivo de campos de tamanho variavel */   

void LiberaRegistro(Record registro, int n);
/* Libera todas as strings apontadas por record e tamb�m os apontadores */
   
Record PesquisaRegistro(char* arq, char* key, char sep, int max, int n);
/* Procura pela chave primaria 'key' no arquivo de formato variavel
   separado por sep, com n campos e linha de tamanho m�ximo max.
   Se encontrar, coloca em 'registro' as informa��es e retorna true, caso 
   contr�rio retorna false */
   
void ImprimeRegistro(Record registro, Header* head, int numcampos);
/* Imprime todos os campos de um registro */

void ExtraiChaves(FILE *arqDlm, char* sep, Header* head);
/* Cria um arquivo 'chaves.ind' com as chaves prim�rias do arquivo de dados arqDlm,
   junto com os respectivos endere�os dos registros no arquivo */
   
void ClassificaChavePrimaria();
/* Cria um arquivo 'chavesClas.ind' a partir do arquivo 'chaves.ind' j� criado,
   classificando-o */

void ImprimeChaves(FILE *arq);
/* Imprime as chaves primarias e o endere�o */


/*******************************NOVAS FUN��ES DO LAB2C*************************/
Record PesqIndexRegistro();
/* ESCREVER O QUE FAZ E INCLUIR OS PAR�METROS */

void RemoveRegistro();
/* ESCREVER O QUE FAZ E INCLUIR PAR�METROS E TIPO DA FUN��O*/
