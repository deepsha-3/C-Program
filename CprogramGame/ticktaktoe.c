#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

bool isMoveValid(int row, int col) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

void playerMove() {
    int row, col;
    do {
        printf("Enter your move (column [0-2] and row [0-2]): ");
        scanf("%d %d", &row, &col);
    } while (!isMoveValid(row, col));
    board[row][col] = PLAYER;
}

void computerMove() {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!isMoveValid(row, col));
    board[row][col] = COMPUTER;
    printf("Computer placed O in position: %d %d\n", row, col);
}

int main() {
    srand(time(NULL));
    initializeBoard();
    printf("Welcome to Tic Tac Toe!\n");
    printf("You are X and the computer is O.\n");

    while (true) {
        printBoard();
        playerMove();
        if (checkWin(PLAYER)) {
            printBoard();
            printf("You win!\n");
            break;
        }
        if (isBoardFull()) {
            printBoard();
            printf("It's a tie!\n");
            break;
        }
        computerMove();
        if (checkWin(COMPUTER)) {
            printBoard();
            printf("Computer wins!\n");
            break;
        }
        if (isBoardFull()) {
            printBoard();
            printf("It's a tie!\n");
            break;
        }
    }
    return 0;
}