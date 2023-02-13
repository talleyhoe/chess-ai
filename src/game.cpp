
#include <cstdint>
#include <stdint.h>


// I'm stealing a lot of code from Daniel Inführ. Checkout his engine Gigantua
#ifdef _MSC_VER
#define _ASSUME(cond) __assume(cond)
#define _Compiletime __forceinline static constexpr
#define _NoInline __declspec(noinline)
#define _Inline inline
#define _ForceInline __forceinline
#define Bitcount(X) __popcnt64(X)
#elif defined(__clang__)
#define _ASSUME(cond) ((cond) ? static_cast<void>(0) : __builtin_unreachable())
#define _Compiletime __attribute__((always_inline)) static constexpr
#define _NoInline __attribute__((noinline))
#define _Inline inline 
#define _ForceInline __attribute__((always_inline))
#define Bitcount(X) static_cast<uint64_t>(__builtin_popcountll(X))
#elif defined(__GNUC__)
#define _ASSUME(cond) ((cond) ? static_cast<void>(0) : __builtin_unreachable())
#define _Compiletime __attribute__((always_inline)) static constexpr
#define _NoInline __attribute__ ((noinline))
#define _Inline inline
#define _ForceInline __attribute__((always_inline)) inline
#define Bitcount(X) static_cast<uint64_t>(__builtin_popcountll(X))
#else
#define _ASSUME(cond) static_cast<void>(!!(cond))
#define _Compiletime static constexpr
#define _Inline inline 
#endif

typedef uint64_t map;

enum class Direction : int_fast8_t {
    NORTH =  8,
    EAST  = -1,
    SOUTH = -8, 
    WEST  =  1,

    NORTH_EAST = NORTH + EAST,
    NORTH_WEST = NORTH + WEST,
    SOUTH_EAST = SOUTH + EAST,
    SOUTH_WEST = SOUTH + WEST,
};

enum class Rank : map {
    R1 = 0x00000000000000FFull,
    R2 = 0x000000000000FF00ull,
    R3 = 0x0000000000FF0000ull,
    R4 = 0x00000000FF000000ull,
    R5 = 0x000000FF00000000ull,
    R6 = 0x0000FF0000000000ull,
    R7 = 0x00FF000000000000ull,
    R8 = 0xFF00000000000000ull
};

enum class File : map {
    FA = 0x0101010101010101ull,
    FB = 0x0202020202020202ull,
    FC = 0x0404040404040404ull,
    FD = 0x0808080808080808ull,
    FE = 0x1010101010101010ull,
    FF = 0x2020202020202020ull,
    FG = 0x4040404040404040ull,
    FH = 0x8080808080808080ull
};
    

// Pieces only have position and color;
class PieceSet {
    public:
        uint64_t position;
        bool white;
};

// Specific pieces have move sets
class Knight: public PieceSet {
    constexpr map MoveNNE(map move_mask) {
        map offsides_mask = ~(Rank::R8 | Rank::R7 | File::FA);
        map legal_knights = (this->position & offsides_mask);

        return legal_knights << (Direction


    // Move mask captures the effect of pins and enemy_or_empty
    template <Direction white>
    constexpr map GenMoves(map move_mask) {
        return 0ull;
    }
};

// A board knows all pieces and checkmasks
class Board {
    public:
        const map black_pawns;
        const map black_knights;
        const map black_bishops;
        const map black_rooks;
        const map black_queen;
        const map black_king;

        const map white_pawns;
        const map white_knights;
        const map white_bishops;
        const map white_rooks;
        const map white_queen;
        const map white_king;

        const map black_pieces;
        const map white_pieces;
        const map all_pieces;

    constexpr Board(
        map bp, map bn, map bb, map br, map bq, map bk,
        map wp, map wn, map wb, map wr, map wq, map wk) :
            black_pawns(bp), black_knights(bn), black_bishops(bb),
            black_rooks(br), black_queen(bq), black_king(bk),

            white_pawns(bp), white_knights(bn), white_bishops(bb),
            white_rooks(br), white_queen(bq), white_king(bk),

            black_pieces( bp | bn | bb | br | bq | bk ),
            white_pieces( wp | wn | wb | wr | wq | wk ),
            all_pieces( black_pieces | white_pieces )
            {}
    
    template <bool is_white>
    constexpr map enemy_or_empty() {
        if (is_white) { return ~(this->white_pieces); }
        else          { return ~(this->black_pieces); }
    }
};

