
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


