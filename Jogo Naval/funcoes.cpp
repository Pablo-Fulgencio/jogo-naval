#include <iostream>
#include <fstream>
#include <conio.h>
#include "funcoes.h"

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
    cout << "Durante a partida, cada jogador escolhera, quando sua vez, uma posicao do tabuleiro inimigo para atacar." << endl;
    cout << "As posicoes de ataque sao organizadas em x e y, onde o primeiro digito refere-se a linha e o segundo a coluna do tabuleiro." << endl;
    cout << "Nao esqueca que a posicao inicial do tabuleiro comeca em (0,0)!!" << endl;
    cout << "Para comecar, defina primeiro as dimensoes iniciais do tabuleiro: Numero de linhas e Colunas e o numero de embarcacoes da partida" << endl; 
    cout << "\033[0m";
}

void visual_leitura_jogador(char nome[]){

    system("cls");
    jogo_naval();

    cout << nome << " Digite as linhas e as colunas das suas embarcacoes" << endl;
    cout << "Digite tambem as orientacoes: V(vertical), ou H(horizontal)" << endl;
    cout << "Utilize a formatacao a seguir: \n";
    cout << "x1 y1 (V/H)\nx2 y2 (V/H)\n.    .    .\n.    .    .\n.    .    ." << endl;
}


void imprime_tabuleiro_jogador(char tabuleiro[MAX][MAX], int num_linhas, int num_colunas){


        for (int i = 0; i < num_colunas; i++) {
            if (i < 10)
                cout << "\033[102m" << "  " << i;
            else
                cout << "\033[102m" << " " << i;
        }
        cout << "  " << "\033[0m" << endl;

        for (int i = 0; i < num_linhas; i++) {
            for (int j = 0; j < num_colunas; j++) {

                if (j == 0) {
                    if (i > 9)
                        cout << "\033[102m" << i << "\033[0m";
                    else
                        cout << "\033[102m" << i << " " << "\033[0m";
                }

                if (tabuleiro[i][j] == 'X')
                    cout << "\033[104;92mX  " << "\033[0m";

                else if (tabuleiro[i][j] == 'O')
                    cout << "\033[104;91mO  " << "\033[0m";

                else if (tabuleiro[i][j] == '~')
                    cout << "\033[104;34m~  " << "\033[0m";
            }

            cout << "  " << "\n";
        }
}

bool configuracao(){

    ofstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo configuracao" << endl;
        return false;
    }

    visual_configuracao();
    int num_de_linhas,num_de_colunas,num_de_embarcacoes;
    cin >> num_de_linhas >> num_de_colunas;
    cin >> num_de_embarcacoes;
    conf << num_de_linhas << " " << num_de_colunas << endl; 
    conf << num_de_embarcacoes;
    conf.close();

    //Validacao numero de embarcacoes do arquivo de configuracao:
    if(num_de_linhas <= 0 || num_de_colunas <=0 || num_de_embarcacoes <=0) return false;

    //Numero maximo de embarcacoes possiveis com base no tamanho do tabuleiro.
    int numero_max_embarcacoes = (num_de_linhas*num_de_colunas)/2;
    if(num_de_embarcacoes > numero_max_embarcacoes){
        system("cls");
        cout << "Erro: quantidade de embarcacoes superior as dimensoes do tabuleiro." << endl;
        return false;
    }
    return true;
}

//Funcao menu.
bool menu(){

        bool  config = false;
        int linha = 1;
        menu_visual();
        while(true){
            int tecla = _getch();
                if(tecla == 0 || tecla==224){
                    tecla = _getch();
                }
            switch(tecla){
                case 72: //Para cima
                    if(linha == 2){
                        linha--;
                        cout << "\033[10;60H";
                        cout << " ";
                        cout << "\033[9;60H";
                        cout << ">";
                        break;
                    }
                    else if(linha == 3){
                        linha--;
                        cout << "\033[11;60H";
                        cout << " ";
                        cout << "\033[10;60H";
                        cout << ">";
                        break;
                    }
                    else {
                        break;
                    }

                case 80: // Para baixo
                    if(linha == 1){
                        linha++;
                        cout << "\033[9;60H";
                        cout << " ";
                        cout << "\033[10;60H";
                        cout << ">";
                        break;
                    }
                    else if(linha == 2){
                        linha++;
                        cout << "\033[10;60H";
                        cout << " ";
                        cout << "\033[11;60H";
                        cout << ">";
                        break;
                    }
                    else {
                        break;
                    }

                case 13: // Enter
                    if(linha == 1){ // jogar
                        system("cls");
                        //Verifica se o arquivo de configuracao ja foi preenchido.
                        if(!config) {
                            if(!configuracao()) return false;
                            system("cls");
                        }
                        return true;
                    }
                    else if(linha == 2){ // configuracao
                        config = true;
                        linha = 1;
                        if (!configuracao()) return false;
                        system("cls");
                        menu_visual();
                        break;
                    }
                    else if(linha == 3){ // sair
                        system("Cls");
                        return false;
                    }
            }
        }
}

