#include "IrmaMoves.h"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> //This only use is making so we can identify characters which is super useful down below

//IrmaMoves by Brandon Nickas
//ID: 6415

//To get the number for the column that each letter corresponds to. We do this a lot so I made a helper function for it
int getNum(char letter){
    switch(letter){
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;

    }
}

//This method creates the dynamic memory for the board to be put in as well as adding values
char **createMapBoard(void){
    char **board = (char**)malloc(8 * sizeof(char*)); //This makes the rows of the 2D array

    for(int c = 0; c < 8; c++){ //This makes the column in each of the rows made above
        board[c] = (char**)malloc(8 * sizeof(char*));
    }

    if(**board || board[0] || board[1] || board[2] || board[3] || board[4] || board[5] || board[6] || board[7]){ //this checks to see if board was made or if there was not enough space
        //For the life of me I could not get strncpy to work so I got around this by manually placing each letter and space
        board[0][0] = 'F';
        board[0][1] = 'F';
        board[0][2] = ' ';
        board[0][3] = ' ';
        board[0][4] = ' ';
        board[0][5] = ' ';
        board[0][6] = ' ';
        board[0][7] = ' ';

        board[1][0] = ' ';
        board[1][1] = 'F';
        board[1][2] = ' ';
        board[1][3] = ' ';
        board[1][4] = ' ';
        board[1][5] = ' ';
        board[1][6] = ' ';
        board[1][7] = ' ';

        board[2][0] = ' ';
        board[2][1] = 'F';
        board[2][2] = 'F';
        board[2][3] = ' ';
        board[2][4] = ' ';
        board[2][5] = ' ';
        board[2][6] = ' ';
        board[2][7] = ' ';

        board[3][0] = ' ';
        board[3][1] = ' ';
        board[3][2] = 'F';
        board[3][3] = ' ';
        board[3][4] = ' ';
        board[3][5] = ' ';
        board[3][6] = ' ';
        board[3][7] = ' ';

        board[4][0] = ' ';
        board[4][1] = ' ';
        board[4][2] = 'K';
        board[4][3] = ' ';
        board[4][4] = ' ';
        board[4][5] = ' ';
        board[4][6] = ' ';
        board[4][7] = ' ';

        board[5][0] = 'C';
        board[5][1] = ' ';
        board[5][2] = ' ';
        board[5][3] = 'B';
        board[5][4] = ' ';
        board[5][5] = ' ';
        board[5][6] = ' ';
        board[5][7] = ' ';

        board[6][0] = ' ';
        board[6][1] = 'C';
        board[6][2] = 'C';
        board[6][3] = ' ';
        board[6][4] = 'D';
        board[6][5] = ' ';
        board[6][6] = ' ';
        board[6][7] = ' ';

        board[7][0] = ' ';
        board[7][1] = ' ';
        board[7][2] = 'C';
        board[7][3] = ' ';
        board[7][4] = ' ';
        board[7][5] = 'D';
        board[7][6] = 'D';
        board[7][7] = ' ';

        return board; //This is the wanted outcome
    } else {
        return NULL; //Null is returned if there is not enough space
    }
}

//This function shows the current state of the board
void printMapBoard(char **board){
    printf("========\n");
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            printf("%c", board[r][c]);
        }
        printf("\n");
    }
    printf("========\n");
    printf("\n"); //This give the line with no spaces that the directions were stated in the directions
}

//This function free all the memory used by the board's columns then deletes the rows
char **destroyMapBoard(char **board){

    for(int c = 0; c < 8; c++){
        free(board[c]);
    }
    free(board);

    return NULL; //returns NULL like instructions say
}

