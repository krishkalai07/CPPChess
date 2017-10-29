//
//  Attack.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/29/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Attack_hpp
#define Attack_hpp

#include <vector>
#include "Piece.hpp"

void attack_per_direction (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, int delta_x, int delta_y, bool check_for_same_direction);

#endif /* Attack_hpp */
