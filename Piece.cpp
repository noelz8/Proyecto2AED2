#include "Piece.h"

#include "Tablero.h"
#include "Move.h"
#include "Typedefs.h"

#include <iostream>

/**
 * @return Returns un array con la posicion de la pieza.
 */
coords_t Piece::getCoordinates() const
{
    coords_t coords;
    coords[0] = this->x;
    coords[1] = this->y;
    return coords;
}
    

std::string Piece::getString() const
{
    std::string baseSymbol;

    if (isWhite)
        baseSymbol = "W";
    else
        baseSymbol = "B";

    if (isKing)
        baseSymbol += "K";
    else
        baseSymbol += " "; 

    return baseSymbol;
}

    
/**
 * Cambia la pieza por una reina en caso de estar al final del tablero
 * se tiene que llamar despues de cada moviento
 */
void Piece::checkIfShouldBeKing(const Board& board)
{
 
    if (isWhite && this->y == Board::SIZE - 1 || 
        !isWhite && this->y == 0)
        setKing();
}
    
/**
 * Genera todos los movimientos disponibles de una pieza dada.
 * @return Returns una lista con todos los movimientos disponibles
 * @param board el tablero de juego
 */
moves_t Piece::getAllPossibleMoves(const Board& board) const
{
 
    moves_t moves(0);
    
  
    int startingY, yIncrement;
    if (isWhite)
    {
        
        startingY = this->y + 1; 
        yIncrement = -2;
    }
    else 
    {
        
        startingY = this->y - 1;
        yIncrement = 2;
    }
    
   
    int rowsToCheck = 1; 
    if (this->isKing)
        rowsToCheck = 2;
    
          
    for (int x = this->x - 1; x <= this->x + 1; x += 2)
    {
       
        int y = startingY - yIncrement; 
        for (int i = 0; i < rowsToCheck; i++) 
        {
         
            y += yIncrement;
            
            
            if (board.isOverEdge(x, y))
                continue;
            
           
            if (board.getValueAt(x, y) == nullptr)
            {
              
                move_ptr_t move(new Move(this->x, this->y, x, y, nullptr, false));
                moves.push_back(move); 
            }
        }
    }
    
   
    moves_t possibleJumps = this->getAllPossibleJumps(board, nullptr);
    moves.insert(moves.end(), possibleJumps.begin(), possibleJumps.end());

    moves.shrink_to_fit();
    return moves;
}
    
/**
 * Encuentra todos los saltos que puede hacer esa pieza
 * @param board el tablero que se utilizara
 * @param precedingMove 
 */
moves_t Piece::getAllPossibleJumps(const Board& board, const move_ptr_t precedingMove) const
{

    moves_t moves(0);
    
   
    int startingY, yIncrement;
    if (isWhite)
    {

        startingY = this->y + 2;
        yIncrement = -4;
    }
    else 
    {
        
        startingY = this->y - 2;
        yIncrement = 4;
    }
    
    
    int rowsToCheck = 1; 
    if (this->isKing)
        rowsToCheck = 2;
    
      
    for (int x = this->x - 2; x <= this->x + 2; x += 4)
    {
       
        int y = startingY - yIncrement; 
        for (int i = 0; i < rowsToCheck; i++) 
        {
           
            y += yIncrement;
            
           
            if (board.isOverEdge(x, y))
                continue;
            
       
            if (precedingMove != nullptr &&
                x == precedingMove->getStartingPosition()[0] && 
                y == precedingMove->getStartingPosition()[1])
                continue;
            
          
            Piece* betweenPiece = board.getValueAt( (this->x + x)/2 , (this->y + y)/2 );
            if (betweenPiece != nullptr &&
                betweenPiece->isWhite != this->isWhite &&
                board.getValueAt(x, y) == nullptr)
            {
                
                move_ptr_t jumpingMove(new Move(this->x, this->y, x, y, precedingMove, true));
                
            
                moves.push_back(jumpingMove);
                  
               
                Piece imaginaryPiece(x, y, this->isWhite);
                
              
                if (this->isKing) imaginaryPiece.setKing();
                
             
                moves_t subsequentMoves = imaginaryPiece.getAllPossibleJumps(board, jumpingMove);

              
		        moves.insert(moves.end(), subsequentMoves.begin(), subsequentMoves.end());
            }
        }
    }
    moves.shrink_to_fit();
    return moves;
}
