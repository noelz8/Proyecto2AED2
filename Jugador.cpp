#include "Jugador.h"

#include "Tablero.h"
#include "Move.h"
#include "Piece.h"
#include "Typedefs.h"

#include <array>
#include <exception>
#include <iostream>
#include <cassert>


void clearScreen();
void triggerEndGame();

/**
 * Obtiene un movimeinto preguntandole al jugador que quiere hacer.
 * @param board El tablero donde se aplicara el movimiento
 * @return Devuelve el tablero modificado con el movimiento indicado por el jugador
 */
void HumanPlayer::getMove(Board& board)
{        
    // Muestra el tablero para ayudar al jugador
    displayBoard(board);
    
    // Pregunta hasta que se ingrese un movimiento valido
    moves_t possibleMoves;
    while (true)
    {
        // Le pide al jugador una ficha
        Piece* pieceMoving = getPieceFromUser(board);
                    
        // check for quit
        if (pieceMoving == nullptr)
            return;
        
        // encuentra todos los movimientos que puede hacer el jugador
        possibleMoves = pieceMoving->getAllPossibleMoves(board);
        
       
        if (possibleMoves.empty())
            std::cout << "Esa pieza no puede moverse, por favor seleccione otra:" << '\n';
        else
        {
            // Le ensena al usuario posbiles movimientos y le pide que escoga uno
		displayBoard(board, possibleMoves);
            move_ptr_t move = getMoveFromUser(possibleMoves);
            
            // apply move to board and return it if the user entered a valid one
            // OTHERWISE, the user requested a retry, so loop again
            if (move != nullptr)
            {
                board.applyMoveToBoard(move, pieceMoving);
                return;
            }
        }
    } 
}
    
/**
 * Responsible for displaying the game board to the user (optionally with possible moves)
 * @param board The board to be displayed
 * @param possibleMoves An optional std::vector of possible moves to display while printing the board.
 * The board will display as normal if this is null.
 */
void HumanPlayer::displayBoard(const Board& board, const moves_t possibleMoves)
{
    // clear the screen for board display
    clearScreen();
    
    // include a hidden top row for coordinates
    for (int y = -1; y < Board::SIZE; y++)
    {   
        // include a hidden left column for coordinates
        for (int x = -1; x < Board::SIZE; x++)
        {
            // add an exception for the top row (print letter coordinates)
            if (y == -1) 
            {
                if (x != -1) // skip hidden column
                    // print a letter, starting with capital a, for each x value
                    std::cout << "-" << (char)(x + 65) << "- ";
                else
                    std::cout << "     "; // still fill the place we skipped
            }
            // add an exception for the left column (print number coordinates)
            else if (x == -1)
            {
                if (y != -1) // skip hidden row
                    // print a number, starting with one, for each y value
                    std::cout << "-" << y + 1 << "- ";
            }
            else
            {
                // get piece here (possibly null)
                Piece* thisPiece = board.getValueAt(x, y);
                
                // if there are any, loop over the possible moves and see if any end at this space
                if (!possibleMoves.empty())
                {
                    // use to determine whether to continue and skip printing other things
                    bool moveFound = false;
                    
                    for (unsigned int i = 0; i < possibleMoves.size(); i++)
                    {
                        coords_t move = possibleMoves[i]->getEndingPosition();
                        if (move[0] == x && move[1] == y)
                        {
                            // if one here, put the list index (one-indexed) here as a char
                            std::cout << "| " << i+1 << " ";
                            moveFound = true;
                        }
                    }
                    
                    // if a move is found here, skip our other possible printings
                    if (moveFound)
                        continue;
                }
             
                // if the piece at this location exists, print it with a bar for cosmetics
                if (thisPiece != nullptr)
                    std::cout << "| " << thisPiece->getString();
                // print out dots (black places) at checkerboard spaces
                else if (board.isCheckerboardSpace(x, y))
                    std::cout << "| . ";
                else
                    std::cout << "|   ";
            }
        }
        std::cout << '\n';
    }
}

