#include<iostream>
#include<Windows.h>
#include<cstdlib>
using namespace std;

#define PLAYER 1
#define AI 2
#define RESTART 4
#define SIZE 3
#define AIMARK 'O'
#define PLAYERMARK 'X'

static bool isRestart = false;
static bool isQuit = false;

void mainMenu() {
    cout << "----------------------" << endl;
    cout << "|    TIC TAC TOE     |" << endl;
    cout << "|    'p' to play     |" << endl;
    cout << "|    'q' to quit     |" << endl;
    cout << "----------------------" << endl;
}

void showBoard(char board[][SIZE])
{
    cout << "-------------" << endl;
    cout << "| " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |"<< endl;
    cout << "-------------" << "    '10' to restart" << endl;
    cout << "| " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |"<< "    '0' to quit" <<  endl;
    cout << "-------------" << endl;
    cout << "| " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |"<< endl;
    cout << "-------------" << endl;
}

void nextScreen() {
    for(int i = 0; i < 30; i++) cout << endl;
}

void boardInitiator(char board[][SIZE]) {
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void endingScreen(int turn) {
    nextScreen();
    if(turn == PLAYER) cout << "PLAYER HAS WON!!!!" << endl;
    else if(turn == AI)cout << "AI HAS WON!!!!" << endl;
    else cout << endl;
    int counter = 1;
    Sleep(1000);
    while (counter >= 1)
    {
        Sleep(1000);
        counter--;
    }
    nextScreen();
}

bool checkRow(char board[][SIZE]) {
    for (int i=0; i<SIZE; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
			return (true);
	}
	return(false);
}

bool checkColumn(char board[][SIZE]) {
    for (int i=0; i<SIZE; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
			return (true);
	}
	return(false);
}

bool checkDiagonal(char board[][SIZE]) {
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ')
		return(true);

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != ' ')
		return(true);

	return(false);
}

bool isGameOver(char board[][SIZE]) {
	return(checkColumn(board) || checkRow(board) || checkDiagonal(board) );
}

int minimax(char board[][SIZE], int depth, bool isAI) {
	int score = 0;
	int bestScore = 0;
	if (isGameOver(board) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestScore = -999;
				for(int i=0; i<SIZE; i++)
				{
					for(int j=0; j<SIZE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = AIMARK;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' ';
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < SIZE; i++)
				{
					for (int j = 0; j < SIZE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = PLAYERMARK;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' ';
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

int bestMove(char board[][SIZE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = AIMARK;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

void playGame(int turn) {
    char board[SIZE][SIZE];
    int markIndex = 0, x = 0, y = 0;

    boardInitiator(board);
    showBoard(board);

    while( isGameOver(board) == false && markIndex != SIZE*SIZE) {
        int a;
        if(turn == AI) {
            if(markIndex == 0) a = 0 + (rand() % 8);
            else a = bestMove(board, markIndex);
            x = a / SIZE;
            y = a % SIZE;
            board[x][y] = AIMARK;
            nextScreen();
            showBoard(board);
            markIndex++;
            turn = PLAYER;
        }
        else if(turn == PLAYER) {
            cout << "You can mark on the following positions: ";
            for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                    if(board[i][j] == ' ') cout << (i * 3 + j) + 1 << " ";
                }
            }
            cout << endl << "Enter your next command: ";
            cin >> a;
            cout << endl;

            if(a == 10) {
                boardInitiator(board);
                turn = RESTART;
                isRestart = true;
                break;
            }
            else if(a == 0) {
                isQuit = true;
                turn = RESTART;
                break;
            }
            a--;
            x = a / SIZE;
            y = a % SIZE;
            if(board[x][y] == ' ' && a < 9 && a >= 0 ) {
                board[x][y] = PLAYERMARK;
                nextScreen();
                showBoard(board);
                markIndex++;
                turn = AI;
            }
            else if(board[x][y] != ' ' && a < 9 && a >= 0) cout << "This position is not available, please choose another position" << endl;
        }
    }
    if(isGameOver(board) == false && markIndex == SIZE*SIZE) {
        cout << "It's a draw ~~~" << endl;
    }

    else {
        if(turn == AI) turn = PLAYER;
        else if(turn == PLAYER) turn = AI;
        endingScreen(turn);
    }
}

int main() {
    nextScreen();
    mainMenu();
    char answer = 'p';
    cout << "Enter your command: ";
    cin >> answer;
    if(answer == 'q') return 0;
    else if(answer != 'q' || answer != 'p') cout << "Invalid command!!" << endl;

    do {
        char choice, choice2;
        nextScreen();
        cout <<  "Do you want to start first? (y/n) : ";
        cin >> choice;
        isRestart = false;

        nextScreen();
        if(choice == 'n') playGame(AI);
        else if(choice == 'y') playGame(PLAYER);

        if(isQuit == true) {
            answer = 'q';
            break;
        }

        if(isRestart == false) {
            cout << "Do you want to continue playing? (y/n) :";
            cin >> choice2;

            if(choice2 == 'y') answer = 'p';
            else if(choice2 == 'n') answer = 'q';
        }
    } while(answer == 'p');
    return 0;
}



