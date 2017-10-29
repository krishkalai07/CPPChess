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
                if (board[i][j]->isWhite() != turn) {
                    board[i][j]->get_controlled_squares(controlled_squares, board);
                    
                    if (dynamic_cast<King *>(board[i][j]) != NULL) {
                        king = dynamic_cast<King *>(board[i][j]);
                    }
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
        
        do {
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
                    if (board[tmp_x][tmp_y]->isWhite() != king->isWhite()) {
                        if (dynamic_cast<Rook *>(board[tmp_x][tmp_y]) != NULL || dynamic_cast<Queen *>(board[tmp_x][tmp_y]) != NULL) {
                            move_piece(board, to_x, to_y, from_x, from_y);
                            if (tmp_x == to_x && tmp_y == to_y) {
                                return board[from_x][from_y]->isWhite() == king->isWhite();
                            }
                            else {
                                return board[tmp_y][tmp_y]->isWhite() == king->isWhite();
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
                    if (board[tmp_x][tmp_y]->isWhite() != king->isWhite()) {
                        if (dynamic_cast<Bishop *>(board[tmp_x][tmp_y]) != NULL || dynamic_cast<Queen *>(board[tmp_x][tmp_y]) != NULL) {
                            move_piece(board, to_x, to_y, from_x, from_y);
                            if (tmp_x == to_x && tmp_y == to_y) {
                                return board[from_x][from_y]->isWhite() == king->isWhite();
                            }
                            else {
                                return board[tmp_y][tmp_y]->isWhite() == king->isWhite();
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
        } while (tmp_x >= 0 && tmp_x < 8 && tmp_y >= 0 && tmp_y < 8);
    }
    else {
        move_piece(board, to_x, to_y, from_x, from_y);
        return simulate_move(board, from_x, from_y, to_x, to_y, king->isWhite());
    }
    move_piece(board, to_x, to_y, from_x, from_y);
    return true;
}

//15  5  10
//  \ | /
//3 - K - 2
//  / | \
//21  7  14
int get_relative_location (std::vector<std::vector<Piece *> >& board, int from_x, int from_y, King *king) {
    int king_x = king->get_x_position();
    int king_y = king->get_y_position();
    if (king_x == from_x) {
        // Same rank
        if (king_y - from_y > 0) {
            return 5;
        }
        else {
            return 7;
        }
    }
    else if (king_y == from_y) {
        // Same file
        if (king_x - from_x > 0) {
            return 2;
        }
        else {
            return 3;
        }
    }
    else if (king_y - from_y == -(king_x - from_x)) {
        // Same diagonal
        if (king_y - from_y > 0) {
            return 10;
        }
        else {
            return 21;
        }
    }
    else if (king_y - from_y == king_x - from_x) {
        // Same anti-diagonal
        if (king_y - from_y > 0) {
            return 15;
        }
        else {
            return 14;
        }
    }
    else {
        // None of the above
        return 1;
    }
}
