
#include <cstdint>
#include <stdint.h>

typedef uint64_t map;

enum Color : bool {
    BLACK = 0,
    WHITE = 1,
};

enum Direction : int_fast8_t {
    NORTH =  8,
    EAST  =  1,
    SOUTH = -8, 
    WEST  = -1,

    NORTH_EAST = NORTH + EAST,
    NORTH_WEST = NORTH + WEST,
    SOUTH_EAST = SOUTH + EAST,
    SOUTH_WEST = SOUTH + WEST,
};

enum Rank : map {
    R1 = 0x00000000000000FFull,
    R2 = 0x000000000000FF00ull,
    R3 = 0x0000000000FF0000ull,
    R4 = 0x00000000FF000000ull,
    R5 = 0x000000FF00000000ull,
    R6 = 0x0000FF0000000000ull,
    R7 = 0x00FF000000000000ull,
    R8 = 0xFF00000000000000ull
};

enum File : map {
    FA = 0x0101010101010101ull,
    FB = 0x0202020202020202ull,
    FC = 0x0404040404040404ull,
    FD = 0x0808080808080808ull,
    FE = 0x1010101010101010ull,
    FF = 0x2020202020202020ull,
    FG = 0x4040404040404040ull,
    FH = 0x8080808080808080ull
};

template <Direction D>
constexpr int_fast8_t BitwiseAbs() {
    int_fast8_t positive_dir = D >> 7;
    positive_dir ^= (D + positive_dir); 
    return positive_dir;
}


template <Direction D>
constexpr map ShiftBoard(map bitboard, uint_fast8_t length = 1) {
    if (D < 0) { return bitboard >> ( BitwiseAbs<D>() * length ); }
    else       { return bitboard << ( BitwiseAbs<D>() * length ); }
}

// Pieces only have position and color;
class PieceSet {
    public:
        map position;
        bool white;

        constexpr PieceSet(map pos, bool is_white) :
            position(pos), white(is_white)
        {}
};

// Specific pieces have move sets
    // Move mask captures the effect of pins and enemy_or_empty

// NOTE: I think I only need the E/W offsides_masks, but N/S should overflow
// Move mask captures the effect of pins and enemy_or_empty

class CardinalSlider {
    public:
        constexpr map MoveS(map empty) {
            map mask = this->position;
            mask |= empty & ShiftBoard<SOUTH>(mask, 1);
            empty &= ShiftBoard<SOUTH>(empty, 1);
            mask |= empty & ShiftBoard<SOUTH>(mask, 2);
            empty &= ShiftBoard<SOUTH>(empty, 2);
            mask |= empty & ShiftBoard<SOUTH>(mask, 4);
            return mask;
        }

        constexpr map MoveN(map empty) {
            map mask = this->position;
            mask |= empty & ShiftBoard<NORTH>(mask, 1);
            empty &= ShiftBoard<NORTH>(empty, 1);
            mask |= empty & ShiftBoard<NORTH>(mask, 2);
            empty &= ShiftBoard<NORTH>(empty, 2);
            mask |= empty & ShiftBoard<NORTH>(mask, 4);
            return mask;
        }

        constexpr map MoveE(map empty) {
            map mask = this->position;
            empty &= ~(File::FA);
            mask |= empty & ShiftBoard<EAST>(mask, 1);
            empty &= ShiftBoard<EAST>(empty,1);
            mask |= empty & ShiftBoard<EAST>(mask, 2);
            empty &= ShiftBoard<EAST>(empty,2);
            mask |= empty & ShiftBoard<EAST>(mask, 4);
            return mask;
        }

        constexpr map MoveW(map empty) {
            map mask = this->position;
            empty &= ~(File::FH);
            mask |= empty & ShiftBoard<EAST>(mask, 1);
            empty &= ShiftBoard<EAST>(empty,1);
            mask |= empty & ShiftBoard<EAST>(mask, 2);
            empty &= ShiftBoard<EAST>(empty,2);
            mask |= empty & ShiftBoard<EAST>(mask, 4);
            return mask;
        }
};

