#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void ImprimeLayout(char posicao[],int n);
void ImprimeInicial();

int main() {
	setlocale(LC_ALL, "Portuguese");
    char posicao[9], vez;
    
    for(int i=0; i<9; i++){
    	posicao[i] = 49 + i;
	}
	
	do{
		ImprimeInicial();
		printf("Precione [X] ou [O] para começar: ");
		vez = getchar();
		system("cls");
		if(vez != 'x' && vez != 'o' && vez != 'X' && vez != 'O'){
			printf("                    Invalido! \n");
		}else if(vez == 'x' || vez == 'o'){
			vez-=32;
		}
	}while(vez!='X' && vez!='O');
	
    ImprimeLayout(posicao, sizeof(posicao));

    return 0;
}

void ImprimeInicial(){
	printf("        ____   ____   ____          ___    ____ \n");
	printf("     | |    | |      |    |        |   \\  |    |\n");
	printf("     | |    | |   _  |    |        |    | |____|\n");
	printf("     | |    | |    | |    |        |    | |    |\n");
	printf("|____| |____| |____| |____|        |___/  |    |\n");
	printf("        ____                 ____               \n");
	printf("|    | |      |      |    | |    |              \n");
	printf("\\    / |___   |      |____| |____|              \n");
	printf(" \\  /  |      |      |    | |    |             \n");
	printf("  \\/   |____  |____  |    | |    |              \n\n");
}

void ImprimeLayout(char posicao[], int n){
	printf("       |       |       \n");
    printf("   %c   |   %c   |   %c  \n", posicao[0], posicao[1], posicao[2]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c  \n", posicao[3], posicao[4], posicao[5]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |   %c  \n", posicao[6], posicao[7], posicao[8]);
    printf("       |       |       \n");
}