#ifndef ponto_h

#define ponto_h
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct tipos{
	unsigned long int inteiro;
	float decimal;
	char caractere;
	char* string;
}TIPOS;

typedef struct tab
{
	char nome[100];
	char chave[100];
}TAB;

void criar_tabela();
void listar_tabela();
int lendoTabelas(char nomeArquivo[100],TAB * tabelas);
int* alocar_int(int colunas);
char **alocar_char(int colunas);
void receber_quantColuna(int colunas, FILE * arquivo);
void criandoTabela(char nomeArquivo[100], char key[100]);
void receber_atributos(char **listAtributos, int colunas, FILE *arquivo);
void declarar_tipo(int *ponteiroTipo, int colunas);
void recebendoInformation(int atributos, int tupla, FILE *arquivo, char **listAtributos,int *listaTipo, TIPOS categoria);

#endif