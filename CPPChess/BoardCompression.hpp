//
//  BoardCompression.hpp
//  CPPChess
//
//  Created by Krish Kalai on 10/28/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#ifndef BoardCompression_hpp
#define BoardCompression_hpp

#include "Piece.hpp"
#include <vector>

const int BOARD_SIZE = 8;

std::string compress_board (std::vector<std::vector<Piece *> >& board);
std::string get_full_FEN (std::vector<std::vector<Piece *> >& board, bool turn, int halfmove_counter, int move_number);
std::string get_piece_placement (std::vector<std::vector<Piece *> >& board);
std::string get_castling_rights (std::vector<std::vector<Piece *> >& board);
std::string get_en_passant_rights (std::vector<std::vector<Piece *> >& board);
std::string index_to_algebraic(int x, int y);

#endif /* BoardCompression_hpp */