//Funcao que recebe as posicoes das embarcacoes dos respectivos jogadores e armazena em cada arquivo separado.
bool leitura_jogadores(char nome1[51], char nome2[51]){

    ifstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo de configuracao." << endl;
        return false;
    }

    int num_linhas,num_colunas,num_embarcacoes;
    conf >> num_linhas >> num_colunas >> num_embarcacoes;
    conf.close();

    ofstream jogador_1("jogador1.txt");
    if(!jogador_1){
        cout << "Erro ao abrir arquivo do jogador 1" << endl;
        return false;
    }

    ofstream jogador_2("jogador2.txt");
    if(!jogador_2){
        cout << "Erro ao abrir arquivo do jogador 2" << endl;
        return false;
    }

    int linha,coluna;
    char orientacao;

    visual_leitura_jogador(nome1);

    //Imprime tabuleiro com marcacoes e ~ (agua).
    for(int i=0; i<num_colunas; i++){
        if(i<10)  cout << "\033[102m" << "  " << i;

        else  cout << "\033[102m" << " " << i;
    }
    cout << "  " << "\033[0m" << endl;

    for(int i=0; i<num_linhas; i++){
        for(int j=0; j<num_colunas; j++){

            if(j==0){ 
                if(i>9) cout << "\033[102m" << i << "\033[0m";
                else cout << "\033[102m" << i << " " << "\033[0m";
            }

            cout << "\033[104;34m~  " << "\033[0m"; 
        }
        cout << "  " << "\n";
    }
    cout << endl;

    for(int i=0; i<num_embarcacoes; i++){
        cin >> linha >> coluna >> orientacao;
        jogador_1 << linha << " " << coluna << " " << orientacao << endl;
    }

    visual_leitura_jogador(nome2);

    //Imprime tabuleiro com marcacoes e ~ (agua).
    for(int i=0; i<num_colunas; i++){
        if(i<10)  cout << "\033[102m" << "  " << i;

        else  cout << "\033[102m" << " " << i;
    }
    cout << "  " << "\033[0m" << endl;

    for(int i=0; i<num_linhas; i++){
        for(int j=0; j<num_colunas; j++){

            if(j==0){ 
                if(i>9) cout << "\033[102m" << i << "\033[0m";
                else cout << "\033[102m" << i << " " << "\033[0m";
            }

            cout << "\033[104;34m~  " << "\033[0m"; 
        }
        cout << "  " << "\n";
    }
    cout << endl;

    for(int i=0; i<num_embarcacoes; i++){
        cin >> linha >> coluna >> orientacao;
        jogador_2 << linha << " " << coluna << " " << orientacao << endl;
    }
    system("cls");

    jogador_1.close();
    jogador_2.close();
    return true;
}

//Funcao que valida as condicoes de jogo e retorna se tudo esta ou nao dentro dos limites definidos no arquivo de configuracao.
bool validacao(char tabuleiro1[MAX][MAX],char tabuleiro2[MAX][MAX]){

    ifstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo configuracao" << endl;
        return false;
    }

    int num_linhas,num_colunas,num_embarcacoes;
    conf >> num_linhas >> num_colunas >> num_embarcacoes;
    conf.close();

    ifstream jogador_1("jogador1.txt");
    if(!jogador_1){
        cout << "Erro ao abrir arquivo do jogador 1" << endl;
        return false;
    }
    
    ifstream jogador_2("jogador2.txt");
    if(!jogador_2){
        cout << "Erro ao abrir arquivo do jogador 2" << endl;
        return false;
    }

    //Validacao: numero de embarcacoes e posicoes. JOGADOR 1
        int contador_de_embarcacoes=0;
        int linha,coluna;
        char orientacao;
       
        while(jogador_1 >> linha){
            jogador_1 >> coluna >> orientacao;

            if(linha >= num_linhas || coluna >= num_colunas || linha < 0 || coluna < 0){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            else if(tabuleiro1[linha][coluna] != 'N'){
                tabuleiro1[linha][coluna] = 'N';
            }

            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            if(orientacao == 'V' || orientacao == 'v'){
                linha += 1;
            }
            else if(orientacao == 'H' || orientacao == 'h'){
                coluna += 1;
            }
            else {
                cout << "Erro: orientacao invalida" << endl;
                return false;
            }

            if(linha >= num_linhas || coluna >= num_colunas || linha < 0 || coluna < 0){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            else if(tabuleiro1[linha][coluna] != 'N'){ 
                tabuleiro1[linha][coluna] = 'N';
            }

            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            contador_de_embarcacoes++;
        }
    
        if(contador_de_embarcacoes != num_embarcacoes){
            cout << "Erro: quantidade de embarcacoes do jogador 1 invalidas." << endl;
                return false;
        }
        jogador_1.close();


    //Validacao: numero de embarcacoes e posicoes. JOGADOR 2

        contador_de_embarcacoes=0;
        while(jogador_2 >> linha){
            jogador_2>> coluna >> orientacao;

            if(linha >= num_linhas || coluna >= num_colunas || linha < 0 || coluna < 0){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            else if(tabuleiro2[linha][coluna] != 'N'){
                tabuleiro2[linha][coluna] = 'N';
            }

            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            if(orientacao == 'V' || orientacao == 'v'){
                linha += 1;
            }
            else if(orientacao == 'H' || orientacao == 'h'){
                coluna += 1;
            }
            else {
                cout << "Erro: orientacao invalida" << endl;
                return false;
            }

            if(linha >= num_linhas || coluna >= num_colunas || linha < 0 || coluna < 0){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            if(tabuleiro2[linha][coluna] != 'N'){
                tabuleiro2[linha][coluna] = 'N';
            }

            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            contador_de_embarcacoes++;
        }

        if(contador_de_embarcacoes != num_embarcacoes){
            cout << "Erro: quantidade de embarcacoes invalidas." << endl;
            cout << contador_de_embarcacoes;
            return false;
        }

        jogador_2.close();
    return true;
}

//Verifica se ainda há embarcacoes no tabuleiro.
bool verifica_numero_celulas(int celulas){
    return celulas;
}

