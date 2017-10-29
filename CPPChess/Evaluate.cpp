//
//  Evaluate.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/29/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Evaluate.hpp"

int get_material_advantage (std::vector<std::vector <Piece *> > board) {
    int white_material = 0;
    int black_material = 0;
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != NULL) {
                if (board[i][j]->isWhite()) {
                    white_material += board[i][j]->get_material_value();
                }
                else {
                    black_material += board[i][j]->get_material_value();
                }
            }
        }
    }
    
    return white_material - black_material;
}

int get_pawn_placement_advantage (std::vector<std::vector <Piece *> > board) {
    int white_pawn_advantage = 0;
    int black_pawn_advantage = 0;
    
    return white_pawn_advantage - black_pawn_advantage;
}

int get_mobility_advantage (std::vector<std::vector <Piece *> > baord) {
    int white_mobility_advantage = 0;
    int black_mobility_advantage = 0;
    
    return white_mobility_advantage - black_mobility_advantage;
}
