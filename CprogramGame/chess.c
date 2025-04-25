#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>  // Add this line to include string functions

#define BOARD_SIZE 8

// Piece representations
#define EMPTY ' '
#define WHITE_KING 'K'
#define WHITE_QUEEN 'Q'
#define WHITE_ROOK 'R'
#define WHITE_BISHOP 'B'
#define WHITE_KNIGHT 'N'
#define WHITE_PAWN 'P'
#define BLACK_KING 'k'
#define BLACK_QUEEN 'q'
#define BLACK_ROOK 'r'
#define BLACK_BISHOP 'b'
#define BLACK_KNIGHT 'n'
#define BLACK_PAWN 'p'

char board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    // Initialize empty squares
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }

    // Set up white pieces
    board[0][0] = board[0][7] = WHITE_ROOK;
    board[0][1] = board[0][6] = WHITE_KNIGHT;
    board[0][2] = board[0][5] = WHITE_BISHOP;
    board[0][3] = WHITE_QUEEN;
    board[0][4] = WHITE_KING;
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = WHITE_PAWN;
    }

    // Set up black pieces
    board[7][0] = board[7][7] = BLACK_ROOK;
    board[7][1] = board[7][6] = BLACK_KNIGHT;
    board[7][2] = board[7][5] = BLACK_BISHOP;
    board[7][3] = BLACK_QUEEN;
    board[7][4] = BLACK_KING;
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[6][i] = BLACK_PAWN;
    }
}

void printBoard() {
    printf("  a b c d e f g h\n");
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        printf("%d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("%d\n", i + 1);
    }
    printf("  a b c d e f g h\n");
}

bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, char piece) {
    // Basic move validation (does not include all chess rules)
    if (fromRow < 0 || fromRow >= BOARD_SIZE || fromCol < 0 || fromCol >= BOARD_SIZE ||
        toRow < 0 || toRow >= BOARD_SIZE || toCol < 0 || toCol >= BOARD_SIZE) {
        return false;
    }

    if (fromRow == toRow && fromCol == toCol) {
        return false;
    }

    char targetPiece = board[toRow][toCol];
    if (isupper(piece) == isupper(targetPiece) && targetPiece != EMPTY) {
        return false;
    }

    // Simplified move checks (not comprehensive)
    switch (tolower(piece)) {
        case 'p': // Pawn
            if (isupper(piece)) { // White pawn
                return (fromCol == toCol && toRow == fromRow + 1 && targetPiece == EMPTY) ||
                       (fromCol == toCol && toRow == fromRow + 2 && fromRow == 1 && targetPiece == EMPTY) ||
                       (abs(fromCol - toCol) == 1 && toRow == fromRow + 1 && targetPiece != EMPTY);
            } else { // Black pawn
                return (fromCol == toCol && toRow == fromRow - 1 && targetPiece == EMPTY) ||
                       (fromCol == toCol && toRow == fromRow - 2 && fromRow == 6 && targetPiece == EMPTY) ||
                       (abs(fromCol - toCol) == 1 && toRow == fromRow - 1 && targetPiece != EMPTY);
            }
        case 'r': // Rook
            return fromRow == toRow || fromCol == toCol;
        case 'n': // Knight
            return (abs(fromRow - toRow) == 2 && abs(fromCol - toCol) == 1) ||
                   (abs(fromRow - toRow) == 1 && abs(fromCol - toCol) == 2);
        case 'b': // Bishop
            return abs(fromRow - toRow) == abs(fromCol - toCol);
        case 'q': // Queen
            return fromRow == toRow || fromCol == toCol || abs(fromRow - toRow) == abs(fromCol - toCol);
        case 'k': // King
            return abs(fromRow - toRow) <= 1 && abs(fromCol - toCol) <= 1;
        default:
            return false;
    }
}

bool makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    char piece = board[fromRow][fromCol];
    if (piece == EMPTY || !isValidMove(fromRow, fromCol, toRow, toCol, piece)) {
        return false;
    }
    board[toRow][toCol] = piece;
    board[fromRow][fromCol] = EMPTY;
    return true;
}

int main() {
    initializeBoard();
    char move[5];
    bool whitesTurn = true;

    while (1) {
        printBoard();
        printf("%s's turn. Enter move (e.g., e2e4) or 'quit' to end: ", whitesTurn ? "White" : "Black");
        scanf("%s", move);

        if (strcmp(move, "quit") == 0) {
            break;
        }

        if (strlen(move) != 4) {
            printf("Invalid move format. Please use format 'e2e4'.\n");
            continue;
        }

        int fromCol = move[0] - 'a';
        int fromRow = move[1] - '1';
        int toCol = move[2] - 'a';
        int toRow = move[3] - '1';

        if (makeMove(fromRow, fromCol, toRow, toCol)) {
            whitesTurn = !whitesTurn;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    printf("Game ended. Thanks for playing!\n");
    return 0;
}