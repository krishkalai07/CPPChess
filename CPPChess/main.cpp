
//  main.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//
// For me, pointer as array reminder: cpp.sh/2shge

#define INPUT_NOTATION 0 //0 for long algebraic, 1 short algeabraic

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
#include "BoardCompression.hpp"
#include "MoveValidation.hpp"

#include "Evaluate.hpp"

void init_board (std::vector<std::vector<Piece *> >& board, std::vector<Point>& white_control, std::vector<Point>& black_control, King *&white_king, King *&black_king);
void print_board (std::vector<std::vector<Piece *> >& board);
bool is_valid_input (std::string input);
void convert_input (std::string input, int &from_x, int &from_y, int &to_x, int &to_y);
void convert_input (std::string input, int &from_x, int &from_y, int &to_x, int &to_y, char &promotion_value);
int number_of_repeated_boards(std::vector<std::string>& FEN_positions, std::string current);
bool vector_contains_point(std::vector<Point>& point_list, int x, int y);

int main(int argc, const char * argv[]) {
    std::vector<std::vector<Piece *> > board;
    std::vector<Point> possible_moves;
    std::vector<Point> white_control;
    std::vector<Point> black_control;
    std::vector<std::string> FEN_values;
    std::fstream fin("RulesTesting.txt");
    King *white_king = NULL;
    King *black_king = NULL;
    std::string input;
    int halfmove_clock = 0;
    int fullmove_counter = 1;
    int from_x = 0;
    int from_y = 0;
    int to_x = 0;
    int to_y = 0;
    char promotion_value = 0;
    bool turn = true; // 1 = white, 0 = black
    bool draw = false;
    bool game_ended = false;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        board.push_back(std::vector<Piece *>());
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i].push_back(NULL);
        }
    }
    
    std::string starting_position = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string current_testing = "rn1qkbnr/pppbpppp/8/1B1p4/3PP3/8/PPP2PPP/RNBQK1NR b KQkq d3 0 3";
    decompress_board(board, current_testing, white_king, black_king, white_control, black_control, turn, halfmove_clock, fullmove_counter);
    //decompress_board(board, "r1n4N/1Kp2b1p/PPp1pr2/PRbQ1pR1/2PP1p1k/PN3B1P/p1PB1q1p/5n2 w - - 0 1", white_king, black_king, white_control, black_control, turn, halfmove_clock, fullmove_counter);
    print_board(board);
    FEN_values.push_back(compress_board(board));
    
    std::cout << get_full_FEN(board, turn, halfmove_clock, fullmove_counter);
    std::cout << std::endl;
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != NULL) {
                board[i][j]->get_controlled_squares(board[i][j]->is_white() ? white_control : black_control);
                
                if (board[i][j]->is_white() == turn) {
                    board[i][j]->get_possible_move_list(possible_moves);
                }
            }
        }
    }
    
    while (!draw && !game_ended && !fin.eof()) {
        //fin >> input;
        //std::cout << (turn ? std::to_string(fullmove_counter) + " " : "") << input << std::endl;
        std::cin >> input;
        
        if (!is_valid_input(input)) {
            continue;
        }
    
        if (input.length() == 4) {
            convert_input(input, from_x, from_y, to_x, to_y);
        }
        else {
            convert_input(input, from_x, from_y, to_x, to_y, promotion_value);
        }
        
        Piece *viewing_piece = board[from_x][from_y];
        
        if (viewing_piece == NULL) {
            std::cout << "Can't move a square" << std::endl;
            continue;
        }
        if (viewing_piece->is_white() != turn) {
            std::cout << "Can't move that piece, wrong color" << std::endl;
            continue;
        }

        if (!viewing_piece->validate_move(to_x, to_y)) {
            std::cout << "Entered illegal move" << std::endl;
            std::cout << std::endl;
            continue;
        }
        if (white_king->is_in_check() || black_king->is_in_check()) {
            if (!simulate_move(board, from_x, from_y, to_x, to_y, turn)) {
                std::cout << "Move puts your king in check" << std::endl;
                std::cout << std::endl;
                continue;
            }
        }
        else {
            if (!is_legal_move(board, from_x, from_y, to_x, to_y, turn ? white_king : black_king)) {
                std::cout << "Move puts your king in check" << std::endl;
                std::cout << std::endl;
                continue;
            }
        }
    
        halfmove_clock++;
        if (board[to_x][to_y] != NULL) {
            halfmove_clock = 0;
        }
        move_piece(board, from_x, from_y, to_x, to_y);
        if (!turn) {
            fullmove_counter++;
        }
        turn = !turn;
        
        if (dynamic_cast<King *>(viewing_piece) != NULL) {
            // Castle a king
            int rank = viewing_piece->is_white() ? 7 : 0;
            
            if (to_x - from_x == 2) {
                // Castle Kingside
                move_piece(board, 7, rank, 5, rank);
            }
            else if (to_x - from_x == -2){
                // Castle Queenside
                move_piece(board, 0, rank, 3, rank);
            }
            dynamic_cast<King *>(viewing_piece)->set_did_move(true);
        }
        else if (dynamic_cast<Pawn *>(viewing_piece) != NULL) {
            Pawn *pawn = dynamic_cast<Pawn *>(viewing_piece);
            
            halfmove_clock = 0;
            
            // En passant
            if (from_x != to_x) {
                if (board[to_x][to_y] == NULL) {
                    board[to_x][pawn->is_white() ? to_y + 1 : to_y - 1] = NULL;
                }
            }
            
            if (abs(from_y - to_y) == 2) {
                pawn->set_move_two_spaces(true);
            }
            
            int p_x = pawn->get_x_position();
            int p_y = pawn->get_y_position();
            
            // Pawn promotion
            if (pawn->get_y_position() == (pawn->is_white() ? 0 : 7)) {
                switch (promotion_value) {
                    case 'q':
                    case 'Q':
                        board[p_x][p_y] = new Queen(p_x, p_y, pawn->is_white(), board);
                        break;
                    case 'r':
                    case 'R':
                        board[p_x][p_y] = new Rook(p_x, p_y, pawn->is_white(), board);
                        break;
                    case 'b':
                    case 'B':
                        board[p_x][p_y] = new Bishop(p_x, p_y, pawn->is_white(), board);
                        break;
                    case 'n':
                    case 'N':
                        board[p_x][p_y] = new Knight(p_x, p_y, pawn->is_white(), board);
                        break;
                }
            }
        }
        
        std::cout << "Material advantage of current position: " << get_material_advantage(board) << std::endl;
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 3; j <= 4; j++) {
                Pawn *pawn = dynamic_cast<Pawn *>(board[i][j]);
                if (pawn != NULL && dynamic_cast<Pawn *>(viewing_piece) != pawn) {
                    pawn->set_move_two_spaces(false);
                }
            }
        }
        
        print_board(board);
        
        if (halfmove_clock >= 50) {
            draw = true;
        }
        
        white_control.clear();
        black_control.clear();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] != NULL) {
                    if (board[i][j]->is_white() == turn) {
                        board[i][j]->get_controlled_squares(white_control);
                    }
                    else {
                        board[i][j]->get_controlled_squares(black_control);
                    }
                }
            }
        }
        
        int count = 0;
        possible_moves.clear();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] != NULL) {
                    if (board[i][j]->is_white() == turn) {
                        possible_moves.clear();
                        board[i][j]->get_possible_move_list(possible_moves);
                        
                        int t_from_x = board[i][j]->get_x_position();
                        int t_from_y = board[i][j]->get_y_position();
                        
                        for (int k = 0; k < possible_moves.size();) {
                            if ((turn ? white_king : black_king)->is_in_check()) {
                                if (!simulate_move(board, t_from_x, t_from_y, possible_moves[k].x, possible_moves[k].y, turn)) {
                                    possible_moves.erase(possible_moves.begin() + k);
                                    continue;
                                }
                            }
                            else {
                                if (!is_legal_move(board, t_from_x, t_from_y, possible_moves[k].x, possible_moves[k].y, turn ? white_king : black_king)) {
                                    possible_moves.erase(possible_moves.begin() + k);
                                    continue;
                                }
                            }
                            k++;
                        }
                        count += possible_moves.size();
                        if (count > 0) {
                            break;
                        }
                    }
                }
            }
            if (count > 0) {
                break;
            }
        }

        if (count == 0) {
            if ((turn ? white_king : black_king)->is_in_check()) {
                game_ended = true;
            }
            else {
                draw = true;
            }
        }
    
        FEN_values.push_back(compress_board(board));
        
        if (number_of_repeated_boards(FEN_values, *(FEN_values.end() - 1)) >= 3) {
            draw = true;
        }
        std::cout << std::endl;
    }
    
    if (draw) {
        std::cout << "Game is a draw" << std::endl;
    }
    if (game_ended) {
        std::cout << (turn ? "Black won this game 0 - 1" : "White won this game 1 - 0") << std::endl;
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

void init_board (std::vector<std::vector<Piece *> >& board, std::vector<Point>& white_control, std::vector<Point>& black_control, King *&white_king, King *&black_king) {
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
    black_king = dynamic_cast<King *>(board[4][0]);
    board[4][7] = new King(4, 7,true, board, black_control);
    white_king = dynamic_cast<King *>(board[4][7]);
    
    //Pawns
    for (int i = 0; i < 8; i++) {
        board[i][1] = new Pawn(i, 1,false, board);
    }
    
    for (int i = 0; i < 8; i++) {
        board[i][6] = new Pawn(i, 6,true, board);
    }
}

void print_board (std::vector<std::vector<Piece *> >& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[j][i] != NULL) {
                std::cout << board[j][i]->get_abbreviation();
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
        if (input.size() == 4) {
            if ((input[0] >= 'a' && input[0] <= 'h') && (input[1] >= '1' && input[1] <= '8')) {
                if ((input[2] >= 'a' && input[2] <= 'h') && (input[3] >= '1' && input[3] <= '8')) {
                    return true;
                }
            }
        }
        if (input.size() == 5) {
            if (input[4] == 'q' || input[4] == 'Q' || input[4] == 'r' || input[4] == 'R' || input[4] == 'b' || input[4] == 'B' || input[4] == 'n' || input[4] == 'N') {
                if ((input[0] >= 'a' && input[0] <= 'h') && (input[1] >= '1' && input[1] <= '8')) {
                    if ((input[2] >= 'a' && input[2] <= 'h') && (input[3] >= '1' && input[3] <= '8')) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void convert_input (std::string input, int &from_x, int &from_y, int &to_x, int &to_y) {
    if (INPUT_NOTATION == 0) {
        from_x = input[0] - 97;
        from_y = 7 - (input[1] - 49);
        to_x = input[2] - 97;
        to_y = 7 - (input[3] - 49);
    }
}

void convert_input (std::string input, int &from_x, int &from_y, int &to_x, int &to_y, char &promotion_value) {
    convert_input(input, from_x, from_y, to_x, to_y);
    promotion_value = input[4];
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

bool vector_contains_point(std::vector<Point>& point_list, int x, int y) {
    for (int i = 0; i < point_list.size(); i++) {
        if (x == point_list[i].x && y == point_list[i].y) {
            return true;
        }
    }
    return false;
}