class OrdinalSlider {
    public:
        constexpr map MoveSE(map empty) {
            map mask = this->position;
            empty &= ~(File::FA);
            mask |= empty & ShiftBoard<SOUTH_EAST>(mask, 1);
            empty &= ShiftBoard<SOUTH_EAST>(empty,1);
            mask |= empty & ShiftBoard<SOUTH_EAST>(mask, 2);
            empty &= ShiftBoard<SOUTH_EAST>(empty,2);
            mask |= empty & ShiftBoard<SOUTH_EAST>(mask, 4);
            return mask;
        }

        constexpr map MoveSW(map empty) {
            map mask = this->position;
            empty &= ~(File::FH);
            mask |= empty & ShiftBoard<SOUTH_WEST>(mask, 1);
            empty &= ShiftBoard<SOUTH_WEST>(empty,1);
            mask |= empty & ShiftBoard<SOUTH_WEST>(mask, 2);
            empty &= ShiftBoard<SOUTH_WEST>(empty,2);
            mask |= empty & ShiftBoard<SOUTH_WEST>(mask, 4);
            return mask;
        }

        constexpr map MoveNE(map empty) {
            map mask = this->position;
            empty &= ~(File::FA);
            mask |= empty & ShiftBoard<NORTH_EAST>(mask, 1);
            empty &= ShiftBoard<NORTH_EAST>(empty,1);
            mask |= empty & ShiftBoard<NORTH_EAST>(mask, 2);
            empty &= ShiftBoard<NORTH_EAST>(empty,2);
            mask |= empty & ShiftBoard<NORTH_EAST>(mask, 4);
            return mask;
        }

        constexpr map MoveNW(map empty) {
            map mask = this->position;
            empty &= ~(File::FH);
            mask |= empty & ShiftBoard<NORTH_WEST>(mask, 1);
            empty &= ShiftBoard<NORTH_WEST>(empty,1);
            mask |= empty & ShiftBoard<NORTH_WEST>(mask, 2);
            empty &= ShiftBoard<NORTH_WEST>(empty,2);
            mask |= empty & ShiftBoard<NORTH_WEST>(mask, 4);
            return mask;
        }
};

class Rook : public PieceSet, public CardinalSlider {
    public:
        constexpr Rook(map pos, bool white) : PieceSet(pos, white)
        {}

        template<bool white>
        constexpr Rook() {
            if constexpr (white) { PieceSet(0x0000000000000081ull, white); }
            else                 { PieceSet(0x8100000000000000ull, white); }
        }

        constexpr map GenMoves(map& move_mask, map& empty) {
            map legal_moves = ( MoveE(empty) | MoveW(empty) |
                                MoveN(empty) | MoveS(empty) );
            legal_moves &= move_mask;
            return legal_moves;
        }
};

class Bishop : public PieceSet, public OrdinalSlider {
    public:
        constexpr Bishop(map pos, bool white) : PieceSet(pos, white)
        {}

        constexpr map GenMoves(map& move_mask, map& empty) {
            map legal_moves = ( MoveNE(empty) | MoveNW(empty) |
                                MoveSE(empty) | MoveSW(empty) );
            legal_moves &= move_mask;
            return legal_moves;
        }
};

class Queen : public PieceSet, public CardinalSlider, public OrdinalSlider {
    public:
        constexpr Queen(map pos, bool white) : PieceSet(pos, white)
        {}

        constexpr map GenMoves(map& move_mask, map& empty) {
            map legal_moves = ( MoveNW(empty) | MoveNE(empty) |
                                MoveSW(empty) | MoveSE(empty) |
                                MoveN(empty)  | MoveS(empty)  |
                                MoveE(empty)  | MoveW(empty)  );
            legal_moves &= move_mask;
            return legal_moves;
        }
};

// Knights and Kings should really use a lookup table w/ index
class Knight: public PieceSet {
    public:
        constexpr Knight(map pos, bool white) : PieceSet(pos, white)
        {}

