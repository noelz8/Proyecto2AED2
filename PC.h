#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "Player.h"

#include <unordered_map>

class Board;


class AIPlayer : public Player
{
    private:
    	bool isWhite;
    	
    
		template <class T, class E>
		T getKeyByValue(std::unordered_map<T, E> map, E value);
    
    public:
		
		AIPlayer(bool isWhite) : isWhite(isWhite) {};

		/**
		 * Obtiene un movimiento
		 * @param board el tablero en cual se aplicara el movimiento
		 * @return Returns el tablero con el movimiento realizado
		 */
		virtual void getMove(Board& board);
};

#endif
