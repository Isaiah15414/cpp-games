#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

string game[3][3] = {
	{ "", "", "" },
	{ "", "", "" },
	{ "", "", "" },
};

string board[5][5] = {
	{ game[0][0], "|", game[0][1], "|", game[0][2], }, // 0,0  0,2  0,4
	{ "---", "|", "---", "|", "---", },
	{ game[1][0], "|", game[1][1], "|", game[1][2], }, // 2,0, 2,2  2,4
	{ "---", "|", "---", "|", "---", },
	{ game[2][0], "|", game[2][1], "|", game[2][2], }, // 4,0  4,2  4,4
};

void printBoard(string game[3][3], string board[5][5]) {
	cout << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			string cell = board[i][j];
			// Update cells
			if (i % 2 == 0 && j % 2 == 0) {
				cell = game[int(i/2)][int(j/2)];
			}
			// Print cells
			if (cell == "") {
				cell = "   ";
			} else if (cell == "X" || cell == "O") {
				cell = " " + cell + " ";
			}
			cout << cell;
		}
		cout << endl;
	}
	cout << endl;
}

bool checkCells(string game[3][3], int x, int y) {
	if (game[x][y] != "") { return false; }
	return true;
}

bool checkWin(string game[3][3]) {
	if (
		// Forward slash
		(game[0][0] == "X" && game[1][1] == "X" && game[2][2] == "X") ||
		(game[0][0] == "O" && game[1][1] == "O" && game[2][2] == "O") ||
		// Backward slash
		(game[0][2] == "X" && game[1][1] == "X" && game[2][0] == "X") ||
		(game[0][2] == "O" && game[1][1] == "O" && game[2][0] == "O")
	) { return true; }
	for (int i = 0; i < 3; i++) {
		if (
			// Vertical
			(game[i][0] == "X" && game[i][1] == "X" && game[i][2] == "X") ||
			(game[i][0] == "O" && game[i][1] == "O" && game[i][2] == "O") ||
			// Horizontal
			(game[0][i] == "X" && game[1][i] == "X" && game[2][i] == "X") ||
			(game[0][i] == "O" && game[1][i] == "O" && game[2][i] == "O")
		) { return true; }
	}
	return false;
}

void cpuMove(string game[3][3]) {
	int row, col;
	do {
		row = rand() % 3;
		col = rand() % 3;
	} while (!checkCells(game, row, col));
	game[row][col] = "O";
}

int main() {
	srand(time(0));
	while (true) {
		cout << "Your turn!\n";
		printBoard(game, board);
		int row, col;
		// Input row
		cout << "Choose a row between 1 and 3.\n";
		do {
			cout << ": ";
			while (!(cin >> row)) {
				cout << ": ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
		} while (row < 1 || row > 3);
		row -= 1;
		// Input column
		cout << "Choose a column between 1 and 3.\n";
		do {
			cout << ": ";
			while (!(cin >> col)) {
				cout << ": ";
				cin.clear();
				cin.ignore(10000, '\n');
			}
		}
		while (col < 1 || col > 3);
		col -= 1;
		// Update board
		cout << endl;
		if (checkCells(game, row, col)) {
			// Your turn
			game[row][col] = "X";
			if (checkWin(game)) {
				cout << "You win!\n";
				break; 
			}
			cout << "Computer is thinking...\n";
			printBoard(game, board);
			sleep((rand() % 3) + 1);
			// CPU's turn
			cpuMove(game);
			if (checkWin(game)) { 
				cout << "You lose...\n";
				break;
			}
		} else {
			cout << "Cell taken.\n";
		}
	}
	printBoard(game, board);
	return 0;
}