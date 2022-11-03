#ifndef PLY_H
#define PLY_H

class Board;

/**
 * Una version abstracta del jugador
 */
class Player
{
	public:
		/**
		 * Obtiene un moviemto preguntadole al jugador que quiere hacer
		 * @param board El tablero
		 */
		virtual void getMove(Board& board) = 0;
};

#endif
