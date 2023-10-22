#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void displayBoard(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

char checkResult(char board[3][3]) {
    // Check rows
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != '-') {
            return board[row][0];
        }
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != '-') {
            return board[0][col];
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-')) {
        return board[1][1];
    }

    // Check for a draw
    int emptyCells = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == '-') {
                emptyCells++;
            }
        }
    }
    if (emptyCells == 0) {
        return 'D'; 
    }

    return '-'; 
}

void* playautomatedgame(void* arg) {
    char board[3][3] = { {'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'} };
    char currentPlayer = 'X';
    int moves = 0;

    while (1) {
        int row, col;

        do {
            row = rand() % 3;
            col = rand() % 3;
        } while (board[row][col] != '-');

        board[row][col] = currentPlayer;
        moves++;
        displayBoard(board);

        char result = checkResult(board);

        if (result != '-') {
            FILE *logFile = fopen("tictactoe_log.txt", "a");
            if (logFile != NULL) {
                fprintf(logFile, "Game result after %d moves: ", moves);
                if (result == 'D') {
                    fprintf(logFile, "Draw\n");
                } else {
                    fprintf(logFile, "Player %c wins\n", result);
                }
                fclose(logFile);
            }

            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    pthread_t game;

    pthread_create(&game, NULL, playautomatedgame,NULL);
  
    pthread_join(game, NULL);

    return 0;
}
