#pragma once
#include <iostream>
#include <fstream>
#include <limits>
#include <ncurses.h>
#include "visual.h"

using namespace std;

bool ler_inteiro_valido(int &valor, const string &mensagem){
    while(true){
        if(cin >> valor) return true;
        cout << mensagem << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool ler_coordenada_valida(int &linha, int &coluna, int max_linhas, int max_colunas){
    while(true){
        if(!(cin >> linha >> coluna)){
            cout << "Entrada invalida. Informe dois numeros inteiros." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if(linha < 0 || linha >= max_linhas || coluna < 0 || coluna >= max_colunas){
            cout << "Coordenada fora do tabuleiro. Tente novamente." << endl;
            continue;
        }

        return true;
    }
}

bool ler_posicao_embarcacao(int &linha, int &coluna, char &orientacao, int max_linhas, int max_colunas){
    while(true){
        if(!(cin >> linha >> coluna >> orientacao)){
            cout << "Entrada invalida. Tente novamente." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if(linha < 0 || linha >= max_linhas || coluna < 0 || coluna >= max_colunas){
            cout << "Posicao fora do tabuleiro. Tente novamente." << endl;
            continue;
        }

        if(orientacao == 'v') orientacao = 'V';
        else if(orientacao == 'h') orientacao = 'H';

        if(orientacao != 'V' && orientacao != 'H'){
            cout << "Orientacao invalida. Use V ou H." << endl;
            continue;
        }

        int linha_final = linha;
        int coluna_final = coluna;
        if(orientacao == 'V') linha_final++;
        else coluna_final++;

        if(linha_final < 0 || linha_final >= max_linhas || coluna_final < 0 || coluna_final >= max_colunas){
            cout << "A embarcacao ultrapassa os limites do tabuleiro. Tente novamente." << endl;
            continue;
        }

        return true;
    }
}

bool configuracao(){

    visual_configuracao();
    finalizar_ncurses();

    ofstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo configuracao" << endl;
        return false;
    }

    int num_de_linhas = 0;
    int num_de_colunas = 0;
    int num_de_embarcacoes = 0;

    while(true){
        cout << "\nDigite as dimensoes do tabuleiro (linhas colunas): ";
        if(!ler_inteiro_valido(num_de_linhas, "Entrada invalida. Tente novamente.")) continue;
        if(!ler_inteiro_valido(num_de_colunas, "Entrada invalida. Tente novamente.")) continue;

        cout << "Digite o numero de embarcacoes: ";
        if(!ler_inteiro_valido(num_de_embarcacoes, "Entrada invalida. Tente novamente.")) continue;

        if(num_de_linhas <= 0 || num_de_colunas <= 0 || num_de_embarcacoes <= 0){
            cout << "Valores invalidos. Informe numeros positivos." << endl;
            continue;
        }

        break;
    }

    conf << num_de_linhas << " " << num_de_colunas << endl; 
    conf << num_de_embarcacoes;
    conf.close();

    int numero_max_embarcacoes = (num_de_linhas*num_de_colunas)/2;
    if(num_de_embarcacoes > numero_max_embarcacoes){
        limpar_tela();
        cout << "Erro: quantidade de embarcacoes superior as dimensoes do tabuleiro." << endl;
        return false;
    }

    inicializar_ncurses();
    return true;
}


bool leitura_jogadores(char nome_j1[51],char nome_j2[51]){

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

    char tabuleiro_referencia_jogador1[num_linhas][num_colunas];
    char tabuleiro_referencia_jogador2[num_linhas][num_colunas];
    for(int i=0;i<num_linhas;i++){
        for(int j=0;j<num_colunas;j++){
            tabuleiro_referencia_jogador1[i][j]='~';
            tabuleiro_referencia_jogador2[i][j]='~';
        }
    }

    int linha,coluna;
    char orientacao;

    visual_leitura_jogador(nome_j1);
    finalizar_ncurses();

    cout << "\033[102m";
    for(int i=0; i<num_colunas; i++){
        if(i<10) cout << "  " << i;
        else cout << " " << i;
    }
    cout << "  \033[0m" << endl;

    for(int i=0; i<num_linhas; i++){
        cout << "\033[102m";
        if(i>9) cout << i;
        else cout << i << " ";
        cout << "\033[0m";

        for(int j=0; j<num_colunas; j++){
            cout << "\033[104;34m" << tabuleiro_referencia_jogador1[i][j] << "  " << "\033[0m";
        }
        cout << "  \n";
    }
    cout << endl;

    for(int i=0; i<num_embarcacoes; i++){
        cout << "\n" << nome_j1 << ", posicione seu barco " << (i + 1) << " de " << num_embarcacoes << endl;
        
        while(true){
            ler_posicao_embarcacao(linha, coluna, orientacao, num_linhas, num_colunas);
            
            // Verifica se a primeira célula está ocupada
            if(tabuleiro_referencia_jogador1[linha][coluna] != '~'){
                cout << "Posicao ja ocupada. Tente novamente." << endl;
                continue;
            }
            
            // Verifica se a segunda célula está ocupada
            int linha_final = linha;
            int coluna_final = coluna;
            if(orientacao == 'V') linha_final++;
            else coluna_final++;
            
            if(tabuleiro_referencia_jogador1[linha_final][coluna_final] != '~'){
                cout << "Posicao ja ocupada. Tente novamente." << endl;
                continue;
            }
            
            break;
        }
        
        // Atualiza tabuleiro para mostrar barco posicionado
        tabuleiro_referencia_jogador1[linha][coluna] = 'N';
        if(orientacao == 'V') {
            tabuleiro_referencia_jogador1[linha + 1][coluna] = 'N';
        } else {
            tabuleiro_referencia_jogador1[linha][coluna + 1] = 'N';
        }
        
        // Salva no arquivo
        jogador_1 << linha << " " << coluna << " " << orientacao << endl;
        
        // Se não for o último barco, mostra o tabuleiro atualizado
        if(i < num_embarcacoes - 1) {
            cout << "\n--- Tabuleiro atualizado ---\n" << endl;
            cout << "\033[102m";
            for(int k=0; k<num_colunas; k++){
                if(k<10) cout << "  " << k;
                else cout << " " << k;
            }
            cout << "  \033[0m" << endl;

            for(int j=0; j<num_linhas; j++){
                cout << "\033[102m";
                if(j>9) cout << j;
                else cout << j << " ";
                cout << "\033[0m";

                for(int k=0; k<num_colunas; k++){
                    if(tabuleiro_referencia_jogador1[j][k] == 'N') {
                        cout << "\033[104;92mN\033[0m ";
                    } else {
                        cout << "\033[104;34m~\033[0m ";
                    }
                }
                cout << "\n";
            }
            cout << endl;
        }
    }


    visual_leitura_jogador(nome_j2);
    finalizar_ncurses();

    cout << "\033[102m";
    for(int i=0; i<num_colunas; i++){
        if(i<10) cout << "  " << i;
        else cout << " " << i;
    }
    cout << "  \033[0m" << endl;

    for(int i=0; i<num_linhas; i++){
        cout << "\033[102m";
        if(i>9) cout << i;
        else cout << i << " ";
        cout << "\033[0m";

        for(int j=0; j<num_colunas; j++){
            cout << "\033[104;34m" << tabuleiro_referencia_jogador2[i][j] << "  " << "\033[0m";
        }
        cout << "  \n";
    }
    cout << endl;

    for(int i=0; i<num_embarcacoes; i++){
        cout << "\n" << nome_j2 << ", posicione seu barco " << (i + 1) << " de " << num_embarcacoes << endl;
        
        while(true){
            ler_posicao_embarcacao(linha, coluna, orientacao, num_linhas, num_colunas);
            
            // Verifica se a primeira célula está ocupada
            if(tabuleiro_referencia_jogador2[linha][coluna] != '~'){
                cout << "Posicao ja ocupada. Tente novamente." << endl;
                continue;
            }
            
            // Verifica se a segunda célula está ocupada
            int linha_final = linha;
            int coluna_final = coluna;
            if(orientacao == 'V') linha_final++;
            else coluna_final++;
            
            if(tabuleiro_referencia_jogador2[linha_final][coluna_final] != '~'){
                cout << "Posicao ja ocupada. Tente novamente." << endl;
                continue;
            }
            
            break;
        }
        
        // Atualiza tabuleiro para mostrar barco posicionado
        tabuleiro_referencia_jogador2[linha][coluna] = 'N';
        if(orientacao == 'V') {
            tabuleiro_referencia_jogador2[linha + 1][coluna] = 'N';
        } else {
            tabuleiro_referencia_jogador2[linha][coluna + 1] = 'N';
        }
        
        // Salva no arquivo
        jogador_2 << linha << " " << coluna << " " << orientacao << endl;
        
        // Se não for o último barco, mostra o tabuleiro atualizado
        if(i < num_embarcacoes - 1) {
            cout << "\n--- Tabuleiro atualizado ---\n" << endl;
            cout << "\033[102m";
            for(int k=0; k<num_colunas; k++){
                if(k<10) cout << "  " << k;
                else cout << " " << k;
            }
            cout << "  \033[0m" << endl;

            for(int j=0; j<num_linhas; j++){
                cout << "\033[102m";
                if(j>9) cout << j;
                else cout << j << " ";
                cout << "\033[0m";

                for(int k=0; k<num_colunas; k++){
                    if(tabuleiro_referencia_jogador2[j][k] == 'N') {
                        cout << "\033[104;92mN\033[0m ";
                    } else {
                        cout << "\033[104;34m~\033[0m ";
                    }
                }
                cout << "\n";
            }
            cout << endl;
        }
    }

    jogador_1.close();
    jogador_2.close();
    return true;
}



bool validacao(){

    finalizar_ncurses();

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

        char tabuleiro1[num_linhas][num_colunas];
        char tabuleiro2[num_linhas][num_colunas];
        for(int i=0;i<num_linhas;i++){
            for(int j=0; j<num_colunas; j++){
                tabuleiro1[i][j] = '~';
                tabuleiro2[i][j] = '~';

            }
        }
        
        while(jogador_1 >> linha){
            jogador_1 >> coluna >> orientacao;

            if(linha < 0 || linha >= num_linhas || coluna < 0 || coluna >= num_colunas){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            if(tabuleiro1[linha][coluna] == '~'){
                tabuleiro1[linha][coluna] = 'N';
            }
            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            if(orientacao == 'V'){
                linha += 1;
            }
            else if(orientacao == 'H'){
                coluna += 1;
            }
            else {
                cout << "Erro: orientacao invalida" << endl;
                return false;
            }

            if(linha < 0 || linha >= num_linhas || coluna < 0 || coluna >= num_colunas){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            if(tabuleiro1[linha][coluna] == '~'){
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

            if(linha < 0 || linha >= num_linhas || coluna < 0 || coluna >= num_colunas){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            if(tabuleiro2[linha][coluna] == '~'){
                tabuleiro2[linha][coluna] = 'N';
            }
            else {
                cout << "Erro: posicao ja ocupada por outra embarcacao" << endl;
                return false;
            }

            if(orientacao == 'V'){
                linha += 1;
            }
            else if(orientacao == 'H'){
                coluna += 1;
            }
            else {
                cout << "Erro: orientacao invalida" << endl;
                return false;
            }

            if(linha < 0 || linha >= num_linhas || coluna < 0 || coluna >= num_colunas){
                cout << "Erro: embarcacao fora do limite." << endl;
                return false;
            }

            if(tabuleiro2[linha][coluna] == '~'){
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


bool verifica_numero_celulas(int celulas){
    return celulas;
}


bool menu(){

    bool config = false;
    int linha = 1;
    menu_visual(linha);

    while(true){
        int tecla = getch();
        switch(tecla){
            case KEY_UP:
                if(linha > 1){
                    linha--;
                }
                break;

            case KEY_DOWN:
                if(linha < 3){
                    linha++;
                }
                break;

            case 10:
            case 13:
                if(linha == 1){
                    limpar_tela();
                    if(!config) {
                        if(!configuracao()) return false;
                        limpar_tela();
                    }
                    return true;
                }
                else if(linha == 2){
                    config = true;
                    linha = 1;
                    if (!configuracao()) return false;
                    limpar_tela();
                    menu_visual(linha);
                    break;
                }
                else if(linha == 3){
                    limpar_tela();
                    return false;
                }
                break;
        }

        menu_visual(linha);
    }
}



