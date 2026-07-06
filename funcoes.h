#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include "visual.h"
#define MAX 1000

using namespace std;

struct Embarcacao{
    int linha;
    int coluna;
    char orientacao;
};

struct Configuracao{
    int linhas;
    int colunas;
    int embarcacoes;
};


bool configuracao(){

    ofstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo configuracao" << endl;
        return false;
    }

    visual_configuracao();

    Configuracao config;

    cin >> config.linhas >> config.colunas;
    cin >> config.embarcacoes;

    conf << config.linhas << " " << config.colunas << endl;
    conf << config.embarcacoes;

    conf.close();

    //Original
    /*int num_de_linhas,num_de_colunas,num_de_embarcacoes;
    cin >> num_de_linhas >> num_de_colunas;
    cin >> num_de_embarcacoes;
    conf << num_de_linhas << " " << num_de_colunas << endl; 
    conf << num_de_embarcacoes;
    conf.close();*/

//Validacao numero de embarcacoes do arquivo de configuracao:


    if(!config.linhas || !config.colunas || !config.embarcacoes){
        return false;
    }
    int numero_max_embarcacoes = (config.linhas*config.colunas)/2;

    
    if(config.embarcacoes > numero_max_embarcacoes){
    system("cls");
    cout << "Erro: quantidade de embarcacoes superior as dimensoes do tabuleiro." << endl;
    return false;
}
   /* if(config.embarcacoes > numero_max_embarcacoes)
    system("cls");
        cout << "Erro: quantidade de embarcacoes superior as dimensoes do tabuleiro." << endl;
return false;*/


       /* if(!num_de_linhas || !num_de_colunas || !num_de_embarcacoes) return false;

        int numero_max_embarcacoes = (num_de_linhas*num_de_colunas)/2;
        if(num_de_embarcacoes > numero_max_embarcacoes){
            system("cls");
            cout << "Erro: quantidade de embarcacoes superior as dimensoes do tabuleiro." << endl;
            return false;
        }*/


    return true;
}


bool leitura_jogadores(char nome1[51], char nome2[51]){

    ifstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo de configuracao." << endl;
        return false;
    }

    Configuracao config;
    

    conf >> config.linhas
         >> config.colunas
         >> config.embarcacoes;
    conf.close();

    /* int config.linhas,config.colunas,config.embarcacoes;
    conf >> config.linhas >> config.colunas >> config.embarcacoes;
    conf.close();*/


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


    /*int barco.linha,barco.coluna;
    char barco.orientacao;*/
    Embarcacao barco;

    visual_leitura_jogador(nome1);


    for(int i=0; i < config.colunas ;i++){
    //for(int i=0; i<config.colunas; i++){
        if(i<10)  cout << "\033[102m" << "  " << i;

        else  cout << "\033[102m" << " " << i;
    }
    cout << "  " << "\033[0m" << endl;

    for(int i=0;i<config.linhas;i++){
    //for(int i=0; i<config.linhas; i++){
        for(int j=0;j<config.colunas;j++){
        //for(int j=0; j<config.colunas; j++){

            if(j==0){ 
                if(i>9) cout << "\033[102m" << i << "\033[0m";
                else cout << "\033[102m" << i << " " << "\033[0m";
            }

            cout << "\033[104;34m~  " << "\033[0m"; 
        }
        cout << "  " << "\n";
    }
    cout << endl;


    for(int i=0;i<config.embarcacoes;i++){

    cin >> barco.linha
    >> barco.coluna
    >> barco.orientacao;

        jogador_1 << barco.linha
          << " "
          << barco.coluna
          << " "
          << barco.orientacao << endl;

    //for(int i=0; i<config.embarcacoes; i++){
        /*cin >> barco.linha >> barco.coluna >> barco.orientacao;
        jogador_1 << barco.linha << " " << barco.coluna << " " << barco.orientacao << endl;*/
    }


    visual_leitura_jogador(nome2);

    for(int i=0; i<config.colunas; i++){
        if(i<10)  cout << "\033[102m" << "  " << i;

        else  cout << "\033[102m" << " " << i;
    }
    cout << "  " << "\033[0m" << endl;

    for(int i=0; i<config.linhas; i++){
        for(int j=0; j<config.colunas; j++){

            if(j==0){ 
                if(i>9) cout << "\033[102m" << i << "\033[0m";
                else cout << "\033[102m" << i << " " << "\033[0m";
            }

            else cout << "\033[104;34m~  " << "\033[0m"; 
        }
        cout << "  " << "\n";
    }
    cout << endl;

    for(int i=0; i<config.embarcacoes; i++){
        cin >> barco.linha >> barco.coluna >> barco.orientacao;
        jogador_2 << barco.linha << " " << barco.coluna << " " << barco.orientacao << endl;
    }
    system("cls");

    jogador_1.close();
    jogador_2.close();
    return true;
}



