#include "jogovelha.h"

void imprimePlacar(int ptsX, int ptsO, const char *jogador1, const char *jogador2, const char VezJogador1){
	setlocale(LC_ALL, "C");
	int tam1 = strlen(jogador1);
	int tam2 = strlen(jogador2);
	int maior = (tam1>tam2)?tam1:tam2;
	int tamTotal = 2*maior+7;
	printf("%90s\033[9AÚ", "");
	for(int i=0; i<tamTotal-2; i++)
		printf("Ä");
	printf("¿\033[1B");
    printf("\033[%dD³%*sPLACAR%*s³\033[1B", tamTotal, maior-1, "", maior, "");
    
    printf("\033[%dDÃ", tamTotal);
    for(int i=0; i<maior+2; i++)
    	printf("Ä");
    printf("Â");
    for(int i=0; i<maior+2; i++)
    	printf("Ä");
    printf("´\033[1B");
    
    printf("\033[%dD³ %*s%*s ³ %*s%*s ³\033[1B", tamTotal, (int)ceil(maior/2.0+tam1/2.0), jogador1, (int)ceil(tam1/2.0-maior/2.0), "", (int)ceil(maior/2.0+tam2/2.0), jogador2, (int)ceil(tam2/2.0-maior/2.0), "");
    
    printf("\033[%dDÃ", tamTotal);
    for(int i=0; i<maior+2; i++)
    	printf("Ä");
    printf("Å");
    for(int i=0; i<maior+2; i++)
    	printf("Ä");
    printf("´\033[1B");
    if(VezJogador1=='X')
    	printf("\033[%dD³ %*d%*s ³ %*d%*s ³\033[1B", tamTotal, maior/2+1, ptsX, (maior%2)?maior/2:maior/2-1, "", maior/2+1, ptsO, (maior%2)?maior/2:maior/2-1, "");
    else
    	printf("\033[%dD³ %*d%*s ³ %*d%*s ³\033[1B", tamTotal, maior/2+1, ptsO, (maior%2)?maior/2:maior/2-1, "", maior/2+1, ptsX, (maior%2)?maior/2:maior/2-1, "");    	
	printf("\033[%dDÀ", tamTotal);
    for(int i=0; i<maior+2; i++)
    	printf("Ä");
    printf("Á");
    for(int i=0; i<maior+2; i++)
    	printf("Ä");
    printf("Ù\033[3E");
	setlocale(LC_ALL, "Portuguese");
}

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ImprimeInicial() {
    setlocale(LC_ALL, "C");
    printf("%48s  ±±±  ±±±   ±±±   ±±± \n", "");
    printf("%48s   ±  ±   ± ±     ±   ±\n", "");
    printf("%48s   ±  ±   ± ±  ±± ±   ±\n", "");
    printf("%48s±  ±  ±   ± ±   ± ±   ±\n", "");
    printf("%48s ±±    ±±±   ±±±   ±±± \n\n", "");

    printf("%54s±±±±   ±±± \n", "");
    printf("%54s±   ± ±   ±\n", "");
    printf("%54s±   ± ±±±±±\n", "");
    printf("%54s±   ± ±   ±\n", "");
    printf("%54s±±±±  ±   ±\n\n", "");

    printf("%45s±   ± ±±±±± ±     ±   ±  ±±± \n", "");
    printf("%45s±   ± ±     ±     ±   ± ±   ±\n", "");
    printf("%45s±   ± ±±±±  ±     ±±±±± ±±±±±\n", "");
    printf("%45s ± ±  ±     ±     ±   ± ±   ±\n", "");
    printf("%45s  ±   ±±±±± ±±±±± ±   ± ±   ±\n\n", "");
    setlocale(LC_ALL, "Portuguese");
}

void ImprimeLayout(char velha[], int n) {
    setlocale(LC_ALL, "C");
    char cor[9][10];
    char X[10] = "\033[91m";
    char O[10] = "\033[94m";

    for(int i = 0; i < 9; i++) {
        if(velha[i] == 'X')
            strcpy(cor[i], X);
        else if(velha[i] == 'O')
            strcpy(cor[i], O);
        else
            snprintf(cor[i], sizeof(cor[i]), "\033[0m");
    }

    printf("%48s       ³       ³       \n", "");
    printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
    printf("%48s       ³       ³       \n", "");
    printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
    printf("%48s       ³       ³       \n", "");
    printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
    printf("%48s       ³       ³       \n", "");
    printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
    printf("%48s       ³       ³       \n", "");
    printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
    printf("%48s       ³       ³       \n", "");
    setlocale(LC_ALL, "Portuguese");
}

void CondicaoVitoria(char velha[], int n, int *vitoria) {
    if(velha[0] == velha[1] && velha[0] == velha[2])      *vitoria = 1;
    else if(velha[3] == velha[4] && velha[3] == velha[5]) *vitoria = 2;
    else if(velha[6] == velha[7] && velha[6] == velha[8]) *vitoria = 3;
    else if(velha[0] == velha[3] && velha[0] == velha[6]) *vitoria = 4;
    else if(velha[1] == velha[4] && velha[1] == velha[7]) *vitoria = 5;
    else if(velha[2] == velha[5] && velha[2] == velha[8]) *vitoria = 6;
    else if(velha[0] == velha[4] && velha[0] == velha[8]) *vitoria = 7;
    else if(velha[2] == velha[4] && velha[2] == velha[6]) *vitoria = 8;
    else                                                  *vitoria = 0;
}

