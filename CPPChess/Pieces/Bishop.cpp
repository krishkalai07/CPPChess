//
//  Bishop.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Bishop.hpp"

Bishop::Bishop(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, board) {
    
}

Bishop::~Bishop() {
    
}

void Bishop::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Bishop::get_controlled_squares(std::vector<Point>& point_list) {
    
}

bool Bishop::validate_move(int to_x, int to_y) {
    int delta_x = 0;
    int delta_y = 0;
    
    if (x_position == to_x && y_position == to_y) {
        return false;
    }
    
    if (abs(x_position - to_x) == abs(y_position - to_y)) {
        for (int i = 1; i < abs(x_position - to_x); i++) {
            delta_x = x_position + (x_position - to_x < 0 ? i : -i);
            delta_y = y_position + (y_position - to_y < 0 ? i : -i);
            if (board[delta_x][delta_y] != NULL) {
                return false;
            }
        }
        if (board[to_x][to_y] != NULL) {
            if (board[to_x][to_y]->isWhite() != color) {
                return true;
            }
        }
        else {
            return true;
        }
    }
    return false;
}
