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
    bool moved_two_spaces_last_move;
    
    void get_forward_moves(std::vector<Point>& point_list);
    void get_capture_moves(std::vector<Point>& point_list);
public:
    
    Pawn(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board);
    
    ~Pawn();
    
    bool did_move_two_spaces_last_move ();
    void get_possible_move_list(std::vector<Point>& point_list);
    void get_controlled_squares(std::vector<Point>& point_list);
    
    void set_move_two_spaces (bool did_move);
    
    bool validate_move(int x, int y);
};

#endif /* Pawn_hpp */
