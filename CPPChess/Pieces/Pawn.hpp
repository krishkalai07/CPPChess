//
//  Pawn.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Pawn_hpp
#define Pawn_hpp

#include <stdio.h>
#include "Piece.hpp"

class Pawn : public Piece {
private:
    void get_forward_moves(std::vector<Point> point_list);
    void get_capture_moves(std::vector<Point> point_list);
public:
    
    Pawn(int x_position, int y_position, bool is_white, Piece **board);
    
    virtual ~Pawn();
    
    void get_possible_move_list(std::vector<Point> point_list);
    void get_controlled_squares(std::vector<Point> point_list);
};

#endif /* Pawn_hpp */