//This mac daddy of a function has to do a lot from making the map and changing ws and wg constantly
char **predictIrmaChange(char* str, Move *irmaMove){

    //This first chunk makes the map and prints it with no changes
    char **board = createMapBoard();
    printMapBoard(board);

    //Find Irma on the map and places it and then printing the map again
    parseNotationString(str, irmaMove); //This is how we know starting values and where we want to move to
    board[irmaMove->from_loc.row][getNum(irmaMove->from_loc.col)] = 'I';
    printMapBoard(board);

    //The current location by default is x and -1 so we need to change that
    irmaMove->current_loc.row = irmaMove->from_loc.row;
    irmaMove->current_loc.col = irmaMove->from_loc.col;

    // I broke moving left/right or up/down into two if statements

    //The first if statements controls left and right movement
    if(getNum(irmaMove->from_loc.col) > getNum(irmaMove->to_loc.col)){ //See to see if Irma is moving left

        //Sets a loop up for how far Irma moves left
        for(int c = 0; c < (getNum(irmaMove->from_loc.col) - getNum(irmaMove->to_loc.col));c++){
            if(isalpha(board[irmaMove->current_loc.row][getNum(irmaMove->current_loc.col)-1])){ //This checks to see if there is a letter in the dynamic memory location where Irma is moving
                //This is what happens where there is a letter or land
                irmaMove->irma.ws -= 15;
                irmaMove->irma.wg -= 10;
                irmaMove->current_loc.col -= 1;
            } else {
                //This is what happens when there is ocean
                irmaMove->irma.ws += 10;
                irmaMove->irma.wg += 5;
                irmaMove->current_loc.col -= 1;
            }
        }
    } else if(getNum(irmaMove->from_loc.col) < getNum(irmaMove->to_loc.col)){ //This is for Irma moving right

        //Sets loop up for how Irma moves right
        for(int c = 0; c < (getNum(irmaMove->to_loc.col) - getNum(irmaMove->from_loc.col));c++){
            if(isalpha(board[irmaMove->current_loc.row][getNum(irmaMove->current_loc.col)+1])){ //checks to see if letter is in the box it is moving to
                //happen when there is a letter in the box
                irmaMove->irma.ws -= 15;
                irmaMove->irma.wg -= 10;
                irmaMove->current_loc.col += 1;
            } else {
                //happens when there is not a letter in the box
                irmaMove->irma.ws += 10;
                irmaMove->irma.wg += 5;
                irmaMove->current_loc.col += 1;
            }
        }
    }

    //This if statements see if Irma is going to move up or down
    if(irmaMove->from_loc.row > irmaMove->to_loc.row){ //Irma is moving down
        for(int r = 0; r < (irmaMove->from_loc.row - irmaMove->to_loc.row); r++){
            if(isalpha(board[irmaMove->current_loc.row - 1][getNum(irmaMove->current_loc.col)])){ //checks to see if a letter is in the box Irma is moving to
                //This is what happens when there is a letter
                irmaMove->irma.ws -= 2;
                irmaMove->irma.wg -= 1;
                irmaMove->current_loc.row -= 1;
            } else {
                //This happens when there is not a letter
                irmaMove->irma.ws += 6;
                irmaMove->irma.wg += 3;
                irmaMove->current_loc.row -= 1;
            }
        }
    } else if(irmaMove->from_loc.row < irmaMove->to_loc.row){ //This means Irma is moving up
        for(int r = 0; r < (irmaMove->to_loc.row - irmaMove->from_loc.row); r++){
            if(isalpha(board[irmaMove->current_loc.row + 1][getNum(irmaMove->current_loc.col)])){ //checks to see if there is a letter in the box Irma is moving to
                //this happens when there is a letter
                irmaMove->irma.ws -= 2;
                irmaMove->irma.wg -= 1;
                irmaMove->current_loc.row += 1;
            } else {
                //this happens when there is not a letter
                irmaMove->irma.ws += 6;
                irmaMove->irma.wg += 3;
                irmaMove->current_loc.row += 1;
            }
        }
    }

    board[irmaMove->from_loc.row][getNum(irmaMove->from_loc.col)] = ' ';
    board[irmaMove->current_loc.row][getNum(irmaMove->current_loc.col)] = 'I';
    printMapBoard(board);

    return board;
}

//This function takes in the string and gets all the information we need and puts it into storage
void parseNotationString(char *str, Move *Irma) {
    sscanf(str, "%c%d %d %d %c%d",
        &Irma->from_loc.col, &Irma->from_loc.row, &Irma->irma.ws, &Irma->irma.wg, &Irma->to_loc.col, &Irma->to_loc.row); //In this line we go step by step setting up where each piece of info needs to go
    Irma->current_loc.col = 'x';
    Irma->current_loc.row = -1;
};

//This was hard
double difficultyRating(void){
    return 4.5;
}

//And it took a long time
double hoursSpent(void){
    return 7;
}


