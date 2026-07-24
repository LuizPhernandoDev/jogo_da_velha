#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

void ImprimeLayout(char velha[],int n);
void ImprimeInicial();
void CondicaoVitoria(char velha[], int n, int *vitoria);

int main() {
	setlocale(LC_ALL, "Portuguese");
    char velha[9], vez, posicao;
    int disponivel, jogadas, vitoria;
    
    for(int i=0; i<9; i++)
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
	
	jogadas = 1;	
	}while(vez!='X' && vez!='O');
    do{
    	do{
    		disponivel = 0;
    		
			ImprimeLayout(velha, sizeof(velha));
			
			printf("É a vez do %c jogar, escolha a posição: \n", vez);
			printf("Disponives: ");
			
			for(int i=0; i<9; i++)
				if(velha[i] == 49+i)
					printf("[%c] ", velha[i]);
			putchar('\n');
			
			fflush(stdin);
			posicao = getchar();
			
			for(int i=0; i<9; i++)
				if(velha[i] == posicao)
					disponivel++;
			
			system("cls");
			
			if(posicao < 49 || posicao > 57 || !(disponivel))
				printf("          Invalido!\n");
			else
				velha[posicao-49] = vez;
			
		}while(posicao < 49 || posicao > 57 || !(disponivel));
		
		CondicaoVitoria(velha, sizeof(velha), &vitoria);
		if(vitoria)
			break;
		
		if(vez == 'X')
			vez = 'O';
		else
			vez = 'X';
			
		jogadas++;
		
	}while(jogadas <= 9);
	
	if(vez != 'a'){
		printf("Parabens!\n");
		printf("O %c é o vencedor.\n", vez);
	}else
	printf("Deu empate!\n");

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
	char cor[9][10];
	char X[10] = "\033[94m";
	char O[10] = "\033[91m";
	
	for(int i = 0; i<9; i++){
		snprintf(cor[i], sizeof(cor[i]), "\033[0m");
		if(velha[i] == 'X')
			strcpy(cor[i], X);
		else if(velha[i] == 'O')
			strcpy(cor[i], O);
	}
		
	printf("       |       |       \n");
    printf("   %s%c\033[0m   |   %s%c\033[0m   |   %s%c\033[0m \n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %s%c\033[0m   |   %s%c\033[0m   |   %s%c\033[0m \n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %s%c\033[0m   |   %s%c\033[0m   |   %s%c\033[0m \n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
    printf("       |       |       \n");
}

void CondicaoVitoria(char velha[], int n, int *vitoria){
	if(velha[0] == velha[1] && velha[0] == velha[2])
		*vitoria = 1;
	else if(velha[3] == velha[4] && velha[3] == velha[5])
		*vitoria = 2;
	else if(velha[6] == velha[7] && velha[6] == velha[8])
		*vitoria = 3;
	else if(velha[0] == velha[3] && velha[0] == velha[6])
		*vitoria = 4;
	else if(velha[1] == velha[4] && velha[1] == velha[7])
		*vitoria = 5;
	else if(velha[2] == velha[5] && velha[2] == velha[8])
		*vitoria = 6;
	else if(velha[0] == velha[4] && velha[0] == velha[8])
		*vitoria = 7;
	else if(velha[2] == velha[4] && velha[2] == velha[6])
		*vitoria = 8;
	else
		*vitoria = 0;
   
}