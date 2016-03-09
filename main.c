#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nomes
{
    char *nome;
}Nomes;

int n_linhas(char *arquivo); //Calcula o numero de linhas existentes no arquivo texto
Nomes *aloca_v(Nomes *n, int num); //Aloca um vetor de Nomes com posições equivalentes ao numero de linhas do arquivo texto
void aloca_nome(Nomes *n, char *arquivo, int linhas);//Aloca espaço para o vetor nome, da estrutura Nomes, e insere o nome de uma cliente no espaço alocado
int cmp(const void *a, const void *b); //Função a ser usada por Qsort
void escreve_arquivo(Nomes *n, char *arquivo, int linhas); //Função que escreve o novo arquivo texto com os nomes das clientes em ordem alfabética

int n_linhas(char *arquivo)
{
    FILE* f = fopen(arquivo,"r");
    int x=0;
    int c;

    do
    {
        c = fgetc(f);
        if(c=='\n')
            x++;

    }while(c >= 0);
    fclose(f);
    return x+1;
}

Nomes *aloca_v(Nomes *n, int num)
{
    n = (Nomes*)malloc(num*sizeof(Nomes));
    return n;
}

void aloca_nome(Nomes *n, char *arquivo, int linhas)
{
    FILE *p = fopen(arquivo, "r");
    char nome[100] ="";
    int i;
    int len_str;

    for(i=0;i<linhas;i++)
    {
        fgets(nome, 99, p);
        len_str = strlen(nome);
        nome[len_str-1] = '\0';
        n[i].nome = (char*)malloc((len_str+1)*sizeof(char));
        strcpy(n[i].nome, nome);
    }
    fclose(p);
}

int cmp(const void *a, const void *b)
{
    Nomes *x = (Nomes*)a;
    Nomes *y = (Nomes*)b;

    int n = strcmp(x->nome, y->nome);
    return n;
}


void escreve_arquivo(Nomes *n, char *arquivo, int linhas)
{
    FILE *f = fopen(arquivo, "w");
    int i;

    fprintf(f,"<ul>\n");
    for(i=0;i<linhas;i++)
    {
        fprintf(f,"  <li>%s</li>\n",n[i].nome);
    }
    fprintf(f,"</ul>");
    fclose(f);
}

void imprime_nomes(Nomes *n, int linhas)
{
    int i;
    for(i=0;i<linhas;i++)
    {
        printf("\n%s",n[i].nome);
    }
    printf("\n\n\n");
}



int main()
{
    int linhas = n_linhas("nomes.txt");
    Nomes *nm = aloca_v(nm, linhas);
    aloca_nome(nm, "nomes.txt", linhas);

    qsort(nm, linhas, sizeof(Nomes), cmp);
    imprime_nomes(nm, linhas);
    escreve_arquivo(nm, "Lista.txt", linhas);


    return 0;
}
