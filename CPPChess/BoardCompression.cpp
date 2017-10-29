//
//  BoardCompression.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/28/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "BoardCompression.hpp"

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
