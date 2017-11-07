//
//  Bishop.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Bishop.hpp"

Bishop::Bishop(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board): Piece(x_position, y_position, is_white, 3, board) {

}

Bishop::~Bishop() {
    
}

void Bishop::get_possible_move_list(std::vector<Point>& point_list) {
    bishop_attack(board, point_list, x_position, y_position, false);
//    attack_per_direction(board, point_list, x_position, y_position, -1, -1, false);
//    attack_per_direction(board, point_list, x_position, y_position, -1, 1, false);
//    attack_per_direction(board, point_list, x_position, y_position, 1, -1, false);
//    attack_per_direction(board, point_list, x_position, y_position, 1, 1, false);
}

void Bishop::get_controlled_squares(std::vector<Point>& point_list, std::vector<std::vector<Piece*> >& temp_board) {
    bishop_attack(temp_board, point_list, x_position, y_position, true);
//    attack_per_direction(temp_board, point_list, x_position, y_position, -1, -1, true);
//    attack_per_direction(temp_board, point_list, x_position, y_position, -1, 1, true);
//    attack_per_direction(temp_board, point_list, x_position, y_position, 1, -1, true);
//    attack_per_direction(temp_board, point_list, x_position, y_position, 1, 1, true);
}

bool Bishop::validate_move(int to_x, int to_y) {
    int delta_x = 0;
    int delta_y = 0;
    
    if (x_position == to_x && y_position == to_y) {
        return false;
    }
    
    if (abs(x_position - to_x) == abs(y_position - to_y)) {
        for (int i = 1; i < abs(x_position - to_x); i++) {
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

char Bishop::get_abbreviation() {
    return color ? 'B' : 'b';
}
