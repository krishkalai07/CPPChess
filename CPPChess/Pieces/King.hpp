//
//  King.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef King_hpp
#define King_hpp

#include <stdio.h>
#include "Piece.hpp"

class King: public Piece {
private:
    void get_normal_moves(std::vector<Point>& point_list);
    void get_castle_moves(std::vector<Point>& point_list);
public:
    King(int x_position, int y_position, bool is_white, Piece ***board);
    
    virtual ~King();
    
    void get_possible_move_list(std::vector<Point>& point_list);
    void get_controlled_squares(std::vector<Point>& point_list);
};

#endif /* King_hpp */
