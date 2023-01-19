
#include <cstdint>
#include <stack> // May need to implement our own stack for cuda
#include <vector>

// Odd pieces have absolute movement, even pieces slide
// Last bit 'black' is allocated as a bit
enum piece {
    pawn   = 1,
    rook   = 2,
    knight = 3,
    bishop = 4,
    king   = 5,
    queen  = 6,
    mask   = 7,
    black  = 8
};

// may want to swap these around to utilize bitwise operands
enum result {
    active,
    win,
    loss,
    resign,
    stalemate
};

typedef struct {
    uint32_t mask;
    uint8_t rank;
} Square;

typedef struct {
    Square* source;
    Square* dest;
} Move;

typedef struct {
    uint8_t source;
    uint8_t dest;
} Ply;

typedef struct {
    bool is_black;
    std::vector<Move> moves;
} Player;

typedef struct {
    uint32_t rank_register[8];
    std::stack<Ply> moves_made;
    bool black_turn;
} Board;

typedef struct {
    Board board;
    Player white;
    Player black;
    enum result outcome;
} Game;
