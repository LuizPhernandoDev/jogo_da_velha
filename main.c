#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void ImprimeLayout(char velha[],int n);
void ImprimeInicial();
char CondicaoVitoria(char velha[], int n, char vez);

int main() {
	setlocale(LC_ALL, "Portuguese");
    char velha[9], vez, posicao, vencedor = 'a';
    int i, disponivel;
    
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
    		disponivel = 0;
    		
			ImprimeLayout(velha, sizeof(velha));
			
			printf("É a vez do %c jogar, escolha a posição: \n", vez);
			printf("Disponives: ");
			
			for(i=0; i<9; i++)
				if(velha[i] == 49+i)
					printf("[%c] ", velha[i]);
			putchar('\n');
			
			fflush(stdin);
			posicao = getchar();
			
			for(i=0; i<9; i++)
				if(velha[i] == posicao)
					disponivel++;
			
			system("cls");
			
			if(posicao < 49 || posicao > 57 || !(disponivel))
				printf("          Invalido!\n");
			else
				velha[posicao-49] = vez;
			
		}while(posicao < 49 || posicao > 57 || !(disponivel));
		
		vencedor = CondicaoVitoria(velha, sizeof(velha), vez);
		
		if(vez == 'X')
			vez = 'O';
		else
			vez = 'X';
			
	}while(vencedor == 'a');

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

char CondicaoVitoria(char velha[], int n, char vez){
	if(velha[0] == velha[1] && velha[0] == velha[2] || velha[3] == velha[4] && velha[3] == velha[5] || velha[6] == velha[7] && velha[6] == velha[8])
		return vez;
	if(velha[0] == velha[3] && velha[0] == velha[6] || velha[1] == velha[4] && velha[1] == velha[7] || velha[2] == velha[5] && velha[2] == velha[8])
		return vez;
	if(velha[0] == velha[4] && velha[0] == velha[8] || velha[2] == velha[4] && velha[2] == velha[6])
		return vez;
	return 'a';
}