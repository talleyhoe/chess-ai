
#include <stack> // May need to implement our own stack for cuda

#include "pieces.h"

// Odd pieces have absolute movement, even pieces slide
// Last bit 'black' is allocated as a bit
enum pieces {
    pawn   = 1,
    rook   = 2,
    knight = 3,
    bishop = 4,
    king   = 5,
    queen  = 6,
    mask   = 7,
    black  = 8
};

typedef struct {
    uint32_t mask;
    uint8_t rank;
} Square;

typedef struct {
    int8_t h_offset;
    int8_t v_offset;
    Square* source;
} PlaceMove;

typedef struct {
    int8_t direction;
    uint8_t max_len;
    Square* source;
} SlideMove;

struct Player {
    bool is_black;
    PlaceMove p_moves[48];
    SlideMove s_moves[16];
};

typedef struct {
    int8_t source;
    int8_t dest;
} Ply;

typedef struct {
    uint32_t rank_register[8];
    std::stack<Ply> moves_made;
} Board;

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
    return game_board;
}

