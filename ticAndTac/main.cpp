#include <vector>
#include <iostream>
using namespace std;
enum RESULT {WIN, LOST, DRAW, NOTFINISHED};

RESULT checkLineResult(char player, char c0, char c1, char c2){
    int playerNumber=0, opponentNumber=0;
    if (c0 == player) {
        playerNumber++;
    } else {
        if (c0 != '_') {
            opponentNumber++;
        }
    }
    if (c1 == player) {
        playerNumber++;
    } else {
        if (c1 != '_') {
            opponentNumber++;
        }
    }
    if (c2 == player) {
        playerNumber++;
    } else {
        if (c2 != '_') {
            opponentNumber++;
        }
    }
    
    if (playerNumber == 3) return WIN;
    if (opponentNumber == 3) return LOST;
    return NOTFINISHED;
}

RESULT checkResult(char player, vector <string> board){
    RESULT temp;
    temp = checkLineResult(player, board[0][0], board[0][1], board[0][2]);
    if (temp != NOTFINISHED) return temp;
    temp = checkLineResult(player, board[1][0], board[1][1], board[1][2]);
    if (temp != NOTFINISHED) return temp;
    temp = checkLineResult(player, board[2][0], board[2][1], board[2][2]);
    if (temp != NOTFINISHED) return temp;
    temp = checkLineResult(player, board[0][0], board[1][0], board[2][0]);
    if (temp != NOTFINISHED) return temp;
    temp = checkLineResult(player, board[0][1], board[1][1], board[2][1]);
    if (temp != NOTFINISHED) return temp;
    temp = checkLineResult(player, board[0][2], board[1][2], board[2][2]);
    if (temp != NOTFINISHED) return temp;
    temp = checkLineResult(player, board[0][0], board[1][1], board[2][2]);
    if (temp != NOTFINISHED) return temp;
    temp = checkLineResult(player, board[0][2], board[1][1], board[2][0]);
    if (temp != NOTFINISHED) return temp;
    
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (board[i][j] == '_') {
                return NOTFINISHED;
            }
        }
    }
    return DRAW;
}

int bestPositionValue(char player, vector <string> board, int& postion) {
    RESULT temp = checkResult(player, board);
    if (temp  == DRAW)  return 0;
    if (temp == WIN)    return 1;
    if (temp == LOST)   return -1;
    
    char opponent;
    if (player == 'X') {
        opponent = 'O';
    } else {
        opponent = 'X';
    }
    
    int currentSum = -10, opponentBestMove, tempSum;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = player;
                tempSum = -bestPositionValue(opponent, board, opponentBestMove);
                if (tempSum > currentSum) {
                    currentSum = tempSum;
                    postion = 3*i+j;
                }
                board[i][j]='_';
            }
        }
    }
    return currentSum;
}

void nextMove(char player, vector <string> board){
    int move=0;
    bestPositionValue(player, board, move);
    cout<<move/3<<" "<<move%3;
}

int main() {
    
    char player;
    vector <string> board;
    
    //If player is X, I'm the first player.
    //If player is O, I'm the second player.
    player = 'O';
    
    //Read the board now. The board is a 3x3 array filled with X, O or _.
//    for(int i=0; i<3; i++) {
//        string s; cin >> s;
//        board.push_back(s);
//    }
    board.push_back("OXX");
    board.push_back("XOO");
    board.push_back("OXX");
    
    nextMove(player,board);
    
    return 0;
}
