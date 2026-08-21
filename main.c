#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "jogovelha.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    char velha[9], vez, posicao, novamente, ptsX=0, ptsO=0, jogador1[50], jogador2[50], VezJogador[50], VezJogador1;
    int disponivel, jogadas, vitoria;

    ImprimeInicial();
    printf("%46sDigíte o nome do 1° jogador: \n\n","");
    printf("%55s","");
    fgets(jogador1, sizeof(jogador1), stdin);
    jogador1[strlen(jogador1+1)] = '\0';
    snprintf(VezJogador, sizeof(VezJogador), jogador1);
    system("cls");
    ImprimeInicial();
    
    printf("%46sDigíte o nome do 2° jogador: \n\n","");
    printf("%55s","");
    fgets(jogador2, sizeof(jogador2), stdin);
    jogador2[strlen(jogador2+1)] = '\0';
    system("cls");
        
    do {
    	ImprimeInicial();
        printf("%43sPressione [X] ou [O] para começar:\n\n","");
        printf("%59s", "");
        vez = getchar();
        limpaBuffer();

        system("cls");

        if(vez != 'x' && vez != 'o' && vez != 'X' && vez != 'O')
            printf("%55sInvalido!\n", "");
        else if(vez == 'x' || vez == 'o')
            vez -= 32;

    } while(vez != 'X' && vez != 'O');
	VezJogador1=vez;
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
                
                printf("\n\n%41sÉ a vez de ", "");
                 if(vez=='X')
            	printf("\033[91m");
            else
            	printf("\033[94m");
                printf("%s\033[m jogar, escolha a posição: \n", VezJogador);
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
            if(vitoria){
            	(vez == 'X') ? ptsX++ : ptsO++;
            	break;
			}
            vez = (vez == 'X') ? 'O' : 'X';
            if(!strcmp(VezJogador, jogador1))
            	snprintf(VezJogador, sizeof(VezJogador), jogador2);
            else
            	snprintf(VezJogador, sizeof(VezJogador), jogador1);
            jogadas++;

        } while(jogadas <= 9);

        if(vitoria) {
            printf("%55sParabéns!\n", "");
            printf("%52sO ", "");
            if(vez=='X')
            	printf("\033[91m");
            else
            	printf("\033[94m");
            printf("%s\033[0m é o vencedor\n\n", VezJogador);
        } else {
            printf("%53sDeu empate!\n\n", "");
        }

        resultado(velha, sizeof(velha), vitoria, vez);
		
		imprimePlacar(ptsX, ptsO, jogador1, jogador2, VezJogador1);
		
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
        if(vitoria)
			vez = (vez == 'X') ? 'O' : 'X';
    } while(novamente == 'S');

    return 0;
}