//
//  Piece.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "Point.hpp"

class Piece {
protected:
    int x_position;
    int y_position;
    bool color;
    
    Piece **board;

public:
    Piece (int x_position, int y_poisition, bool is_white, Piece** board);
    Piece (Piece& piece);
    virtual ~Piece();
    
    int get_x_position();
    int get_y_position();
    bool isWhite();
    
    void set_x_position(int x_position);
    void set_y_position(int y_position);
    
    virtual void get_possible_move_list(std::vector<Point> point_list) = 0;
    virtual void get_controlled_squares(std::vector<Point> point_list) = 0;
    
    void list_possible_moves(std::vector<Point>& point_list);
};

#endif /* Piece_hpp */