#include <iostream>
#include <fstream>
#include <limits>
#include "funcoes.h"
using namespace std;


int main(){

    system("cls");
    if(!menu()) return 0;

    char nome_j1[51];
    char nome_j2[51];
    cout << "Jogador 1:\nDigite seu nome: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(nome_j1,51);

    cout << "\n";
    cout << "Jogador 2:\nDigite seu nome: ";
    cin.getline(nome_j2,51);

    if(!leitura_jogadores(nome_j1,nome_j2)) return false;
    if (!validacao()) return false;


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
    
            cout << "\n\nVez de: " << nome_j1 << endl;
    
            /* Imprime o tabuleiro de referencia do jogador 1 
            Tabuleiro de refencia : Tabuleiro que mostra as jogadas realizadas pelo jogador, no tabuleiro adversario
            sem mostrar as posicoes dos navios nao atingidos */
    
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

                        if(tabuleiro_referencia_jogador1[i][j] == 'X')
                                cout << "\033[104;92mX  " << "\033[0m";

                        else if (tabuleiro_referencia_jogador1[i][j] == 'O')
                                cout << "\033[104;91mO  " << "\033[0m";

                        else if(tabuleiro_referencia_jogador1[i][j] == '~') 
                                cout << "\033[104;34m~  " << "\033[0m"; 
                    
                    }
                    cout << "  " << "\n";
                }


            cout << "Digite a linha e a coluna do disparo: ";
            cin >> linha >> coluna;

            while(linha>=num_linhas || coluna>=num_colunas){
                cout << "\nPonto fora dos limites do tabuleiro" << endl;
                cout << "Digite novamente as coordenadas do disparo: "; 
                cin >> linha >> coluna;
            }

            while(tabuleiro_referencia_jogador1[linha][coluna] == 'X' || tabuleiro_referencia_jogador1[linha][coluna] == 'O'){
                cout << "\nVoce ja realizou um disparo nessa posicao." << endl;
                cout << "Digite novamente as coordenadas do disparo: "; 
                cin >> linha >> coluna;    
            }

            if(tabuleiro_jogador2[linha][coluna] == 'N'){
                cout << "Voce acertou uma embarcacao!" << endl;
                tabuleiro_referencia_jogador1[linha][coluna] = 'X';

                cout << "Tabuleiro atualizado: " << endl;

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

                        if(tabuleiro_referencia_jogador1[i][j] == 'X')
                                cout << "\033[104;92mX  " << "\033[0m";

                        else if (tabuleiro_referencia_jogador1[i][j] == 'O')
                                cout << "\033[104;91mO  " << "\033[0m";

                        else if(tabuleiro_referencia_jogador1[i][j] == '~') 
                                cout << "\033[104;34m~  " << "\033[0m"; 
                    
                    }
                    cout << "  " << "\n";
                }
            
                numero_de_celulas_j2--;
                if(!verifica_numero_celulas(numero_de_celulas_j2)){
                    cout << "Todas as embarcacoes de "<< nome_j2 << "foram afundadas" << endl;
                    cout << nome_j1 << " Venceu.\nParabens!" << endl;
                    return 0;
                }
            }

            else if(tabuleiro_jogador2[linha][coluna] == '~'){
                cout << "Voce errou." << endl;
                tabuleiro_referencia_jogador1[linha][coluna] = 'O';

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

                        if(tabuleiro_referencia_jogador1[i][j] == 'X')
                                cout << "\033[104;92mX  " << "\033[0m";

                        else if (tabuleiro_referencia_jogador1[i][j] == 'O')
                                cout << "\033[104;91mO  " << "\033[0m";

                        else if(tabuleiro_referencia_jogador1[i][j] == '~') 
                                cout << "\033[104;34m~  " << "\033[0m"; 
                    
                    }
                    cout << "  " << "\n";
                }
            }
        }


        //Jogo Jogador 2:
        else {
            alternador += 1;
            cout << "\n\nVez de: " << nome_j2 << endl;

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

                        if(tabuleiro_referencia_jogador2[i][j] == 'X')
                                cout << "\033[104;92mX  " << "\033[0m";

                        else if (tabuleiro_referencia_jogador2[i][j] == 'O')
                                cout << "\033[104;91mO  " << "\033[0m";

                        else if(tabuleiro_referencia_jogador2[i][j] == '~') 
                                cout << "\033[104;34m~  " << "\033[0m"; 
                    
                    }
                    cout << "  " << "\n";
                }

            cout << "digite a linha e a coluna do disparo: ";
            cin >> linha >> coluna;

            while(linha>=num_linhas || coluna>=num_colunas){
                cout << "\nPonto fora dos limites do tabuleiro" << endl;
                cout << "Digite novamente as coordenadas do disparo: "; 
                cin >> linha >> coluna;
            }

            while(tabuleiro_referencia_jogador2[linha][coluna] == 'X' || tabuleiro_referencia_jogador2[linha][coluna] == 'O'){
                cout << "\nVoce ja realizou um disparo nessa posicao." << endl;
                cout << "Digite novamente as coordenadas do disparo: "; 
                cin >> linha >> coluna;    
            }

            if(tabuleiro_jogador1[linha][coluna] == 'N'){
                cout << "Voce acertou uma embarcacao!" << endl;
                tabuleiro_referencia_jogador2[linha][coluna] = 'X';


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

                        if(tabuleiro_referencia_jogador2[i][j] == 'X')
                                cout << "\033[104;92mX  " << "\033[0m";

                        else if (tabuleiro_referencia_jogador2[i][j] == 'O')
                                cout << "\033[104;91mO  " << "\033[0m";

                        else if(tabuleiro_referencia_jogador2[i][j] == '~') 
                                cout << "\033[104;34m~  " << "\033[0m"; 
                    
                    }
                    cout << "  " << "\n";
                }


                numero_de_celulas_j1--;
                if(!verifica_numero_celulas(numero_de_celulas_j1)){
                    cout << "Todas as embarcacoes de "<< nome_j1 << "foram afundadas" << endl;
                    cout << nome_j2 << "Venceu.\nParabens!" << endl;
                    return 0;
                }
            }

            else if(tabuleiro_jogador1[linha][coluna] == '~'){
                cout << "Voce errou." << endl;
                tabuleiro_referencia_jogador2[linha][coluna] = 'O';



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

                        if(tabuleiro_referencia_jogador2[i][j] == 'X')
                                cout << "\033[104;92mX  " << "\033[0m";

                        else if (tabuleiro_referencia_jogador2[i][j] == 'O')
                                cout << "\033[104;91mO  " << "\033[0m";

                        else if(tabuleiro_referencia_jogador2[i][j] == '~') 
                                cout << "\033[104;34m~  " << "\033[0m"; 
                    
                    }
                    cout << "  " << "\n";
                }
            }
        }
    }
}

