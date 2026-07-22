#include <stdio.h>
#include <stdlib.h>

void ImprimeLayout(char posicao[],int n);

int main() {
    char posicao[9];
    
    for(int i=0; i<9; i++){
    	posicao[i] = 49 + i;
	}
	
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
	
	system("pause");
	system("cls");
    
    ImprimeLayout(posicao, sizeof(posicao));

    return 0;
}

void ImprimeLayout(char posicao[],int n){
	printf("       |       |       \n");
    printf("   %c   |   %c   |    %c  \n", posicao[0], posicao[1], posicao[2]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |    %c  \n", posicao[3], posicao[4], posicao[5]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |    %c  \n", posicao[6], posicao[7], posicao[8]);
    printf("       |       |       \n");
}