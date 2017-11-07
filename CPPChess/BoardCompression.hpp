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
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"

const int BOARD_SIZE = 8;

std::string compress_board (std::vector<std::vector<Piece *> >& board);
std::string get_full_FEN (std::vector<std::vector<Piece *> >& board, bool turn, int halfmove_counter, int move_number);
void decompress_board (std::vector<std::vector<Piece *> >& board, std::string FEN, King *&white_king, King *&black_king, std::vector<Point>& white_control, std::vector<Point>& black_control, bool &turn, int &move_number, int &halfmove_counter);
void add_piece (std::vector<std::vector<Piece *> >& board, char abbreviation, int x, int y, std::vector<Point>& white_control, std::vector<Point>& black_control);
std::string get_piece_placement (std::vector<std::vector<Piece *> >& board);
std::string get_castling_rights (std::vector<std::vector<Piece *> >& board);
std::string get_en_passant_rights (std::vector<std::vector<Piece *> >& board);
std::string index_to_algebraic(int x, int y);

std::vector<std::string> split (std::string src);

#endif /* BoardCompression_hpp */
