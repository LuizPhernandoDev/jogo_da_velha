#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "jogovelha.h"

struct Historco {
    char vencedor[10];
    char perdedor[10];
    char vez[2];
    int placar[2];
};

typedef struct Historco Historco;

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    char vez, posicao, novamente, VezJogador1, NumUsuario, c, MelhorDe, tipoHitorico;
    char usuario[10], jogadores[3][10], velha[9], HistoricoUsuario[2][10];
    char ptsX = 0, ptsO = 0, qtdUsuarios = 0;
    char menu = '1';
    char NovoJogador[50] = "user";
    int disponivel, jogadas, vitoria, i, j, k, dado[2], tam, qtdPartidas, qtdHistorico;
    Historco Jogadores;
    char NomeArquivo[50];
    FILE *f;

    int rodando = 1;

    while (rodando) {
        EscolhaMenu(&menu);

        f = fopen("dados/usuarios.txt", "r");
        qtdUsuarios = 0;
        if (f != NULL) {
            do {
                if (fscanf(f, "%9s", usuario) == 1) {
                    c = fgetc(f);
                    qtdUsuarios++;
                } else {
                    break;
                }
            } while (c != EOF);
            fclose(f);
        }
        NumUsuario = 0;

        if (menu == '1') {
            int voltarMenu = 0;

            for (j = 0; j < 2; j++) {
                do {
                    ImprimeUsuarios(qtdUsuarios, NumUsuario, &voltarMenu);

                    if (voltarMenu)
                        break;

                    printf("\033[u");

                    NumUsuario = getchar();
                    if (NumUsuario == '\n')
                        NumUsuario = getchar();
                    else
                        limpaBuffer();

                    system("cls");

                    if (NumUsuario == 'V' || NumUsuario == 'v') {
                        voltarMenu = 1;
                        break;
                    }
                } while (!(NumUsuario >= '1' && NumUsuario <= qtdUsuarios + 48) || (j == 1 && NumUsuario - 48 == k));

                if (voltarMenu) break;

                f = fopen("dados/usuarios.txt", "r");
                if (f != NULL) {
                    for (k = 0; k < NumUsuario - 48; k++)
                        fscanf(f, "%s", jogadores[j]);
                    fclose(f);
                }
            }

            if (voltarMenu) continue;

            MelhorDe = '1';
            do {
                setlocale(LC_ALL, "Portuguese");
                if (!(MelhorDe >= '1' && MelhorDe <= '3'))
                    printf("%55sInvalido!\n", "");

                printf("%36sEscolha uma opção da quantidade de partida: \033[s\n\n", "");
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
                if (MelhorDe == '\n')
                    MelhorDe = getchar();
                else
                    limpaBuffer();

                system("cls");
                if (MelhorDe == 'V' || MelhorDe == 'v') {
                    voltarMenu = 1;
                    break;
                }

            } while (!(MelhorDe >= '1' && MelhorDe <= '3'));

            if (voltarMenu) continue;

            switch (MelhorDe) {
                case '1': MelhorDe = 3; break;
                case '2': MelhorDe = 5; break;
                case '3': MelhorDe = 7; break;
            }

            do {
                for (j = 0; j < 2; j++) {
                    ImprimeInicial();
                    printf("\033[97m%*s\033[m gire o dado\n\n", (int)(54 + strlen(jogadores[j]) / 2), jogadores[j]);
                    printf("%37s", "");
                    system("pause");
                    system("cls");

                    dado[j] = rand() % 6 + 1;

                    ImprimeInicial();
                    printf("\033[97m%*s\033[m tirou %d no dado\n\n", (int)(52 + strlen(jogadores[j]) / 2), jogadores[j], dado[j]);
                    printf("%37s", "");
                    system("pause");
                    system("cls");
                }
            } while (dado[0] == dado[1]);

            snprintf(jogadores[2], sizeof(jogadores[2]), "%s", jogadores[(dado[0] > dado[1]) ? 0 : 1]);

            do {
                ImprimeInicial();
                printf("\033[97m%*s\033[m pressione [X] ou [O] para começar: \n\n", (int)(43 + strlen(jogadores[2]) / 2), jogadores[2]);
                printf("%59s", "");

                vez = getchar();
                if (vez == '\n')
                    vez = getchar();
                else
                    limpaBuffer();

                system("cls");

                if (vez != 'x' && vez != 'o' && vez != 'X' && vez != 'O')
                    printf("%55sInvalido!\n", "");
                else if (vez == 'x' || vez == 'o')
                    vez -= 32;

            } while (vez != 'X' && vez != 'O');

            VezJogador1 = (dado[0] > dado[1]) ? vez : (vez == 'X') ? 'O' : 'X';

            ptsX = ptsO = 0;
            do {
                vitoria = 0;
                jogadas = 1;

                for (int i = 0; i < 9; i++)
                    velha[i] = '1' + i;

                do {
                    do {
                        disponivel = 0;

                        printf("\n\n\n");
                        ImprimeLayout(velha, sizeof(velha));

                        printf("\n\n%41sÉ a vez de ", "");
                        if (vez == 'X')
                            printf("\033[91m");
                        else
                            printf("\033[94m");
                        printf("%s\033[m jogar, escolha a posição: \n", jogadores[2]);
                        printf("%36sDisponíveis: ", "");

                        for (int i = 0; i < 9; i++)
                            if (velha[i] == '1' + i)
                                printf("[%c] ", velha[i]);
                        putchar('\n');

                        printf("\n%59s", "");

                        posicao = getchar();
                        if (posicao == '\n')
                            posicao = getchar();
                        else
                            limpaBuffer();

                        for (int i = 0; i < 9; i++)
                            if (velha[i] == posicao)
                                disponivel++;

                        system("cls");

                        if (posicao < '1' || posicao > '9' || !(disponivel))
                            printf("%55sInvalido!\n", "");
                        else
                            velha[posicao - '1'] = vez;

                    } while (posicao < '1' || posicao > '9' || !(disponivel));

                    CondicaoVitoria(velha, sizeof(velha), &vitoria);
                    if (vitoria) {
                        (vez == 'X') ? ptsX++ : ptsO++;
                        break;
                    }
                    vez = (vez == 'X') ? 'O' : 'X';
                    if (!strcmp(jogadores[2], jogadores[0]))
                        snprintf(jogadores[2], sizeof(jogadores[2]), "%s", jogadores[1]);
                    else
                        snprintf(jogadores[2], sizeof(jogadores[2]), "%s", jogadores[0]);
                    jogadas++;

                } while (jogadas <= 9);

                if (vitoria) {
                    printf("%55sParabéns!\n", "");
                    printf("%49s", "");
                    if (vez == 'X')
                        printf("\033[91m");
                    else
                        printf("\033[94m");
                    printf("%s\033[0m venceu\n\n", jogadores[2]);
                } else {
                    printf("%53sDeu empate!\n\n", "");
                }

                resultado(velha, sizeof(velha), vitoria, vez);

                imprimePlacar(ptsX, ptsO, jogadores[0], jogadores[1], VezJogador1);

                printf("%37s", "");
                system("pause");
                system("cls");

                if (vitoria) {
                    vez = (vez == 'X') ? 'O' : 'X';
                    if (!strcmp(jogadores[2], jogadores[0]))
                        snprintf(jogadores[2], sizeof(jogadores[2]), "%s", jogadores[1]);
                    else
                        snprintf(jogadores[2], sizeof(jogadores[2]), "%s", jogadores[0]);
                }

            } while (ptsX < MelhorDe / 2 + 1 && ptsO < MelhorDe / 2 + 1);

            tam = strlen(jogadores[0]);

            printf("\n\n\n\n\n\n\n\n");
            printf("%49sParabéns \033[97m%s\033[0m, você ganhou!\n", "", (strcmp(jogadores[0], jogadores[2])) ? jogadores[0] : jogadores[1]);
            printf("%57sPLACAR FINAL\n", "");
            setlocale(LC_ALL, "C");
            printf("%50sÚÄÄÄÄÄÄÄÄÄÄÄÂ\033[s\n", "");
            printf("%50s³ %*s%s%s%*s\033[0m ³\n", "", (tam % 2) ? (9 - tam) / 2 : (9 - tam) / 2 + 1, "", (vez == 'X') ? "\033[91m" : "\033[94m", jogadores[0], (9 - tam) / 2, "");
            printf("%50sÃÄÄÄÄÄÄÄÄÄÄÄÅ\n", "");

            tam = strlen(jogadores[1]);

            printf("\033[uÄÄÄÄÄÄÄÄÄÄÄ¿");
            printf("\033[u\033[1B %*s%s%s%*s\033[0m ³\n", (tam % 2) ? (9 - tam) / 2 : (9 - tam) / 2 + 1, "", (vez == 'O') ? "\033[91m" : "\033[94m", jogadores[1], (9 - tam) / 2, "");
            printf("\033[u\033[2BÄÄÄÄÄÄÄÄÄÄÄ´\n");

            printf("%50s³ %5d%4s ³ %5d%4s ³\n", "", (!strcmp(jogadores[0], jogadores[2])) ? ptsO : ptsX, "", (!strcmp(jogadores[0], jogadores[2])) ? ptsX : ptsO, "");
            printf("%50sÀÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÙ\n\n\n", "");

            printf("%40s", "");
            system("pause");
            system("cls");

            snprintf(Jogadores.vencedor, sizeof(Jogadores.vencedor), "%s", (strcmp(jogadores[2], jogadores[0])) ? jogadores[0] : jogadores[1]);
            snprintf(Jogadores.perdedor, sizeof(Jogadores.perdedor), "%s", (strcmp(jogadores[2], jogadores[0])) ? jogadores[1] : jogadores[0]);
            snprintf(Jogadores.vez, sizeof(Jogadores.vez), "%s", (vez == 'X') ? "OX" : "XO");
            Jogadores.placar[0] = (vez == 'X') ? ptsO : ptsX;
            Jogadores.placar[1] = (vez == 'X') ? ptsX : ptsO;

            for (i = 0; i < 2; i++) {
                snprintf(NomeArquivo, sizeof(NomeArquivo), "dados/partida/%s.txt", jogadores[i]);

                f = fopen(NomeArquivo, "ab+");

                if (f != NULL) {
                    fwrite(&Jogadores, sizeof(Historco), 1, f);
                    fclose(f);
                } else {
                    printf("%37sErro ao abrir o arquivo! Certifique-se de que a pasta 'dados/partida' existe.\n", "");
                }
            }

        } else if (menu == '2') {
            do {
                if (strlen(NovoJogador) > 9)
                    printf("%42sO nome deve ter menos de 9 caractes!\n", "");
                printf("%46sDigite o nome do novo usuário\n\n", "");
                printf("%55s", "");
                fgets(NovoJogador, sizeof(NovoJogador), stdin);

                NovoJogador[strcspn(NovoJogador, "\n")] = '\0';

                if (strlen(NovoJogador) > sizeof(NovoJogador))
                    limpaBuffer();
                system("cls");
            } while (strlen(NovoJogador) > 9 || strlen(NovoJogador) == 0);

            f = fopen("dados/usuarios.txt", "a+");
            if (f != NULL) {
                fprintf(f, "%s\n", NovoJogador);
                fclose(f);
            }

        } else if (menu == '3') {
            tipoHitorico = '1';
            do {
                setlocale(LC_ALL, "Portuguese");
                if (tipoHitorico != '1' && tipoHitorico != '2')
                    printf("%55sInvalido!\n", "");

                printf("%41sEscolha uma opição para ver o historio: \033[s\n\n", "");
                setlocale(LC_ALL, "C");
                printf("%50sÚÄÄÄ¿ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n", "");
                printf("%50s³ 1 ³-³ Personalizada ³\n", "");
                printf("%50sÀÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
                printf("%50sÚÄÄÄ¿ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n", "");
                printf("%50s³ 2 ³-³    Pessoal    ³\n", "");
                printf("%50sÀÄÄÄÙ ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
                setlocale(LC_ALL, "Portuguese");

                printf("\033[u");
                tipoHitorico = getchar();
                if (tipoHitorico == '\n')
                    tipoHitorico = getchar();
                else
                    limpaBuffer();
                system("cls");
            } while (tipoHitorico != '1' && tipoHitorico != '2');

            qtdHistorico = 0;
            int voltarMenu = 0;

            if (tipoHitorico == '1') {
                for (int j = 0; j < 2; j++) {
                    do {
                        ImprimeUsuarios(qtdUsuarios, NumUsuario, &voltarMenu);

                        if (voltarMenu) {
                            
                            break;
                        }

                        printf("\033[u");

                        NumUsuario = getchar();
                        if (NumUsuario == '\n')
                            NumUsuario = getchar();
                        else
                            limpaBuffer();
                        system("cls");

                        if (NumUsuario == 'V' || NumUsuario == 'v') {
                            voltarMenu = 1;
                            break;
                        }
                    } while (!(NumUsuario >= '1' && NumUsuario <= qtdUsuarios + 48) || (j == 1 && NumUsuario - 48 == k));

                    if (voltarMenu) break;

                    f = fopen("dados/usuarios.txt", "r");
                    if (f != NULL) {
                        for (k = 0; k < NumUsuario - 48; k++)
                            fscanf(f, "%s", HistoricoUsuario[j]);
                        fclose(f);
                    }
                }

                if (voltarMenu) continue;

                snprintf(NomeArquivo, sizeof(NomeArquivo), "dados/partida/%s.txt", HistoricoUsuario[0]);
                f = fopen(NomeArquivo, "rb");
                if (f == NULL) {
                    printf("\n\n\n\n\n\n\n\n\n\n%37s", "");
                    printf("Erro: O jogador não possui historico de partida.\n\n\n");
                } else {
                    qtdPartidas = 0;
                    while (fread(&Jogadores, sizeof(Historco), 1, f) == 1) {
                        qtdPartidas++;
                    }
                    for (i = 0; i < qtdPartidas; i++) {
                        fseek(f, i * sizeof(Historco), SEEK_SET);
                        fread(&Jogadores, sizeof(Historco), 1, f);

                        if ((!strcmp(HistoricoUsuario[0], Jogadores.vencedor)) ^ (!strcmp(HistoricoUsuario[1], Jogadores.perdedor)) || (!strcmp(HistoricoUsuario[1], Jogadores.vencedor)) ^ (!strcmp(HistoricoUsuario[0], Jogadores.perdedor))) {

                            if (i == qtdPartidas - 1 && !qtdHistorico) {
                                printf("\n\n\n\n\n\n\n\n\n\n%37s", "");
                                printf("Erro: Os jogadores não possui historico de partida.\n\n\n");
                            }
                            continue;
                        }
                        qtdHistorico++;
                        tam = strlen(HistoricoUsuario[0]);

                        setlocale(LC_ALL, "C");
                        printf("%50sÚÄÄÄÄÄÄÄÄÄÄÄÂ\033[s\n", "");
                        printf("%50s³ %*s%s%s%*s\033[0m ³\n", "", (tam % 2) ? (9 - tam) / 2 : (9 - tam) / 2 + 1, "", (!strcmp(HistoricoUsuario[0], Jogadores.vencedor)) ? ((Jogadores.vez[0] == 'X') ? "\033[91m" : "\033[94m") : ((Jogadores.vez[0] == 'X') ? "\033[94m" : "\033[91m"), HistoricoUsuario[0], (9 - tam) / 2, "");
                        printf("%50sÃÄÄÄÄÄÄÄÄÄÄÄÅ\n", "");

                        tam = strlen(HistoricoUsuario[1]);

                        printf("\033[uÄÄÄÄÄÄÄÄÄÄÄ¿");
                        printf("\033[u\033[1B %*s%s%s%*s\033[0m ³\n", (tam % 2) ? (9 - tam) / 2 : (9 - tam) / 2 + 1, "", (!strcmp(HistoricoUsuario[1], Jogadores.vencedor)) ? ((Jogadores.vez[0] == 'X') ? "\033[91m" : "\033[94m") : ((Jogadores.vez[0] == 'X') ? "\033[94m" : "\033[91m"), HistoricoUsuario[1], (9 - tam) / 2, "");
                        printf("\033[u\033[2BÄÄÄÄÄÄÄÄÄÄÄ´\n");

                        printf("%50s³ %5d%4s ³ %5d%4s ³\n", "", (!strcmp(HistoricoUsuario[0], Jogadores.vencedor)) ? Jogadores.placar[0] : Jogadores.placar[1], "", (!strcmp(HistoricoUsuario[1], Jogadores.vencedor)) ? Jogadores.placar[0] : Jogadores.placar[1], "");
                        printf("%50sÀÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
                    }
                    fclose(f);
                }
                printf("%39s", "");
                system("pause");
                system("cls");

            } else if (tipoHitorico == '2') {
                do {
                    ImprimeUsuarios(qtdUsuarios, NumUsuario, &voltarMenu);

                    if (voltarMenu)
                        break;

                    printf("\033[u");

                    NumUsuario = getchar();
                    if (NumUsuario == '\n')
                        NumUsuario = getchar();
                    else
                        limpaBuffer();
                    system("cls");

                    if (NumUsuario == 'V' || NumUsuario == 'v') {
                        voltarMenu = 1;
                        break;
                    }
                } while (!(NumUsuario >= '1' && NumUsuario <= qtdUsuarios + 48));

                if (voltarMenu) continue;

                f = fopen("dados/usuarios.txt", "r");
                if (f != NULL) {
                    for (k = 0; k < NumUsuario - 48; k++)
                        fscanf(f, "%s", HistoricoUsuario[0]);
                    fclose(f);
                }

                snprintf(NomeArquivo, sizeof(NomeArquivo), "dados/partida/%s.txt", HistoricoUsuario[0]);

                f = fopen(NomeArquivo, "rb");
                if (f == NULL) {
                    printf("\n\n\n\n\n\n\n\n\n\n%37s", "");
                    printf("Erro: O jogador nao possui historico de partida.\n\n\n");
                } else {
                    qtdPartidas = 0;
                    while (fread(&Jogadores, sizeof(Historco), 1, f) == 1) {
                        qtdPartidas++;
                    }
                    for (i = 0; i < qtdPartidas; i++) {
                        fseek(f, i * sizeof(Historco), SEEK_SET);
                        fread(&Jogadores, sizeof(Historco), 1, f);
                        snprintf(HistoricoUsuario[1], sizeof(HistoricoUsuario[1]), "%s", (strcmp(HistoricoUsuario[0], Jogadores.vencedor)) ? Jogadores.vencedor : Jogadores.perdedor);

                        tam = strlen(HistoricoUsuario[0]);

                        setlocale(LC_ALL, "C");
                        printf("%50sÚÄÄÄÄÄÄÄÄÄÄÄÂ\033[s\n", "");
                        printf("%50s³ %*s%s%s%*s\033[0m ³\n", "", (tam % 2) ? (9 - tam) / 2 : (9 - tam) / 2 + 1, "", (!strcmp(HistoricoUsuario[0], Jogadores.vencedor)) ? ((Jogadores.vez[0] == 'X') ? "\033[91m" : "\033[94m") : ((Jogadores.vez[0] == 'X') ? "\033[94m" : "\033[91m"), HistoricoUsuario[0], (9 - tam) / 2, "");
                        printf("%50sÃÄÄÄÄÄÄÄÄÄÄÄÅ\n", "");

                        tam = strlen(HistoricoUsuario[1]);

                        printf("\033[uÄÄÄÄÄÄÄÄÄÄÄ¿");
                        printf("\033[u\033[1B %*s%s%s%*s\033[0m ³\n", (tam % 2) ? (9 - tam) / 2 : (9 - tam) / 2 + 1, "", (!strcmp(HistoricoUsuario[1], Jogadores.vencedor)) ? ((Jogadores.vez[0] == 'X') ? "\033[91m" : "\033[94m") : ((Jogadores.vez[0] == 'X') ? "\033[94m" : "\033[91m"), HistoricoUsuario[1], (9 - tam) / 2, "");
                        printf("\033[u\033[2BÄÄÄÄÄÄÄÄÄÄÄ´\n");

                        printf("%50s³ %5d%4s ³ %5d%4s ³\n", "", (!strcmp(HistoricoUsuario[0], Jogadores.vencedor)) ? Jogadores.placar[0] : Jogadores.placar[1], "", (!strcmp(HistoricoUsuario[1], Jogadores.vencedor)) ? Jogadores.placar[0] : Jogadores.placar[1], "");
                        printf("%50sÀÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÙ\n", "");
                    }
                    fclose(f);
                }
                printf("%39s", "");
                system("pause");
                system("cls");
            }
        }
    }

    return 0;
}