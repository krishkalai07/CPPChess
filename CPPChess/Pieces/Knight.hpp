//
//  Knight.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Knight_hpp
#define Knight_hpp

#include <stdio.h>
#include "Piece.hpp"

class Knight: public Piece {
public:
    
    Knight(int x_position, int y_position, bool is_white, Piece **board);
    
    virtual ~Knight();
    
    void get_possible_move_list(std::vector<Point> point_list);
    void get_controlled_squares(std::vector<Point> point_list);
};

#endif /* Knight_hpp */
