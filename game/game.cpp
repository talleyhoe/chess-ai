
#include "game.h"

Player init_player(bool is_black) {
    Player magnus = { .is_black = false };
    return magnus;
}

void gen_moves(Player& player) {
}

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

Game start_game() {
    Game new_game = {
        .board = init_board(),
        .white = init_player(0),
        .black = init_player(1),
        .outcome = active
    };
    return new_game;
}

// Turn layout
//  generate (new) moves
//  
