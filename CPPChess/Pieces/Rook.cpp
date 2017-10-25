//
//  Rook.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Rook.hpp"
#define ABS(i) (i < 0 ? -i : i)

Rook::Rook(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, board) {
    has_moved = false;
}

Rook::~Rook() {
    
}

bool Rook::did_move() {
    return has_moved;
}

void Rook::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Rook::get_controlled_squares(std::vector<Point>& point_list) {
    bool stop_upward = false;
    bool stop_rightward = false;
    bool stop_downward = false;
    bool stop_leftward = false;
    
    for (int i = 1; !stop_upward || !stop_downward || !stop_leftward || !stop_rightward; i++) {
        //upward
        if (y_position - i < 0) {
            stop_upward = true;
        }
        if (!stop_upward) {
            if (board[x_position][y_position - i] != NULL) {
                stop_upward = true;
            }
            point_list.push_back(Point(x_position, y_position - i));
        }
        
        //downward
        if (y_position + i > 7) {
            stop_downward = true;
        }
        if (!stop_downward) {
            if (board[x_position][y_position + i] != NULL) {
                stop_downward = true;
            }
            point_list.push_back(Point(x_position, y_position + i));
        }
        
        //rightward
        if (x_position + i > 7) {
            stop_rightward = true;
        }
        if (!stop_rightward) {
            if (board[x_position + i][y_position] != NULL) {
                stop_rightward = true;
            }
            point_list.push_back(Point(x_position + i, y_position));
        }
        
        //leftward
        if (x_position - i < 0) {
            stop_leftward = true;
        }
        if (!stop_leftward) {
            if (board[x_position - i][y_position] != NULL) {
                stop_leftward = true;
            }
            point_list.push_back(Point(x_position - i, y_position));
        }
    }
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
        return board[to_x][to_y] == NULL || board[to_x][to_y]->isWhite() != color;
    }
    return false;
}

char Rook::get_abbreviation() {
    return color ? 'R' : 'r';
}
