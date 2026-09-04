#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "jogovelha.h"

int main() {
	srand(time(NULL));
	
    setlocale(LC_ALL, "Portuguese");
    char vez, posicao, novamente, VezJogador1, NumUsuario, c, MelhorDe;
    char usuario[10], jogadores[3][10], velha[9];
    char ptsX=0, ptsO=0, qtdUsuarios=0;
    char menu='1';
    char NovoJogador[50]="user";
    int disponivel, jogadas, vitoria, i, j, k, dado[2];
    
    FILE *f;
    
    MENU:
    EscolhaMenu(&menu);
	
	if(menu == '1'){
    	f = fopen("dados\\usuarios.txt", "r");
    	
    	qtdUsuarios=0;
    	do{
    		fscanf(f, "%9s", usuario);
			c = fgetc(f);
			qtdUsuarios++;
		}while(c != EOF);
		qtdUsuarios--;
    	NumUsuario=0;
    	
    	fclose(f);
    	for(int j=0; j<2; j++){
    		do{    			
	    		ImprimeUsuarios(qtdUsuarios, NumUsuario);
	    		
				printf("\033[u");
				
				NumUsuario = getchar();
				if(NumUsuario=='\n')
					NumUsuario = getchar();
				else
					limpaBuffer();
				system("cls");
				if(NumUsuario=='V' || NumUsuario=='v'){
					menu = '1';
					goto MENU;
				}
			}while(!(NumUsuario>='1' && NumUsuario<=qtdUsuarios+48) || j==1 && NumUsuario-48==k );
			
	    	f = fopen("dados\\usuarios.txt", "r");
	    	
	    	for(k=0; k<NumUsuario-48; k++)
	    		fscanf(f, "%s", jogadores[j]);
	    		
	    	fclose(f);
		}
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
    
    	f = fopen("dados\\usuarios.txt", "a+");
    	fprintf(f, "%s\n", NovoJogador);
    	fclose(f);
    	goto MENU;
	}
	MelhorDe='1';
	do{	
		setlocale(LC_ALL, "Portuguese");
		if(!(MelhorDe>='1' && MelhorDe<='3'))
			printf("%55sInvalido!\n", "");
			
	    printf("%36sEscolha uma opição da quantidade de partida: \033[s\n\n", "");
	    setlocale(LC_ALL, "C");
	    printf("%49sÚÄÄÄ¿ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n", "");
		printf("%49s³ 1 ³-³  Melhor de 3  ³\n", "");
		printf("%49sÀÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
		printf("%49sÚÄÄÄ¿ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n", "");
		printf("%49s³ 2 ³-³  Melhor de 5  ³\n", "");
		printf("%49sÀÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
		printf("%49sÚÄÄÄ¿ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n", "");
		printf("%49s³ 3 ³-³  Melhor de 7  ³\n", "");
		printf("%49sÀÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
		printf("%49sÚÄÄÄ¿ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n", "");
		printf("%49s³ V ³-³  Voltar menu  ³\n", "");
		printf("%49sÀÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
		setlocale(LC_ALL, "Portuguese");
		
		printf("\033[u");
		
		MelhorDe = getchar();
		if(MelhorDe=='\n')
			MelhorDe = getchar();
		else
			limpaBuffer();
		system("cls");
		if(MelhorDe=='V' || MelhorDe=='v')
			goto MENU;
		
	}while(!(MelhorDe>='1' && MelhorDe<='3'));
	switch (MelhorDe){
		case '1':
			MelhorDe=3;
			break;
		case '2':
			MelhorDe=5;
			break;
		case '3':
			MelhorDe=7;
			break;
	}
	
	do{
		for(j=0; j<2; j++){
			ImprimeInicial();
			printf("\033[97m%*s\033[m gire o dado\n\n", 54+strlen(jogadores[j])/2, jogadores[j]);
			printf("%37s", "");
			system("pause");
			system("cls");
			
			dado[j] = rand()%6 + 1;
			
			ImprimeInicial();
			printf("\033[97m%*s\033[m tirou %d no dado\n\n", 52+strlen(jogadores[j])/2, jogadores[j], dado[j]);
			printf("%37s", "");
			system("pause");
			system("cls");
		}
	}while(dado[0]==dado[1]);
	
	snprintf(jogadores[2], sizeof(jogadores[2]), jogadores[(dado[0]>dado[1])?0:1]);
	
    do {
    	ImprimeInicial();
        printf("\033[97m%*s\033[m pressione [X] ou [O] para começar: \n\n", 43+strlen(jogadores[2])/2, jogadores[2]);
        printf("%59s", "");
        
        vez = getchar();
		if(vez=='\n')
			vez = getchar();
		else
			limpaBuffer();

        system("cls");

        if(vez != 'x' && vez != 'o' && vez != 'X' && vez != 'O')
            printf("%55sInvalido!\n", "");
        else if(vez == 'x' || vez == 'o')
            vez -= 32;

    } while(vez != 'X' && vez != 'O');
	VezJogador1=vez;
	ptsX = ptsO = 0;
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
				if(posicao=='\n')
					posicao = getchar();
				else
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
		
        /*do {
        	printf("\n\n\n\n\n\n\n\n\n");
            printf("%50sQuer jogar novamente:\n\n", "");
            printf("%56s[S] Sim\n\n", "");
            printf("%56s[N] Não\n\n", "");
            printf("%59s", "");
            novamente = getchar();
            if(novamente=='\n')
        			novamente = getchar();

            if(novamente == 's' || novamente == 'n')
                novamente -= 32;

            system("cls");

            if(novamente != 'S' && novamente != 'N')
                printf("%55sInvalido!\n", "");
        } while(novamente != 'S' && novamente != 'N');
        */
        
        if(vitoria){
        	vez = (vez == 'X') ? 'O' : 'X';
			if(!strcmp(jogadores[2], jogadores[0]))
	        	snprintf(jogadores[2], sizeof(jogadores[2]), jogadores[1]);
	        else
	        	snprintf(jogadores[2], sizeof(jogadores[2]), jogadores[0]);
		}
			
    } while(ptsX<MelhorDe/2+1 && ptsO<MelhorDe/2+1);
    
    goto MENU;

    return 0;
}