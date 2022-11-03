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
 * Obtiene un movimiento preguntandole al jugador que quiere hacer.
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
            // Le enseña al usuario posbiles movimientos y le pide que escoga uno
            displayBoard(board, possibleMoves);
            move_ptr_t move = getMoveFromUser(possibleMoves);
            
            // aplica el movimiento al tablero
            if (move != nullptr)
            {
                board.applyMoveToBoard(move, pieceMoving);
                return;
            }
        }
    } 
}
    
/**
 * Responsable de mostrar los movimientos posibles al usario
 * @param El tablero que se mostrara
 * @param possibleMoves
 * El tablero se mostrara normalmente aunque el movimiento sea nulo.
 */
void HumanPlayer::displayBoard(const Board& board, const moves_t possibleMoves)
{
    // limpia la pantalla para mostrar el tablero
    clearScreen();
    
   
    for (int y = -1; y < Board::SIZE; y++)
    {   
        
        for (int x = -1; x < Board::SIZE; x++)
        {
          
            if (y == -1) 
            {
                if (x != -1) 
                  
                    std::cout << "-" << (char)(x + 65) << "- ";
                else
                    std::cout << "     "; 
            }
         
            else if (x == -1)
            {
                if (y != -1)
                   
                    std::cout << "-" << y + 1 << "- ";
            }
            else
            {
                // Obtiene la pieza a mover
                Piece* thisPiece = board.getValueAt(x, y);
                
                // Si hay una se mueve entre todos los moviemientos disponibles
                if (!possibleMoves.empty())
                {
                    
                    bool moveFound = false;
                    
                    for (unsigned int i = 0; i < possibleMoves.size(); i++)
                    {
                        coords_t move = possibleMoves[i]->getEndingPosition();
                        if (move[0] == x && move[1] == y)
                        {
                          
                            std::cout << "| " << i+1 << " ";
                            moveFound = true;
                        }
                    }
                    
                
                    if (moveFound)
                        continue;
                }
             
              
                if (thisPiece != nullptr)
                    std::cout << "| " << thisPiece->getString();
              
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
 * Se encarga de mostrar el tablero
 * @param board El tablero que se mostrara
 */
void HumanPlayer::displayBoard(const Board& board)
{
	
	static moves_t emptyPossibleMoves(0);
	displayBoard(board, emptyPossibleMoves);
}

/**
 * Le pide al usuario una pieza en el tablero
 * y se asegura que sea una pieza del mismo color
 * @param board el tablero que se revisara
 * @return 
 */
Piece* HumanPlayer::getPieceFromUser(const Board& board)
{
    // Se repite hasta que se obtenga una pieza valida
    while (true)
    {       
        using namespace std;
        
        string raw;
        
        cout << getColor() << ", indique las coordenadas de la pieza a mover:" << '\n';
        try
        {
            getline(cin, raw);
           
            
         
            if (raw == "exit")
            {
                triggerEndGame();
                return nullptr;
            }
            // se asegura que la coordenada este bien escrita
            else if (raw.length() < 2)
                throw ("Porfavor ingrese un coordenada de la forma'[letra][numero]'.");
                
            
            char letterChar = raw[0];
            char numberChar = raw[1];
            if (isdigit(letterChar)) 
            {
                letterChar = numberChar;
                numberChar = raw[0];
            }   
                            
          
            int x = letterChar - 97;
            int y = numberChar - 48 - 1;

          
            if (board.isOverEdge(x, y))
                throw ("Porfavor ingrese una coordenada");              
            
         
            Piece* userPiece = board.getValueAt(x, y);
            
          
            if (userPiece == nullptr)
                cout << "No hay una pieza en ese lugar!\n" << '\n';
            else if (userPiece->isWhite != this->isWhite)
                cout << "Esa no es su pieza!\n" << '\n';
          
            else
                return board.getValueAt(x, y); 
        }
        catch (const char* e) 
        {
           cout << e << '\n';
           cin.ignore(32767, '\n');
           cin.clear();
        }
    }
}
    
/**
 * Le pide al usuario un numero el cual representa un movimiento
 * previamente se verifica que el movimiento sea valido
 * @param possibleMoves La lista de posibles movimientos
 * @return 
 */
move_ptr_t HumanPlayer::getMoveFromUser(const moves_t possibleMoves)
{
    int moveNum;
    
   
    while (true)
    {   
    	using namespace std;
    
        cout << getColor() << ", porfavor seleccione un movimiento por el numero: ";
        try 
        {
            cin >> moveNum;
            
          
            if (!cin.good())
            	throw ("Ingrese un numero.");
          
            else if (moveNum > possibleMoves.size())
                throw ("Por favor ingrese uno de los numeros en el tablero, o 0 para salir.");
          
            else if (moveNum == 0)
                return nullptr;  

			/
           cin.ignore(32767, '\n');
	                           
            
            return possibleMoves[moveNum - 1];
        }
        catch (const char* e) 
           cout << e << '\n';
           cin.ignore(32767, '\n');
           cin.clear();
        }
    }
}
    
/**
 * @return
 */
std::string HumanPlayer::getColor()
{
    return isWhite ? "Blanco" : "Negro";
}
