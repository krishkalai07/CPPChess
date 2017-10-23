//
//  Pawn.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Pawn.hpp"

Pawn::Pawn(int x_position, int y_position, bool is_white, std::vector<std::vector<Piece *> >& board): Piece(x_position, y_position, is_white, board) {
    std::cout << "Pawn constructor" << std::endl;
}

Pawn::~Pawn() {
    std::cout << "Pawn destructor" << std::endl;
}

void Pawn::get_possible_move_list(std::vector<Point>& point_list) {
    
}

void Pawn::get_controlled_squares(std::vector<Point>& point_list) {
    
}

void Pawn::get_forward_moves(std::vector<Point>& point_list) {
    
}

void Pawn::get_capture_moves(std::vector<Point>& point_list) {
    
}

