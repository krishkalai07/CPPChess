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
#define ABS(i) (i < 0 ? -i : i)

class Knight: public Piece {
public:
    
    Knight(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board);
    
    virtual ~Knight();
    
    void get_possible_move_list(std::vector<Point>& point_list);
    void get_controlled_squares(std::vector<Point>& point_list);
    bool validate_move(int x, int y);
    char get_abbreviation();
};

#endif /* Knight_hpp */
