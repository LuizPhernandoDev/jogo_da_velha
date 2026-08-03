#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

void ImprimeLayout(char velha[],int n);
void ImprimeInicial();
void CondicaoVitoria(char velha[], int n, int *vitoria);
void resultado(char velha[], int n, int vitoria, char vez);

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
	
	if(vitoria){
		printf("Parabens!\n");
		printf("O %c é o vencedor.\n\n", vez);
	}else
		printf("Deu empate!\n\n");
	
	resultado(velha, sizeof(velha), vitoria, vez);

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
	setlocale(LC_ALL, "C");
	char cor[9][10];
	char X[10] = "\033[94m";
	char O[10] = "\033[91m";
	
	for(int i = 0; i<9; i++){
		if(velha[i] == 'X')
			strcpy(cor[i], X);
		else if(velha[i] == 'O')
			strcpy(cor[i], O);
		else
			snprintf(cor[i], sizeof(cor[i]), "\033[0m");	
	}
		
	printf("       ³       ³       \n");
    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
    printf("       ³       ³       \n");
    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
    printf("       ³       ³       \n");
    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
    printf("       ³       ³       \n");
    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
    printf("       ³       ³       \n");
    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
    printf("       ³       ³       \n");
    setlocale(LC_ALL, "Portuguese");
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

void resultado(char velha[], int n, int vitoria, char vez){
	setlocale(LC_ALL, "C");
	char cor[9][10];
	char CorVitoria[10];
	char X[10] = "\033[94m";
	char O[10] = "\033[91m";
	
	for(int i = 0; i<9; i++){
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
	
	switch (vitoria){
		case 0:
			printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
		    printf("       ³       ³       \n");
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
		    printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
		    printf("       ³       ³       \n");
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
		    printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
		    printf("       ³       ³       \n");
		    break;
		case 1:
			printf("       ³       ³       \n");
		    printf("%sÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄ\033[0m\n", CorVitoria, velha[0], velha[1], velha[2]);
		    printf("       ³       ³       \n");
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
		    printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
		    printf("       ³       ³       \n");
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
		    printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
		    printf("       ³       ³       \n");
		    break;
		case 2:
			printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
		    printf("       ³       ³       \n");
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
		    printf("       ³       ³       \n");
		    printf("%sÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄ\033[0m\n", CorVitoria, velha[3], velha[4], velha[5]);
		    printf("       ³       ³       \n");
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
		    printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m \n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
		    printf("       ³       ³       \n");
		    printf("       ³       ³       \n");
		    break;
		case 3:
			printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
		    printf("       ³       ³       \n");
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
		    printf("       ³       ³       \n");
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
		    printf("       ³       ³       \n");
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n");
		    printf("       ³       ³       \n");
		    printf("%sÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄÄÄÄÄ%cÄÄÄ\033[0m\n", CorVitoria, velha[6], velha[7], velha[8]);
		    printf("       ³       ³       \n");
		    break;
		case 4:
			printf("   %s³\033[0m   ³       ³       \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
		    printf("   %s³\033[0m   ³       ³       \n", CorVitoria);
		    printf("ÄÄÄ%s³\033[0mÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", CorVitoria);
		    printf("   %s³\033[0m   ³       ³       \n", CorVitoria);
		    printf("   %s%c\033[0m\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
		    printf("   %s³\033[0m   ³       ³       \n", CorVitoria);
		    printf("ÄÄÄ%s³\033[0mÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", CorVitoria);
		    printf("   %s³\033[0m   ³       ³       \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
		    printf("   %s³\033[0m   ³       ³       \n", CorVitoria);
		    break;
		case 5:
			printf("       ³   %s³\033[0m   ³       \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
		    printf("       ³   %s³\033[0m   ³       \n", CorVitoria);
		    printf("ÄÄÄÄÄÄÄÅÄÄÄ%s³\033[0mÄÄÄÅÄÄÄÄÄÄÄ\n", CorVitoria);
		    printf("       ³   %s³\033[0m   ³       \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
		    printf("       ³   %s³\033[0m   ³       \n", CorVitoria);
		    printf("ÄÄÄÄÄÄÄÅÄÄÄ%s³\033[0mÄÄÄÅÄÄÄÄÄÄÄ\n", CorVitoria);
		    printf("       ³   %s³\033[0m   ³       \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
		    printf("       ³   %s³\033[0m   ³       \n", CorVitoria);
		    break;
		case 6:
			printf("       ³       ³   %s³\033[0m   \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
		    printf("       ³       ³   %s³\033[0m   \n", CorVitoria);
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄ%s³\033[0mÄÄÄ\n", CorVitoria);
		    printf("       ³       ³   %s³\033[0m   \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
		    printf("       ³       ³   %s³\033[0m   \n", CorVitoria);
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄ%s³\033[0mÄÄÄ\n", CorVitoria);
		    printf("       ³       ³   %s³\033[0m   \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
		    printf("       ³       ³   %s³\033[0m   \n", CorVitoria);
		    break;
		case 7:
			printf(" %s\\_\033[0m    ³       ³       \n", CorVitoria);
		    printf("   %s%c_\033[0m  ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
		    printf("     %s\\_\033[0m³       ³       \n", CorVitoria);
		    printf("ÄÄÄÄÄÄÄ%s\\\033[0mÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", CorVitoria);
		    printf("       ³ %s\\_\033[0m    ³       \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c_\033[0m  ³   %s%c\033[0m\n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
		    printf("       ³     %s\\_\033[0m³       \n", CorVitoria);
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ%s\\\033[0mÄÄÄÄÄÄÄ\n", CorVitoria);
		    printf("       ³       ³ %s\\_\033[0m    \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³   %s%c_\033[0m\n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
		    printf("       ³       ³     %s\\\033[0m \n", CorVitoria);
		    break;
		case 8:
			printf("       ³       ³    %s_/\033[0m \n", CorVitoria);
		    printf("   %s%c\033[0m   ³   %s%c\033[0m   ³  %s_%c\033[0m\n", cor[0], velha[0], cor[1], velha[1], cor[2], velha[2]);
		    printf("       ³       ³%s_/\033[0m     \n", CorVitoria);
		    printf("ÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ%s/\033[0mÄÄÄÄÄÄÄ\n", CorVitoria);
		    printf("       ³    %s_/\033[0m ³       \n", CorVitoria);
		    printf("   %s%c\033[0m   ³  %s_%c\033[0m   ³   %s%c\033[0m\n", cor[3], velha[3], cor[4], velha[4], cor[5], velha[5]);
		    printf("       ³%s_/\033[0m     ³       \n", CorVitoria);
		    printf("ÄÄÄÄÄÄÄ%s/\033[0mÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ\n", CorVitoria);
		    printf("    %s_/\033[0m ³       ³       \n", CorVitoria);
		    printf("  %s_%c\033[0m   ³   %s%c\033[0m   ³   %s%c\033[0m\n", cor[6], velha[6], cor[7], velha[7], cor[8], velha[8]);
		    printf(" %s/\033[0m     ³       ³       \n", CorVitoria);
		    break;
	}
	setlocale(LC_ALL, "Portuguese");
}