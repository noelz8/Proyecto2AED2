#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <array>
#include "Typedefs.h"

class Board;
class Move;



class Piece
{
    private:
    	int x;
    	int y;
    	bool isKing = false;
    	
    
		void setKing() { isKing = true; }
		
		
		moves_t getAllPossibleJumps(const Board& board, const move_ptr_t precedingMove) const;
		
    public:
    	const bool isWhite;

	
		Piece(int x, int y, bool isWhite) : x(x), y(y), isWhite(isWhite) {};
	
		coords_t getCoordinates() const;
		
		std::string getString() const;
		
		void checkIfShouldBeKing(const Board& board);

		
		void moveTo(int x, int y) { this->x = x; this->y = y; }
		
		
		moves_t getAllPossibleMoves(const Board& board) const;
};
		
#endif