        constexpr map MoveNNE(map empty) {
            map offsides_mask = ~(File::FA);
            map legal_knights = (this->position & offsides_mask);
            uint_fast8_t offset = (2 * Direction::NORTH) + Direction::EAST;
            return (legal_knights << offset) & empty;
        }

        constexpr map MoveNNW(map empty) {
            map offsides_mask = ~(File::FH);
            map legal_knights = (this->position & offsides_mask);
            uint_fast8_t offset = (2 * Direction::NORTH) + Direction::WEST;
            return (legal_knights << offset) & empty;
        }

        constexpr map MoveNEE(map empty) {
            map offsides_mask = ~(File::FA | File::FB);
            map legal_knights = (this->position & offsides_mask);
            uint_fast8_t offset = Direction::NORTH + (2 * Direction::EAST);
            return (legal_knights << offset) & empty;
        }

        constexpr map MoveNWW(map empty) {
            map offsides_mask = ~(File::FG | File::FH);
            map legal_knights = (this->position & offsides_mask);
            uint_fast8_t offset = Direction::NORTH + (2 * Direction::WEST);
            return (legal_knights << offset) & empty;
        }

        constexpr map MoveSSE(map empty) {
            map offsides_mask = ~(File::FA);
            map legal_knights = (this->position & offsides_mask);
            uint_fast8_t offset = (2 * Direction::SOUTH) + Direction::EAST;
            return (legal_knights >> offset) & empty;
        }

        constexpr map MoveSSW(map empty) {
            map offsides_mask = ~(File::FH);
            map legal_knights = (this->position & offsides_mask);
            uint_fast8_t offset = (2 * Direction::SOUTH) + Direction::WEST;
            return (legal_knights >> offset) & empty;
        }

        constexpr map MoveSEE(map empty) {
            map offsides_mask = ~(File::FA | File::FB);
            map legal_knights = (this->position & offsides_mask);
            uint_fast8_t offset = Direction::SOUTH + (2 * Direction::EAST);
            return (legal_knights >> offset) & empty;
        }

        constexpr map MoveSWW(map empty) {
            map offsides_mask = ~(File::FG | File::FH);
            map legal_knights = (this->position & offsides_mask);
            uint_fast8_t offset = Direction::SOUTH + (2 * Direction::WEST);
            return (legal_knights >> offset) & empty;
        }

        constexpr map GenMoves(map move_mask, map empty) {
            map legal_moves = ( MoveNNE(empty) | MoveNNW(empty) | 
                                MoveNEE(empty) | MoveNWW(empty) |
                                MoveSSE(empty) | MoveSSW(empty) |
                                MoveSEE(empty) | MoveSWW(empty) );
            legal_moves &= move_mask;
            return legal_moves;
        }
};

class Pawn : public PieceSet {
    bool unmoved_pieces = true;
    map  en_passant = 0;

    public:
        template <bool white>
        consteval map InitialRank() {
            if constexpr (white) { return Rank::R2; }
            else                 { return Rank::R7; }
        }

        constexpr Pawn(map pos, bool is_white, bool unmoved_pawns) :
            PieceSet(pos, is_white), 
            unmoved_pieces(unmoved_pawns)
        {}

        template <bool is_white>
        constexpr Pawn(map pos) :
            PieceSet(pos, is_white), 
            unmoved_pieces(InitialRank<is_white>() & pos)
        {}

        template<bool white>
        constexpr Pawn() : 
            PieceSet(InitialRank<white>(), white), 
            unmoved_pieces(true)
        {}

        template <bool white>
        constexpr map MoveSingle(map empty) {
            map mask = this->position;
            if constexpr (white) { return empty & ShiftBoard<NORTH>(mask, 1); }
            else                 { return empty & ShiftBoard<SOUTH>(mask, 1); }
        }

        template <bool white>
        constexpr map MoveDouble(map empty) {
            map unmoved_pawns = this->position & InitialRank<white>();
            if constexpr (white) {
                return empty & ShiftBoard<NORTH>(unmoved_pawns, 2); 
            } else {
                return empty & ShiftBoard<SOUTH>(unmoved_pawns, 2);
            }
        }

