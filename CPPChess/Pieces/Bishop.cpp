//
//  Bishop.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Bishop.hpp"

Bishop::Bishop(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, board) {
    std::cout << "Bishop constructor" << std::endl;
}

Bishop::~Bishop() {
    std::cout << "Bishop destructor" << std::endl;
}

void Bishop::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Bishop::get_controlled_squares(std::vector<Point>& point_list) {
    
}
