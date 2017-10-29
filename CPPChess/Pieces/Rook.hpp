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
private:
    bool has_moved;
    
public:
    Rook(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board);
    
    virtual ~Rook();
    
    bool did_move();
    
    void get_possible_move_list(std::vector<Point>& point_list);
    void get_controlled_squares(std::vector<Point>& point_list, std::vector<std::vector<Piece*> >& temp_board);
    bool validate_move(int x, int y);
    char get_abbreviation();
};

#endif /* Rook_hpp */
