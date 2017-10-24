//
//  main.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//
// For me, pointer as array reminder: cpp.sh/2shge

#define BOARD_SIZE 8
#define INPUT_NOTATION 0 //0 for long algebraic, 1 for 0-based array index, 2 for 1-based array index

#include <iostream>
#include <fstream>
#include <vector>

#include "Piece.hpp"
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

void init_board (std::vector<std::vector<Piece *> >& board, std::vector<Point>& white_control, std::vector<Point>& black_control);
void print_board (std::vector<std::vector<Piece *> >& board);

void move_piece(std::vector<std::vector<Piece *> >& board, int from_x, int from_y, int to_x, int to_y);
bool is_valid_input (std::string input);
void convert_input (std::string input, int &from_x, int &from_y, int &to_x, int &to_y);

int main(int argc, const char * argv[]) {
    std::vector<std::vector<Piece *> > board;
    std::vector<Piece *> file;
    std::vector<Point> possible_moves;
    std::vector<Point> white_control;
    std::vector<Point> black_control;
    std::fstream fin("KasparovVVeselin.txt");
    std::string input;
    int from_x = 0;
    int from_y = 0;
    int to_x = 0;
    int to_y = 0;
    bool game_ended = false;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        board.push_back(file);
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i].push_back(NULL);
        }
    }
    
    init_board(board, white_control, black_control);
    print_board(board);
    std::cout << std::endl;
    
    while (!fin.eof()) {
        fin >> input;
        std::cout << input << std::endl;
        if (!is_valid_input(input)) {
            break;
        }
    
        convert_input(input, from_x, from_y, to_x, to_y);
        
        std::cout << "From: " << from_x << " " << from_y << std::endl;
        std::cout << "To: " << to_x << " " << to_y << std::endl;
        
        Piece *viewing_piece = board[from_x][from_y];
        
        if (viewing_piece == NULL) {
            continue;
        }
        if (!viewing_piece->validate_move(to_x, to_y)) {
            std::cout << "WHY" << std::endl;
        }
        if (!viewing_piece->validate_move(to_x, to_y)) {
            std::cout << "Entered illegal move" << std::endl;
            std::cout << std::endl;
            continue;
        }
    
        if (dynamic_cast<Pawn *>(viewing_piece) != NULL) {
            Pawn *my_pawn = dynamic_cast<Pawn *>(viewing_piece);
            if (from_x != to_x) {
                if (board[to_x][to_y] == NULL) {
                    board[to_x][my_pawn->isWhite() ? to_y + 1 : to_y - 1] = NULL;
                }
            }
        }
        
        move_piece(board, from_x, from_y, to_x, to_y);
        
        if (dynamic_cast<King *>(viewing_piece) != NULL) {
            // Castle a king
            int rank = viewing_piece->isWhite() ? 7 : 0;
            
            if (to_x - from_x > 0) {
                // Castle Kingside
                move_piece(board, 7, rank, 5, rank);
            }
            else {
                // Castle Queenside
                move_piece(board, 0, rank, 3, rank);
            }
        }
        else if (dynamic_cast<Pawn *>(viewing_piece) != NULL) {
            Pawn *my_pawn = dynamic_cast<Pawn *>(viewing_piece);
            if (abs(from_y - to_y) == 2) {
                my_pawn->set_move_two_spaces(true);
            }
            
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    Pawn *pawn = dynamic_cast<Pawn *>(board[i][j]);
                    if (pawn != NULL && my_pawn != pawn) {
                        pawn->set_move_two_spaces(false);
                    }
                }
            }
        }
        
        print_board(board);
        std::cout << std::endl;
    }
    
    // Delete the pointers in the vector (to free memeory)
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            delete board[i][j];
        }
    }
    
    fin.close();
    
    return 0;
}

void init_board (std::vector<std::vector<Piece *> >& board, std::vector<Point>& white_control, std::vector<Point>& black_control) {
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
    board[4][0] = new King(4, 0,false, board, white_control);
    //black_king = (King)board[4][0];
    board[4][7] = new King(4, 7,true, board, black_control);
    //white_king = (King)board[4][7];
    
    //Pawns
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Pawn(i, 1,false, board);
    }
    
    for (int i = 0; i < 8; i++) {
        board[i][6] = new Pawn(i, 6,true, board);
    }
}

void print_board (std::vector<std::vector<Piece *> >& board) {
    Piece *casted_value = NULL;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Piece *temp = board[j][i];
            if (dynamic_cast<Pawn *>(temp) != NULL) {
                casted_value = dynamic_cast<Pawn *>(temp);
                std::cout << (casted_value->isWhite() ? "P" : "p");
            }
            else if (dynamic_cast<Knight *>(temp) != NULL) {
                casted_value = dynamic_cast<Knight *>(temp);
                std::cout << (casted_value->isWhite() ? "N" : "n");
            }
            else if (dynamic_cast<Bishop *>(temp) != NULL) {
                casted_value = dynamic_cast<Bishop *>(temp);
                std::cout << (casted_value->isWhite() ? "B" : "b");
            }
            else if (dynamic_cast<Rook *>(temp) != NULL) {
                casted_value = dynamic_cast<Rook *>(temp);
                std::cout << (casted_value->isWhite() ? "R" : "r");
            }
            else if (dynamic_cast<Queen *>(temp) != NULL) {
                casted_value = dynamic_cast<Queen *>(temp);
                std::cout << (casted_value->isWhite() ? "Q" : "q");
            }
            else if (dynamic_cast<King *>(temp) != NULL) {
                casted_value = dynamic_cast<King *>(temp);
                std::cout << (casted_value->isWhite() ? "K" : "k");
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool is_valid_input(std::string input) {
    if (INPUT_NOTATION == 0) {
        if (input[0] >= 'a' && input[0] <= 'h') {
            if (input[1] >= '1' && input[1] <= '8') {
                if (input[3] >= 'a' && input[3] <= 'h') {
                    if (input[4] >= '1' && input[4] <= '8') {
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
}

void convert_input (std::string input, int &from_x, int &from_y, int &to_x, int &to_y) {
    from_x = input[0] - 97;
    from_y = 7 - (input[1] - 49);
    to_x = input[3] - 97;
    to_y = 7 - (input[4] - 49);
}

void move_piece(std::vector<std::vector<Piece *> >& board, int from_x, int from_y, int to_x, int to_y) {
    Piece *viewing_piece = board[from_x][from_y];
    board[to_x][to_y] = viewing_piece;
    viewing_piece->set_x_position(to_x);
    viewing_piece->set_y_position(to_y);
    board[from_x][from_y] = NULL;
    
    //delete viewing_piece;
}
