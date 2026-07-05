#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include "funcoes.h"
using namespace std;

void print_board_header(int num_colunas){
    cout << "   ";
    for(int i = 0; i < num_colunas; i++){
        if(i < 10) cout << "  " << i;
        else cout << " " << i;
    }
    cout << endl;
}

void print_board_row(int linha, const char row[], int num_colunas, bool mostra_navios){
    if(linha < 10) cout << linha << "  ";
    else cout << linha << " ";
    
    for(int j = 0; j < num_colunas; j++){
        char c = row[j];
        cout << " ";
        if(mostra_navios){
            if(c == 'N') cout << "\033[104;92mN\033[0m ";
            else cout << "\033[104;34m~\033[0m ";
        } else {
            if(c == 'X') cout << "\033[104;92mX\033[0m ";
            else if(c == 'O') cout << "\033[104;91mO\033[0m ";
            else cout << "\033[104;34m~\033[0m ";
        }
    }
    cout << endl;
}

int main(){

    inicializar_ncurses();
    limpar_tela();
    if(!menu()) {
        finalizar_ncurses();
        return 0;
    }

    inicializar_ncurses();

    char nome_j1[51];
    char nome_j2[51];
    echo();
    curs_set(1);

    printw("Jogador 1:\nDigite seu nome: ");
    refresh();
    getnstr(nome_j1, 50);

    printw("\nJogador 2:\nDigite seu nome: ");
    refresh();
    getnstr(nome_j2, 50);

    noecho();
    curs_set(0);

    if(!leitura_jogadores(nome_j1,nome_j2)) {
        finalizar_ncurses();
        return 1;
    }
    if (!validacao()) {
        finalizar_ncurses();
        return 1;
    }

    ifstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo de configuracao." << endl;
        return 1;
    }

    //Leitura de numero de linhas,colunas e numero de embarcacoes do arquivo de configuracao:
    int num_linhas,num_colunas,embarcacoes;
    conf >> num_linhas >> num_colunas >> embarcacoes;
    conf.close();

    //Declaracao do numero de celulas(navios completos) de cada jogador:
    int numero_de_celulas_j1 = embarcacoes*2;
    int numero_de_celulas_j2 = embarcacoes*2;

    //Declaracao de tabuleiros dos jogadores e dos tabuleiros de referencia:
    char tabuleiro_jogador1[num_linhas][num_colunas];
    char tabuleiro_jogador2[num_linhas][num_colunas];
    char tabuleiro_referencia_jogador1[num_linhas][num_colunas];
    char tabuleiro_referencia_jogador2[num_linhas][num_colunas];

    //Inicialização dos tabuleiros com ~ ("agua") 
    for(int i=0;i<num_linhas;i++){
        for(int j=0;j<num_colunas;j++){
            tabuleiro_jogador1[i][j]='~';
            tabuleiro_jogador2[i][j]='~';
            tabuleiro_referencia_jogador1[i][j]='~';
            tabuleiro_referencia_jogador2[i][j]='~';
        }
        }


    ifstream player1("jogador1.txt");
    if(!player1){
        cout << "Erro ao abrir arquivo de jogador 1" << endl;
        return 1;
    }

    ifstream player2("jogador2.txt");
    if(!player2){
        cout << "Erro ao abrir arquivo de jogador 2" << endl;
        return 1;
    }    


    //Leitura e preenchimento dos tabuleiros dos respectivos jogadores:
    int linha,coluna;
    char orientacao;

    while(player1 >> linha){
        player1 >> coluna >> orientacao;
        tabuleiro_jogador1[linha][coluna]='N';

        if(orientacao == 'V')
            linha+=1;

        else if(orientacao == 'H')
            coluna+=1;

        tabuleiro_jogador1[linha][coluna] = 'N';
    }

    while(player2 >> linha){
        player2 >> coluna >> orientacao;
        tabuleiro_jogador2[linha][coluna]='N';

        if(orientacao == 'V')
            linha+=1;

        else if(orientacao == 'H')
            coluna+=1;

        tabuleiro_jogador2[linha][coluna] = 'N';
    }
    player1.close();
    player2.close();


    //Jogo jogador 1:
    int alternador = 0;
    while(true){

        //Alternador: alterna a vez da jogada entre par(jogador 1) e impar(jogador 2).
        if(alternador%2==0){
            alternador += 1;
            limpar_tela();

            cout << "\n\nVez de: " << nome_j1 << endl;
            cout << "\nSeu tabuleiro:" << endl;

            print_board_header(num_colunas);
            for(int i = 0; i < num_linhas; i++){
                print_board_row(i, tabuleiro_jogador1[i], num_colunas, true);
            }

            cout << "\nSeu campo de ataques:" << endl;
            print_board_header(num_colunas);
            for(int i = 0; i < num_linhas; i++){
                print_board_row(i, tabuleiro_referencia_jogador1[i], num_colunas, false);
            }

            while(true){
                cout << "\nDigite a linha e a coluna do disparo: ";
                if(!ler_coordenada_valida(linha, coluna, num_linhas, num_colunas)) continue;

                if(tabuleiro_referencia_jogador1[linha][coluna] == 'X' || tabuleiro_referencia_jogador1[linha][coluna] == 'O'){
                    cout << "\nVoce ja realizou um disparo nessa posicao." << endl;
                    continue;
                }

                break;
            }

            if(tabuleiro_jogador2[linha][coluna] == 'N'){
                cout << "Voce acertou uma embarcacao!" << endl;
                tabuleiro_referencia_jogador1[linha][coluna] = 'X';

                cout << "Tabuleiro atualizado: " << endl;
                print_board_header(num_colunas);
                for(int i = 0; i < num_linhas; i++){
                    print_board_row(i, tabuleiro_referencia_jogador1[i], num_colunas, false);
                }
            
                numero_de_celulas_j2--;
                if(!verifica_numero_celulas(numero_de_celulas_j2)){
                    cout << "Todas as embarcacoes de "<< nome_j2 << " foram afundadas!" << endl;
                    cout << nome_j1 << " Venceu!\nParabens!" << endl;
                    cout << "\nPressione Enter para encerrar..." << endl;
                    cin.ignore();
                    finalizar_ncurses();
                    return 0;
                }
            }

            else if(tabuleiro_jogador2[linha][coluna] == '~'){
                cout << "Voce errou." << endl;
                tabuleiro_referencia_jogador1[linha][coluna] = 'O';

                cout << "Tabuleiro atualizado: " << endl;
                print_board_header(num_colunas);
                for(int i = 0; i < num_linhas; i++){
                    print_board_row(i, tabuleiro_referencia_jogador1[i], num_colunas, false);
                }
            }
        }


        //Jogo Jogador 2:
        else {
            alternador += 1;
            limpar_tela();
            cout << "\n\nVez de: " << nome_j2 << endl;
            cout << "\nSeu tabuleiro:" << endl;

            print_board_header(num_colunas);
            for(int i = 0; i < num_linhas; i++){
                print_board_row(i, tabuleiro_jogador2[i], num_colunas, true);
            }

            cout << "\nSeu campo de ataques:" << endl;
            print_board_header(num_colunas);
            for(int i = 0; i < num_linhas; i++){
                print_board_row(i, tabuleiro_referencia_jogador2[i], num_colunas, false);
            }

            while(true){
                cout << "\nDigite a linha e a coluna do disparo: ";
                if(!ler_coordenada_valida(linha, coluna, num_linhas, num_colunas)) continue;

                if(tabuleiro_referencia_jogador2[linha][coluna] == 'X' || tabuleiro_referencia_jogador2[linha][coluna] == 'O'){
                    cout << "\nVoce ja realizou um disparo nessa posicao." << endl;
                    continue;
                }

                break;
            }

            if(tabuleiro_jogador1[linha][coluna] == 'N'){
                cout << "Voce acertou uma embarcacao!" << endl;
                tabuleiro_referencia_jogador2[linha][coluna] = 'X';

                cout << "Tabuleiro atualizado: " << endl;
                print_board_header(num_colunas);
                for(int i = 0; i < num_linhas; i++){
                    print_board_row(i, tabuleiro_referencia_jogador2[i], num_colunas, false);
                }

                numero_de_celulas_j1--;
                if(!verifica_numero_celulas(numero_de_celulas_j1)){
                    cout << "Todas as embarcacoes de "<< nome_j1 << " foram afundadas!" << endl;
                    cout << nome_j2 << " Venceu!\nParabens!" << endl;
                    cout << "\nPressione Enter para encerrar..." << endl;
                    cin.ignore();
                    finalizar_ncurses();
                    return 0;
                }
            }

                        else if(tabuleiro_jogador1[linha][coluna] == '~'){
                cout << "Voce errou." << endl;
                tabuleiro_referencia_jogador2[linha][coluna] = 'O';

                cout << "Tabuleiro atualizado: " << endl;
                print_board_header(num_colunas);
                for(int i = 0; i < num_linhas; i++){
                    print_board_row(i, tabuleiro_referencia_jogador2[i], num_colunas, false);
                }
            }
        }
    }
    finalizar_ncurses();
}

