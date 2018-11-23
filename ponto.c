
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


	printf("\nPara nomes compostos (mais de uma palavra), use _ como espaço!\n\n");

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

	declarar_tipo(listaTipos, atributos, arquivo);

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

int get_size()
{
    FILE *file = fopen("tabelas.TXT", "r");

    if (file == NULL)
	{
		printf("erro na abertura do arquivo ou o arquivo não existe!\n");
		return 0;
	}

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

int lendoTabelas(char nomeArquivo[100]){
	int i=0;

	char linha[100];

	char * ptr_palavra;
	
	if(get_size() == 0)
	{
	    printf("O arquivo esta vazio.\n");
	    return 0;
	}

	FILE * todosArquivos;
	todosArquivos = fopen("tabelas.TXT", "r+");

	do{
		i++;
		fgets(linha, 100, todosArquivos);

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
	printf("\nPara nomes compostos (mais de uma palavra), use _ como espaço!\n\n");

	for (i = 0; i < colunas; i++)
	{	
		if (i == 0)
		{
			printf("Qual o nome da chave primária?\n(obrigatoriamente ela deve ser um número inteiro positivo):\n");
		}
		else{
			printf("digite o nome do %d atributo\n", i+1);
		}
		fgets(listAtributos[i], 100, stdin);
		fprintf(arquivo, "%s", listAtributos[i]);
		fseek(arquivo, -1 , SEEK_CUR);
		fprintf(arquivo, " |");
	}

	fprintf(arquivo, "\n");
}

void declarar_tipo(int *ponteiroTipo, int colunas,FILE *arquivo){
	int i, tipo;
	printf("\nTipos dos atributos:\ndigite 1 para inteiro\ndigite 2 para double\ndigite 3 para char\ndigite 4 para string\n");

	if (arquivo == NULL)
		{
			printf("erro na abertura do arquivo\n");
		} 

	fseek(arquivo, 0, SEEK_END);

	for (i = 0; i < colunas; i++)
	{
		if (i == 0)
		{
			ponteiroTipo[i] = 1;
		}
		else{
			printf("\ntipo do %d atributo: \n", i+1);
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
	}

	for (i = 0; i < colunas; i++)
	{
		fprintf(arquivo, "%d,", ponteiroTipo[i]);
	}
	fprintf(arquivo, "|\n");

}

void listar_tabela(){

	int i,j;
	j = 0;
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
		j++;
		fgets(linha, 100,todosArquivos);
	}

	fseek(todosArquivos, 0, SEEK_SET);

	for (i = 0; i < j-1; i++)
	{
		fgets(linha, 100,todosArquivos);

		ptr_palavra = strpbrk (linha, " ");

		printf("%s", ptr_palavra+1);
	}

    fclose(todosArquivos);
    return;
}


void criar_novaLinha()
{
	int colunas,i,p,j,controle,repet;
	repet = 0;
	FILE * arquivo;
	int chavePrimaria;
	int listaChave[100] = {0};
	char lixo[100];
	char listaTipos[100];
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

	fscanf(arquivo,"colunas:%d,", &colunas);

	listaAtributos = alocar_char(colunas);
	listInformation = alocar_char(colunas);

	for (i = 0; i < colunas; i++)
	{
		fscanf(arquivo,"%s |", listaAtributos[i]);
	}
	fseek(arquivo, 1, SEEK_CUR);

	fscanf(arquivo, "%s|", listaTipos);

	j = 0;
	while(!feof(arquivo)){
		fscanf(arquivo, "%d |", &listaChave[j]);
		fgets(lixo, 100, arquivo);
		j++;
	}


	//fseek(arquivo, 0 , SEEK_END);

	if (arquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	for (i = 0; i < colunas; i++)
	{
		printf("digite %s:\n", listaAtributos[i]);
		if (i == 0){
			fscanf(stdin, "%d", &chavePrimaria);
			getchar();
			for (p = 0; p < j; p++)
			{
				if (chavePrimaria == listaChave[p])
				{
					printf("essa chave já existe\n");
					printf("digite outra chave\n");
					repet = 1;
				}
			}
			if (repet == 1)
			{
				i = i-1;
				repet = 0;
			}
			else
			{
				fprintf(arquivo, "%d", chavePrimaria);
				fprintf(arquivo, " |");
			}
		}
		else{
			fgets(listInformation[i], 100, stdin);
			fprintf(arquivo, "%s", listInformation[i]);
			fseek(arquivo, -1 , SEEK_CUR);
			fprintf(arquivo, " |");
		}
	}

	fprintf(arquivo, "\n");
	fclose(arquivo);

	for(i=0; i<colunas; i++){
		free(listaAtributos[i]);
	}
	free(listaAtributos);

	for(i=0; i<colunas; i++){
		free(listInformation[i]);
	}
	free(listInformation);
	
	return;
}

void listar_dadosTabela(){

	int colunas,i,j,k,p,controle, tamanhoString, quantidadeSpace;
	FILE * arquivo;
	char **listaAtributos;
	char listaTipos[100], string[100];
	char nomeTabela[100];


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

	fscanf(arquivo,"colunas:%d,", &colunas);

	listaAtributos = alocar_char(colunas*100);

	fseek(arquivo, 1, SEEK_CUR);

	fgets(listaAtributos[0], 100, arquivo);

	fgets(listaTipos, 100, arquivo);

	j = 0;
	while(!feof(arquivo)){
		j++;
		fgets(listaAtributos[j], 100, arquivo);
	}

	fseek(arquivo, 0, SEEK_SET);
	for (i = 0; i < 4; i++)
	{
		if (i==1)
		{
			for (k = 0; k < colunas; k++)
			{
				fscanf(arquivo,"%s |", string);
				tamanhoString = 0;
				quantidadeSpace= 0;
				tamanhoString = strlen(string);
		    	quantidadeSpace = 15 - tamanhoString;
						
				printf("%s", string);
				for (p = 0; p < quantidadeSpace; p++)
				{
					printf(" ");
				}
			printf("|");
			}
	    	printf("\n");
	    }
		else{
			fgets(listaAtributos[i], 100, arquivo);
		}
	}


	for (i = 0; i < 16*colunas; i++)
	{
		printf("-");
	}
	printf("\n");


	for (i = 0; i < j-1; i++){

		for(k = 0; k < colunas; k++){
	
				fscanf(arquivo,"%s |", string);
				tamanhoString = 0;
				quantidadeSpace= 0;
				tamanhoString = strlen(string);
		    	quantidadeSpace = 15 - tamanhoString;
						
						printf("%s", string);
						for (p = 0; p < quantidadeSpace; p++)
						{
							printf(" ");
						}
				printf("|");
			}
		printf("\n");
	}

	fclose(arquivo);
	for(i=0; i<colunas; i++){
		free(listaAtributos[i]);
	}
	free(listaAtributos);
	
	return;
}

//falta a 5

void apagar_linhaTabela(){

	int i,j,controle,key,chaveP;
	j=0;
	char nomeTabela[100];
	char linha[100];
	FILE * todosArquivos;
	FILE * novoArquivo;
	char indices[100];
	char * nova;

	nova = "transição.TXT";

	printf("Qual o nome da tabela?\n");
	fgets(nomeTabela,100,stdin);

	controle = lendoTabelas(nomeTabela);

	if (controle == 0)
	{
		printf("essa tabela não existe\n");
		return;
	}

	printf("Qual a chave primária da linha?\n");
	scanf("%d", &chaveP);
	getchar();

	strcat(nomeTabela,".TXT");

	todosArquivos = fopen(nomeTabela, "r");
	novoArquivo = fopen(nova, "w");
	
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	if (novoArquivo == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	while(!feof(todosArquivos)){
		j++;
		fgets(linha, 100,todosArquivos);
	}

	fseek(todosArquivos, 0, SEEK_SET);

	for (i = 0; i < 3; i++)
	{
		fgets(indices, 100, todosArquivos);
		fprintf(novoArquivo, "%s", indices);

	}
	
	for (i = 0; i < j-4; i++)
	{
		fscanf(todosArquivos, "%d |", &key);
		fgets(linha, 100, todosArquivos);
	
		if (key != chaveP)
		{
			fprintf(novoArquivo,"%d |", key);
			fprintf(novoArquivo, "%s", linha);
		}
	}
	remove(nomeTabela);
	rename(nova, nomeTabela);
	fclose(novoArquivo);
	return;
}

void apagar_tabela(){

	int i,j,controle;
	j=0;
	char nomeTabela[100];
	char linha[100];
	char * ptr_palavra;
	char **listaTabelas;
	FILE * todosArquivos;
	FILE * novoArquivo;
	char * tabela;
	char * nova;

	listaTabelas = alocar_char(1000);

	tabela = "tabelas.TXT";
	nova = "transição.TXT";

	printf("Qual o nome da tabela que deseja apagar?\n");
	fgets(nomeTabela,100,stdin);

	controle = lendoTabelas(nomeTabela);

	if (controle == 0)
	{
		printf("essa tabela não existe\n");
		return;
	}

	todosArquivos = fopen(tabela, "r");
	novoArquivo = fopen(nova, "w");
	
	if (todosArquivos == NULL)
	{
		printf("erro na abertura do arquivo\n");
		return;
	}

	while(!feof(todosArquivos)){
		j++;
		fgets(linha, 100,todosArquivos);
	}

	fseek(todosArquivos, 0, SEEK_SET);

	for (i = 0; i < j-1; i++)
	{
		fgets(linha, 100,todosArquivos);

		ptr_palavra = strpbrk (linha, " ");

		if (strcmp(ptr_palavra+1, nomeTabela) != 0)
		{
			fprintf(novoArquivo, "Nome: %s", ptr_palavra+1);
		}
	}

	strcat(nomeTabela,".TXT");

	remove(nomeTabela);
	remove(tabela);
	rename(nova, tabela);

	fclose(novoArquivo);

	return;
}
