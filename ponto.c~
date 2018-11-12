
#include "ponto.h"

void criar_tabela()
{
	// atributos é a quantidade de atributos, tipo é o número que corresponde ao tipo,listaAtributos é a lista que vai receber os nomes dos atributos, listaTipos é a lista de atributos já com seu tipo.

	int atributos,i,j,tipo,p;
	char chavePrimaria[100];
	char ** listaAtributos;
	int *listaTipos;
	char nomeArquivo[100];
	int controle;
	FILE * arquivo;

	getchar();

	printf("Qual o nome da tabela ou do arquivo:\n");
	fgets(nomeArquivo, 100, stdin);

	controle = lendoTabelas(nomeArquivo);

	if (controle == 1)
	{
		printf("essa tabela já existe\n");
		return;
	}

	criandoTabela(nomeArquivo);

	printf("Digite a quantidade de atributos incluindo a chave primaria (colunas):\n");
	scanf("%d", &atributos);
	getchar();

	/*ALOCAÇÃO*/

	listaTipos = alocar_int(atributos);

	listaAtributos = alocar_char(atributos);


	strcat(nomeArquivo,".TXT");
	arquivo = fopen(nomeArquivo,"w+");
	
	if (arquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
	}

	receber_quantColuna(atributos, arquivo);

	receber_atributos(listaAtributos, atributos, arquivo);

	declarar_tipo(listaTipos, atributos);

	fclose(arquivo);

	for(i=0; i<atributos; i++){
		free(listaAtributos[i]);
	}
	free(listaAtributos);
	free(listaTipos);

	return;
}

int * alocar_int(int colunas){
	int *lisTipos;
	lisTipos = (int*) malloc(colunas * sizeof(int));
	if (lisTipos == NULL)
		{
			printf("memoria insuficiente\n");
		}
	return lisTipos;
}


char **alocar_char(int colunas){
	char **lisAtrib;
	int i;
	lisAtrib = (char**) malloc(colunas * sizeof(char*));
	if (lisAtrib == NULL)
		{
			printf("memoria insuficiente\n");
		}	
	for (i = 0; i < colunas; i++)
	{
		lisAtrib[i] = (char*) malloc (colunas * sizeof(char));
		if (lisAtrib[i] == NULL)
		{
			printf("memoria insuficiente\n");
		}
	}
	return lisAtrib;

}


int lendoTabelas(char nomeArquivo[100]){
	int i=0;

	char linha[100];

	char * ptr_palavra;
	
	FILE * todosArquivos;
	todosArquivos = fopen("tabelas.TXT", "r+");
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return -1;
	}
	do{
		i++;
		fgets(linha, 100,todosArquivos);
		
		ptr_palavra = strpbrk (linha, " ");

		if (strcmp(ptr_palavra+1, nomeArquivo) == 0){
			fclose(todosArquivos);
			return 1;
		}

	}while(!feof(todosArquivos));

    fclose(todosArquivos);
    return 0;
}

void criandoTabela(char nomeArquivo[100]){
	FILE * todosArquivos;
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
	}
	todosArquivos = fopen("tabelas.TXT", "a+");
	fprintf(todosArquivos, "Nome: %s", nomeArquivo);
	
	fclose(todosArquivos);
}

void receber_quantColuna(int colunas, FILE * arquivo){
	fprintf(arquivo, "colunas:%d,\n", colunas);
}

void receber_atributos(char **listAtributos, int colunas, FILE *arquivo){
	int i,j;

	for (i = 0; i < colunas; i++)
	{	
		if (i == 0)
		{
			printf("Qual o nome da chave primária (obrigatoriamente ela deve ser um número inteiro positivo):\n");
		}
		else{
			printf("digite o %d atributo\n", i+1);
		}
		fgets(listAtributos[i], 100, stdin);
		fprintf(arquivo, "%s", listAtributos[i]);
		fseek(arquivo, -1 , SEEK_CUR);
		fprintf(arquivo, " |");
	}

	fprintf(arquivo, "\n");
}

void declarar_tipo(int *ponteiroTipo, int colunas){
	int i, tipo;
	printf("\nTipos dos atributos:\ndigite 1 para inteiro\ndigite 2 para double\ndigite 3 para char\ndigite 4 para string\n");
	FILE *arquivoTipo;
	
	arquivoTipo = fopen("tipos.TXT", "a+");

	if (arquivoTipo == NULL)
		{
			printf("erro na abertura do arquivo\n");
		} 

	fseek(arquivoTipo, 0, SEEK_END);

	for (i = 0; i < colunas; i++)
	{
		printf("tipo do %d atributo: \n", i+1);
		scanf("%d", &tipo);

		switch (tipo)
		{
   			case 1:
     			ponteiroTipo[i] = 1;
   				break;

   			case 2:
 	    		ponteiroTipo[i] = 2;
   				break;

   			case 3:
   				ponteiroTipo[i] = 3;
   				break;

   			case 4:
   				ponteiroTipo[i] = 4;	
   				break;

   			default:
   				printf("valor invalido\n");
   				printf("insira outro valor\n");
   				i = i-1;
   				break;
		}
	}

	for (i = 0; i < colunas; i++)
	{
		fprintf(arquivoTipo, "%d,", ponteiroTipo[i]);
	}
	fprintf(arquivoTipo, "|\n");
	fclose(arquivoTipo);
}

void listar_tabela(){

	char linha[100];
	char * ptr_palavra;
	
	FILE * todosArquivos;
	todosArquivos = fopen("tabelas.TXT", "r");
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}
	while(!feof(todosArquivos)){

		fgets(linha, 100,todosArquivos);
		ptr_palavra = strpbrk (linha, " ");
		printf("%s", ptr_palavra);
	}

    fclose(todosArquivos);
    return;
}


void criar_novaLinha()
{
	int colunas,i,controle;
	FILE * arquivo;
	char **listaAtributos;
	char **listInformation;
	char nomeTabela[100];
	//TIPOS categoria;

	printf("Nome da tabela?\n");
	fgets(nomeTabela, 100, stdin);

	controle = lendoTabelas(nomeTabela);
	if (controle == 0)
	{
		printf("essa tabela não existe!\n");
		return;
	}

	strcat(nomeTabela,".TXT");

	arquivo = fopen(nomeTabela,"r+");

	if (arquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	fscanf(arquivo,"colunas:%d,\n", &colunas);

	listaAtributos = alocar_char(colunas);
	listInformation = alocar_char(colunas);

	for (i = 0; i < colunas; i++)
	{
		fscanf(arquivo,"%s |", listaAtributos[i]);
	}

	fseek(arquivo, 0 , SEEK_END);

	if (arquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	for (i = 0; i < colunas; i++)
	{
		printf("digite %s:\n", listaAtributos[i]);
		fgets(listInformation[i], 100, stdin);
		fprintf(arquivo, "%s", listInformation[i]);
		fseek(arquivo, -1 , SEEK_CUR);
		fprintf(arquivo, " |");
	}

	fprintf(arquivo, "\n");
	fclose(arquivo);
	
	return;
}