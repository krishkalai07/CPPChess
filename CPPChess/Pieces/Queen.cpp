//
//  Queen.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Queen.hpp"
#define ABS(i) (i < 0 ? -i : i)

Queen::Queen(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, board) {
    
}

Queen::~Queen() {
    
}

void Queen::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Queen::get_controlled_squares(std::vector<Point>& point_list) {
    bool stop_up_left = false;
    bool stop_up_right = false;
    bool stop_down_left = false;
    bool stop_down_right = false;
    bool stop_upward = false;
    bool stop_rightward = false;
    bool stop_downward = false;
    bool stop_leftward = false;
    
    for (int i = 1; !stop_up_left || !stop_up_right || !stop_down_left || !stop_down_right || !stop_upward || !stop_downward || !stop_leftward || !stop_rightward; i++) {
        //upward left
        if (x_position - i < 0 || y_position - i < 0) {
            stop_up_left = true;
        }
        if (!stop_up_left) {
            if (board[x_position - i][y_position - i] != NULL) {
                stop_up_left = true;
            }
            point_list.push_back(Point(x_position - i, y_position - i));
        }
        
        //up right
        if (x_position + i > 7 || y_position - i < 0) {
            stop_up_right = true;
        }
        if (!stop_up_right) {
            if (board[x_position + i][y_position - i] != NULL) {
                stop_up_right = true;
            }
            point_list.push_back(Point(x_position + i, y_position - i));
        }
        
        //down left
        if (x_position - i < 0 || y_position + i > 7) {
            stop_down_left = true;
        }
        if (!stop_down_left) {
            if (board[x_position - i][y_position + i] != NULL) {
                stop_down_left = true;
            }
            point_list.push_back(Point(x_position + i, y_position + i));
        }
        
        //down right
        if (x_position + i > 7 || y_position + i > 7) {
            stop_down_right = true;
        }
        if (!stop_down_right) {
            if (board[x_position + i][y_position + i] != NULL) {
                stop_down_right = true;
            }
            point_list.push_back(Point(x_position - i, y_position + i));
        }
        
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

bool Queen::validate_move(int to_x, int to_y) {
    int delta_x = 0;
    int delta_y = 0;
    
    if (x_position == to_x && y_position == to_y) {
        return false;
    }
    
    if ((abs(x_position - to_x) != 0 && abs(y_position - to_y) == 0) ||
        (abs(x_position - to_x) == 0 && abs(y_position - to_y) != 0) ||
        (abs(x_position - to_x) == abs(y_position - to_y))) {
        for (int i = 1; i < abs(x_position - to_x); i++) {
            delta_x = (x_position - to_x < 0 ? x_position + i : (x_position - to_x > 0 ? x_position-i : x_position));
            delta_y = (y_position - to_y < 0 ? y_position + i : (y_position - to_y > 0 ? y_position-i : y_position));
            if (board[delta_x][delta_y] != NULL) {
                return false;
            }
        }
        if (board[to_x][to_y] == NULL) {
            return true;
        }
        else {
            if (board[to_x][to_y]->isWhite() != color) {
                return true;
            }
        }
        //return board[to_x][to_y] == NULL || board[to_x][to_y]->isWhite() != color;
    }
    return false;
}

char Queen::get_abbreviation() {
    return color ? 'Q' : 'q';
}
