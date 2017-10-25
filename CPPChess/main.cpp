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
std::string compress_board (std::vector<std::vector<Piece *> >& board);
std::string get_full_FEN (std::vector<std::vector<Piece *> >& board, bool turn, int halfmove_counter, int move_number);
std::string get_piece_placement (std::vector<std::vector<Piece *> >& board);
std::string get_castling_rights (std::vector<std::vector<Piece *> >& board);
std::string get_en_passant_rights (std::vector<std::vector<Piece *> >& board);
std::string index_to_algebraic(int x, int y);
int number_of_repeated_boards(std::vector<std::string>& FEN_positions, std::string current);

int main(int argc, const char * argv[]) {
    std::vector<std::vector<Piece *> > board;
    std::vector<Piece *> file;
    std::vector<Point> possible_moves;
    std::vector<Point> white_control;
    std::vector<Point> black_control;
    std::vector<std::string> FEN_values;
    std::fstream fin("ThreeFoldRepetition.txt");
    std::string input;
    int halfmove_counter = 0;
    int move_number = 1;
    int from_x = 0;
    int from_y = 0;
    int to_x = 0;
    int to_y = 0;
    bool turn = true; // 1 = white, 0 = black
    bool draw = false;
    //bool game_ended = false;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        board.push_back(file);
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i].push_back(NULL);
        }
    }
    
    init_board(board, white_control, black_control);
    print_board(board);
    std::cout << get_full_FEN(board, turn, halfmove_counter, move_number) << std::endl;
    FEN_values.push_back(compress_board(board));
    std::cout << compress_board(board) << " :: " << number_of_repeated_boards(FEN_values, *(FEN_values.end() - 1)) << std::endl;
    std::cout << std::endl;
    
    while (!draw) {
        fin >> input;
        //std::cin >> input;
        std::cout << input << std::endl;
        if (!is_valid_input(input)) {
            break;
        }
    
        convert_input(input, from_x, from_y, to_x, to_y);
        
//        std::cout << "From: " << from_x << " " << from_y << std::endl;
//        std::cout << "To: " << to_x << " " << to_y << std::endl;
        
        Piece *viewing_piece = board[from_x][from_y];
        
        if (viewing_piece == NULL) {
            std::cout << "Can't move a square" << std::endl;
            continue;
        }
        if (viewing_piece->isWhite() != turn) {
            std::cout << "Can't move that piece, wrong color" << std::endl;
            continue;
        }
        if (!viewing_piece->validate_move(to_x, to_y)) {
            std::cout << "GIMME A BREAKPOINT" << std::endl;
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
        
        halfmove_counter++;
        if (board[to_x][to_y] != NULL) {
            halfmove_counter = 0;
        }
        move_piece(board, from_x, from_y, to_x, to_y);
        if (!turn) {
            move_number++;
        }
        turn = !turn;
        
        if (dynamic_cast<King *>(viewing_piece) != NULL) {
            // Castle a king
            int rank = viewing_piece->isWhite() ? 7 : 0;
            
            if (to_x - from_x == 2) {
                // Castle Kingside
                move_piece(board, 7, rank, 5, rank);
            }
            else if (to_x - from_x == -2){
                // Castle Queenside
                move_piece(board, 0, rank, 3, rank);
            }
        }
        else if (dynamic_cast<Pawn *>(viewing_piece) != NULL) {
            Pawn *my_pawn = dynamic_cast<Pawn *>(viewing_piece);
            halfmove_counter = 0;
            
            if (abs(from_y - to_y) == 2) {
                my_pawn->set_move_two_spaces(true);
            }
        }
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                Pawn *pawn = dynamic_cast<Pawn *>(board[i][j]);
                if (pawn != NULL && dynamic_cast<Pawn *>(viewing_piece) != pawn) {
                    pawn->set_move_two_spaces(false);
                }
            }
        }
        
        print_board(board);
        
        if (halfmove_counter >= 50) {
            draw = true;
        }
        
        std::cout << get_full_FEN(board, turn, halfmove_counter, move_number) << std::endl;
        FEN_values.push_back(compress_board(board));
        std::cout << compress_board(board) << " :: " << number_of_repeated_boards(FEN_values, *(FEN_values.end() - 1)) << std::endl;
        if (number_of_repeated_boards(FEN_values, *(FEN_values.end() - 1)) >= 3) {
            draw = true;
        }
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
}

