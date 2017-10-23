//
//  main.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include <iostream>
#include <iomanip>

int main(int argc, const char * argv[]) {
    // insert code here...
    const int count = 10;
    int **limits = new int*[count];
    
    for (int i = 0; i < count; i++) {
        limits[i] = new int[count];
        for (int j = 0; j < count; j++) {
            limits[i][j] = (i+1)*(j+1);
        }
    }
    
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            std::cout << std::setw(3) << std::left << limits[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            std::cout << std::setw(3) << std::right << *(*(limits+j)+i);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    return 0;
}

