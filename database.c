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

/* database.c - conjunto de fun��es para manipula��o de banco de dados */

#include "database.h"
#include "languages.h"


/* Fun��es Auxiliares (n�o inclu�das em database.h) ***************************/

void TiraBrancosDoFinal(char* s){
/* Elimina todos os brancos em excesso no final de uma string. */
    
    int i = strlen(s) - 1;     //�ltimo elemento da string
    while(i >= 0 && s[i] == branco)
       i--;
    s[i+1] = '\0';
    
} /* TiraBrancosDoFinal */


int TamMaxRegistro(Header* h, int campos){
/* Calcula o tamanho m�ximo do registro de um arquivo de dados configurado por 
   head, com n campos */
   int i, tam = 0;
   for(i=0;i<campos;i++) tam += h[i].tamanho;
   tam += campos;                            //para caber os delimitadores
   return tam;
   
} /* TamMaxRegistro */


Boolean SoZeros(char *string) {
/* Fun��o auxiliar: Retorna "true" se a string s� cont�m zeros ou
   "false" caso contr�rio. */
   
   char *s1, s2[10] = "123456789";
   s1 = strpbrk(string, s2);
   
   if(s1 == NULL)
      return true;
   
   return false;
    
} /* SoZeros */


Boolean ValidaDados(Record reg, Header *h, int numcampos) {
/* Retorna 'true' se os dados de um registro forem v�lidos ou 'false'
   caso contr�rio */
        
     int i;
     
     /* Verifica se n�o falta nenhum dado obrigatorio */
     for(i = 0; i < numcampos; i++)
        if(reg[i][0] == '\0' && h[i].obrig == true) {
            printf("%s\n\n", ERRO_DADOS_OBRIG);
            return false;
        }
     
     /* Verifica RA */
     if(!VerificaStringNumericaNaoNula(reg[0], 6)) {
        printf("%s: %s\n\n", ERRO_RA, reg[0]);
        return false;
     }
     
     /* Verifica telefone contato */
     if(!VerificaStringNumericaNaoNula(reg[3], 8)) {
        printf("%s: %s\n\n", ERRO_TEL, reg[3]);
        return false;
     }
     
     /* Verifica telefone alternativo */
     if(reg[4][0] != '\0' && !VerificaStringNumericaNaoNula(reg[4], 8)) {
        printf("%s: %s\n\n", ERRO_TEL, reg[4]);
        return false;
     }
     
     /* Verifica sexo */
     if(reg[5][0] != '\0' && reg[5][0] != 'M' && reg[5][0] != 'F') {
        printf("%s: %s\n\n", ERRO_SEXO, reg[5]);
        return false;
     }
     
     /* Verifica curso */
     if(!VerificaStringNumericaNaoNula(reg[6], 2)) {
        printf("%s: %s\n\n", ERRO_CURSO, reg[6]);
        return false;
     }
     
     return true;
     
} /* ValidaDados */

/*************************** Fun��es Auxiliares (n�o inclu�das em database.h) */


Boolean VerificaStringNumericaNaoNula(char *string, int nDig){
/* Verifica se string s� cont�m n�meros, se os n�meros n�o s�o todos 0 e
   se string tem nDig. */

    int i, tam = strlen(string);
    
    if(tam != nDig || SoZeros(string) || !VerificaDigitos(string))
       return false;
    
    return true;
    
} /* VerificaStringNumericaNaoNula */


Boolean VerificaDigitos(char *string) {
/* Retorna "true" se a string s� cont�m digitos de 0-9
   ou retorna "false" caso contr�rio */

    int i, tam = strlen(string);
    
    for(i = 0; i < tam; i++)
       if(!isdigit(string[i]))
          return false;
    
    return true;

} /* VerificaDigitos */


Boolean LeConfig(char *sep){
/* Procura o arquivo Config.l1b e carrega em lang e sep a lingua de interface 
   do programa e o caractere que deve separar os dados no arquivo de entrada. 
   Retorna erro se n�o encontrar o arquivo ou se o conte�do for inv�lido */
   
    char lingua[5];
    FILE *arqConfig = fopen("Config.l1b", "rt");
    
    if (arqConfig == NULL) 
                        return false;     
   
    fscanf(arqConfig, "%s", lingua);  //leitura do br no arquivo                        
    fseek(arqConfig, 2, SEEK_CUR);
    *sep = fgetc(arqConfig);   //leitura do separador
    
    fclose(arqConfig); 
   
    Linguagem(lingua);

    return true;   
} /* LeConfig */


