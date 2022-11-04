#include "Tablero.h"

#include "Piece.h"
#include "Move.h"
#include "Typedefs.h"

/**
 * Se encarga de crear un tablero nuevo
 * Llena el tablero con las piezas en sus posiciones iniciales
 */
Board::Board()
{

    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            // agrega las piezas blancas en la parte superior del tablero
            if (y < 3 && isCheckerboardSpace(x, y))
            {
                setValueAt(x, y, new Piece(x, y, true));
            }
   
            else if (y >= SIZE - 3 && isCheckerboardSpace(x, y))
            {
				setValueAt(x, y, new Piece(x, y, false));
            }
    
            else
            {
            	setValueAt(x, y, nullptr);
            }
        }
    }
}

Board::Board(const Board& board)
{
	for (int pos = 0; pos < SIZE*SIZE; pos++)
    {
		setValueAt(pos, board.getValueAt(pos));  
    }
}


Board::~Board()
{
	for (int pos = 0; pos < SIZE*SIZE; pos++)
    {
    	delete getValueAt(pos);
		setValueAt(pos, nullptr);  
    }
}
    
/**
 * Usando la pieza y el movimiento aplica este ultimo al tablero
 * @param move 
 * @param piece la pieza que se movera
 */
void Board::applyMoveToBoard(const move_ptr_t move, Piece* piece)
{

    
    coords_t moveStartingPos = piece->getCoordinates();
    coords_t moveEndingPos = move->getEndingPosition();
    
    
    std::vector<Piece*> jumpedPieces = move->getJumpedPieces(*this);
    if (!jumpedPieces.empty())
    {
      
        for (unsigned int i = 0; i < jumpedPieces.size(); i++)
        {
            if (jumpedPieces[i] != nullptr)
            {
                setValueAt(jumpedPieces[i]->getCoordinates()[0], 
                			jumpedPieces[i]->getCoordinates()[1], nullptr);
            }
        }
    }
        
   
    setValueAt(moveStartingPos[0], moveStartingPos[1], nullptr);
    piece->moveTo(moveEndingPos[0], moveEndingPos[1]);
    

    piece->checkIfShouldBeKing(*this);
    

    setValueAt(moveEndingPos[0], moveEndingPos[1], piece);
}
    

void Board::setValueAt(int position, Piece* piece)
{
    coords_t coords = getCoordsFromPos(position); 
    setValueAt(coords[0], coords[1], piece);
}


Piece* Board::getValueAt(int position) const
{
    coords_t coords = getCoordsFromPos(position); 
    return getValueAt(coords[0], coords[1]); 
}
    

coords_t Board::getCoordsFromPos(int position) const
{
    coords_t coords;
    
    
    coords[0] = position % SIZE;
    coords[1] = position / SIZE; 
    return coords;
}
    

int Board::getPosFromCoords(int x, int y) const
{
   
    return SIZE*y + x;
}
    

bool Board::isCheckerboardSpace(int x, int y) const
{
   return x % 2 == y % 2;
}
    

bool Board::isOverEdge(int x, int y) const
{
    return (x < 0 || x >= SIZE ||
            y < 0 || y >= SIZE);
}
    

bool Board::isOverEdge(int position) const
{
    coords_t coords = getCoordsFromPos(position);
    return isOverEdge(coords[0], coords[1]); 
}
