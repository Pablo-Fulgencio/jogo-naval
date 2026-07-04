#pragma once
#include <iostream>

using namespace std;

void jogo_naval(){
    cout << "\033[3;54H";
    cout << "\033[106;31m Jogo Naval \033[0m" << endl;
    cout << "\n";
}

void menu_visual(){

    cout << "\033[5;54H";
    cout << "\033[5;106;31m Bem-Vindo(a) ao Jogo Naval \033[0m" << endl;
    cout << "\033[9;60H";
    cout << "> Jogar" << endl;
    cout << "\033[10;60H";
    cout << "  Configuracoes" << endl;
    cout << "\033[11;60H";
    cout << "  Sair" << endl;
    cout << "\033[0m";
}


void visual_configuracao(){
    
    system("cls");
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

    system("cls");
    jogo_naval();

    cout << nome << " Digite as linhas e as colunas das suas embarcacoes" << endl;
    cout << "Digite tambem as orientacoes: V(vertical), ou H(horizontal)" << endl;
    cout << "Utilize a formatacao a seguir: \n";
    cout << "x1 y1 (V/H)\nx2 y2 (V/H)\n.    .    .\n.    .    .\n.    .    ." << endl;
}


