#include "Pipe.h"
#include "stdafx.h"
#include <thread>
#include "Board.h"

using std::cout;
using std::endl;
using std::cin;

int main()
{
	srand(time_t(NULL));

	
	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return 0;
		}
	}
	

	char msgToGraphics[1024];
	const string START_MASSAGE = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0";
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, START_MASSAGE.c_str()); // just example...
	Board board(START_MASSAGE);
	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// Iterate through each row
		for (char i = Location::MIN_ROW; i <= Location::MAX_ROW; i++) {
			// Iterate through each column
			for (char j = Location::MIN_COL; j <= Location::MAX_COL; j++) {
				// Print the type of piece at the current location
				if (board[Location(j, i)] != nullptr) {
					cout << board[Location(j, i)]->GetPieceType();
					// Print the color of the piece
					if ((board[Location(j, i)]->GetColor() == W)) {
						cout << "B ";
					}
					else {
						cout << "W ";
					}
				}
				// If there is no piece at the current location, print "##"
				else {
					cout << "## ";
				}
			}
			cout << std::endl;
		}
	
		MoveResult result = board.MovePiece(Location(msgFromGraphics[0], msgFromGraphics[1]), Location(msgFromGraphics[2], msgFromGraphics[3])); //sends the coordinates of the location of the piece and the location of where it wants to go
		

		strcpy_s(msgToGraphics, std::to_string(result).c_str()); // msgToGraphics should contain the result of the operation




		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();


	}

	p.close();
}