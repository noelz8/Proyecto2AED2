#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Typedefs.h"

class Piece;
class Move;
	
/**
 * Guarda y maneja las interacciones con el tablero.
 */
class Board
{
    public:
   
    	const static int SIZE = 8;

		/**
		 * Se encarga de generar un tablero nuevo
		 */
		Board();

		
		Board(const Board& board);
		
		/**
		 * Se encarga de eliminar piezas del tablero
		 */
		~Board();
   
		/**
		 * con la pieza y el movimiento dados se encarga de mover la pieza en el tablero.
		 * @param move El movimiento que se ejecutara.
		 * @param piece La pieza a mover
		 */
		void applyMoveToBoard(const move_ptr_t move, Piece* piece);
    
    	/**
		 * Obtiene la pieza que este en esa direccion
		 * @param x 
		 * @param y 
		 * @return 
		 */
		Piece* getValueAt(int x, int y) const { return this->boardArray[y][x]; }
    
	
		Piece* getValueAt(int position) const;
    
	
		int getPosFromCoords(int x, int y) const;
    
	
		bool isCheckerboardSpace(int x, int y) const;
		
	
		bool isOverEdge(int x, int y) const;
		
	
		bool isOverEdge(int position) const;
		
	private:
    	Piece* boardArray[SIZE][SIZE];
	
	
		void setValueAt(int x, int y, Piece* piece) 
		{ this->boardArray[y][x] = piece; }
		
	
		void setValueAt(int position, Piece* piece);
	
		 coords_t getCoordsFromPos(int position) const;
};

#endif
