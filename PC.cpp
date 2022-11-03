#include "PC.h"

#include "Tablero.h"
#include "Piece.h"
#include "Move.h"
#include "Typedefs.h"

#include <unordered_map>
#include <vector>
#include <cstdlib>

/**
 * Obtiene un movimiento
 * @param board el tablero donde se aplicara el movimiento
 * @return Returns el tablero modificado
 */
void AIPlayer::getMove(Board& board)
{
	using namespace std;
	typedef unordered_map<Piece*, moves_t> move_choices_t;
	typedef unordered_map<move_ptr_t, Piece*> best_moves_t; 

    // Crea una lista con todos los movimientos posibles
    move_choices_t possibleChoices;
    
    // Se mueve por todas las piezas en el tablero hasta encontrar una que se pueda mover.
    for (int x = 0; x < Board::SIZE; x++)
    {
        for (int y = 0; y < Board::SIZE; y++)
        {
    
            Piece* piece = board.getValueAt(x, y);
            if (piece != nullptr && piece->isWhite == this->isWhite)
            {
              
                moves_t possibleMoves = piece->getAllPossibleMoves(board);
                
             
                if (!possibleMoves.empty())
                    possibleChoices[piece] = possibleMoves;
            }
        }
    }
           
  
    Piece* furthestBackwardPiece = possibleChoices.begin()->first;
    Piece* furthestForwardPiece =  possibleChoices.begin()->first;
    
    // itera a traves de todas las posibilidades
    best_moves_t bestMovesPerPiece;
    for (auto it : possibleChoices)
    {
    	Piece* piece = it.first;
    	
    
        int thisPieceY = piece->getCoordinates()[1];
        if (thisPieceY > furthestForwardPiece->getCoordinates()[1])
        {
           
            if (isWhite)
                furthestForwardPiece = piece;
            else
                furthestBackwardPiece = piece;
        }
        else if (thisPieceY < furthestBackwardPiece->getCoordinates()[1])
        {
       
            if (isWhite)
                furthestBackwardPiece = piece;
            else
                furthestForwardPiece = piece;
        }
        
        // para cada posible movimiento, itera a traves de todos y guarda la cantidad de saltos.
        moves_t possibleMoves = possibleChoices[piece];
        move_ptr_t maxJumpMove = possibleMoves[0];
        int maxJumpMoveLength = 0;
        for (unsigned int i = 0; i < possibleMoves.size(); i++)
        {
           
            vector<Piece*> jumpedPieces = possibleMoves[i]->getJumpedPieces(board);
            if (!jumpedPieces.empty())
            {
                int jumpLength = jumpedPieces.size();
                
               
                if (jumpLength >= maxJumpMoveLength)
                {
                    maxJumpMoveLength = jumpLength;
                    maxJumpMove = possibleMoves[i];
                }
            }
        }
        
        // agrega el movimiento al arreglo
        bestMovesPerPiece[maxJumpMove] = piece;
    }
    
    // itera a traves de las piezas y los mejores movimientos y elige uno
    move_ptr_t absoluteBestMove = bestMovesPerPiece.begin()->first; 
    int absoluteBestMoveJumpLength = 0;
    for (auto it : bestMovesPerPiece)
    {
    	move_ptr_t move = it.first;
    
       
        vector<Piece*> jumpedPieces = move->getJumpedPieces(board);
        
       
        if (!jumpedPieces.empty())
        {
            int thisBestMoveJumpLength = jumpedPieces.size();
        
           
            if (thisBestMoveJumpLength >= absoluteBestMoveJumpLength)
            {
                absoluteBestMoveJumpLength = thisBestMoveJumpLength;
                absoluteBestMove = move;
            }
        }
    }
   
    if (absoluteBestMoveJumpLength > 0)
    {
        board.applyMoveToBoard(absoluteBestMove, bestMovesPerPiece[absoluteBestMove]);
    }
    else 
    {
        int randomNum = rand() & 100;
        if (randomNum >= 50)
        {
        	// obtiene los mejores movimientos de la pieza.
            board.applyMoveToBoard(getKeyByValue(bestMovesPerPiece, furthestBackwardPiece), furthestBackwardPiece);
        }
        else
        {
            board.applyMoveToBoard(getKeyByValue(bestMovesPerPiece, furthestForwardPiece), furthestForwardPiece);
        }  
    }
}
    
template <class T, class E>
T AIPlayer::getKeyByValue(std::unordered_map<T, E> map, E value) 
{
    for (auto it : map) 
    {
        if (it.second == value)
        {
            return it.first;
        }
    }
    return nullptr;
}
