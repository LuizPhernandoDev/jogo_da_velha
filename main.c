#include <stdio.h>

int main() {
    char posicao[9];
    
    for(int i=0; i<9; i++){
    	posicao[i] = 49 + i;
	}
    
    printf("       |       |       \n");
    printf("   %c   |   %c   |    %c  \n", posicao[0], posicao[1], posicao[2]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |    %c  \n", posicao[3], posicao[4], posicao[5]);
    printf("_______|_______|_______\n");
    printf("       |       |       \n");
    printf("   %c   |   %c   |    %c  \n", posicao[6], posicao[7], posicao[8]);
    printf("       |       |       \n");

    return 0;
}