void resultado(char velha[], int n, int vitoria, char vez) {
    setlocale(LC_ALL, "C");
    char cor[9][10];
    char CorVitoria[10] = "\033[0m";
    char X[10] = "\033[91m";
    char O[10] = "\033[94m";

    for(int i = 0; i < 9; i++) {
        if(velha[i] == 'X')
            strcpy(cor[i], X);
        else if(velha[i] == 'O')
            strcpy(cor[i], O);
        else
            snprintf(cor[i], sizeof(cor[i]), "\033[0m");
    }
    if(vez == 'X')
        strcpy(CorVitoria, X);
    else if(vez == 'O')
        strcpy(CorVitoria, O);

    switch (vitoria) {
        case 0:
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
            printf("%48s       ³       ³       \n", "");
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
            printf("%48s       ³       ³       \n", "");
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
            printf("%48s       ³       ³       \n\n", "");
            break;
        case 1:
            printf("%48s       ³       ³       \n", "");
            printf("%48s%sÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄ\033[0m\n", "", CorVitoria, velha[0], velha[1], velha[2]);
            printf("%48s       ³       ³       \n", "");
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
            printf("%48s       ³       ³       \n", "");
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
            printf("%48s       ³       ³       \n\n", "");
            break;
        case 2:
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
            printf("%48s       ³       ³       \n", "");
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
            printf("%48s       ³       ³       \n", "");
            printf("%48s%sÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄ\033[0m\n", "", CorVitoria, velha[3], velha[4], velha[5]);
            printf("%48s       ³       ³       \n", "");
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
            printf("%48s       ³       ³       \n\n", "");
            break;
        case 3:
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
            printf("%48s       ³       ³       \n", "");
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
            printf("%48s       ³       ³       \n", "");
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
            printf("%48s       ³       ³       \n", "");
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "");
            printf("%48s       ³       ³       \n", "");
            printf("%48s%sÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄ\033[0m\n", "", CorVitoria, velha[6], velha[7], velha[8]);
            printf("%48s       ³       ³       \n\n", "");
            break;
        case 4:
            printf("%48s   %s³\033[0m   ³       ³       \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
            printf("%48s   %s³\033[0m   ³       ³       \n", "", CorVitoria);
            printf("%48sÄÄÄ%s³\033[0mÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "", CorVitoria);
            printf("%48s   %s³\033[0m   ³       ³       \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
            printf("%48s   %s³\033[0m   ³       ³       \n", "", CorVitoria);
            printf("%48sÄÄÄ%s³\033[0mÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "", CorVitoria);
            printf("%48s   %s³\033[0m   ³       ³       \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
            printf("%48s   %s³\033[0m   ³       ³       \n\n", "", CorVitoria);
            break;
        case 5:
            printf("%48s       ³   %s³\033[0m   ³       \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
            printf("%48s       ³   %s³\033[0m   ³       \n", "", CorVitoria);
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄ%s³\033[0mÄÄÄÅÄÄÄÄÄÄÄ\n", "", CorVitoria);
            printf("%48s       ³   %s³\033[0m   ³       \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
            printf("%48s       ³   %s³\033[0m   ³       \n", "", CorVitoria);
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄ%s³\033[0mÄÄÄÅÄÄÄÄÄÄÄ\n", "", CorVitoria);
            printf("%48s       ³   %s³\033[0m   ³       \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
            printf("%48s       ³   %s³\033[0m   ³       \n\n", "", CorVitoria);
            break;
        case 6:
            printf("%48s       ³       ³   %s³\033[0m   \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
            printf("%48s       ³       ³   %s³\033[0m   \n", "", CorVitoria);
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄ%s³\033[0mÄÄÄ\n", "", CorVitoria);
            printf("%48s       ³       ³   %s³\033[0m   \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
            printf("%48s       ³       ³   %s³\033[0m   \n", "", CorVitoria);
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄ%s³\033[0mÄÄÄ\n", "", CorVitoria);
            printf("%48s       ³       ³   %s³\033[0m   \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
            printf("%48s       ³       ³   %s³\033[0m   \n\n", "", CorVitoria);
            break;
        case 7:
            printf("%48s %s\\_\033[0m    ³       ³       \n", "", CorVitoria);
            printf("%48s   %s%c_\033[0m  ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
            printf("%48s     %s\\_\033[0m³       ³       \n", "", CorVitoria);
            printf("%48sÄÄÄÄÄÄÄ%s\\\033[0mÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "", CorVitoria);
            printf("%48s       ³ %s\\_\033[0m    ³       \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c_\033[0m  ³   %s%c\033[0m\n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
            printf("%48s       ³     %s\\_\033[0m³       \n", "", CorVitoria);
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ%s\\\033[0mÄÄÄÄÄÄÄ\n", "", CorVitoria);
            printf("%48s       ³       ³ %s\\_\033[0m    \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c_\033[0m\n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
            printf("%48s       ³       ³     %s\\\033[0m \n\n", "", CorVitoria);
            break;
        case 8:
            printf("%48s       ³       ³    %s_/\033[0m \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³   %s%c\033[0m   ³  %s_%c\033[0m\n", "", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
            printf("%48s       ³       ³%s_/\033[0m     \n", "", CorVitoria);
            printf("%48sÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ%s/\033[0mÄÄÄÄÄÄÄ\n", "", CorVitoria);
            printf("%48s       ³    %s_/\033[0m ³       \n", "", CorVitoria);
            printf("%48s   %s%c\033[0m   ³  %s_%c\033[0m   ³   %s%c\033[0m\n", "", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
            printf("%48s       ³%s_/\033[0m     ³       \n", "", CorVitoria);
            printf("%48sÄÄÄÄÄÄÄ%s/\033[0mÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", "", CorVitoria);
            printf("%48s    %s_/\033[0m ³       ³       \n", "", CorVitoria);
            printf("%48s  %s_%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", "", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
            printf("%48s %s/\033[0m     ³       ³       \n\n", "", CorVitoria);
            break;
	}
	setlocale(LC_ALL, "Portuguese");
}