std::string compress_board (std::vector<std::vector<Piece *> >& board) {
    std::string compression;
    
    compression += get_piece_placement(board);
    compression += " ";
    compression += get_castling_rights(board);
    compression += " ";
    compression += get_en_passant_rights(board);
    
    return compression;
}

std::string get_full_FEN (std::vector<std::vector<Piece *> >& board, bool turn, int halfmove_counter, int move_number) {
    std::string compression;

    compression += get_piece_placement(board);
    compression += turn ? " w " : " b ";
    compression += get_castling_rights(board);
    compression += ' ';
    compression += get_en_passant_rights(board);
    
    compression += " " + std::to_string(halfmove_counter);
    compression += " " + std::to_string(move_number);
    
    return compression;
}

std::string index_to_algebraic(int x, int y) {
    std::string algebraic;
    
    algebraic += 'a' + x;
    algebraic += '1' + (7-y);
    
    return algebraic;
}

int number_of_repeated_boards(std::vector<std::string>& FEN_positions, std::string current) {
    int count = 0;
    for (int i = 0; i < FEN_positions.size(); i++) {
        if (current == FEN_positions[i]) {
            count++;
        }
    }
    return count;
}

std::string get_piece_placement (std::vector<std::vector<Piece *> >& board) {
    std::string board_compression;
    int empty_squares = 0;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        empty_squares = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[j][i] == NULL) {
                empty_squares++;
            }
            else {
                if (empty_squares != 0) {
                    board_compression += std::to_string(empty_squares);
                }
                board_compression += board[j][i]->get_abbreviation();
                empty_squares = 0;
            }
        }
        
        if (empty_squares != 0) {
            board_compression += std::to_string(empty_squares);
        }
        
        if (i != 7) {
            board_compression += '/';
        }
    }
    
    return board_compression;
}

std::string get_castling_rights (std::vector<std::vector<Piece *> >& board) {
    std::string castling_rights;
    
    if (board[4][7] != NULL && dynamic_cast<King *>(board[4][7]) != NULL && !dynamic_cast<King *>(board[4][7])->did_move()) {
        if (board[7][7] != NULL && dynamic_cast<Rook *>(board[7][7]) != NULL && !dynamic_cast<Rook *>(board[7][7])->did_move()) {
            castling_rights += "K";
        }
        
        if (board[0][7] != NULL && dynamic_cast<Rook *>(board[0][7]) != NULL && !dynamic_cast<Rook *>(board[0][7])->did_move()) {
            castling_rights += "Q";
        }
    }
    
    if (board[4][0] != NULL && dynamic_cast<King *>(board[4][0]) != NULL && !dynamic_cast<King *>(board[4][0])->did_move()) {
        if (board[7][0] != NULL && dynamic_cast<Rook *>(board[7][0]) != NULL && !dynamic_cast<Rook *>(board[7][0])->did_move()) {
            castling_rights += "k";
        }
        
        if (board[0][0] != NULL && dynamic_cast<Rook *>(board[0][0]) != NULL && !dynamic_cast<Rook *>(board[0][0])->did_move()) {
            castling_rights += "q";
        }
    }
    
    if (castling_rights.size() == 0) {
        castling_rights += "-";
    }
    
    return castling_rights;
}

std::string get_en_passant_rights (std::vector<std::vector<Piece *> >& board) {
    std::string en_passant_destination;
    
    for (int i = 3; i <= 4; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[j][i] != NULL) {
                if (dynamic_cast<Pawn *>(board[j][i]) != NULL) {
                    if(dynamic_cast<Pawn *>(board[j][i])->did_move_two_spaces_last_move()) {
                        int direction = board[j][i]->isWhite() ? 1 : -1;
                        en_passant_destination += index_to_algebraic(j, i + direction);
                        return en_passant_destination;
                    }
                }
            }
        }
    }
    
    if (en_passant_destination.size() == 0) {
        en_passant_destination += '-';
    }
    
    return en_passant_destination;
}
