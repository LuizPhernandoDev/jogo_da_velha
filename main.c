#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void ImprimeLayout(char velha[],int n);
void ImprimeInicial();

int main() {
	setlocale(LC_ALL, "Portuguese");
    char velha[9], vez, posicao;
    int i;
    
    for(i=0; i<9; i++)
    	velha[i] = 49 + i;
	
	do{
		ImprimeInicial();
		printf("Precione [X] ou [O] para começar: ");
		vez = getchar();
		
		system("cls");
		
		if(vez != 'x' && vez != 'o' && vez != 'X' && vez != 'O')
			printf("          Invalido!\n");
		else if(vez == 'x' || vez == 'o')
			vez-=32;
			
	}while(vez!='X' && vez!='O');
    do{
    	do{
			ImprimeLayout(velha, sizeof(velha));
			
			printf("É a vez do %c jogar, escolha a posição: \n", vez);
			printf("Disponives: ");
			
			for(i=0; i<9; i++)
				if(velha[i] == 49+i)
					printf("[%c] ", velha[i]);	
			putchar('\n');
			
			fflush(stdin);
			posicao = getchar();
			
			system("cls");
			
			if(posicao < 49 || posicao > 57)
				printf("          Invalido!\n");
			else
				velha[posicao-49] = vez;
				
		}while(posicao < 49 || posicao > 57);
		
		if(vez == 'X')
			vez = 'O';
		else
			vez = 'X';
			
	}while(1);

    return 0;
}

void ImprimeInicial(){
	setlocale(LC_ALL, "C");
	printf("  ±±±  ±±±   ±±±   ±±± \n");
	printf("   ±  ±   ± ±     ±   ±\n");
	printf("   ±  ±   ± ±  ±± ±   ±\n");
	printf("±  ±  ±   ± ±   ± ±   ±\n");
	printf(" ±±    ±±±   ±±±   ±±± \n\n");
	
	printf("±±±±   ±±± \n");
	printf("±   ± ±   ±\n");
	printf("±   ± ±±±±±\n");
	printf("±   ± ±   ±\n");
	printf("±±±±  ±   ±\n\n");
	
	printf("±   ± ±±±±± ±     ±   ±  ±±± \n");
	printf("±   ± ±     ±     ±   ± ±   ±\n");
	printf("±   ± ±±±±  ±     ±±±±± ±±±±±\n");
	printf(" ± ±  ±     ±     ±   ± ±   ±\n");
	printf("  ±   ±±±±± ±±±±± ±   ± ±   ±\n");
	setlocale(LC_ALL, "Portuguese");
}

void ImprimeLayout(char velha[], int n){
	printf("       |       |       \n");
    printf("   %c   |   %c   |   %c  \n", velha[0], velha[1], velha[2]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c  \n", velha[3], velha[4], velha[5]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c  \n", velha[6], velha[7], velha[8]);
    printf("       |       |       \n");
}