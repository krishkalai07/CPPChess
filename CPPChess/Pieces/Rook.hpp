//
//  Rook.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Rook_hpp
#define Rook_hpp

#include <stdio.h>
#include "Piece.hpp"

class Rook: public Piece {
public:
    
    Rook(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board);
    
    virtual ~Rook();
    
    void get_possible_move_list(std::vector<Point>& point_list);
    void get_controlled_squares(std::vector<Point>& point_list);
};

#endif /* Rook_hpp */
