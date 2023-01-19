
#include "game.h"

Board init_board() {
    Board game_board;
    game_board.rank_register[0] = 0x23456432;
    game_board.rank_register[1] = 0x11111111;
    game_board.rank_register[2] = 0x00000000;
    game_board.rank_register[3] = 0x00000000;
    game_board.rank_register[4] = 0x00000000;
    game_board.rank_register[5] = 0x00000000;
    game_board.rank_register[6] = 0x99999999;
    game_board.rank_register[7] = 0xABCDECBA;
    game_board.black_turn = 0;
    return game_board;
}

uint8_t left_slide(Player& agent, Square* spot) {
    uint8_t length = 0;
    bool search = 1;
    Square final_destination;
    while search {
    } if (length) {
        SlideMove move = 
    return length;
}

uint8_t square_slide(Player& agent, Square* spot) {
    uint8_t valid_moves = 0;
    uint8_t length = 0;

    // Scan around the spot to determine valid lengths
    // If you find valid (non-zero length) moves pop onto move list
    return valid_moves;
}

