#include "Move.h"

#include "Piece.h"
#include "Tablero.h"
#include "Typedefs.h"

/**
 * @return Returns un array que representa las coordenadas iniciales del movimiento
 */
coords_t Move::getStartingPosition() const
{
    coords_t position;
    position[0] = x1;
    position[1] = y1;
    return position;
}

/**
 * @return Returns un array con las coordenadas finales del movimiento
 */
coords_t Move::getEndingPosition() const
{
    coords_t position;
    position[0] = x2;
    position[1] = y2;
    return position;
}
    
/**
 * @return Returns 
 * @param board el tablero en el que se buscaran las piezas
 */
std::vector<Piece*> Move::getJumpedPieces(const Board& board) const
{
	
    std::vector<Piece*> pieces(0);
    
  !
    if (isJump)
    {
        int pieceX = (x1 + x2)/2;
        int pieceY = (y1 + y2)/2;
        
     
        pieces.push_back(board.getValueAt(pieceX, pieceY));
        
    
        if (precedingMove != nullptr)
        {
            std::vector<Piece*> prevJumped = precedingMove->getJumpedPieces(board);
            pieces.insert(pieces.end(), prevJumped.begin(), prevJumped.end()); 
            
        
        }
    }
    
 
    pieces.shrink_to_fit();
    return pieces;
}
