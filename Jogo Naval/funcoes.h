#pragma once
#include <iostream>
#define MAX 100

using namespace std;

//Estrutura com dados do jogo dos jogadores
struct Jogador{
    char nome[51];
    char tabuleiro[MAX][MAX];
    char tabuleiro_referencia[MAX][MAX];
};

void imprime_tabuleiro_jogador(char tabuleiro[MAX][MAX], int num_linhas, int num_colunas);

void jogo_naval();

void menu_visual();

void visual_configuracao();

void visual_leitura_jogador(char nome[]);

//Funcao que recebe as dimensoes do tabuleiro a ser usado durante o jogo e arquivando.
bool configuracao();

//Funcao menu.
bool menu();

//Funcao que recebe as posicoes das embarcacoes dos respectivos jogadores e armazena em cada arquivo separado.
bool leitura_jogadores(char nome1[51], char nome2[51]);


//Funcao que valida as condicoes de jogo e retorna se tudo esta ou nao dentro dos limites definidos no arquivo de configuracao.
bool validacao(char tabuleiro1[MAX][MAX],char tabuleiro2[MAX][MAX]);


//Verifica se ainda há embarcacoes no tabuleiro.
bool verifica_numero_celulas(int celulas);
