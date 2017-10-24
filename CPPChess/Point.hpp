//
//  Point.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>
#include <iostream>

class Point {
public:
    int x;
    int y;
    
    Point (int,int);
//    Point (Point&);
    ~Point();
    
    bool operator==(Point &point);
    friend std::ostream& operator<<(std::ostream&, Point&);
};

#endif /* Point_hpp */
