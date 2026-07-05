#pragma once
#include <iostream>
#include <ncurses.h>

using namespace std;

void inicializar_ncurses(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void limpar_tela(){
    clear();
    refresh();
}

void finalizar_ncurses(){
    endwin();
}

void jogo_naval(){
    cout << "\033[3;54H";
    cout << "\033[106;31m Jogo Naval \033[0m" << endl;
    cout << "\n";
}

void menu_visual(int opcao_selecionada = 1){
    clear();
    mvprintw(2, 20, "Bem-Vindo(a) ao Jogo Naval");
    mvprintw(6, 20, "%s Jogar", opcao_selecionada == 1 ? ">" : " ");
    mvprintw(8, 20, "%s Configuracoes", opcao_selecionada == 2 ? ">" : " ");
    mvprintw(10, 20, "%s Sair", opcao_selecionada == 3 ? ">" : " ");
    refresh();
}


void visual_configuracao(){
    
    limpar_tela();
    jogo_naval();

    cout << "\033[32m";
    cout << "\nConsideracoes iniciais:" << endl;
    cout << "Cada partida sera composta por dois jogadores, onde cada um escolhera as posicoes inciais de suas embarcacoes." << endl;
    cout << "Durante a partida, cada jogador escolhera, quando sua vez, uma posicao do tabuleiro para atacar" << endl;
    cout << "As posicoes de ataque sao organizadas em x e y, onde o primeiro digito refere-se a posicao x e o segundo a posicao y do tabuleiro." << endl;
    cout << "Durante os ataques, nao eh necessario escolher uma orientacao (V ou H)" << endl;
    cout << "Nao esqueca que a posicao inicial do tabuleiro comeca em (0,0)!!" << endl;
    cout << "Para comecar, defina primeiro as dimensoes iniciais do tabuleiro: Numero de linhas e Colunas, respectivamente: Logo em seguida, defina o numero de embarcacoes da partida" << endl; 
    cout << "\033[0m";
}


void visual_leitura_jogador(char nome[51]){

    limpar_tela();
    jogo_naval();

    cout << nome << " Digite as linhas e as colunas das suas embarcacoes" << endl;
    cout << "Digite tambem as orientacoes: V(vertical), ou H(horizontal)" << endl;
    cout << "Utilize a formatacao a seguir: \n";
    cout << "x1 y1 (V/H)\nx2 y2 (V/H)\n.    .    .\n.    .    .\n.    .    ." << endl;
}


