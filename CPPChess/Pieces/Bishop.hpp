//
//  Bishop.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Bishop_hpp
#define Bishop_hpp

#include <stdio.h>
#include "Piece.hpp"

class Bishop: public Piece {
public:
    
    Bishop(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board);
    
    virtual ~Bishop();
    
    void get_possible_move_list(std::vector<Point>& point_list);
    void get_controlled_squares(std::vector<Point>& point_list, std::vector<std::vector<Piece*> >& temp_board);
    bool validate_move(int x, int y);
    char get_abbreviation();
};

#endif /* Bishop_hpp */