void AbreArquivoFixo(char* nome, FILE** arqFix, FILE** arqCfg){
/* Abre o arquivo de entrada (.fix com registros de tamanho fixo) e
   seu respectivo arquivo de configura��o (.cfg) */   
   
   *arqFix = Fopen(nome, "r");    /* Abre arquivo de dados */
   
   /* abre arquivo de configura��o (mesmo nome com extens�o .cfg) */
   nome[strlen(nome)-3] = '\0';
   *arqCfg = Fopen(strcat(nome, "cfg"), "r");
   
} /* AbreArquivoFixo */
   

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
   para a pr�xima leitura. Retorna NULL se houver algum erro no registro. */
   
   
   int i;
   Record registro;
   
   registro = malloc(sizeof(char*)*n);
   
   for(i=0;i<n;i++){
                    
      registro[i] = (char*)malloc(sizeof(char)*(h[i].tamanho+1));
      strncpy(registro[i], &linha[h[i].inicio-1], h[i].tamanho);
      registro[i][h[i].tamanho] = '\0';              
      TiraBrancosDoFinal(registro[i]);
   
   }
   
   if(!ValidaDados(registro, h, n)) {
       LiberaRegistro(registro, n);
       return NULL;
   }
       
   return registro;
   
}/* LeRegistroFixo */
   

FILE* ConverteFixoDelim(char* nome, FILE* arqFix, char sep, Header* head, int numcampos){
/* Converte um arquivo de campos de tamanho fixo em outro de campos de tamanho variavel.
   Despreza registros invalidos */      

   FILE* dlm;
   int i, numRegs = 0, numBytesFix, numBytesDlm, tamanhofix, regInv = 0;
   char *linha;
   char fimReg;
   Record registro;
   
   dlm = Fopen(nome, "w");
   
   fimReg = head[numcampos-1].msg[0];

   tamanhofix = + head[numcampos-1].inicio+head[numcampos-1].tamanho;
   
   linha = malloc(sizeof(char)*(tamanhofix));
                  
   /* Escreve os dados no novo arquivo */
   while(!feof(arqFix)) {
                                       
       numRegs++;
       
       fread(linha, tamanhofix, 1, arqFix);
       
       registro = LeRegistroFixo(linha, numcampos, head);
       
       if(registro != NULL) {
       
           for(i=0; i<numcampos-1; i++)
               fprintf(dlm, "%s%c", registro[i], sep);     
       
           fprintf(dlm, "%s\n", registro[i]);
   
           LiberaRegistro(registro, numcampos);
        }
        else
            regInv++;
   }
   
   numBytesFix = ftell (arqFix); /* Conta os bytes do arquivo original */
   numBytesDlm = ftell (dlm);  /* Conta os bytes do arquivo convertido */
   
   fprintf(stdout, "\n%s: %d\n", NUM_REGS, numRegs);
   fprintf(stdout, "%d %s\n", regInv, NUM_REG_INV);
   fprintf(stdout, "%s: %d\n", NUM_BYTES_FIX, numBytesFix);
   fprintf(stdout, "%s: %d\n", NUM_BYTES_DLM, numBytesDlm);
   
   free(linha);                 
   fclose(dlm);
   return dlm;
}   
   
   
      
void ImprimeArquivoFixo(FILE* arqFix, int numcampos, Header* head){
/* Imprime os dados de um arquivo de campos de tamanho fixo. Nao imprime
   registros invalidos */

     int i, tamanhofix, regInv = 0;
     char *linha;
     Record registro;
     printf("\n");
                  
     tamanhofix = + head[numcampos-1].inicio+head[numcampos-1].tamanho;
     
     linha = malloc(sizeof(char)*(tamanhofix));
     
     while(!feof(arqFix)) {
                                       
        fread(linha, tamanhofix, 1, arqFix);  /* pega uma linha do arquivo */
                      
        registro = LeRegistroFixo(linha, numcampos, head); /*transforma em um registro */
                      
        if(registro != NULL) {
            ImprimeRegistro(registro, head, numcampos); /* imprime */
            LiberaRegistro(registro, numcampos);
        }
        else
            regInv++;
     }
     
     printf("%d %s\n\n", regInv, NUM_REG_INV);
                   
     free(linha);
                   
     fseek(arqFix, 0, SEEK_SET);     /* Volta para o inicio do arquivo */ 
      
} /* ImprimeArquivoFixo */


