//
//  Queen.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Queen.hpp"

Queen::Queen(int x_position, int y_position, bool is_white, Piece ***board):Piece(x_position, y_position, is_white, board) {
    std::cout << "Queen constructor" << std::endl;
}

Queen::~Queen() {
    std::cout << "Queen destructor" << std::endl;
}

void Queen::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Queen::get_controlled_squares(std::vector<Point>& point_list) {
    
}
