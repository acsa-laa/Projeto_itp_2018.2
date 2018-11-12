#include "ponto.h"

int main()
{
	int escolha;

	char continuidade;

	printf("O que você quer fazer?\n");

	
	do{	
		printf("-digite 1 para criar tabela\n-digite 2 para listar tabelas\n-digite 3 para criar nova linha na tabela\n");
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
   					getchar();
					criar_novaLinha();
   					break;

   				case 4:
   					printf("nenhuma opção por enquanto\n");	
   					break;

   				default:
   					printf("valor invalido\n");
   					break;
		}
		printf("Quer continuar? (s/n)\n");
		scanf(" %c", &continuidade);
	}while(continuidade == 's');
	return 0;
}