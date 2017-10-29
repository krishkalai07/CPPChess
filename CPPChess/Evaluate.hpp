//
//  Evaluate.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/29/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Evaluate_hpp
#define Evaluate_hpp

#include <vector>
#include "Piece.hpp"

int get_material_advantage (std::vector<std::vector <Piece *> > board);
int get_pawn_placement_advantage (std::vector<std::vector <Piece *> > board);
int get_mobility_advantage (std::vector<std::vector <Piece *> > baord);

#endif /* Evaluate_hpp */
