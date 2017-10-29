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

void King::set_did_move(bool has_moved) {
    this->has_moved = has_moved;
}

void King::get_possible_move_list(std::vector<Point>& point_list) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Prevent checking the square it's on.
            if (i == 0 && j == 0) {
                continue;
            }
            
            if (x_position+i >= 0 && x_position+i < 8 && y_position+j >= 0 && y_position+j < 8) {
                if (board[x_position+i][y_position+j] == NULL) {
                    Point point = Point(x_position+i, y_position+j);
                    if (this->color && !vector_contains_point(control_squares, point.x, point.y)) {
                        point_list.push_back(Point(x_position+i, y_position+j));
                    }
                    else if (!this->color && !vector_contains_point(control_squares, point.x, point.y)) {
                        point_list.push_back(Point(x_position+i, y_position+j));
                    }
                }
                else {
                    if (this->color != board[x_position+i][y_position+j]->isWhite()) {
                        point_list.push_back(Point(x_position+i, y_position+j));
                    }
                }
            }
        }
    }
    
    // Castling
    if (!has_moved) {
        if (vector_contains_point(control_squares, x_position, y_position)) {
            return;
        }
        
        // Castling king-side
        if (board[x_position+1][y_position] == NULL && board[x_position+2][y_position] == NULL) {
            if (!vector_contains_point(control_squares, x_position + 1, y_position) && !vector_contains_point(control_squares, x_position + 2, y_position)) {
                if (board[x_position + 3][y_position] != NULL && dynamic_cast<Rook*>(board[x_position + 3][y_position]) != NULL && !dynamic_cast<Rook*>(board[x_position + 3][y_position])->did_move()) {
                    point_list.push_back(Point(x_position + 2, y_position));
                }
            }
        }
        // Castling queen-side
        if (board[x_position-1][y_position] == NULL && board[x_position-2][y_position] == NULL && board[x_position-3][y_position] == NULL) {
            if (!vector_contains_point(control_squares, x_position - 1, y_position) && !vector_contains_point(control_squares, x_position - 2, y_position)) {
                if (board[x_position - 4][y_position] != NULL && dynamic_cast<Rook *>(board[x_position - 4][y_position]) != NULL && !dynamic_cast<Rook *>(board[x_position - 4][y_position])->did_move()) {
                    point_list.push_back(Point(x_position - 2, y_position));
                }
            }
        }
    }
}

void King::get_controlled_squares(std::vector<Point>& point_list, std::vector<std::vector<Piece*> >& temp_board) {
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

void King::get_controlled_squares(std::vector<Point>& point_list) {
    get_controlled_squares(point_list, this->board);
}

bool King::vector_contains_point(std::vector<Point>& point_list, int x, int y) {
    for (int i = 0; i < point_list.size(); i++) {
        if (x == point_list[i].x && y == point_list[i].y) {
            return true;
        }
    }
    return false;
}

bool King::is_in_check () {
    update_controlled_spaces();
    return vector_contains_point(control_squares, x_position, y_position);
}

bool King::validate_move(int x, int y) {
    if (x_position == x && y_position == y) {
        return false;
    }

    update_controlled_spaces();
    
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

void King::update_controlled_spaces() {
    control_squares.clear();
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != NULL && board[i][j]->isWhite() != color) {
                board[i][j]->get_controlled_squares(control_squares);
            }
        }
    }
}
