# Chess Game Design
## Data Structures

Pieces
- Position: A 64-bit uint, flattened 8x8 bit field
- PieceType: A 8-bit uint, id's (W/B),R,B,N,Q,K,P & captured status
- Board_ptr

Board
- Positions - Contains all of the positions of the pieces (for validation)
- Turn_ind - a bit (1 = white, 0 = black)
- Halfmove Clock - a FEN thing
- Fullmove Number - Number of moves. Starts at 1 and increments after black's move
    
Game
- Summons players (input)
- Manages their boards (output)
- Maintains order (rules)
    
    
