#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void ImprimeUsuarios(char qtdUsuarios, char NumUsuario);

void EscolhaMenu(char *menu);

void ImprimeLayout(char velha[], int n);

void ImprimeInicial();

void CondicaoVitoria(char velha[], int n, int *vitoria);

void resultado(char velha[], int n, int vitoria, char vez);

void limpaBuffer();

void imprimePlacar(int ptsX, int ptsO, const char *jogador1, const char *jogador2, const char VezJogador1);