void ImprimeArquivoDelim(FILE* arqDel, int numcampos, Header* head, char c){
/* Imprime os dados de um arquivo de campos de tamanho variavel */

    Record reg;  
    int i;
    long pos, upos;
    Boolean fim=false;
    
    fseek (arqDel, 0, SEEK_END);       //pega a ultima posicao do arquivo
    upos = ftell(arqDel);  
    
    fseek (arqDel, 0, SEEK_SET);       //volta para o inicio do arquivo
    
    
     while(fim==false) {               //faz o loop ate o fim do arquivo

         pos = ftell(arqDel);          //pega a posicao atual
         
         if(pos<upos){                 //verifica se o arquivo chegou ao fim
         
            reg = CarregaRegDelim(arqDel, pos, numcampos, c);            //cria o registro atual
         
            if(reg!=NULL){                                               //verifica se o registyro atual foi excluido


              for(i=0;i<numcampos-1;i++){                                //escreve o resgitro caso nao esteja excluido
                 fprintf(stdout, "%s: ", head[i].nome);
                 fprintf(stdout, "%s \n", reg[i]);
              }   

              fprintf(stdout, "\n");                       

              LiberaRegistro(reg,numcampos);                             //liberar

           }     
                                                                
        } 
        else                        // se chegou ao fim, finaliza o loop
          fim=true;
        
     }           
      
} /* ImprimeArquivoVariavel */
      
      
void LiberaRegistro(Record registro, int n){
/* Libera todas as strings apontadas por record e tamb�m os apontadores */
     
     int i;
     for(i = 0; i < n; i++)
        free(registro[i]);
     free(registro);
     
} /* LiberaRegistro */


Record PesquisaRegistro(char* arq, char* key, char sep, int max, int n){
/* Procura pela chave primaria 'key' no arquivo de formato variavel
   separado por sep, com n campos e linha de tamanho m�ximo max.
   Se encontrar, coloca em 'registro' as informa��es e retorna true, caso 
   contr�rio retorna false */

   FILE* f = Fopen(arq, "rt");
   char* linha = malloc(sizeof(char)*max);
   int i = 0;
   Record rec = Malloc(sizeof(char*)*n);

   while(!feof(f)) {
                    fgets(linha, max, f);
                    rec[0] = strtok(linha,&sep);

                    if (strcmp(rec[0],key) == 0) {     //achou a chave
                                                       //se foi removido nunca vai achar

                       for(i=0;i<n-1;i++){
                             //se pr�ximo campo � vazio             
                             if(*(rec[i]+strlen(rec[i])+1)==sep){
                                     *(rec[i]+strlen(rec[i])+1) = '\0';
                                     i++;
                                     rec[i] = (rec[i-1]+strlen(rec[i-1])+1);
                             }

                             rec[i+1] = strtok (rec[i]+strlen(rec[i])+1, &sep);

                       }
                       return rec;
    
                    }
   }
   return NULL;  

} /* PesquisaRegistro */


void ImprimeRegistro(Record registro, Header *head, int numcampos){
/* Imprime todos os campos de um registro */
   int i;
   
   for(i=0; i<numcampos-1; i++) {
       fprintf(stdout, "%s: ", head[i].nome);
       fprintf(stdout, "%s \n", registro[i]);
   }
   printf("\n");
   
} /* ImprimeRegistro */



void ExtraiChaves(FILE *arqDlm, char* sep, Header* head){
/* Cria um arquivo 'chaves.ind' com as chaves prim�rias do arquivo de
   dados arqDlm, junto com os respectivos endere�os dos registros no arquivo */
   
   FILE* ind;
   char linha[400];            //melhor seria passar tamreg como argumento e declarar com este tamanho
   char *key;
   long endereco;
   
   ind = Fopen("chaves.ind", "w");
                  
   key = malloc(sizeof(char)*head[0].tamanho);
   rewind(arqDlm);
 
   while(!feof(arqDlm)) {
        endereco = ftell(arqDlm);  
        fgets(linha, 400, arqDlm);
        key = strtok(linha,sep);
        if(!feof(arqDlm)) {
                          //verifica se o registro n�o foi removido logicamente
                          if(key[0] != '*')
                                    fprintf(ind, "%s %10ld\n", key, endereco);
        }
   }
   free(key); 
   fclose(ind);
 
} /* ExtraiChaves */


void ClassificaChavePrimaria(){
/* Cria um arquivo 'chavesClas.ind' a partir do arquivo 'chaves.ind' j� criado,
   classificando-o */
   
   system("sort chaves.ind /o chavesClas.ind");

} /* ClassificaChavePrimaria */


