//
//  Piece.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Piece.hpp"

Piece::Piece (int x_position, int y_position, bool is_white, int material_value, std::vector<std::vector<Piece *> >& board): board(board) {
    this->x_position = x_position;
    this->y_position = y_position;
    this->color = is_white;
    this->material_value = material_value;
}

Piece::~Piece() {
    
}

int Piece::get_x_position() {
    return x_position;
}
int Piece::get_y_position() {
    return y_position;
}

int Piece::get_material_value() {
    return material_value;
}

bool Piece::is_white() {
    return color;
}

void Piece::set_x_position(int x) {
    this->x_position = x;
}

void Piece::set_y_position(int y) {
    this->y_position = y;
}

void Piece::get_controlled_squares(std::vector<Point>& point_list) {
    get_controlled_squares(point_list, board);
}