/**
 * Responsible for displaying the game board to the user (WITHOUT possible moves)
 * @param board The board to be displayed
 */
void HumanPlayer::displayBoard(const Board& board)
{
	// emptyPossibleMoves will never change now, but that's okay
	static moves_t emptyPossibleMoves(0);
	displayBoard(board, emptyPossibleMoves);
}

/**
 * Asks the user for a piece on the board (for them to move),
 * and ensures it is an actual piece of the correct color
 * @param board The board to check against
 * @return The Piece object to be returned (will be an actual piece)
 */
Piece* HumanPlayer::getPieceFromUser(const Board& board)
{
    // keep trying again until we get a valid peice chosen
    while (true)
    {       
        using namespace std;
        
        string raw;
        
        cout << getColor() << ", indique las coordenadas de la pieza a mover:" << '\n';
        try
        {
            getline(cin, raw);
            // TODO: To lower case
            
            // allow user to exit
            if (raw == "exit")
            {
                triggerEndGame();
                return nullptr;
            }
            // ensure a valid coordinate input
            else if (raw.length() < 2)
                throw ("Porfavor ingrese un coordenada de la forma'[letra][numero]'.");
                
            // Presume that the user entered the letter coordinate first, but flip them if it's the other way around
            char letterChar = raw[0];
            char numberChar = raw[1];
            if (isdigit(letterChar)) // the letter is actually a number...
            {
                letterChar = numberChar;
                numberChar = raw[0];
            }   
                            
            // get coordinates by shifting the corresponding character to its numeric value (0-indexed)
            int x = letterChar - 97;
            int y = numberChar - 48 - 1;

            // ensure there's no out-of-bounds entries 
            if (board.isOverEdge(x, y))
                throw ("Porfavor ingrese una coordenada");              
            
            // now get the actual piece there
            Piece* userPiece = board.getValueAt(x, y);
            
            // and see if it is valid (isn't null and is this player's color)
            if (userPiece == nullptr)
                cout << "No hay una pieza en ese lugar!\n" << '\n';
            else if (userPiece->isWhite != this->isWhite)
                cout << "Esa no es su pieza!\n" << '\n';
            // if successful, make sure not to return a local variable 
            else
                return board.getValueAt(x, y); 
        }
        catch (const char* e) // catch incorrect parse or our throw exception
        {
           cout << e << '\n';
           cin.ignore(32767, '\n');
           cin.clear();
        }
    }
}
    
/**
 * Asks the user for a number representing a move of a particular piece,
 * checking that it is an available move. (The user should be shown all moves beforehand)
 * @param possibleMoves The list of possible moves the user can request
 * @return The Move object representing the chosen move (may be null if the user chooses to get a new piece)
 */
move_ptr_t HumanPlayer::getMoveFromUser(const moves_t possibleMoves)
{
    int moveNum;
    
    // keep trying again until we get a valid move chosen
    while (true)
    {   
    	using namespace std;
    
        cout << getColor() << ", porfavor seleccione un movimiento por el numero: ";
        try 
        {
            cin >> moveNum;
            
            // ensure correct parse
            if (!cin.good())
            	throw ("Ingrese un numero.");
            // ensure they enter a move that we printed
            else if (moveNum > possibleMoves.size())
                throw ("Por favor ingrese uno de los numeros en el tablero, o 0 para salir.");
            // allow user to quit back to another piece by entering 0
            else if (moveNum == 0)
                return nullptr;  

			// make sure cin is clean for the next input
           cin.ignore(32767, '\n');
	                           
            // return the move the user entered (switch to 0-indexed), once we get a valid entry
            return possibleMoves[moveNum - 1];
        }
        catch (const char* e) // catch incorrect parse or our throw exception
        {
           cout << e << '\n';
           cin.ignore(32767, '\n');
           cin.clear();
        }
    }
}
    
/**
 * @return Returns a titlecase string representing this player's color
 */
std::string HumanPlayer::getColor()
{
    return isWhite ? "Blanco" : "Negro";
}