Boolean Removido(FILE *arq, int end) {
/* Verifica se o registro de endere�o 'end' tem a marca de remo��o '*', retornando
   'true' em caso afirmativo ou 'false' caso contr�rio. */
        
    char c;
    
    fseek(arq, end, SEEK_SET);
    
    c = fgetc(arq);
    
    if(c == '*')
        return true;
        
    return false;
    
} /* Removido */


void ImprimeChaves(FILE *arq, FILE *arqDlm){
/* Imprime as chaves primarias e o endere�o.
   N�o imprime chaves de registros removidos (registros marcados com '*'). */

   char chave[16], end[16];
   
   fscanf(arq, "%s", chave);
   
   while(!feof(arq)){ 
      
      fscanf(arq, "%s", end);
      
      if(!Removido(arqDlm, atoi(end))) {  /* verifica se n�o foi removido */
      
          printf("\n%s: %s\n", CHAVE_PRIM, chave);
          printf("%s: %s\n", ENDERECO, end);
      }
      
      fscanf(arq, "%s", chave);
   }
   
   printf("\n");
   
} /* ImprimeChaves */


/*******************************NOVAS FUN��ES DO LAB2C*************************/

int IndexRegistro(FILE *arqChaves, int chavePrim){
/* Procura 'chavePrim' no arquivo de indices 'arqChaves'.
   Retorna o endere�o do registro se encontrar ou -1 caso contr�rio. */

   int tam, end, n = 0, inf, sup, meio, indice;
   char aux[30];
   
   fgets(aux, 30, arqChaves);
   tam = strlen(aux)+1;      /* Tamanho de uma linha */
   
   fseek(arqChaves, 0, SEEK_END);
   n = ftell(arqChaves) / tam;      /* Numero de indices */
   
   rewind(arqChaves);
   
   inf = 0;
   sup = n-1;
   
   /* pesquisa bin�ria */
   while(inf <= sup) {
             
             meio = (inf+sup)/2;
             fseek(arqChaves, tam*meio, SEEK_CUR);
             fscanf(arqChaves, "%d", &indice);
             
             if(chavePrim == indice) {     /* achou */
                 fscanf(arqChaves, "%d", &end);
                 return end;
             }
             
             if (chavePrim < indice) {      /* menor */
                 sup = meio-1;
                 fseek(arqChaves, 0, SEEK_SET);
             }
             
             else {          /* maior */
                 inf = meio+1;
                 fseek(arqChaves, 0, SEEK_SET);
             }
   }
   
   return -1;   /* n�o achou */
   
} /* PesqIndexRegistro */


Record CarregaRegDelim(FILE *arqDlm, int endFis, int n, char sep){
/* Retorna um registro de endere�o 'endFis' do arquivo 'arqDlm' ou retorna
   NULL caso o registro tenha sido removido. */
      
    Record reg = Malloc(sizeof(char*)*n);
    char aux[300], *linha;
    int i;
    
    fseek(arqDlm, endFis, SEEK_SET);
    
    fgets(aux, 300, arqDlm);
    linha = Malloc(sizeof(char)*(strlen(aux)+1));
    strcpy(linha, aux);
    
    reg[0] = strtok(linha, &sep);
    
    if(reg[0][0] == '*') {     /* registro removido */
        free(linha);
        free(reg);
        return NULL;
    }
    
    for(i=0;i<n-1;i++){
    /* se pr�ximo campo � vazio */
        if(*(reg[i]+strlen(reg[i])+1)==sep){
            *(reg[i]+strlen(reg[i])+1) = '\0';
            i++;
            reg[i] = (reg[i-1]+strlen(reg[i-1])+1);
        }
        reg[i+1] = strtok (reg[i]+strlen(reg[i])+1, &sep);
    }
    
    return reg;
      
} /* CarregaRegDelim */


void RemoveRegistro(FILE *arq, int end){
/* Remove um registro de endere�o 'end' do arquivo 'arq' inserindo o caractere
   '*' no primeiro digito do ra como marca de remo��o. */

    char *chave;
    
    fseek(arq, end, SEEK_SET);
    
    chave = malloc(sizeof(char)*6);
    fread(chave, sizeof(char), 6, arq);      /* le a chave do registro a ser removido */
    
    fseek(arq, end, SEEK_SET);
    
    chave[0] = '*';       /* insere a marca de remo��o */
    
    fwrite(chave, sizeof(char), 6, arq);      /* reescreve a chave, agora com a marca de remo��o */
    
    free(chave);
    
} /* RemoveRegistro */


