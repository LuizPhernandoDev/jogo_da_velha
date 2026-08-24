#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "jogovelha.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    char velha[9], vez, posicao, novamente, VezJogador1, NumUsuario;
    char usuario[10], jogadores[3][10], NovoJogador[50]="user";
    char ptsX=0, ptsO=0, qtdUsuarios=0;
    char c;
    char menu='1';
    int disponivel, jogadas, vitoria, tam;
    
    FILE *f;
    
    Usuaiocadastrado:
    do{
    	ImprimeInicial();
    	if(menu != '1' && menu != '2')
			printf("%39sOpção por falta. Escolha uma opção para jogar\n\n", "");
		else
			printf("%45sEscolha uma opição para jogar\n\n", "");
    	printf("%51s[1] - Novo jogo\n\n", "");
    	printf("%51s[2] - Cadastrar usuário\n\n", "");
    	printf("%59s","");
    	menu = getchar();
    	system("cls");
	}while(menu != '1' && menu != '2');
	
	if(menu == '1'){
    	f = fopen("usuarios.txt", "r");
    	do{
    		fscanf(f, "%s", usuario);
			c = fgetc(f);
			qtdUsuarios++;
		}while(c != EOF);
		qtdUsuarios--;
    	
    	for(int j=0; j<2; j++){
    		do{
    			fclose(f);
    			f = fopen("usuarios.txt", "r");
	    		printf("%43sEscolha um usuário disponivel: \033[s\n\n", "");
				for(int i=0; i<qtdUsuarios; i++){
					fscanf(f, "%s", usuario);
					
					tam = strlen(usuario);
					
					setlocale(LC_ALL, "C");
					printf("%50sÚÄÄÄ¿ ÚÄÄÄÄÄÄÄÄÄÄÄ¿\n", "");
					printf("%50s³ %d ³-³ %*s%s%*s ³\n", "",  i+1, (tam%2)?(9 - tam)/2:(9 - tam)/2+1, "", usuario, (9 - tam)/2, "");
					printf("%50sÀÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
					setlocale(LC_ALL, "Portuguese");
				}
				printf("\033[u");
				NumUsuario = getchar();
				if(NumUsuario=='\n')
					NumUsuario = getchar();
				
				system("cls");
			}while(!(NumUsuario>='1' && NumUsuario<=qtdUsuarios+48));
			fclose(f);
	    	f = fopen("usuarios.txt", "r");
	    	
	    	for(int i=0; i<NumUsuario-48; i++)
	    		fscanf(f, "%s", jogadores[j]);
		}
		fclose(f);
	}else if(menu == '2'){
    	limpaBuffer();
    	do{
    		if(strlen(NovoJogador) > 9)
    			printf("%42sO nome deve ter menos de 9 caractes!\n", "");
    		printf("%46sDigite o nome do novo usuário\n\n", "");
			printf("%55s","");
			fgets(NovoJogador, sizeof(NovoJogador), stdin);
    		NovoJogador[strlen(NovoJogador+1)] = '\0';
    		if(strlen(NovoJogador) > sizeof(NovoJogador))
				limpaBuffer();
			system("cls");
		}while(strlen(NovoJogador) > 9);
    
    	f = fopen("usuarios.txt", "a+");
    	fprintf(f, "%s\n", NovoJogador);
    	fclose(f);
    	goto Usuaiocadastrado;
	}
	snprintf(jogadores[2], sizeof(jogadores[2]), jogadores[0]);
        
    do {
    	ImprimeInicial();
        printf("%43sPressione [X] ou [O] para começar:\n\n","");
        printf("%59s", "");
        limpaBuffer();
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
                printf("%s\033[m jogar, escolha a posição: \n", jogadores[2]);
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
            if(!strcmp(jogadores[2], jogadores[0]))
            	snprintf(jogadores[2], sizeof(jogadores[2]), jogadores[1]);
            else
            	snprintf(jogadores[2], sizeof(jogadores[2]), jogadores[0]);
            jogadas++;

        } while(jogadas <= 9);

        if(vitoria) {
            printf("%55sParabéns!\n", "");
            printf("%52sO ", "");
            if(vez=='X')
            	printf("\033[91m");
            else
            	printf("\033[94m");
            printf("%s\033[0m é o vencedor\n\n", jogadores[2]);
        } else {
            printf("%53sDeu empate!\n\n", "");
        }

        resultado(velha, sizeof(velha), vitoria, vez);
		
		imprimePlacar(ptsX, ptsO, jogadores[0], jogadores[1], VezJogador1);
		
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
        if(vitoria){
        	vez = (vez == 'X') ? 'O' : 'X';
			if(!strcmp(jogadores[2], jogadores[0]))
	        	snprintf(jogadores[2], sizeof(jogadores[2]), jogadores[1]);
	        else
	        	snprintf(jogadores[2], sizeof(jogadores[2]), jogadores[0]);
		}
			
    } while(novamente == 'S');

    return 0;
}