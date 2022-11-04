#include "Player.h"
#include "PC.h"
#include "Jugador.h"
#include "Tablero.h"
#include "Piece.h"
#include "Move.h"

#include <vector>
#include <iostream>



bool isPlayer1 = true;
bool endGameNow = false; 

/**
 * Limpia la terminal
 */
void clearScreen()
{
	
	std::cout << "\033[2J\033[1;1H"; 
}


void triggerEndGame()
{
	endGameNow = true;
}


bool askIfTwoPlayer()
{
	
	while (true)
	{
		using namespace std;
	
	    
	    clearScreen();
	    cout << "*******Bienvenido*******\n" << '\n';
	    cout << "Ingrese 'exit' para salir en cualquier momento.\n" << '\n';
	    cout << "Ingrese 1 para empezar a jugar:"<< '\n';

	   
	    string response;
	    getline(cin, response);
	    if (response == "1") 
            return false;
	    else if (response == "2")
            return true;
        else if (response == "exit")
        {
            triggerEndGame();
            return true;
        }
    }
}


bool endGame(const Board& board)
{
	
	if (endGameNow)
	    return true;
	else
	{
	  
	    int movableWhiteNum = 0;
	    int movableBlackNum = 0;
	    for (int pos = 0; pos < Board::SIZE*Board::SIZE; pos++)
	    {
	      
	        Piece* pieceHere = board.getValueAt(pos);
	        if (pieceHere != nullptr)
	        {
	          
	            if (!pieceHere->getAllPossibleMoves(board).empty())
	            {
	                if (pieceHere->isWhite)
	                    movableWhiteNum++;
	                else
	                    movableBlackNum++;
	            }
	        }
	    }
		
		using namespace std;
		
	   
	    if (movableWhiteNum + movableBlackNum == 0)
	        cout << "Empate" << endl;
	    else if (movableWhiteNum == 0)
	        cout << "Ganan las negras" << endl;
	    else if (movableBlackNum == 0)
	        cout << "Ganan las blancas!" << endl;
	    else
	        return false;

	    return true;
	}
}

int main()
{
	
	Board board;

	Player* player1;
	Player* player2;

	if (askIfTwoPlayer())
	{
	    player1 = new HumanPlayer(true);
	    player2 = new HumanPlayer(false);
	}
	else
	{
	    player1 = new HumanPlayer(true);
	   
	    player2 = new AIPlayer(false);
	}
	clearScreen();

	while ( !endGame(board) )
	{
	    if (isPlayer1)
	    {
	        player1->getMove(board);
	    }
	    else
	    {
	        player2->getMove(board);
	    }

	 
	    isPlayer1 = !isPlayer1;
	}
	
	delete player1;
	delete player2;
	
	return 0;
}

