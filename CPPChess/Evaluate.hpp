//
//  Evaluate.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/29/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Evaluate_hpp
#define Evaluate_hpp

#include "Piece.hpp"
#include "Pawn.hpp"

int get_material_advantage (std::vector<std::vector <Piece *> >& board);
int get_pawn_placement_advantage (std::vector<std::vector <Piece *> >& board);
int get_mobility_advantage (std::vector<std::vector <Piece *> >& baord);

int pawns_in_file(std::vector<std::vector <Piece *> >& board, int file, bool color);

int get_isolated_pawns (std::vector<std::vector <Piece *> >& board, bool color);
int get_doubled_pawns (std::vector<std::vector <Piece *> >& board, bool color);
int get_backward_pawns (std::vector<std::vector <Piece *> >& board, bool color);
int get_phlanax (std::vector<std::vector <Piece *> >& board, bool color);

#endif /* Evaluate_hpp */
