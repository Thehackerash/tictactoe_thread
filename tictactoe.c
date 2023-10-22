#include <stdio.h>
#include <pthread.h>           
#include <stdlib.h>     
#include <time.h>        
#include <unistd.h>


void display(char gameboard[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%c ", gameboard[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

char check(char gameboard[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (gameboard[row][0] == gameboard[row][1] && gameboard[row][1] == gameboard[row][2] && gameboard[row][0] != '-') {
            return gameboard[row][0];
        }
    }

    for (int col = 0; col < 3; col++) {
        if (gameboard[0][col] == gameboard[1][col] && gameboard[1][col] == gameboard[2][col] && gameboard[0][col] != '-') {
            return gameboard[0][col];
        }
    }

    if ((gameboard[0][0] == gameboard[1][1] && gameboard[1][1] == gameboard[2][2] && gameboard[0][0] != '-') ||
        (gameboard[0][2] == gameboard[1][1] && gameboard[1][1] == gameboard[2][0] && gameboard[0][2] != '-')) {
        return gameboard[1][1];
    }

    int emptycell = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (gameboard[row][col] == '-') {
                emptycell++;
            }
        }
    }
    if (emptycell == 0) {
        return 'D'; 
    }
    return '-'; 
}

void* playgame(void* arg) {
    char gameboard[3][3] = { {'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'} };
    char player = 'X';
    int turns = 0;

    while (1) {
        int row, col;

        do {
            row = rand() % 3;
            col = rand() % 3;
        } while (gameboard[row][col] != '-');

        gameboard[row][col] = player;
        turns++;
        display(gameboard);

        char res = check(gameboard);

        if (res != '-') {
            FILE *logfile = fopen("log.txt", "a");
            if (logfile != NULL) {
                fprintf(logfile, "Game result after move %d : ", turns);
                if (res == 'D') {
                    fprintf(logfile, "Draw\n");
                } else {
                    fprintf(logfile, "Player %c wins\n", res);
                }
                fclose(logfile);
            }
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
}

int main() {
    srand((unsigned int)getpid());

    pthread_t g;
    pthread_create(&g, NULL, playgame,NULL);
    pthread_join(g, NULL);

    return 0;
}
