# Chess Game Design
## Data Structures

Board: CCR
We need to know all relevent information on the board (pieces and positions), 
so we can create and update each piece's move sets. There are 6 different types 
of pieces, 2 colors or 12 distinct piece types. We also need to account for en
passant captures, and castling oportunities. Castling will be determined by
board state and first move indicators, so we also need a first move indicator.
Thats a total of 14 different square states, which we can fit in 4 bits.

We can represent each rank (row) with 32 bits (8 * 4), so the board can be 
fully described with 8 32-bit registers, 32 bytes. Pretty good.

Moves:
We're going to create an event driven board that only allows legal moves,
determining pinned pieces and required moves/captures. 
At most there can be 160 moves (fewer if we account for board position).

Future Improvements:
    Moves:
        The pieces can be divided based on their move characteristics, and 
        generated at the same time via a SIMD schema.
