//
//  Evaluate.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/29/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Evaluate.hpp"

int get_material_advantage (std::vector<std::vector <Piece *> >& board) {
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

int get_pawn_placement_advantage (std::vector<std::vector <Piece *> >& board) {
    int white_pawn_advantage = 0;
    int black_pawn_advantage = 0;
    
    return white_pawn_advantage - black_pawn_advantage;
}

int get_isolated_pawns (std::vector<std::vector <Piece *> >& board, bool color) {
    int pawn_count = 0;
    
    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != NULL && dynamic_cast<Pawn *>(board[i][j]) != NULL && board[i][j]->isWhite() == color) {
                if (i != 0 && i != 7) {
                    if (pawns_in_file(board, i - 1, color) == 0 && pawns_in_file(board, i + 1, color) == 0) {
                        pawn_count += 1;
                        i++;
                        break;
                    }
                }
                else if (i != 0) {
                    if (pawns_in_file(board, i - 1, color) == 0) {
                        pawn_count += 1;
                        i++;
                        break;
                    }
                }
                else {
                    if (pawns_in_file(board, i + 1, color) == 0) {
                        pawn_count += 1;
                        i++;
                        break;
                    }
                }
            }
        }
    }
    
    return pawn_count;
}

int pawns_in_file(std::vector<std::vector <Piece *> >& board, int file, bool color) {
    int count = 0;
    
    for (int i = 1; i < 7; i++) {
        if (board[file][i] != NULL && board[file][i]->isWhite() == color && dynamic_cast<Pawn *>(board[file][i]) != NULL) {
            count++;
        }
    }
    
    return count;
}

int get_doubled_pawns (std::vector<std::vector <Piece *> >& board, bool color) {
    int files_with_doubled_pawns = 0;
    
    for (int i = 0; i < 8; i++) {
        files_with_doubled_pawns++;
    }
    
    return files_with_doubled_pawns;
}

int get_backward_pawns (std::vector<std::vector <Piece *> >& board, bool color) {
    
    return 0;
}

int get_phlanax (std::vector<std::vector <Piece *> > board, bool color) {
    
    return 0;
}

int get_mobility_advantage (std::vector<std::vector <Piece *> >& baord) {
    int white_mobility_advantage = 0;
    int black_mobility_advantage = 0;
    
    return white_mobility_advantage - black_mobility_advantage;
}


