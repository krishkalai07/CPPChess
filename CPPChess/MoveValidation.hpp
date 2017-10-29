//
//  MoveValidation.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/28/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef MoveValidation_hpp
#define MoveValidation_hpp

#include "Piece.hpp"
#include "King.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"

#define BOARD_SIZE 8

bool simulate_move(std::vector<std::vector<Piece *> > board, int from_x, int from_y, int to_x, int to_y, bool turn);
void move_piece(std::vector<std::vector<Piece *> >& board, int from_x, int from_y, int to_x, int to_y);

bool is_legal_move (std::vector<std::vector<Piece *> > board, int from_x, int from_y, int to_x, int to_y, King *king);
int get_relative_location (std::vector<std::vector<Piece *> >& board, int from_x, int from_y, King *king);

#endif /* MoveValidation_hpp */
