#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

void ImprimeLayout(char velha[], int n);
void ImprimeInicial();
void CondicaoVitoria(char velha[], int n, int *vitoria);
void resultado(char velha[], int n, int vitoria, char vez);
void limpaBuffer();

int main() {
    setlocale(LC_ALL, "Portuguese");
    char velha[9], vez, posicao, novamente;
    int disponivel, jogadas, vitoria;

    do {
        ImprimeInicial();
        printf("%42sPressione [X] ou [O] para começar:\n\n","");
        printf("%59s", "");
        vez = getchar();
        limpaBuffer();

        system("cls");

        if(vez != 'x' && vez != 'o' && vez != 'X' && vez != 'O')
            printf("%55sInvalido!\n", "");
        else if(vez == 'x' || vez == 'o')
            vez -= 32;

    } while(vez != 'X' && vez != 'O');
	
	do {
        vitoria = 0;
        jogadas = 1;

        for(int i = 0; i < 9; i++)
            velha[i] = '1' + i;
            
        do {
            do {
                disponivel = 0;
                
                printf("\n\n\n");
                ImprimeLayout(velha, sizeof(velha));
                
                printf("\n\n%41sÉ a vez do %c jogar, escolha a posição: \n", "", vez);
                printf("%36sDisponíveis: ", "");

                for(int i = 0; i < 9; i++)
                    if(velha[i] == '1' + i)
                        printf("[%c] ", velha[i]);
                putchar('\n');
                
                printf("\n%59s", "");
                posicao = getchar();
                limpaBuffer();

                for(int i = 0; i < 9; i++)
                    if(velha[i] == posicao)
                        disponivel++;

                system("cls");

                if(posicao < '1' || posicao > '9' || !(disponivel))
                    printf("%55sInvalido!\n", "");
                else
                    velha[posicao - '1'] = vez;

            } while(posicao < '1' || posicao > '9' || !(disponivel));

            CondicaoVitoria(velha, sizeof(velha), &vitoria);
            if(vitoria)
                break;

            vez = (vez == 'X') ? 'O' : 'X';
            jogadas++;

        } while(jogadas <= 9);

        if(vitoria) {
            printf("%55sParabéns!\n", "");
            printf("%52sO %c é o vencedor\n\n", "", vez);
        } else {
            printf("%53sDeu empate!\n\n", "");
        }

        resultado(velha, sizeof(velha), vitoria, vez);
		
		printf("%37s", "");
		system("pause");
		system("cls");
		
        do {
        	printf("\n\n\n\n\n\n\n\n\n");
            printf("%50sQuer jogar novamente:\n\n", "");
            printf("%56s[S] Sim\n\n", "");
            printf("%56s[N] Não\n\n", "");
            printf("%59s", "");
            novamente = getchar();
            limpaBuffer();

            if(novamente == 's' || novamente == 'n')
                novamente -= 32;

            system("cls");

            if(novamente != 'S' && novamente != 'N')
                printf("%55sInvalido!\n", "");

        } while(novamente != 'S' && novamente != 'N');

    } while(novamente == 'S');

    return 0;
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
    char X[10] = "\033[94m";
    char O[10] = "\033[91m";

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
    char X[10] = "\033[94m";
    char O[10] = "\033[91m";

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