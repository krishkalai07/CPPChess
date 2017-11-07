//
//  Attack.cpp
//  CPPChess
//
//  Created by Krish Kalai on 10/29/17.
//  Copyright © 2017 krishkalai07. All rights reserved.
//

#include "Attack.hpp"

void attack_per_direction (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, int delta_x, int delta_y, bool check_for_same_color) {
    for (int target_x = from_x + delta_x, target_y = from_y + delta_y; target_x >= 0 && target_x < 8 && target_y >= 0 && target_y < 8; target_x += delta_x, target_y += delta_y) {
        if (board[target_x][target_y] == NULL) {
            // Square is empty, undconditionally push it
            point_list.push_back(Point(target_x, target_y));
        }
        else {
            if (check_for_same_color || board[target_x][target_y]->is_white() != board[target_x][target_y]->is_white()) {
                // Square has a piece on it, add it conditionally.
                point_list.push_back(Point(target_x, target_y));
            }
            break;
        }
    }
}

void queen_attack (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, int delta_x, int delta_y, bool check_for_same_color) {
    bishop_attack(board, point_list, from_x, from_y, check_for_same_color);
    rook_attack(board, point_list, from_x, from_y, check_for_same_color);
}

void rook_attack (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, bool check_for_same_color) {
    attack_per_direction(board, point_list, from_x, from_y, 0, 1, check_for_same_color);
    attack_per_direction(board, point_list, from_x, from_y, 1, 0, check_for_same_color);
    attack_per_direction(board, point_list, from_x, from_y, -1, 0, check_for_same_color);
    attack_per_direction(board, point_list, from_x, from_y, 0, -1, check_for_same_color);
}

void bishop_attack (std::vector<std::vector<Piece *> >& board, std::vector<Point>& point_list, int from_x, int from_y, bool check_for_same_color) {
    attack_per_direction(board, point_list, from_x, from_y, -1, -1, check_for_same_color);
    attack_per_direction(board, point_list, from_x, from_y, -1, 1, check_for_same_color);
    attack_per_direction(board, point_list, from_x, from_y, 1, -1, check_for_same_color);
    attack_per_direction(board, point_list, from_x, from_y, 1, 1, check_for_same_color);
}
