
#include "pieces.h"

const uint32_t PAWN   = 1;
const uint32_t ROOK   = 2;
const uint32_t KNIGHT = 3;
const uint32_t BISHOP = 4;
const uint32_t QUEEN  = 5;
const uint32_t KING   = 6;
const uint32_t DUMMY  = 7;
const uint32_t BLACK  = 8; // The bit

// The hex board will be little endianness
class Board
{
public:
    Board() {                          //  DUMMY
        rank_register[0] = 0x23456432; // Castling white
		rank_register[1] = 0x11111111;
		rank_register[2] = 0x00000000; // En passant capture
		rank_register[3] = 0x00000000;
		rank_register[4] = 0x00000000;
		rank_register[5] = 0x00000000; // En passant capture
		rank_register[6] = 0x99999999;
		rank_register[7] = 0xABCDECBA; // Castling black
    }

    void move(uint8_t vector) {
    }

private:
    uint32_t rank_register[8]; // 32B (8 * 4)
    uint64_t white_pieces;     //  8B
    uint64_t black_pieces;     //  8B
    
};

// We want fast moves for our search, but game history should be a-smol-a-p
// So there can be two discriptors
struct Move {
    uint8_t source;    // 6 bits
    uint8_t length;    // 3 bits
    uint8_t direction; // 3 bits
};


// We have a hex board, now we need to generate a list of moves
// Each piece can have up to 8 moves with maximum (/pin) lenth of 7
//   Direction = 3 bits
//   Length = 3 bits

