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
 * database.c - conjunto de fun��es para manipula��o de banco de dados
 */

#include "database.h"



Boolean VerificaDigitos(char *string) {
/* Retorna "true" se a string s� cont�m digitos de 0-9
   ou retorna "false" caso contr�rio */

    int i, tam = strlen(string);
    
    for(i = 0; i < tam; i++)
       if(!isdigit(string[i]))
          return false;
    
    return true;

} /* VerificaDigitos */


Boolean LeConfig(char * sep, char * lingua){
/* Procura o arquivo Config.l1b e carrega em sep o caractere que deve separar 
   os dados no arquivo de entrada e em lingua o identificador da linua de 
   interface. Retorna erro se n�o encontrar o arquivo ou se o conte�do 
   for inv�lido */
   
   return true;
}


void AbreArquivoFixo(char* nome, FILE** arqFix, FILE** arqCfg){
/* Abre o arquivo de entrada (.fix com registros de tamanho fixo) e
   seu respectivo arquivo de configura��o (.cfg) */   
   
   *arqFix = Fopen(nome, "r");    /* Abre arquivo de dados */
   
   /* abre arquivo de configura��o (mesmo nome com extens�o .cfg) */
   nome[strlen(nome)-3] = '\0';
   *arqCfg = Fopen(strcat(nome, "cfg"), "r");
   
} /* AbreArquivoFixo */
   
   
void TiraBrancosDoFinal(char* s){
/* Elimina todos os brancos em excesso no final de uma string. */
    
    int i = strlen(s) - 1;     //�ltimo elemento da string
    while(i >= 0 && s[i] == branco)
       i--;
    s[i+1] = '\0';
    
} /* TiraBrancosDoFinal */


void CarregaHeader(Header** h, int* numcampos, FILE* arqCfg){
/* Carrega o vetor head com os campos do banco de dados definido por arqCfg */

    int i, final;
    char c;
    
    fscanf(arqCfg, "%d", numcampos);     /* Le n�mero de campos */
    fseek(arqCfg, 2, SEEK_CUR);
    *h = malloc(sizeof(Header)*(*numcampos));     /* Aloca o vetor head */
    
    for(i = 0; i < *numcampos; i++) {
        
        /* Le nome */
        fread((*h+i)->nome, tamPrimCampoHd, 1, arqCfg);
        (*h+i)->nome[tamPrimCampoHd] = '\0';
        TiraBrancosDoFinal((*h+i)->nome);
    
        /* Le tipo */
        (*h+i)->tipo = fgetc(arqCfg);
        
        /* Le endere�o de inicio e final de um campo e calcula seu tamanho */
        fscanf(arqCfg, "%d %d", &((*h+i)->inicio), &final);
        (*h+i)->tamanho = final - (*h+i)->inicio + 1;
        
        /* Le caractere de obrigatoriedade do campo */
        fseek(arqCfg, 1, SEEK_CUR);
        c = fgetc(arqCfg);
        if(c == 'S')
            (*h+i)->obrig = true;
        else
            (*h+i)->obrig = false;
            
        /* Le mensagem */    
        fseek(arqCfg, 1, SEEK_CUR);
        fread((*h+i)->msg, tamUltCampoHd, 1, arqCfg);
        (*h+i)->msg[tamUltCampoHd] = '\0';
        TiraBrancosDoFinal((*h+i)->msg);
    
        fseek(arqCfg, 2, SEEK_CUR);
    }
    
} /* CarregaHeader */

Record LeRegistroFixo(char* linha, int n, Header* h) {
/* Aloca a mem�ria din�mica necess�ria e carrega na mesma o conte�do dos n 
   campos do registro corrente de arqFix. Carrega Record com os endere�os do 
   conte�do de cada campo. Deixa o ponteiro de arqFix na posi��o apropriada
   para a pr�xima leitura */
   
   int i;
   Record registro;
   
   for(i=0;i<n;i++){
   registro[i] = malloc(sizeof(char*)*h[i].tamanho);
   strncpy(registro[i],&linha[h[i].inicio-1],h[i].tamanho);
   //registro[i][1]='/0';
   
   printf("\n\n%d\n\n - %s\n",h[i].tamanho, registro[i]);
               
                    
   }
   
   return registro;
}
   

FILE* ConverteFixoDelim(char* nome, FILE* arq, char c){
/* Retorna o ponteiro para um arquivo de "nome.dlm", com os mesmos registros de 
   arq, separados pelo delimitador c. Para tanto, invoca RemoveBrancos para
   compactar os campos que n�o preenchem todo o espa�o do campo fixo */
   FILE* dlm;
   return dlm;
}   
   
   
Record LeRegistroDelim(FILE* arq, int n){
/* Aloca a mem�ria din�mica necess�ria e carrega na mesma o conte�do dos n 
   campos do registro corrente de um arquivo de dados em formato delimitado
   (arq). Carrega Record com os endere�os do conte�do de cada campo. 
   Deixa o ponteiro de arqFix na posi��o apropriada para a pr�xima leitura */
   
   Record registro;
   return registro;
}
      
   
   
