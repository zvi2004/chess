/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include "Board.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::string;


void main()
{
	Board b;
	bool isWhite = true;
	std::string msg;
	int errorMsg = 0, mate = 0;
	srand(time_t(NULL));


	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	char msgToGraphics[1024];
	// msgToGraphics should contain the board string accord the protocol
	// YOUR CODE

	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0"); // just example...

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics
		// according the protocol. Ex: e2e4           (move e2 to e4)

		errorMsg = b.move(msgFromGraphics[0] - 97, msgFromGraphics[1] - 49, msgFromGraphics[2] - 97, msgFromGraphics[3] - 49,isWhite);
		if (errorMsg == 1)
		{
			mate = b.CheckMate(!isWhite);
			if (mate == 8)
			{
				errorMsg = 8;
			}
		}
		/*
		msg = b.toString(isWhite);
		for (int i = 0; i <= 64; i++)
		{
			msgToGraphics[i] = msg[i];
		}
		//strcpy_s(msgToGraphics, b.toString(isWhite)); // msgToGraphics should contain the result of the operation
		*/
		
		/******* JUST FOR EREZ DEBUGGING ******/
		int r = rand() % 10; // just for debugging......
		msgToGraphics[0] = (char)(errorMsg + '0');
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
		if (msgToGraphics[0] == '0' || msgToGraphics[0] == '1')
			isWhite = !isWhite;
	}

	p.close();
}