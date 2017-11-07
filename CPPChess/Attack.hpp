//
//  Attack.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/29/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Attack_hpp
#define Attack_hpp

#include "Piece.hpp"

void attack_per_direction (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, int delta_x, int delta_y, bool check_for_same_color);

void queen_attack (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, bool check_for_same_color);

void rook_attack (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, bool check_for_same_color);

void bishop_attack (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, bool check_for_same_color);
#endif /* Attack_hpp */
