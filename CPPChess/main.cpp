//
//  main.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/21/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

int main(int argc, const char * argv[]) {
    Piece ***board = new Piece**[8];
    for (int i = 0; i < 8; i++) {
        board[i] = new Piece*[8];
        for (int j = 0; j < 8; j++) {
            board[i][j] = NULL;
        }
    }
    
    Pawn p(0, 0, false, board);
    Knight n(0, 0, false, board);
    Bishop b(0, 0, false, board);
    Rook r(0, 0, false, board);
    Queen q(0, 0, false, board);
    King k(0, 0, false, board);
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete board[i][j];
        }
    }
    delete [] board;
    
//    const int count = 10;
//    int **limits = new int*[count];
//    
//    for (int i = 0; i < count; i++) {
//        limits[i] = new int[count];
//        for (int j = 0; j < count; j++) {
//            limits[i][j] = (i+1)*(j+1);
//        }
//    }
//    
//    for (int i = 0; i < count; i++) {
//        for (int j = 0; j < count; j++) {
//            std::cout << std::setw(3) << std::left << limits[i][j];
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//    
//    for (int i = 0; i < count; i++) {
//        for (int j = 0; j < count; j++) {
//            std::cout << std::setw(3) << std::right << *(*(limits+j)+i);
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
    
    return 0;
}

