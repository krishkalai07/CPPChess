//
//  Knight.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Knight.hpp"

Knight::Knight(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, board) {
    std::cout << "Knight constructor" << std::endl;
}

Knight::~Knight() {
    std::cout << "Knight destructor" << std::endl;
}

void Knight::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Knight::get_controlled_squares(std::vector<Point>& point_list) {
    
}
