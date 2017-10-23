//
//  Piece.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Piece.hpp"

Piece::Piece (int x_position, int y_position, bool is_white, Piece** board) {
    this->x_position = x_position;
    this->y_position = y_position;
    this->color = is_white;
    this->board = board;
}

Piece::Piece (Piece& piece): Piece(piece.x_position, piece.y_position, piece.color, piece.board) {
//    this->x_position = piece.x_position;
//    this->y_position = piece.y_position;
//    this->color = piece.color;
//    this->board = piece.board;
}

Piece::~Piece() {
    std::cout << "Piece Destructor" << std::endl;
}

int Piece::get_x_position() {
    return x_position;
}
int Piece::get_y_position() {
    return y_position;
}

bool Piece::isWhite() {
    return color;
}

void Piece::set_x_position(int x) {
    this->x_position = x;
}

void Piece::set_y_position(int y) {
    this->y_position = y;
}
