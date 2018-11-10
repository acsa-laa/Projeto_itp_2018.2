#include "ponto.h"

int main()
{
	int i,escolha;

	printf("O que você quer fazer?\n");

	printf("-digite 1 para criar tabela\n-digite 2 para listar tabelas\n");

	scanf("%d", &escolha);
	
	switch (escolha)
		{
   			case 1:
     			criar_tabela();
   				break;

   			case 2:
 	    		listar_tabela();
   				break;

   			case 3:
   				printf("nenhuma opção por enquanto\n");
   				break;

   			case 4:
   				printf("nenhuma opção por enquanto\n");	
   				break;

   			default:
   				printf("valor invalido\n");
   				printf("insira outro valor\n");
   				i = i-1;
   				break;
		}

	return 0;
}