        template <bool white>
        constexpr map MoveAttack(map enemy) {
            enemy &= this->en_passant;
            map attacks;
            if constexpr (white) {
                attacks  = ShiftBoard<NORTH_EAST>(this->position, 1);
                attacks |= ShiftBoard<NORTH_WEST>(this->position, 1);
            } else {
                attacks  = ShiftBoard<SOUTH_EAST>(this->position, 1);
                attacks |= ShiftBoard<SOUTH_WEST>(this->position, 1);
            } return enemy & attacks;
        }

        template <bool white, bool unmoved_pawns>
        constexpr map GenMoves(map empty, map enemy) {
            map mask = ( MoveSingle<white>(empty) | 
                         MoveAttack<white>(enemy) );
            if constexpr (unmoved_pawns) {
                mask |= MoveDouble<white>(empty);
            }
            return mask;
        }
};

class King : public PieceSet {
    public:
        constexpr King(map pos, bool white) : PieceSet(pos, white)
        {}

        constexpr map GenMoves(map move_mask) {
            map legal_moves = ( ShiftBoard<NORTH_WEST>(this->position, 1) |
                                ShiftBoard<NORTH_EAST>(this->position, 1) |
                                ShiftBoard<SOUTH_EAST>(this->position, 1) |
                                ShiftBoard<SOUTH_WEST>(this->position, 1) |
                                ShiftBoard<NORTH>     (this->position, 1) |
                                ShiftBoard<SOUTH>     (this->position, 1) |
                                ShiftBoard<EAST>      (this->position, 1) |
                                ShiftBoard<WEST>      (this->position, 1) );
            return move_mask & legal_moves;
        }
};

// Helps us prune move generation to only relevent piece sets
class BoardState {
    public:
        bool white_turn;
        
        const bool black_pawns;
        const bool black_knights;
        const bool black_bishops;
        const bool black_rooks;
        const bool black_queen;
        const bool black_king;

        const bool white_pawns;
        const bool white_knights;
        const bool white_bishops;
        const bool white_rooks;
        const bool white_queen;
        const bool white_king;

        uint_fast32_t ply_count;
};

// A board knows all pieces and checkmasks
class Board {
    public:
        const Pawn   black_pawns;
        const Knight black_knights;
        const Bishop black_bishops;
        const Rook   black_rooks;
        const Queen  black_queen;
        const King   black_king;

        const Pawn   white_pawns;
        const Knight white_knights;
        const Bishop white_bishops;
        const Rook   white_rooks;
        const Queen  white_queen;
        const King   white_king;

        const map black_pieces;
        const map white_pieces;
        const map occupied;
        const map empty;

        const map check_mask;
        const map pin_mask;

    constexpr Board(
        map bp, map bn, map bb, map br, map bq, map bk,
        map wp, map wn, map wb, map wr, map wq, map wk) :
            black_pawns(Pawn(bp)),
            black_knights(Knight(bn, Color::BLACK)),
            black_bishops(Bishop(bb, 0)), 
            black_rooks(Rook(br, Color::BLACK)), 
            black_queen(Queen(bq, Color::BLACK)), 
            black_king(King(bk, Color::BLACK)),

            white_pawns(bp),
            white_knights(bn),
            white_bishops(bb),
            white_rooks(br),
            white_queen(bq),
            white_king(bk),

            black_pieces( bp | bn | bb | br | bq | bk ),
            white_pieces( wp | wn | wb | wr | wq | wk ),
            occupied( black_pieces | white_pieces ),
            empty( ~occupied ),

            check_mask(0ull), pin_mask(0ull)
        {
            black_pawns = Pawn<Color::BLACK>(bp);
        }
    
    template <bool is_white>
    constexpr map EnemyOrEmpty() {
        if (is_white) { return ~(this->white_pieces); }
        else          { return ~(this->black_pieces); }
    }
};

