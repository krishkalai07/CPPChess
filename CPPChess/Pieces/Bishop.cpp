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
    // All left up
    for (int i = 1; x_position - i >= 0 && y_position - i >= 0; i++) {
        if (board[x_position-i][y_position-i] == NULL) {
            point_list.push_back(Point(x_position-i, y_position-i));
        }
        else {
            if (board[x_position-i][y_position-i]->isWhite() != this->color) {
                point_list.push_back(Point(x_position - i, y_position - i));
            }
            break;
        }
    }
    
    // All left down
    for (int i = 1; x_position- i >= 0 && y_position + i < 8; i++) {
        if (board[x_position - i][y_position + i] == NULL) {
            point_list.push_back(Point(x_position - i, y_position + i));
        }
        else {
            if (board[x_position - i][y_position + i]->isWhite() != this->color) {
                point_list.push_back(Point(x_position - i, y_position + i));
            }
            break;
        }
    }
    
    // All right down
    for (int i = 1; x_position + i < 8 && y_position + i < 8; i++) {
        if (board[x_position + i][y_position + i] == NULL) {
            point_list.push_back(Point(x_position + i, y_position + i));
        }
        else {
            if (board[x_position + i][y_position + i]->isWhite() != this->color) {
                point_list.push_back(Point(x_position + i, y_position + i));
            }
            break;
        }
    }
    
    // All right up
    for (int i = 1; x_position + i < 8 && y_position - i >= 0; i++) {
        if (board[x_position+ i][y_position - i] == NULL) {
            point_list.push_back(Point(x_position + i, y_position - i));
        }
        else {
            if (board[x_position + i][y_position - i]->isWhite() != this->color) {
                point_list.push_back(Point(x_position + i, y_position - i));
            }
            break;
        }
    }
}

void Bishop::get_controlled_squares(std::vector<Point>& point_list, std::vector<std::vector<Piece*> >& temp_board) {
    bool stop_up_left = false;
    bool stop_up_right = false;
    bool stop_down_left = false;
    bool stop_down_right = false;
    
    for (int i = 1; !stop_up_left || !stop_up_right || !stop_down_left || !stop_down_right; i++) {
        //upward left
        if (x_position - i < 0 || y_position - i < 0) {
            stop_up_left = true;
        }
        if (!stop_up_left) {
            if (temp_board[x_position - i][y_position - i] != NULL) {
                stop_up_left = true;
            }
            point_list.push_back(Point(x_position - i, y_position - i));
        }
        
        //up right
        if (x_position + i > 7 || y_position - i < 0) {
            stop_up_right = true;
        }
        if (!stop_up_right) {
            if (temp_board[x_position + i][y_position - i] != NULL) {
                stop_up_right = true;
            }
            point_list.push_back(Point(x_position + i, y_position - i));
        }
        
        //down left
        if (x_position - i < 0 || y_position + i > 7) {
            stop_down_left = true;
        }
        if (!stop_down_left) {
            if (temp_board[x_position - i][y_position + i] != NULL) {
                stop_down_left = true;
            }
            point_list.push_back(Point(x_position - i, y_position + i));
        }
        
        //down right
        if (x_position + i > 7 || y_position + i > 7) {
            stop_down_right = true;
        }
        if (!stop_down_right) {
            if (temp_board[x_position + i][y_position + i] != NULL) {
                stop_down_right = true;
            }
            point_list.push_back(Point(x_position + i, y_position + i));
        }
    }
}

void Bishop::get_controlled_squares(std::vector<Point>& point_list) {
    get_controlled_squares(point_list, board);
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
        return board[to_x][to_y] == NULL || board[to_x][to_y]->isWhite() != color;
    }
    return false;
}

char Bishop::get_abbreviation() {
    return color ? 'B' : 'b';
}
