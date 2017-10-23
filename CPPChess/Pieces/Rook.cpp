//
//  Rook.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Rook.hpp"

Rook::Rook(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, board) {
    std::cout << "Rook constructor" << std::endl;
}

Rook::~Rook() {
    std::cout << "Rook destructor" << std::endl;
}

void Rook::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Rook::get_controlled_squares(std::vector<Point>& point_list) {
    
}
