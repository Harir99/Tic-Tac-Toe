#include "ttt.h"
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct BoardNode htable[HSIZE];
void finalScore(Board board);
int diagCrossed(Board board,char ch);
int rowCrossed(Board board,char ch);
int colCrossed(Board board,char ch);

void init_boards(){
    int i = 0;
    for (i = 0; i < HSIZE; i++) {
        htable[i].init = 0;
    }
}
int depth( Board board ){
    int i = 0;
    int count = 0;
    for ( i = 0; i < 9; i++) {
        if(board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O'){
            //number of markers ( X s and O s) on the board.
            count++;
        } 
    }

    return count;
     
}
int colCrossed(Board board,char ch){
    int i = 0;
    // column win
    for ( i = 0; i <= 6; i+=3){
        if(board[pos2idx[i]] == ch && board[pos2idx[i+1]] == ch && board[pos2idx[i+2]] == ch){
            return 0;
        }
    }
    return -1;
}
int rowCrossed(Board board,char ch){
    int i = 0;
    // column win
    for ( i = 0; i < 3; i++){
        if(board[pos2idx[i]] == ch && board[pos2idx[i+3]] == ch && board[pos2idx[i+6]] == ch){
            return 0;
        }
    }
    return -1;
}
int diagCrossed(Board board,char ch){
    // column win
    if(board[pos2idx[0]] == ch && board[pos2idx[4]] == ch && board[pos2idx[8]] == ch){
        return 0;
    }
    else if(board[pos2idx[2]] == ch && board[pos2idx[4]] == ch && board[pos2idx[6]] == ch){
        return 0;
    }  
    return -1;
}

char winner( Board board ){
    int count = depth(board);
    char winner;

    // ‘-‘ , if the game is over and a draw (the board is filled and no-one has won) 
    if(count == 9){
        winner = '-';
    }
    // ‘X’ , if X has won the game
    else if(colCrossed(board,'X') == 0 || rowCrossed(board,'X') == 0 || diagCrossed(board,'X')  == 0){
        winner = 'X';
    }

    // ‘O’ , if O has won the game
    else if(colCrossed(board,'O') == 0 || rowCrossed(board,'O') == 0 || diagCrossed(board,'O') == 0){
        winner = 'O';        
    }
    // ‘?’ , if the game is incomplete and no-one has won
    else {
        winner = '?';
    }
    return winner;
}


// get who's turn is it
char turn( Board board ){

    int i = 0;
    int xCount = 0, OCount = 0;
    int count = depth(board);
    char Whosturn;

    // if board is full
    if(count == 9 || (winner(board) == 'O' || winner(board) =='X')){
        Whosturn = '-';
    }

    // compute whos turn X  or O
    else if (count % 2 == 0) {
        Whosturn = 'X';

    } else {
        Whosturn = 'O';
    }
    
    return Whosturn;
}

void init_board( Board board ){
   int index = board_hash(board);
    
    // init should be set to 1 
        htable[index].init = 1; 
    
    // turn should be set to the return value of the turn function for the given board 
        htable[index].turn = turn(board);
        
    // depth should be set to the return value of the depth function for the given board 
        htable[index].depth = depth(board);

    // board should be set to the argument board (by calling the strcpy function)
         strcpy(htable[index].board,board); 

    // winner should be set to the return value of the winner function for the given board 
        htable[index].winner = winner(board);
}
void join_graph( Board board ){
    int i = 0;
    int index = board_hash(board);
    Board newBoard;
    int newIndex = 0;
    for (i = 0; i < 9; i++){
        // check for X and O filled places 
        htable[index].move[i] = (board[pos2idx[i]] == 'X') ? -1: htable[index].move[i]; 
        htable[index].move[i] = (board[pos2idx[i]] == 'O') ? -1: htable[index].move[i]; 

        //if spot is empty, then place required marker in right place 
        if(board[pos2idx[i]] != 'X' && board[pos2idx[i]] != 'O') {
            strcpy(newBoard,board);
            newBoard[pos2idx[i]] = turn(newBoard);
            newIndex = board_hash(newBoard);
            htable[index].move[i] = newIndex;

            // if there is no entry 
            if(htable[newIndex].init == 0){ 
                init_board(newBoard);
                join_graph(newBoard);
            }

        }
    }
}

//stuck here
//assign score to entry in htable has a vale of 1
void compute_score () {
    finalScore(START_BOARD);
}

void finalScore(Board board){
    int index = board_hash(board);
    int i = 0;
    int move = 0;
    int max = 0; 
    int min = 0;
    if (htable[index].depth == 9) {
        if(htable[index].winner == 'X') {
            htable[index].score = 1;
        } else if(htable[index].winner == 'O') {
            htable[index].score = -1; 
        } else if(htable[index].winner == '-') {
            htable[index].score = 0; 
        } 
    }else {
        if(htable[index].winner == 'X') {
            htable[index].score = 1;
        } else if(htable[index].winner == 'O') {
            htable[index].score = -1; 
        } else if(htable[index].winner == '-') {
            htable[index].score = 0; 
        } else {
            max = -4; 
            min = -4;
            for ( i = 0; i < 9; i++){
                move = htable[index].move[i];
                if (htable[index].move[i] != -1) {
                    finalScore(htable[move].board);
                    if(min == -4){
                        min = htable[move].score;
                        max = htable[move].score;
                    }else {
                        if (htable[move].score < min) {
                            min = htable[move].score;  
                        }
                        if (htable[move].score > max) {
                            max = htable[move].score;  
                        }
                    }
                    
                }
                if (htable[index].turn == 'X') {        
                    htable[index].score = max;
                } else if (htable[index].turn == 'O') {             
                    htable[index].score = min;
                } 
            }
        }
        
    }     
}
int best_move(int board) {
    int i, j;
    int bestScore;//use this to calculate which move to return
    int score = -4;
    int move;
    bestScore = -4;//start with an arbitrary low value 
    for(i = 0; i < 9; i++) {
        move = htable[board].move[i];
        if(htable[board].move[i] != -1) {
            if(score == -4){
                score = htable[move].score; 
                bestScore = htable[move].score; 
            }else {
                    if (htable[move].score < score) {
                    score = htable[move].score;  
                }
                if (htable[move].score > bestScore) {
                    bestScore = htable[move].score;  
                }
            }               
        }
    
    }
    
    for(i = 0; i < 9; i++) {
        if(htable[board].move[i] != -1) {
            move = htable[board].move[i];
            if(htable[board].turn == 'X'){
                if(htable[move].score == bestScore){
                    return i;
                }
            }else if(htable[board].turn == 'O'){
                if(htable[move].score == score){
                    return i;
                }
            }
            
        }
    }
    return -4;
}
