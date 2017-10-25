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
#include "Rook.hpp"
#include "Piece.hpp"

class King: public Piece {
private:
    std::vector<Point> control_squares;
    bool has_moved;
    
    bool vector_contains_point(std::vector<Point>& point_list, int x, int y);
    bool is_in_check ();
    void get_normal_moves (std::vector<Point>& point_list);
    void get_castle_moves (std::vector<Point>& point_list);
public:
    King(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board, std::vector<Point>& control_squares);
    
    virtual ~King();
    
    bool did_move();
    
    void get_possible_move_list (std::vector<Point>& point_list);
    void get_controlled_squares (std::vector<Point>& point_list);
    bool validate_move (int x, int y);
    char get_abbreviation();
};

#endif /* King_hpp */
