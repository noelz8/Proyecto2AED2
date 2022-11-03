#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"
#include "Typedefs.h"

class Board;
class Move;
class Piece;

#include <vector>
#include <string>

/**
 * Se encarga de comunicarse con el jugador.
 *   
 */
class HumanPlayer : public Player
{
    private:
	    const bool isWhite;
		
		/**
		 * Se encarga de mostrar el tablero con los posbiles movimientos
		 * @param board The El tablero
		 * @param possibleMoves un vector con los posibles movimientos a realizar
		 */
		void displayBoard(const Board& board, const moves_t possibleMoves);
		
		/**
		 * Muestra el tablero al usuario
		 * @param board el tablero
		 */
		void displayBoard(const Board& board);
		
		/**
		 * le pide al usuario una pieza en el tablero,
		 * y se asegura que sea del mismo color
		 * @param board el tablero 
		 * @return 
		 */
		Piece* getPieceFromUser(const Board& board);
		
		/**
		 * le pide al usuario un numero el cual es un movimiento
		 * y se asegura que sea un movimiento valido
		 * @param possibleMoves la lista con los posibles movimientos
		 * @return 
		 */
		move_ptr_t getMoveFromUser(const moves_t possibleMoves);
		

		std::string getColor();
	    
	public:
		
		HumanPlayer(bool isWhite) : isWhite(isWhite) {};
		
		/**
		 * Obtiene un movimiento preguntandole al usuario que movimiento desea realizar
		 * @param board el tablero en el cual se aplicara el movimiento
		 */
		virtual void getMove(Board& board);
};

#endif