bool validacao(char tabuleiro1[MAX][MAX],char tabuleiro2[MAX][MAX]){

    ifstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo configuracao" << endl;
        return false;
    }

    Configuracao config;

    conf >> config.linhas 
         >> config.colunas 
         >> config.embarcacoes;

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
        Embarcacao barco;
       
        while(jogador_1 >> barco.linha){
            jogador_1 >> barco.coluna >> barco.orientacao;

            if(barco.linha > config.linhas || barco.coluna > config.colunas){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            else if(tabuleiro1[barco.linha][barco.coluna] != 'N'){
                tabuleiro1[barco.linha][barco.coluna] = 'N';
            }

            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            if(barco.orientacao == 'V'){
                barco.linha += 1;
            }
            else if(barco.orientacao == 'H'){
                barco.coluna += 1;
            }
            else {
                cout << "Erro: barco.orientacao invalida" << endl;
                return false;
            }

            if(barco.linha > config.linhas || barco.coluna > config.colunas){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            if(tabuleiro1[barco.linha][barco.coluna] != 'N'){ 
                tabuleiro1[barco.linha][barco.coluna] = 'N';
            }

            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            contador_de_embarcacoes++;
        }
    
        if(contador_de_embarcacoes != config.embarcacoes){
            cout << "Erro: quantidade de embarcacoes do jogador 1 invalidas." << endl;
                return false;
        }
        jogador_1.close();


    //Validacao: numero de embarcacoes e posicoes. JOGADOR 2

        contador_de_embarcacoes=0;
        while(jogador_2 >> barco.linha){
            jogador_2>> barco.coluna >> barco.orientacao;

            if(barco.linha > config.linhas || barco.coluna > config.colunas){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            else if(tabuleiro2[barco.linha][barco.coluna] != 'N'){
                tabuleiro2[barco.linha][barco.coluna] = 'N';
            }

            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            if(barco.orientacao == 'V'){
                barco.linha += 1;
            }
            else if(barco.orientacao == 'H'){
                barco.coluna += 1;
            }
            else {
                cout << "Erro: barco.orientacao invalida" << endl;
                return false;
            }

            if(barco.linha > config.linhas || barco.coluna > config.colunas){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            if(tabuleiro2[barco.linha][barco.coluna] != 'N'){
                tabuleiro2[barco.linha][barco.coluna] = 'N';
            }

            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            contador_de_embarcacoes++;
        }

        if(contador_de_embarcacoes != config.embarcacoes){
            cout << "Erro: quantidade de embarcacoes invalidas." << endl;
            cout << contador_de_embarcacoes;
            return false;
        }

        jogador_2.close();
    return true;
}


bool verifica_numero_celulas(int celulas){
    return celulas;
}


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
                        if(!config) {
                            //Verifica se o arquivo de configuracao ja foi preenchido.
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

void imprime_tabuleiro_jogador(char tabuleiro[MAX][MAX], Configuracao config){


    for (int i = 0; i < config.colunas; i++) {
        if (i < 10)
            cout << "\033[102m" << "  " << i;
            else
                cout << "\033[102m" << " " << i;
        }

        cout << "  " << "\033[0m" << endl;

        for (int i = 0; i < config.linhas; i++) {
            for (int j = 0; j < config.colunas; j++) {

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


