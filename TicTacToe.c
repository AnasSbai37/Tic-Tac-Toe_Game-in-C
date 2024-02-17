// User #1 is playing 'X' and user #2 is playing 'O'
 
#include <stdio.h>
#include <stdbool.h>
 
#define SIZE 9
 
const char player1 = 'X';
const char player2 = 'O';
 
void clearScreen(void);
void drawTitle(void);
void drawBoard(char array[]);
void drawInitialScreen(char array[]);
void drawFooter(int);
void playerInput(int*);
bool validateUserInput(int, char array[]);
void placeSymbol(int, int, char array[]);
bool detectWin(char array[], int);
void printWin(int);
void swapUsers(int*);
void printDraw(void);
 
int main() {
 
    char boardArray[SIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int currentPlayer = 1; // 1 or 2
    int playerTurn = -1;
    int turnCounter = 0;
 
    while (turnCounter < SIZE) {
        drawInitialScreen(boardArray);
        if (detectWin(boardArray, SIZE)) {
            swapUsers(&currentPlayer);
            printWin(currentPlayer);
 
            return 0;
        }
        drawFooter(currentPlayer);
        playerInput(&playerTurn);
        if (validateUserInput(playerTurn, boardArray)) {
            placeSymbol(playerTurn, currentPlayer, boardArray);
            swapUsers(&currentPlayer);
            turnCounter++;
        }
    }
 
    drawInitialScreen(boardArray);
    printDraw();
 
    return 0;
}
 
void clearScreen() {
    printf("\e[1;1H\e[2J");
}
 
void drawTitle() {
    printf("\n\t   Tic Tac Toe\n\n");
    printf("  Player 1 (%c)  -  Player 2 (%c)\n\n", player1, player2);
}
 
void drawBoard(char array[]) {
    for (int i = 0; i < SIZE; i++) {
        switch (i) {
            case 0:
            case 3:
            case 6:
            case 8:
                printf("\t     |     |     \n");
                break;
            case 1:
            case 4:
            case 7:
                printf("\t  %c  |  %c  |  %c  \n", array[i-1], array[i], array[i+1]);
                break;
            case 2:
            case 5:
                printf("\t_____|_____|_____\n");
                break;
        }
    }
}
 
void drawInitialScreen(char array[]) {
    clearScreen();
    drawTitle();
    drawBoard(array);
}
 
void drawFooter(int player) {
    printf("\nPlayer %i, enter a number: ", player);
}
 
void playerInput(int *input) {
    scanf("%i", input);
}
 
bool validateUserInput(int input, char array[]) {
    if (input > 9 || input < 1) {
        printf("Illegal input number!\nPress [ENTER] to continue ");
        while(getchar()!='\n');
        getchar();
 
        return false;
    }
 
    if (array[input-1] == player1 || array[input-1] == player2) {
        printf("This cell is already taken!\nPress [ENTER] to continue ");
        while(getchar()!='\n');
        getchar();
 
        return false;
    }
 
    return true;
}
 
void placeSymbol(int turn, int player, char array[]) {
    array[turn-1] = player == 1 ? player1 : player2;
}
 
bool detectWin(char array[], int size) {
    for (int i = 0; i < size; i += 3) {
        if (array[i] == array[i+1] && array[i+1] == array[i+2]) {
            return true;
        }
    }
 
    for (int i = 0; i < 3; i++) {
        if (array[i] == array[i+3] && array[i+3] == array[i+6]) {
            return true;
        }
    }
 
    if (array[0] == array[4] && array[4] == array[8]) {
        return true;
    }
 
    if (array[2] == array[4] && array[4] == array[6]) {
        return true;
    }
 
    return false;
}
 
void printWin(int player) {
    printf("\nPlayer %i WIN!\n", player);
}
 
void swapUsers(int *player) {
    *player = *player == 1 ? 2 : 1;
}
 
void printDraw() {
    printf("\nNobody won! Draw!\n");
}