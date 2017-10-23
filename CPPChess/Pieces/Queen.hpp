//
//  Queen.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Queen_hpp
#define Queen_hpp

#include <stdio.h>
#include "Piece.hpp"

class Queen: public Piece {
public:
    
    Queen(int x_position, int y_position, bool is_white, Piece ***board);
    
    virtual ~Queen();
    
    void get_possible_move_list(std::vector<Point>& point_list);
    void get_controlled_squares(std::vector<Point>& point_list);
};

#endif /* Queen_hpp */
