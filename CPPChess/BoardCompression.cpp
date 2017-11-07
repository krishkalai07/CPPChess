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

void decompress_board (std::vector<std::vector<Piece *> >& board, std::string FEN, King *&white_king, King *&black_king, std::vector<Point>& white_control, std::vector<Point>& black_control, bool &turn, int &move_number, int &halfmove_counter) {
    std::vector<std::string> tokens = split(FEN);    
    std::string placement = tokens[0];
    std::string s_turn = tokens[1];
    std::string castling_rights = tokens[2];
    std::string en_passant_right = tokens[3];
    std::string s_move_number = tokens[4];
    std::string s_halfmove_counter = tokens[5];
    
    for (int i = 0; i < 8; i++) {
        board.push_back(std::vector<Piece *>());
        for (int j = 0; j < 8; j++) {
            board[i].push_back(NULL);
        }
    }
    
    for (int current_index = 0, current_rank = 0, current_file = 0; current_index < placement.length(); current_index++) {
        if (placement[current_index] == '/') {
            current_file = 0;
            current_rank++;
            continue;
        }
        
        if (placement[current_index] == '8') {
            continue;
        }
        
        if (placement[current_index] >= '1' && FEN[current_index] <= '7') {
            current_file += FEN[current_index] - 48;
            continue;
        }
        add_piece(board, placement[current_index], current_file, current_rank, white_control, black_control);
        
        if (placement[current_index] == 'k') {
            black_king = dynamic_cast<King *>(board[current_file][current_rank]);
        }
        if (placement[current_index] == 'K') {
            white_king = dynamic_cast<King *>(board[current_file][current_rank]);
        }
        current_file++;
    }
    
    turn = s_turn == "w" ? true : false;
    
    //Castling Rights
    if (castling_rights[0] == '-') {
        white_king->set_did_move(true);
        black_king->set_did_move(true);
        // If the kings have moved, there's no point in setting the rooks too.
    }
    else {
        bool w_king = false, w_queen = false;
        bool b_king = false, b_queen = false;
        for (int i = 0; i < castling_rights.length(); i++) {
            if (castling_rights[i] == 'K') {
                w_king = true;
            }
            else if (castling_rights[i] == 'Q') {
                w_queen = true;
            }
            else if (castling_rights[i] == 'k') {
                b_king = true;
            }
            else if (castling_rights[i] == 'q') {
                b_queen = true;
            }
        }
        
        if (!w_king) {
            if (board[7][7] != NULL && dynamic_cast<Rook *>(board[7][7]) != NULL) {
                dynamic_cast<Rook *>(board[7][7])->set_did_move(true);
            }
        }
        if (!w_queen) {
            if (board[0][7] != NULL && dynamic_cast<Rook *>(board[0][7]) != NULL) {
                dynamic_cast<Rook *>(board[0][7])->set_did_move(true);
            }
        }
        if (!b_king) {
            if (board[7][0] != NULL && dynamic_cast<Rook *>(board[7][0]) != NULL) {
                dynamic_cast<Rook *>(board[7][0])->set_did_move(true);
            }
        }
        if (!b_queen) {
            if (board[0][0] != NULL && dynamic_cast<Rook *>(board[0][0]) != NULL) {
                dynamic_cast<Rook *>(board[0][0])->set_did_move(true);
            }
        }
    }
    
    // En-passant rights
    if (en_passant_right != "-") {
        int x_index = en_passant_right[0] - 'a';
        int y_index = (en_passant_right[1] - '8') - 8;
        
        if (board[x_index][y_index] != NULL) {
            dynamic_cast<Pawn *>(board[x_index][y_index])->set_move_two_spaces(true);
        }
    }
    
    move_number = std::stoi(s_move_number);
    halfmove_counter = std::stoi(s_halfmove_counter);
}

void add_piece (std::vector<std::vector<Piece *> >& board, char abbreviation, int x, int y, std::vector<Point>& white_control, std::vector<Point>& black_control) {
    switch (abbreviation) {
        case 'k':
            board[x][y] = new King(x, y, false, board, white_control);
            break;
        case 'K':
            board[x][y] = new King(x, y, true, board, black_control);
            break;
        case 'q':
            board[x][y] = new Queen(x, y, false, board);
            break;
        case 'Q':
            board[x][y] = new Queen(x, y, true, board);
            break;
        case 'r':
            board[x][y] = new Rook(x, y, false, board);
            break;
        case 'R':
            board[x][y] = new Rook(x, y, true, board);
            break;
        case 'b':
            board[x][y] = new Bishop(x, y, false, board);
            break;
        case 'B':
            board[x][y] = new Bishop(x, y, true, board);
            break;
        case 'n':
            board[x][y] = new Knight(x, y, false, board);
            break;
        case 'N':
            board[x][y] = new Knight(x, y, true, board);
            break;
        case 'p':
            board[x][y] = new Pawn(x, y, false, board);
            break;
        case 'P':
            board[x][y] = new Pawn(x, y, true, board);
            break;
    }
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
                        int direction = board[j][i]->is_white() ? 1 : -1;
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

std::vector<std::string> split (std::string src) {
    std::vector<std::string> tokens;
    char delim = ' ';
    
    int init = 0, count = 0;
    for (int i = 0; i < src.length(); i++, count++) {
        if (src[i] == delim) {
            tokens.push_back(src.substr(init, count));
            count = -1;
            init = i+1;
        }
    }
    tokens.push_back(src.substr(init, count));
    return tokens;
}
