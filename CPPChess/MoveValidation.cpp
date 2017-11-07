//
//  MoveValidation.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/28/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "MoveValidation.hpp"

#pragma mark - old methods
bool simulate_move(std::vector<std::vector<Piece *> > board, int from_x, int from_y, int to_x, int to_y, bool turn) {
    std::vector<Point> controlled_squares;
    King *king = NULL;
    
    move_piece(board, from_x, from_y, to_x, to_y);
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != NULL) {
                if (board[i][j]->is_white() != turn) {
                    board[i][j]->get_controlled_squares(controlled_squares, board);
                }
                if (board[i][j]->is_white() == turn && dynamic_cast<King *>(board[i][j]) != NULL) {
                    king = dynamic_cast<King *>(board[i][j]);
                }
            }
        }
    }
    
    if (vector_contains_point(controlled_squares, king->get_x_position(), king->get_y_position())) {
        move_piece(board, to_x, to_y, from_x, from_y);
        return false;
    }
    
    move_piece(board, to_x, to_y, from_x, from_y);
    return true;
}

void move_piece(std::vector<std::vector<Piece *> >& board, int from_x, int from_y, int to_x, int to_y) {
    Piece *viewing_piece = board[from_x][from_y];
    board[to_x][to_y] = viewing_piece;
    viewing_piece->set_x_position(to_x);
    viewing_piece->set_y_position(to_y);
    board[from_x][from_y] = NULL;
}

#pragma mark - new methods

bool is_legal_move (std::vector<std::vector<Piece *> > board, int from_x, int from_y, int to_x, int to_y, King *king) {
    move_piece(board, from_x, from_y, to_x, to_y);
    
    if (dynamic_cast<King *>(board[from_x][from_y]) == NULL) {
        int direction = get_relative_location(board, from_x, from_y, king);
        if (direction == 1) {
            move_piece(board, to_x, to_y, from_x, from_y);
            return true;
        }
        
        int tmp_x = king->get_x_position();
        int tmp_y = king->get_y_position();
        
        while (true) {
            if (direction % 2 == 0) {
                tmp_x++;
            }
            if (direction % 3 == 0) {
                tmp_x--;
            }
            if (direction % 5 == 0) {
                tmp_y--;
            }
            if (direction % 7 == 0) {
                tmp_y++;
            }

            if (tmp_x < 0 || tmp_x >= 8 || tmp_y < 0 || tmp_y >= 8) {
                move_piece(board, to_x, to_y, from_x, from_y);
                return true;
            }
            
            if (board[tmp_x][tmp_y] != NULL) {
                if (direction == 2 || direction == 3 || direction == 5 || direction == 7) {
                    if (board[tmp_x][tmp_y]->is_white() != king->is_white()) {
                        if (dynamic_cast<Rook *>(board[tmp_x][tmp_y]) != NULL || dynamic_cast<Queen *>(board[tmp_x][tmp_y]) != NULL) {
                            move_piece(board, to_x, to_y, from_x, from_y);
                            if (tmp_x == to_x && tmp_y == to_y) {
                                return board[from_x][from_y]->is_white() == king->is_white();
                            }
                            else {
                                return board[tmp_y][tmp_y]->is_white() == king->is_white();
                            }
                        }
                        else {
                            move_piece(board, to_x, to_y, from_x, from_y);
                            return true;
                        }
                    }
                    else {
                        move_piece(board, to_x, to_y, from_x, from_y);
                        return true;
                    }
                }
                else if (direction == 10 || direction == 14 || direction == 25 || direction == 21) {
                    if (board[tmp_x][tmp_y]->is_white() != king->is_white()) {
                        if (dynamic_cast<Bishop *>(board[tmp_x][tmp_y]) != NULL || dynamic_cast<Queen *>(board[tmp_x][tmp_y]) != NULL) {
                            move_piece(board, to_x, to_y, from_x, from_y);
                            if (tmp_x == to_x && tmp_y == to_y) {
                                return board[from_x][from_y]->is_white() == king->is_white();
                            }
                            else {
                                return board[tmp_y][tmp_y]->is_white() == king->is_white();
                            }
                        }
                        else {
                            move_piece(board, to_x, to_y, from_x, from_y);
                            return true;
                        }
                    }
                    else {
                        move_piece(board, to_x, to_y, from_x, from_y);
                        return true;
                    }
                }
            }
        }
    }
    else {
        move_piece(board, to_x, to_y, from_x, from_y);
        std::vector<Point> point_list;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                point_list.clear();
                if (i == 0 && i == j) {
                    continue;
                }
                
                attack_per_direction(board, point_list, to_x, to_y, i, j, false);
                
                for (Point p : point_list) {
                    if (board[p.x][p.y] != NULL) {
                        if ((i == 0 || j == 0) && (dynamic_cast<Rook *>(board[p.x][p.y]) != NULL || dynamic_cast<Queen *>(board[p.x][p.y]) != NULL)) {
                            return false;
                        }
                        if ((abs(i) == 1 && abs(j) == 1) && (dynamic_cast<Bishop *>(board[p.x][p.y]) != NULL || dynamic_cast<Queen *>(board[p.x][p.y]) != NULL)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    move_piece(board, to_x, to_y, from_x, from_y);
    return true;
}

//15  5  10
//  \ | /
//3 — K — 2
//  / | \
//21  7  14
int get_relative_location (std::vector<std::vector<Piece *> >& board, int from_x, int from_y, King *king) {
    int king_x = king->get_x_position();
    int king_y = king->get_y_position();
    if (king_x == from_x) {
        return king_y - from_y > 0 ? 5 : 7;
    }
    else if (king_y == from_y) {
        return king_x - from_x > 0 ? 2 : 3;
    }
    else if (king_y - from_y == -(king_x - from_x)) {
        return king_y - from_y > 0 ? 10 : 21;
    }
    else if (king_y - from_y == king_x - from_x) {
        return king_y - from_y > 0 ? 15 : 14;
    }
    else {
        return 1;
    }
}
