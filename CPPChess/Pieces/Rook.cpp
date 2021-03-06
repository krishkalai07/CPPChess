//
//  Rook.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Rook.hpp"
#define ABS(i) (i < 0 ? -i : i)

Rook::Rook(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, 5, board) {
    has_moved = false;
}

Rook::~Rook() {
    
}

bool Rook::did_move() {
    return has_moved;
}

void Rook::set_did_move(bool did_move) {
    this->has_moved = did_move;
}

void Rook::get_possible_move_list(std::vector<Point>& point_list) {
    rook_attack(board, point_list, x_position, y_position, false);
    attack_per_direction(board, point_list, x_position, y_position, -1, 0, false);
    attack_per_direction(board, point_list, x_position, y_position, 1, 0, false);
    attack_per_direction(board, point_list, x_position, y_position, 0, -1, false);
    attack_per_direction(board, point_list, x_position, y_position, 0, 1, false);
}

void Rook::get_controlled_squares(std::vector<Point>& point_list, std::vector<std::vector<Piece*> >& temp_board) {
    rook_attack(temp_board, point_list, x_position, y_position, true);
//    attack_per_direction(temp_board, point_list, x_position, y_position, -1, 0, true);
//    attack_per_direction(temp_board, point_list, x_position, y_position, 1, 0, true);
//    attack_per_direction(temp_board, point_list, x_position, y_position, 0, -1, true);
//    attack_per_direction(temp_board, point_list, x_position, y_position, 0, 1, true);
}

bool Rook::validate_move(int to_x, int to_y) {
    int delta_x = 0;
    int delta_y = 0;
    
    if (x_position == to_x && y_position == to_y) {
        return false;
    }
    
    if ((abs(x_position - to_x) != 0 && abs(y_position - to_y) == 0) || (abs(x_position - to_x) == 0 && abs(y_position - to_y) != 0)) {
        int condition = abs(x_position - to_x) > abs(y_position - to_y) ? abs(x_position - to_x) : abs(y_position - to_y);
        for (int i = 1; i < condition; i++) {
            delta_x = (x_position - to_x < 0 ? x_position + i : (x_position - to_x > 0 ? x_position-i : x_position));
            delta_y = (y_position - to_y < 0 ? y_position + i : (y_position - to_y > 0 ? y_position-i : y_position));
            
            if (board[delta_x][delta_y] != NULL) {
                return false;
            }
        }
        return board[to_x][to_y] == NULL || board[to_x][to_y]->is_white() != color;
    }
    return false;
}

char Rook::get_abbreviation() {
    return color ? 'R' : 'r';
}
