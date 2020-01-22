#include <iostream>
#include <ctype.h>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Jogo feito por Vinicius Gomes: https://github.com/vinnyz-code

int table[3][3];

void resetTable() {

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            table[i][j] = 0;
        }
    }

}

void defineMark(int *mark, int *pc_mark, char symbol) {

    if(symbol == 'X') {

        *mark = 1;
        *pc_mark = 2;

    } else {

        *mark = 2;
        *pc_mark = 1;

    }

}

void loading() {

    for(int i=0; i<3; i++) {

        cout << "Carregando";
        Sleep(250);
        cout << ".";
        Sleep(250);
        cout << ".";
        Sleep(250);
        cout << ".";
        Sleep(250);

        system("cls");

    }

}

void printTable() {

	cout << "TABULEIRO:\n\n";
	cout << "     1   2   3\n";
	cout << "    -----------\n";

	for (int i=0; i<3; i++) {
		if (i == 1 || i == 2) {
			cout << "   |-----------\n";
		}

		cout << " " << i+1 << " |";

		for (int j=0; j<3; j++) {

            if (table[i][j] == 0) {
				if (j == 2) {
					cout << "   ";
				} else {
					cout << "   |";
				}
			}
			if (table[i][j] == 1) {
				if (j == 2) {
					cout << " X ";
				} else {
					cout << " X |";
				}
			}
			if (table[i][j] == 2) {
				if (j == 2) {
					cout << " O ";
				} else {
					cout << " O |";
				}
			}

		}

		cout << "\n";
	}

    cout << "\n\n";

}

int testaPosicao(int linha, int coluna) {

    if(table[linha][coluna] == 1 || table[linha][coluna] == 2) {

        return 2;

    } else {

        return 1;

    }

}

void jogadaComp(int *pc_mark) {

    srand (time(NULL));

    int line, col;

    do {

        line = rand() % 3;
        col = rand() % 3;


    } while(testaPosicao(line, col) == 2);

    table[line][col] = *pc_mark;

}

int testGanhandor(int *mark) {

    int line = 0, col = 0, diag_dir = 0, diag_invert = 0, win = 0;

    for(int i=0; i<3; i++) {
        col = 0;
        for(int j=0; j<3; j++) {
            if(table[i][j] == *mark) {
                col++;
            }
        }
        if(col == 3) {
            win++;
        }
    }

    for(int i=0; i<3; i++) {
        line = 0;
        for(int j=0; j<3; j++) {
            if(table[j][i] == *mark) {
                line++;
            }
        }
        if(line == 3) {
            win++;
        }
    }

    for(int i=0; i<3; i++) {

        if(table[i][i] == *mark) {
            diag_dir++;
        }

    }

    if(diag_dir == 3) {
        win++;
    }

    int aux = 2;
    for(int i=0; i<3; i++) {

        if(table[i][aux] == *mark) {
            diag_invert++;
        }

        aux--;
    }

    if(diag_invert == 3) {
        win++;
    }

    if(win >= 1) {

        return 1;

    } else {

        return 0;

    }

}

void winScreen(string winner) {

    system("cls");

    printTable();

    cout << "O " << winner << " GANHOU!!!\n";
    cout << "O " << winner << " GANHOU!!!\n";
    cout << "O " << winner << " GANHOU!!!\n\n";

    system("pause");

}

int main()
{

    setlocale(LC_ALL,"");

    char newgame[3];

    do {

        system("cls");

        char start[3];

        cout << ">> Bem-vindo ao Jogo da Velha do Vinição <<\n\n";

        do {

            cout << "Deseja começar a jogar? (S/N)\n";
            cout << "Resposta: ";

            cin >> start;

            start[0] = toupper(start[0]);

            if(start[0] != 'N' && start[0] != 'S') {

                cout << "\nResposta inesperada!\n";

            } else {

                if (start[0] == 'S') {

                    char option[7];

                    do {

                        cout << "\nDeseja jogar contra a máquina ou contra outro jogador? (M/J)\n";
                        cout << "Resposta: ";

                        cin >> option;

                        option[0] = toupper(option[0]);

                        if(option[0] != 'M' && option[0] != 'J') {

                            cout << "\nResposta inesperada!";

                        }

                    } while(option[0] != 'M' && option[0] != 'J');

                    if(option[0] == 'J') {

                        cout << "\nOpção ainda em desenvolvimento!\n\n";

                        return 0;

                    }

                    char symbol;

                    do {

                        cout << "\nSelecione o símbolo que você deseja jogar. (X/O)\n";
                        cout << "Resposta: ";

                        cin >> symbol;

                        symbol = toupper(symbol);

                        if(symbol != 'X' && symbol != 'O') {

                            cout << "\nResposta inesperada!";

                        }

                    } while(symbol != 'X' && symbol != 'O');

                    int mark, pc_mark;

                    defineMark(&mark, &pc_mark, symbol);

                    resetTable();

                    system("cls");

                    loading();

                    do {

                        printTable();

                        cout << "Indique as coordenadas de onde você deseja marcar.\n";

                        int line, col;

                        do {

                            do {

                                cout << "Linha: ";

                                cin >> line;

                                line--;

                                if(line < 0 || line > 2 || cin.fail()) {

                                    cout << "\nResposta inesperada!\n";
                                    cin.clear();
                                    cin.ignore(10, '\n');

                                }

                            } while(line < 0 || line > 2);

                            do {

                                cout << "Coluna: ";

                                cin >> col;

                                col--;

                                if(col < 0 || col > 2 || cin.fail()) {

                                    cout << "\nResposta inesperada!\n";
                                    cin.clear();
                                    cin.ignore(10, '\n');

                                }

                            } while(col < 0 || col > 2);

                            if(testaPosicao(line, col) == 2) {

                                cout << "\nPosição inválida!\n\n";

                            }

                        } while(testaPosicao(line, col) == 2);

                        table[line][col] = mark;

                        if(testGanhandor(&mark)) {

                            winScreen("JOGADOR");

                            break;

                        }

                        system("cls");

                        printTable();

                        cout << "O computador está jogando...";

                        jogadaComp(&pc_mark);

                        if(testGanhandor(&pc_mark)) {

                            winScreen("COMPUTADOR");

                            break;

                        }

                        Sleep(1600);

                        system("cls");


                    } while(1);

                } else {

                    return 0;

                }

            }

        } while(start[0] != 'N' && start[0] != 'S');

        do {

            cout << "\nDeseja jogar novamente? (S/N)\n";
            cout << "Resposta: ";

            cin >> newgame;

            newgame[0] = toupper(newgame[0]);

            if(newgame[0] != 's' && newgame[0] != 'N') {

                cout << "\nResposta inesperada!";

            }

        } while(newgame[0] != 'S' && newgame[0] != 'N');

    } while(newgame[0] == 'S');

    return 0;

}
