#include"Minesweeper.h"
#include"Coordinates.h"
#include<conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACE 32
#define FLAG 'f'
#define QUIT 'q'
#define REPLAY 'r'

TerminalColoring* terminal = new TerminalColoring();

Coordinates readNextMove() {
	int x, y;

	cout << "x = "; cin >> x;
	cout << "y = "; cin >> y;

	Coordinates coord(x,y);

	return coord;
}

void printSpaces(int spaces = 5) {
	for (int i = 0; i < spaces; i++) {
		cout << " ";
	}
}

int readParameter(string message, int low, int high) {
	int parameter;
	do {
		printSpaces();
		cout << message;
		cin >> parameter;
	} while (parameter < low || parameter > high);

	return parameter;
}

GameParameters readGameParameters() {
	GameParameters gp;

	cout << endl;
	string rowsMessage = "Enter number of rows [1-50]: ";
	gp.rows = readParameter(rowsMessage,1,50);

	string columnsMessage = "Enter number of columns [1-50]: ";
	gp.columns = readParameter(columnsMessage,1,50);

	string difficultyMessage = "Enter difficulty level [1-99]: ";
	gp.difficulty = readParameter(difficultyMessage, 1, 99);

	return gp;
}

char readCommand() {
	char command;

	do {
		cout << '\n' << '\n';
		printSpaces();
		string message = "Play again (r) / Quit (q): ";
		terminal->printColored(message, terminal->GREEN);
		cin >> command;
		cout << '\n';
	} while (command != QUIT && command != REPLAY);

	return command;
}

void printWinningMessage() {
	string message = "C O N G R A T U L A T I O N S,    Y O U    W O N !!!";
	terminal->printColored(message, terminal->GREEN);
	cout << '\n';
}

void printGameOverMessage() {
	string message = "G A M E   O V E R !!!";
	terminal->printColored(message, terminal->RED);
	cout << '\n';
}

void playGame() {
	GameParameters gp = readGameParameters();
	Minesweeper* minesweeper = new Minesweeper(gp);

	minesweeper->startGame();

	do {
		int command = _getch();

		if (command == KEY_UP) {
			minesweeper->up();
		}
		else if (command == KEY_RIGHT) {
			minesweeper->right();
		}
		else if (command == KEY_DOWN) {
			minesweeper->down();
		}
		else if (command == KEY_LEFT) {
			minesweeper->left();
		}
		else if (command == SPACE) {
			minesweeper->nextMove();
		}
		else if (command == FLAG) {
			minesweeper->flag();
		}
		else {
			continue;
		}

	} while (!minesweeper->finished());

	cout << '\n' << '\n';
	printSpaces();

	if (minesweeper->winner()) {
		printWinningMessage();
	}
	else {
		printGameOverMessage();
	}

	minesweeper->~Minesweeper();
	//delete minesweeper; /* se apeleaza destructorul in mod implicit */
}


int main() {

	do {
		playGame();
	} while (readCommand() != QUIT);

	return 0;
}