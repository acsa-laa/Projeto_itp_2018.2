
#include "ponto.h"

void criar_tabela()
{
	// atributos é a quantidade de atributos, tupla a quantidade de tuplas, tipo é o número que corresponde ao tipo,listaAtributos é a lista que vai receber os nomes dos atributos, listaTipos é a lista de atributos já com seu tipo.

	int atributos,i,j,tipo,p;
	char chavePrimaria[100];
	char ** listaAtributos;
	int *listaTipos;
	char nomeArquivo[100];
	int controle;
	FILE * arquivo;
	TIPOS categoria;
	TAB tabelas [200];
	TAB * ptr_tabelas = &tabelas[0];

	getchar();

	printf("Qual o nome da tabela ou do arquivo:\n");
	fgets(nomeArquivo, 100, stdin);

	controle = lendoTabelas(nomeArquivo,tabelas);

	if (controle == 1)
	{
		printf("essa tabela já existe\n");
		return;
	}

	printf("Digite a chave primária (obrigatoriamente deve ser um número positivo)\n");
	fgets(chavePrimaria, 100, stdin);

	criandoTabela(nomeArquivo, chavePrimaria);

	printf("Digite a quantidade de atributos (colunas):\n");
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

	//recebendoInformation(atributos, tupla, arquivo, listaAtributos, listaTipos, categoria);

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


int lendoTabelas(char nomeArquivo[100], TAB * tabelas){
	int i=0;

	char linha[100];
	char linha2[100];

	char * ptr_palavra;
	char * ptr_palavra2;
	
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
		fgets(linha2, 100,todosArquivos);
		
		ptr_palavra = strpbrk (linha, " ");

		if (strcmp(ptr_palavra+1, nomeArquivo) == 0){
			fclose(todosArquivos);
			return 1;
		}
		
		ptr_palavra2 = strpbrk (linha2, " ");


	}while(!feof(todosArquivos));

    fclose(todosArquivos);
    return 0;
}

void criandoTabela(char nomeArquivo[100], char key[100]){
	FILE * todosArquivos;
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
	}
	todosArquivos = fopen("tabelas.TXT", "a+");
	fprintf(todosArquivos, "Nome: %s", nomeArquivo);
	fprintf(todosArquivos,"Chave: %s",key); 
	//fseek(todosArquivos,-1,SEEK_END);
	//fprintf(todosArquivos, "");
	fclose(todosArquivos);
}

void receber_quantColuna(int colunas, FILE * arquivo){
	fprintf(arquivo, "colunas:%d,\n", colunas);
}

void receber_atributos(char **listAtributos, int colunas, FILE *arquivo){
	int i,j;
	for (i = 0; i < colunas; i++)
	{	
		printf("digite o %d atributo\n", i+1);
		fgets(listAtributos[i], 100, stdin);
		
		fprintf(arquivo, "%s", listAtributos[i]);
		fseek(arquivo, -1 , SEEK_CUR);
		fprintf(arquivo, "|");
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
	char linha2[100];

	//char * ptr_palavra;
	//char * ptr_palavra2;
	
	FILE * todosArquivos;
	todosArquivos = fopen("tabelas.TXT", "r+");
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}
	while(!feof(todosArquivos)){

		fscanf(todosArquivos,"Nome: %s\n", linha);
		fscanf(todosArquivos,"Chave: %s\n", linha2);

		printf("%s\n", linha);
	}

    fclose(todosArquivos);
    return;
}
/*void recebendoInformation(int atributos, int tupla, FILE *arquivo, char **listAtributos, int * listaTipos, TIPOS categoria){

int i,j;

for(j = 0; j < tupla; j++){

		for(i = 0; i < atributos; i++){
			printf("digite %s da linha %d:\n", listAtributos[i], (j+1));
			if(listaTipos[i] == 1){
				scanf("%lu", &categoria.inteiro);
				fprintf(arquivo, "%lu", categoria.inteiro);
				fprintf(arquivo,"/");
			}
			if(listaTipos[i] == 2){
				scanf("%f", &categoria.decimal);
				fprintf(arquivo, "%f", categoria.decimal);
				fprintf(arquivo,"/");
			}
			if(listaTipos[i] == 3){
				getchar();
				scanf("%c", &categoria.caractere);
				fprintf(arquivo, "%c", categoria.caractere);
				fprintf(arquivo,"/");
			}
			if(listaTipos[i] == 4){
				getchar();
				fgets(categoria.string, 100, stdin);
				//scanf("%s",categoria.string);
				fprintf(arquivo, "%s", categoria.string);
				//scanf("%s",nome);
				fseek(arquivo,-1,SEEK_CUR);
				fprintf(arquivo,"/");
			}
		}
		fseek(arquivo, -1 , SEEK_CUR);
		fprintf(arquivo, "%s\n", "/");
	}
}*/

