//
//  main.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#define BOARD_SIZE 8

#include <iostream>
#include <vector>

#include "Piece.hpp"
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

void init_board (std::vector<std::vector<Piece *> >& board);
void print_board (std::vector<std::vector<Piece *> >& board);

int main(int argc, const char * argv[]) {
    // For me, pointer as array reminder: cpp.sh/2shge
    
    std::vector<std::vector<Piece *> > board;
    std::vector<Piece *> file;
    for (int i = 0; i < 8; i++) {
        board.push_back(file);
        for (int j = 0; j < 8; j++) {
            board[i].push_back(NULL);
        }
    }
    
    init_board(board);
    print_board(board);
    
    return 0;
}

void init_board (std::vector<std::vector<Piece *> >& board) {
    //Rook
    board[0][0] = new Rook(0, 0,false, board);
    board[7][0] = new Rook(7, 0,false, board);
    board[0][7] = new Rook(0, 7,true, board);
    board[7][7] = new Rook(7, 7,true, board);
    
    //Knight
    board[1][0] = new Knight(1, 0,false, board);
    board[6][0] = new Knight(6, 0,false, board);
    board[1][7] = new Knight(1, 7,true, board);
    board[6][7] = new Knight(6, 7,true, board);
    
    //Bishop
    board[2][0] = new Bishop(2,0,false, board);
    board[5][0] = new Bishop(5,0,false, board);
    board[2][7] = new Bishop(2,7,true, board);
    board[5][7] = new Bishop(5,7,true, board);
    
    //Queen
    board[3][0] = new Queen(3, 0,false, board);
    board[3][7] = new Queen(3, 7,true, board);
    
    //King
    board[4][0] = new King(4, 0,false, board);
    //black_king = (King)board[4][0];
    board[4][7] = new King(4, 7,true, board);
    //white_king = (King)board[4][7];
    
    //Pawns
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Pawn(i, 1,false, board);
    }
    
    for (int i = 0; i < 8; i++) {
        board[i][6] = new Pawn(i, 6,true, board);
    }
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            delete board[i][j];
        }
    }
}

void print_board (std::vector<std::vector<Piece *> >& board) {
    Piece *casted_value = NULL;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (dynamic_cast<Pawn *>(board[i][j]) != NULL) {
                casted_value = dynamic_cast<Pawn *>(board[i][j]);
                std::cout << (casted_value->isWhite() ? "P" : "p");
            }
            else if (dynamic_cast<Knight *>(board[i][j]) != NULL) {
                casted_value = dynamic_cast<Knight *>(board[i][j]);
                std::cout << (casted_value->isWhite() ? "N" : "n");
            }
            else if (dynamic_cast<Bishop *>(board[i][j]) != NULL) {
                casted_value = dynamic_cast<Bishop *>(board[i][j]);
                std::cout << (casted_value->isWhite() ? "B" : "b");
            }
            else if (dynamic_cast<Rook *>(board[i][j]) != NULL) {
                casted_value = dynamic_cast<Rook *>(board[i][j]);
                std::cout << (casted_value->isWhite() ? "R" : "r");
            }
            else if (dynamic_cast<Queen *>(board[i][j]) != NULL) {
                casted_value = dynamic_cast<Queen *>(board[i][j]);
                std::cout << (casted_value->isWhite() ? "Q" : "q");
            }
            else if (dynamic_cast<King *>(board[i][j]) != NULL) {
                casted_value = dynamic_cast<King *>(board[i][j]);
                std::cout << (casted_value->isWhite() ? "K" : "k");
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
