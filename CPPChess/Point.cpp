//
//  Point.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Point.hpp"

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::~Point(){
    
}

bool Point::operator==(Point &point) {
    return this->x == point.x && this->y == point.y;
}

std::ostream& operator<<(std::ostream& os, Point &p) {
    os << "(" << p.x << " " << p.y << ")";
    return os;
}
