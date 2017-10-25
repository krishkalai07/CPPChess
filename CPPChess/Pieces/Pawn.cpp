//
//  Pawn.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Pawn.hpp"

Pawn::Pawn(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board): Piece(x_position, y_position, is_white, board) {
    moved_two_spaces_last_move = false;
}

Pawn::~Pawn() {
    
}

bool Pawn::did_move_two_spaces_last_move () {
    return moved_two_spaces_last_move;
}

void Pawn::get_possible_move_list(std::vector<Point>& point_list) {
    get_forward_moves(point_list);
    get_capture_moves(point_list);
}

void Pawn::get_controlled_squares(std::vector<Point>& point_list) {
    
}

void Pawn::get_forward_moves(std::vector<Point>& point_list) {
    int movement_direction = color ? -1 : 1;
    
    if (y_position == (isWhite() ? 6 : 1)) {
        if (board[x_position][y_position + (2 * movement_direction)] == NULL) {
            point_list.push_back(Point(x_position, y_position + (2*movement_direction)));
        }
    }
    
    if (board[x_position][y_position + movement_direction] == NULL) {
        point_list.push_back(Point(x_position, y_position + movement_direction));
    }
}

void Pawn::get_capture_moves(std::vector<Point>& point_list) {
    int movement_direction = color ? -1 : 1;
    
    // Left
    if (x_position != 0) {
        // Diagonal
        if (board[x_position - 1][y_position + movement_direction] != NULL) {
            if (board[x_position - 1][y_position + movement_direction]->isWhite() != color) {
                point_list.push_back(Point(x_position - 1, y_position + movement_direction));
            }
        }
        
        // En-passant
        if (y_position == color ? 3 : 4) {
            if (board[x_position - 1][y_position + movement_direction] != NULL) {
                Pawn *casted_piece = dynamic_cast<Pawn *>(board[x_position - 1][y_position]);
                if (casted_piece != NULL) {
                    if (casted_piece->moved_two_spaces_last_move) {
                        point_list.push_back(Point(x_position - 1, y_position + movement_direction));
                    }
                }
            }
        }
    }
    
    // Right
    if (x_position != 7) {
        // Diagonal
        if (board[x_position + 1][y_position + movement_direction] != NULL) {
            if (board[x_position + 1][y_position + movement_direction]->isWhite() != color) {
                point_list.push_back(Point(x_position + 1, y_position + movement_direction));
            }
        }
        
        if (y_position == color ? 3 : 4) {
            if (board[x_position - 1][y_position + movement_direction] != NULL) {
                Pawn *casted_piece = dynamic_cast<Pawn *>(board[x_position - 1][y_position]);
                if (casted_piece != NULL) {
                    if (casted_piece->moved_two_spaces_last_move) {
                        point_list.push_back(Point(x_position - 1, y_position + movement_direction));
                    }
                }
            }
        }
    }
}

void Pawn::set_move_two_spaces (bool did_move) {
    moved_two_spaces_last_move = did_move;
}

bool Pawn::validate_move(int x, int y) {
    int direction = color ? -1 : 1;
    
    if (x_position == x && y_position) {
        return false;
    }
    
    if (abs(y_position - y) == 2 && x_position == x) {
        if (y_position == color ? 6 : 1) {
            if (board[x_position][y_position + direction] == NULL && board[x_position][y_position + (2 * direction)] == NULL) {
                return true;
            }
        }
    }
    else if (abs(y_position - y) == 1) {
        if (x_position == x) {
            if (board[x][y] == NULL) {
                return true;
            }
        }
        else {
            if (board[x][y] != NULL) {
                if (board[x][y]->isWhite() != color) {
                    return true;
                }
            }
            else {
                Pawn *casted_pawn = dynamic_cast<Pawn *>(board[x][y - direction]);
                if (casted_pawn != NULL) {
                    if (casted_pawn->moved_two_spaces_last_move) {
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
}

char Pawn::get_abbreviation() {
    return color ? 'P' : 'p';
}
