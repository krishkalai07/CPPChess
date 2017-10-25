//
//  King.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "King.hpp"

King::King(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board, std::vector<Point>& control_squares):Piece(x_position, y_position, is_white, board) {
    this->control_squares = control_squares;
    this->has_moved = false;
}

King::~King() {
    
}

bool King::did_move() {
    return has_moved;
}

void King::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void King::get_controlled_squares(std::vector<Point>& point_list) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Prevent checking the square it's on.
            if (i == 0 && j == 0) {
                continue;
            }
            
            if (x_position+i >= 0 && x_position+i < 8 && y_position+j >= 0 && y_position+j < 8) {
                point_list.push_back(Point(x_position+i,y_position+j));
            }
        }
    }
}

bool King::vector_contains_point(std::vector<Point>& point_list, int x, int y) {
    for (int i = 0; i < control_squares.size(); i++) {
        if (x == control_squares[i].x && y == control_squares[i].y) {
            return true;
        }
    }
    return false;
}

bool King::is_in_check () {
    return vector_contains_point(control_squares, x_position, y_position);
}

bool King::validate_move(int x, int y) {
    if (x_position == x && y_position == y) {
        return false;
    }
    
    if (abs(x_position - x) == 2) {
        if (!has_moved) {
            Rook *edge_rook = dynamic_cast<Rook *>(x_position - x == 2 ? board[7][(color ? 7 : 0)] : board[0][(color ? 7 : 0)]);
            if (edge_rook != NULL && !edge_rook->did_move()) {
                if ((x - x_position > 0 && board[x_position+1][y_position] == NULL && board[x_position+2][y_position] == NULL) ||
                    (x - x_position < 0 && board[x_position-1][y_position] == NULL && board[x_position-2][y_position] == NULL)) {
                    if (!is_in_check()) {
                        if (!vector_contains_point(control_squares, x_position - x > 0 ? x_position - 1 : x_position + 1, y_position) &&
                            !vector_contains_point(control_squares, x_position - x > 0 ? x_position - 2 : x_position + 2, y_position)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else {
        if (abs(x_position - x) <= 1 && abs(y_position - y) <= 1) {
            if (!vector_contains_point(control_squares, x, y)) {
                return true;
            }
        }
    }
    return false;
}

char King::get_abbreviation() {
    return color ? 'K' : 'k';
}
