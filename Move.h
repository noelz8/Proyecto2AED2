#ifndef MOVE_H
#define MOVE_H

#include <array>
#include <vector>
#include "Typedefs.h"

class Piece;
class Board;

class Move
{
	private:
	    const int x1, y1, x2, y2;
    	const move_ptr_t precedingMove;
    	const bool isJump;
    
    public:    
		/**
		 * @param x1 Posicion inicial x
		 * @param y1 Posicion incial y
		 * @param x2 Posicion final x
		 * @param y2 Posicion final y
		 * @param precedingMove
		 */
		Move(int x1, int y1, int x2, int y2, const move_ptr_t precedingMove, bool isJump) :
			x1(x1), y1(y1), x2(x2), y2(y2), precedingMove(precedingMove), isJump(isJump)
			{};

		
		coords_t getStartingPosition() const;
		

		coords_t getEndingPosition() const;
		
		
		std::vector<Piece*> getJumpedPieces(const Board& board) const;
};

#endif
