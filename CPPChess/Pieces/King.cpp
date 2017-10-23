//
//  King.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/22/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "King.hpp"

King::King(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board):Piece(x_position, y_position, is_white, board) {
    std::cout << "King constructor" << std::endl;
}

King::~King() {
    std::cout << "King destructor" << std::endl;
}

void King::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void King::get_controlled_squares(std::vector<Point>& point_list) {
    
}
