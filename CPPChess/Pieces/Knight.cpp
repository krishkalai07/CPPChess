//
//  Knight.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Knight.hpp"

Knight::Knight(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, board) {
    
}

Knight::~Knight() {
    
}

void Knight::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Knight::get_controlled_squares(std::vector<Point>& point_list) {
    
}

bool Knight::validate_move(int x, int y) {
    if (position->x == x && position->y == y) {
        return false;
    }
    
    if (abs(abs(x_position - x) - abs(y_position - y)) == 1) {
        if (board[x][y] == NULL) {
            return true;
        }
        else {
            if (board[x][y]->isWhite() != color) {
                return true;
            }
        }
    }
    return false;
}

char Knight::get_abbreviation() {
    return color ? 'N' : 'n';
}
