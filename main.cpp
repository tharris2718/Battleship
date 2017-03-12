#include <iostream>
#include <ctime>
#include <cstdlib>
#include <utility>

#include "Ships.h"

using namespace std;

int main(){
	srand(time(nullptr));

	//get the rules out of the way
	//just an explanation of all the rules, spaced out with cin.get()'s

	cout << "Hello and welcome to a modified version of battleship.\n" <<
		"In case you are not familiar with the rules, in this game you start\n" <<
		"with a fleet of ships. Unfortunately, so does your opponent (the computer).\n" <<
		"The aim of the game is to guess where your opponent's ships are,\n" <<
		"and sink them all, before your opponent does! Press enter to continue.\n";

	cin.get();

	cout << "Here's your standard fleet for a 10x10 board:\n" <<
		"1 raft, which takes up one space, fires 0 times per turn,\n" <<
		"and doubles your fleet's number of available hits\n\n" <<

		"1 battleship, which occupies 5 spaces in a line, fires twice per turn,\n" <<
		"and also doubles your fleet's firepower\n\n" <<

		"1 boomerang, which looks like an \'L\' three spaces high,\n" <<
		"and three spaces long; it can fire twice per turn\n\n" <<

		"1 donut, which is a 3x3 square with a hole in the middle;\n" <<
		"it can fire thrice per turn\n" <<
		"Ready to continue? Press enter or something...\n";

	cin.get();

	cout <<	"Now for the board: all spaces will look like a \'-\' by default.\n" <<
		"If you fire on a space and hit something, or if your opponent does the same,\n" <<
		"the space will display an \'X\'. If you or your opponent fire on a space and\n" <<
		"miss, the space will display an \'M\'. A space on your side of the board will\n" <<
		"display an \'R\' to denote a raft, a \'B\' for a battleship,\n" <<
		"an \'R\' for a boomerang, or a \'D\' for a donut.\n" <<
		"Hit enter one more time.\n\n";

	cin.get();

	//now to start the game
	cout << "And that is all of the rules. Both you and the computer will begin with\n" <<
		"standard fleets described above. The game only has easy mode for now, so your\n" <<
		"opponent will guess random tiles until your fleet has been sunk. Good luck!\n" <<
		"Press a key to begin.\n\n";

	cin.get();

	//stores the player's fleet of ships
	matrix playerFleet(10);

	cout << "Here is you empty board.\n";
	playerFleet.display();

	//stores the computer's fleet of ships
	matrix opponentFleet(10);

	//displays player's hits and misses on the enemy
	matrix playerGuesses(10);

	cout << "Boards made. Now time for the ships.\n";


	//a lot of variables are about to be made, so we'll create a scope here to get ride of them all at the end
	{
			//now to determine where the battleships go, since they are the largest ship

			//generates a starting index for the x and y values where the battleship starts to appear
			int playBSStartX = rand() % 6;
			int playBSStartY = rand() % 6;

			//roll new starting coords for the opponent
			int oppBSStartX = rand() % 6;
			int oppBSStartY = rand() % 6;

			//add in the player's and opponent's battleships

			playerFleet.addShip(new battleship());
			//the matrix returned with the battleship's shape
			matrix& BSmatrix = playerFleet[0]->shipShape();

			cout << "Here's a sample battleship:\n";
			playerFleet[0]->shipShape().display();

			cout << "We've found your battleship's shape. Starting coords:\n" << playBSStartX << ", " << playBSStartY << endl ;
			cout << "Here is what the battleship looks like: \n";
			BSmatrix.display();
			cin.get();

			//paste the battleship into the fleet
			playerFleet.pasteShip(BSmatrix, playBSStartX, playBSStartY, 5, 5);

			//search through the returned matrix for the actual spaces that the battleship occupies
			for (int i = 0; i < 25; ++i){
				tile curr = BSmatrix.coordinates(i % 5, i / 5);
				cout << "Found a tile!\n";
				if (curr.getMark() == 'B'){
					playerFleet[0]->occupySpace(curr);
					cout << "Gratz, battleship can properly occupy a space.\n";
				}
			}

			cout << "Battleship occupied proper tiles.\n";

			cout << "Your battleship has been put into your board.\n";

			//now for the opponent's battleship
			opponentFleet.addShip(new battleship());
		
			BSmatrix = opponentFleet[0]->shipShape();

			cout << "Opponent's battleship constructed.\n";

			//search through the returned matrix for the actual spaces that the battleship occupies
			for (int i = 0; i < 25; ++i){
				tile curr = BSmatrix.coordinates(i % 5, i / 5);
				if (curr.getMark() == 'B')
					opponentFleet[0]->occupySpace(curr);
			}

			cout << "Putting in the opponent's battleship.\n";

			//paste the battleship into the fleet
			opponentFleet.pasteShip(BSmatrix, oppBSStartX, oppBSStartY, 5, 5);

			cout << "Battleships made!\n";

			//next is the boomerang; just going to guess around until we find a 3x3 set of unoccupied tiles
			//could come up with an algorithm to randomly generate starting x and y coords right the first time,
			//but that will get progressively more convoluted as the fleet gets bigger

			bool tilesOccupied = true;
			int playBoomStartX;
			int playBoomStartY;
			while (tilesOccupied){
				tilesOccupied = false;
				playBoomStartX = rand() % 8;
				playBoomStartY = rand() % 8;

				for (int i = 0; i < 3, ++i;)
					for (int j = 0; j < 3; ++j)
						if (playerFleet.coordinates(playBoomStartX + j, playBoomStartY + i).getMark() != '-'){
							tilesOccupied = true;
							break;//at least break out of one loop
						}
				//done checking to see if the spaces are occupied
			}//at this point, the starting x and y coords should be valid

			playerFleet.addShip(new boomerang());

			matrix boomMatrix = playerFleet[1]->shipShape();
			playerFleet.pasteShip(playerFleet[1]->shipShape(), playBoomStartX, playBoomStartY, 3, 3);

			//check for which tiles the boomerang occupies, add them to the ship's vector of occupied tiles
			for (int i = 0; i < 10; ++i){
				tile curr = boomMatrix.coordinates(i % 3, i / 3);
				if (curr.getMark() == 'O')
					playerFleet[1]->occupySpace(curr);
			}

			//now for the opponent's boomerang
			int oppBoomStartX;
			int oppBoomStartY;
			tilesOccupied = true;
			while (tilesOccupied){
				tilesOccupied = false;
				oppBoomStartX = rand() % 8;
				oppBoomStartY = rand() % 8;

				for (int i = 0; i < 3, ++i;)
					for (int j = 0; j < 3; ++j)
						if (opponentFleet.coordinates(oppBoomStartX + j, oppBoomStartY + i).getMark() != '-'){
							tilesOccupied = true;
							break;//at least break out of one loop
						}
				//done checking to see if the spaces are occupied
			}//at this point, the starting x and y coords should be valid

			opponentFleet.addShip(new boomerang());
			boomMatrix = opponentFleet[1]->shipShape();
			opponentFleet.pasteShip(boomMatrix, oppBoomStartX, oppBoomStartY, 3, 3);

			for (int i = 0; i < 10; ++i){
				tile curr = boomMatrix.coordinates(i % 3, i / 3);
				if (curr.getMark() == 'O')
					opponentFleet[1]->occupySpace(curr);
			}

			cout << "Boomerangs made!\n";

		//next is donut, looking a lot like boomerang

		int playDoStartX;
		int playDoStartY;
		tilesOccupied = true;
		while (tilesOccupied){
			tilesOccupied = false;
			playDoStartX = rand() % 8;
			playDoStartY = rand() % 8;

			for (int i = 0; i < 3, ++i;)
				for (int j = 0; j < 3; ++j)
					if (playerFleet.coordinates(playDoStartX + j, playDoStartY + i).getMark() != '-'){
						tilesOccupied = true;
						break;//at least break out of one loop
					}
			//done checking to see if the spaces are occupied
		}//at this point, the starting x and y coords should be valid

		playerFleet.addShip(new donut());
		matrix doMatrix = playerFleet[2]->shipShape();
		playerFleet.pasteShip(doMatrix, playDoStartX, playDoStartY, 3, 3);
		//only leave the middle space out of the list of occupied tiles
		for (int i = 0; i < 10; ++i)
			if (i != 4)
				playerFleet[2]->occupySpace(doMatrix.coordinates(i % 3, i / 3));

		//now for the opponent's donut
		int oppDoStartX;
		int oppDoStartY;
		tilesOccupied = true;
		while (tilesOccupied){
			tilesOccupied = false;
			oppDoStartX = rand() % 8;
			oppDoStartY = rand() % 8;

			for (int i = 0; i < 3, ++i;)
				for (int j = 0; j < 3; ++j)
					if (opponentFleet.coordinates(oppDoStartX + j, oppDoStartY + i).getMark() != '-'){
						tilesOccupied = true;
						break;//at least break out of one loop
					}
			//done checking to see if the spaces are occupied
		}//at this point, the starting x and y coords should be valid

		opponentFleet.addShip(new donut());
		doMatrix = opponentFleet[2]->shipShape();
		opponentFleet.pasteShip(doMatrix, oppDoStartX, oppDoStartY, 3, 3);
		for (int i = 0; i < 10; ++i)
			if (i != 4)
				opponentFleet[2]->occupySpace(doMatrix.coordinates(i % 3, i / 3));

		cout << "Donuts made!\n";

		//now for raft, which should be much easier

		int playRaftStartX;
		int playRaftStartY;
		tilesOccupied = true;
		while (tilesOccupied){
			tilesOccupied = false;
			playRaftStartX = rand() % 10;
			playRaftStartY = rand() % 10;

			if (playerFleet.coordinates(playRaftStartX, playRaftStartY).getMark() != '-')
				tilesOccupied = true;

		}//at this point, the starting x and y coords should be valid

		playerFleet.addShip(new raft());
		playerFleet.pasteShip(playerFleet[3]->shipShape(), playRaftStartX, playRaftStartY, 1, 1);
		//just add (startX, startY) to the raft's spacesOccupied
		playerFleet[3]->occupySpace(playerFleet.coordinates(playRaftStartX, playRaftStartY));

		//now for the opponent's raft
		int oppRaftStartX;
		int oppRaftStartY;
		tilesOccupied = true;
		while (tilesOccupied){
			tilesOccupied = false;
			oppRaftStartX = rand() % 10;
			oppRaftStartY = rand() % 10;

			if (opponentFleet.coordinates(oppRaftStartX, oppRaftStartY).getMark() != '-')
				tilesOccupied = true;

		}//at this point, the starting x and y coords should be valid

		opponentFleet.addShip(new raft());
		opponentFleet.pasteShip(opponentFleet[3]->shipShape(), oppRaftStartX, oppRaftStartY, 1, 1);
		opponentFleet[3]->occupySpace(opponentFleet.coordinates(oppRaftStartX, oppRaftStartY));
	}

	cout << "Alright, your fleet has been built...here it is:\n";
	playerFleet.display();

	cin.get();

	return 0;
}