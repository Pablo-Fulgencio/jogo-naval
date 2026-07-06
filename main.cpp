#include <iostream>
#include <fstream>
#include "funcoes.h"
#define MAX 100
using namespace std;

//Estrutura com dados do jogo dos jogadores
struct Jogador{
    char nome[51];
    char tabuleiro[MAX][MAX];
    char tabuleiro_referencia[MAX][MAX];
};

int main(){

    system("cls");
    if(!menu()) return 0;

    Jogador jogador1,jogador2;
    cout << "Jogador 1:\nDigite seu nome: ";
    cin.ignore(1000, '\n');
    cin.getline(jogador1.nome,51);

    cout << "\n";
    cout << "Jogador 2:\nDigite seu nome: ";
    cin.getline(jogador2.nome,51);

    //Leitura de numero de linhas,colunas e numero de embarcacoes do arquivo de configuracao:
    ifstream conf("config.txt");
    if(!conf){
        cout << "Erro ao abrir arquivo de configuracao" << endl;
        return 1;
    }

    int num_linhas,num_colunas,embarcacoes;
    conf >> num_linhas >> num_colunas >> embarcacoes;
    conf.close();

    //inicializacao dos tabuleiros.
    for(int i=0;i<num_linhas;i++){
        for(int j=0;j<num_colunas;j++){
            jogador1.tabuleiro[i][j]='~';
            jogador2.tabuleiro[i][j]='~';
            jogador1.tabuleiro_referencia[i][j]='~';
            jogador2.tabuleiro_referencia[i][j]='~';
        }
    }

    if(!leitura_jogadores(jogador1.nome,jogador2.nome)) return false;
    if (!validacao(jogador1.tabuleiro,jogador2.tabuleiro)) return false;

    //Declaracao do numero de celulas(navios completos) de cada jogador:
    int numero_de_celulas_j1 = embarcacoes*2;
    int numero_de_celulas_j2 = embarcacoes*2;

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
        jogador1.tabuleiro[linha][coluna]='N';

        if(orientacao == 'V' || orientacao == 'v')
            linha+=1;

        else if(orientacao == 'H' || orientacao == 'h')
            coluna+=1;

        jogador1.tabuleiro[linha][coluna] = 'N';
    }
    player1.close();

    while(player2 >> linha){
        player2 >> coluna >> orientacao;
        jogador2.tabuleiro[linha][coluna]='N';

        if(orientacao == 'V' || orientacao == 'v')
            linha+=1;

        else if(orientacao == 'H' || orientacao == 'h')
            coluna+=1;

        jogador2.tabuleiro[linha][coluna] = 'N';
    }
    player2.close();


    //Jogo  do jogador 1:
    int alternador = 0;
    while(true){

        //Alternador: alterna a vez da jogada entre par(jogador 1) e impar(jogador 2).
        if(alternador%2==0){
            alternador += 1;
    
            cout << "\n.\n.\n.\nVez de: \n.\n.\n." << jogador1.nome<< endl;
    
            imprime_tabuleiro_jogador(jogador1.tabuleiro_referencia,num_linhas,num_colunas);
            cout << ".\n.\n." << endl;
            /* Imprime o tabuleiro de referencia do jogador. 
            Tabuleiro de refencia : Tabuleiro que mostra as jogadas realizadas pelo jogador, no tabuleiro adversario
            sem mostrar as posicoes dos navios nao atingidos */

            cout << "Digite a linha e a coluna do disparo: ";
            cin >> linha >> coluna;
            cin.ignore(1000, '\n');

            //O loop so termina quando a posicao escolhida pelo jogador estiver dentro dos limites do tabuleiro
            while(linha>=num_linhas || coluna>=num_colunas){
                cout << "\nPonto fora dos limites do tabuleiro" << endl;
                cout << "Digite novamente as coordenadas do disparo: "; 
                cin >> linha >> coluna;
                cin.ignore(1000, '\n');
            }

            //O loop verifica se a posicao escolhida ja nao foi escolhida anteriormente.
            while(jogador1.tabuleiro_referencia[linha][coluna] == 'X' || jogador1.tabuleiro_referencia[linha][coluna] == 'O'){
                cout << "\nVoce ja realizou um disparo nessa posicao." << endl;
                cout << "Digite novamente as coordenadas do disparo: "; 
                cin >> linha >> coluna;    
                cin.ignore(1000, '\n');
            }

            if(jogador2.tabuleiro[linha][coluna] == 'N'){
                cout << "Voce acertou uma embarcacao!" << endl;
                jogador1.tabuleiro_referencia[linha][coluna] = 'X';

                cout << "Tabuleiro atualizado: \n.\n.\n." << endl;

                imprime_tabuleiro_jogador(jogador1.tabuleiro_referencia,num_linhas,num_colunas);
                cout << ".\n.\n." << endl;
            
                numero_de_celulas_j2--;
                if(!verifica_numero_celulas(numero_de_celulas_j2)){
                    cout << "Todas as embarcacoes de "<< jogador2.nome << " foram afundadas" << endl;
                    cout << jogador1.nome << " Venceu.\nParabens!" << endl;
                    cout << ".\n.\n." << endl;
                    return 0;
                }
            }

            else if(jogador2.tabuleiro[linha][coluna] == '~'){
                cout << "Voce errou.\n.\n.\n." << endl;
                jogador1.tabuleiro_referencia[linha][coluna] = 'O';

                cout << "Tabuleiro atualizado: \n.\n.\n." << endl;

                imprime_tabuleiro_jogador(jogador1.tabuleiro_referencia,num_linhas,num_colunas);
                cout << ".\n.\n." << endl;
            }
            cout << "Pressione qualquer tecla para continuar..." << endl;
            _getch();
            system("cls");
        }


        //Jogo Jogador 2:
        else {
            alternador += 1;

            cout << "\n.\n.\n.\nVez de: \n.\n.\n." << jogador2.nome<< endl;

            imprime_tabuleiro_jogador(jogador2.tabuleiro_referencia,num_linhas,num_colunas);
            cout << ".\n.\n." << endl;
            /* Imprime o tabuleiro de referencia do jogador. 
            Tabuleiro de refencia : Tabuleiro que mostra as jogadas realizadas pelo jogador, no tabuleiro adversario
            sem mostrar as posicoes dos navios nao atingidos */

            cout << "digite a linha e a coluna do disparo: ";
            cin >> linha >> coluna;
            cin.ignore(1000, '\n');

            while(linha>=num_linhas || coluna>=num_colunas){
                cout << "\nPonto fora dos limites do tabuleiro" << endl;
                cout << "Digite novamente as coordenadas do disparo: "; 
                cin >> linha >> coluna;
                cin.ignore(1000, '\n');
            }

            while(jogador2.tabuleiro_referencia[linha][coluna] == 'X' || jogador2.tabuleiro_referencia[linha][coluna] == 'O'){
                cout << "\nVoce ja realizou um disparo nessa posicao." << endl;
                cout << "Digite novamente as coordenadas do disparo: "; 
                cin >> linha >> coluna;   
                cin.ignore(1000, '\n'); 
            }

            if(jogador1.tabuleiro[linha][coluna] == 'N'){
                cout << "Voce acertou uma embarcacao!" << endl;
                jogador2.tabuleiro_referencia[linha][coluna] = 'X';
                
                cout << "Tabuleiro atualizado: \n.\n.\n." << endl;

                imprime_tabuleiro_jogador(jogador2.tabuleiro_referencia,num_linhas,num_colunas);
                cout << "\n.\n.\n." << endl;

                numero_de_celulas_j1--;
                if(!verifica_numero_celulas(numero_de_celulas_j1)){
                    cout << "Todas as embarcacoes de "<< jogador1.nome << "foram afundadas" << endl;
                    cout << jogador2.nome << "Venceu.\nParabens!" << endl;
                    return 0;
                }
            }

            else if(jogador1.tabuleiro[linha][coluna] == '~'){
                cout << "Voce errou." << endl;
                jogador2.tabuleiro_referencia[linha][coluna] = 'O';
                
                cout << "Tabuleiro atualizado: \n.\n.\n." << endl;

                imprime_tabuleiro_jogador(jogador2.tabuleiro_referencia,num_linhas,num_colunas);
                cout << ".\n.\n." << endl;
            }
            cout << "Pressione qualquer tecla para continuar..." << endl;
            _getch();
            system("cls");
        }
    }
}
