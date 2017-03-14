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

	/*
	cout << "Hello and welcome to a modified version of battleship.\n" <<
	"In case you are not familiar with the rules, in this game you start\n" <<
	"with a fleet of ships. Unfortunately, so does your opponent (the computer).\n" <<
	"The aim of the game is to guess where your opponent's ships are,\n" <<
	"and sink them all, before your opponent does! Press enter to continue.\n";

	cin.get();

	cout << "Here's your standard fleet for a 10x10 board:\n" <<
	"1 raft, which takes up one space, fires 0 times per turn,\n" <<
	"and doubles your fleet's number of available hits\n\n" <<

	"1 battleship, which occupies 5 spaces in a line and fires once per turn,\n\n" <<

	"1 boomerang, which looks like an \'L\' three spaces high,\n" <<
	"and three spaces long; it can fire once per turn\n\n" <<

	"1 donut, which is a 3x3 square with a hole in the middle;\n" <<
	"it can fire twice per turn\n" <<
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

	*/

	//now to start the game
	cout << "And that is all of the rules. Both you and the computer will begin with\n" <<
		"standard fleets described above. The game only has easy mode for now, so your\n" <<
		"opponent will guess random tiles until your fleet has been sunk. Good luck!\n" <<
		"Press a key to begin.\n\n";

	cin.get();

	//stores the player's fleet of ships
	matrix playerFleet(10);

	//stores the computer's fleet of ships
	matrix opponentFleet(10);

	//displays player's hits and misses on the enemy
	matrix playerGuesses(10);

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
		matrix BSmatrix = playerFleet[0]->shipShape();

		//paste the battleship into the fleet
		playerFleet.pasteShip(BSmatrix, playBSStartX, playBSStartY, 5, 5);

		//search through the returned matrix for the actual spaces that the battleship occupies
		for (int i = 0; i < 25; ++i){
			tile curr = BSmatrix.coordinates(i % 5, i / 5);
			if (curr.getMark() == 'B')
				playerFleet[0]->occupySpace(i % 5, i / 5);
		}

		//now for the opponent's battleship
		opponentFleet.addShip(new battleship());

		BSmatrix = opponentFleet[0]->shipShape();

		//search through the returned matrix for the actual spaces that the battleship occupies
		for (int i = 0; i < 25; ++i){
			tile curr = BSmatrix.coordinates(i % 5, i / 5);
			if (curr.getMark() == 'B')
				opponentFleet[0]->occupySpace(i % 5, i / 5);
		}

		//paste the battleship into the fleet
		opponentFleet.pasteShip(BSmatrix, oppBSStartX, oppBSStartY, 5, 5);

		//next is the boomerang; just going to guess around until we find a 3x3 set of unoccupied tiles
		//could come up with an algorithm to randomly generate starting x and y coords right the first time,
		//but that will get progressively more convoluted as the fleet gets bigger

		int boomStartX;
		int boomStartY;

		playerFleet.addShip(new boomerang());

		do{
			boomStartX = rand() % 8;
			boomStartY = rand() % 8;
		} while (!playerFleet[1]->goodSet(playerFleet, boomStartX, boomStartY));

		//keep on coming up with coordinates, until we get a valid starting point

		matrix boomMatrix = playerFleet[1]->shipShape();
		playerFleet.pasteShip(boomMatrix, boomStartX, boomStartY, 3, 3);

		//check for which tiles the boomerang occupies, add them to the ship's vector of occupied tiles
		for (int i = 0; i < 9; ++i){
			tile curr = boomMatrix.coordinates(i % 3, i / 3);
			if (curr.getMark() == 'O')
				playerFleet[1]->occupySpace(i % 3, i / 3);
		}

		//now for the opponent's boomerang
		opponentFleet.addShip(new boomerang());

		do{
			boomStartX = rand() % 8;
			boomStartY = rand() % 8;
		} while (!opponentFleet[1]->goodSet(playerFleet, boomStartX, boomStartY));


		boomMatrix = opponentFleet[1]->shipShape();
		opponentFleet.pasteShip(boomMatrix, boomStartX, boomStartY, 3, 3);

		for (int i = 0; i < 9; ++i){
			tile curr = boomMatrix.coordinates(i % 3, i / 3);
			if (curr.getMark() == 'O')
				opponentFleet[1]->occupySpace(i % 3, i / 3);
		}

		//next is donut, looking a lot like boomerang
		playerFleet.addShip(new donut());

		int doStartX;
		int doStartY;

		do{
			doStartX = rand() % 8;
			doStartY = rand() % 8;
		} while (!playerFleet[2]->goodSet(playerFleet, doStartX, doStartY));

		matrix doMatrix = playerFleet[2]->shipShape();
		playerFleet.pasteShip(doMatrix, doStartX, doStartY, 3, 3);
		//only leave the middle space out of the list of occupied tiles
		for (int i = 0; i < 9; ++i)
			if (i != 4)
				playerFleet[2]->occupySpace(i % 3, i / 3);

		//now for the opponent's donut
		opponentFleet.addShip(new donut());

		do{
			doStartX = rand() % 8;
			doStartY = rand() % 8;
		} while (!opponentFleet[2]->goodSet(playerFleet, doStartX, doStartY));


		doMatrix = opponentFleet[2]->shipShape();
		opponentFleet.pasteShip(doMatrix, doStartX, doStartY, 3, 3);
		for (int i = 0; i < 9; ++i)
			if (i != 4)
				opponentFleet[2]->occupySpace(i % 3, i / 3);

		//now for raft, which should be much easier
		playerFleet.addShip(new raft());

		int raftStartX;
		int raftStartY;

		do{
			raftStartX = rand() % 10;
			raftStartY = rand() % 10;

		} while (!playerFleet[3]->goodSet(playerFleet, doStartX, doStartY));


		playerFleet.pasteShip(playerFleet[3]->shipShape(), raftStartX, raftStartY, 1, 1);
		//just add (startX, startY) to the raft's spacesOccupied
		playerFleet[3]->occupySpace(raftStartX, raftStartY);

		//now for the opponent's raft
		opponentFleet.addShip(new raft());

		do{
			raftStartX = rand() % 10;
			raftStartY = rand() % 10;
		} while (!opponentFleet[3]->goodSet(playerFleet, doStartX, doStartY));


		opponentFleet.pasteShip(opponentFleet[3]->shipShape(), doStartX, doStartY, 1, 1);
		opponentFleet[3]->occupySpace(doStartX, doStartY);

		cout << "Alright, your fleet has been built...here it is:\n";
		playerFleet.display();

	}

	bool playerUp = true;
	bool opponentUp = true;

	//round loop
	while (playerUp && opponentUp){
		cout << "Well, the game is not over yet...you have " << playerFleet.fleetSize() << " ships left\n";
		int numHits = 0;
		int multiplier = 1;
		for (int i = 0; i < playerFleet.fleetSize(); ++i){
			numHits += playerFleet[i]->getHits();
			multiplier *= playerFleet[i]->getMult();
		}

		//collect the coordinates
		vector<int> coordinates;
		
		do{
			cout << "You have " << numHits * multiplier << " hits to make. Enter your coordinates\n" <<
				"in the form (x, y), with spaces in between please...\n" <<
				"or honestly however you wish,\n" <<
				"so long as each number you enter is between 0 and 9, inclusive.\n";

			//the idea is to stop cin from running wild by taking in a test int, then filling coordinates with ints whenever
			//test != 1000
			int test = 1000;
			cin >> test;
			
			if (test != 1000){
				coordinates.push_back(test);
				//start fetching numbers
				while (cin.peek() != '\n' && coordinates.size() < 2 * numHits * multiplier){
					int temp;
					cin >> temp;
					coordinates.push_back(temp);
				}
			}

		} while (coordinates.size() < 2 * numHits * multiplier);

		//make hits for every space entered
		for (int i = 0; i < coordinates.size(); i+=2){
			if (coordinates[i] < 10 && coordinates[i + 1] < 10){
				if (opponentFleet.coordinates(coordinates[i], coordinates[i + 1]).recieveHit()){
					playerGuesses.coordinates(coordinates[i], coordinates[i + 1]).setMark('X');
				}

				else
					playerGuesses.coordinates(coordinates[i], coordinates[i + 1]).setMark('M');
			}

			else
				cout << "You entered a wrong pair of coordinates...and you don't have a second chance to get them right!\n";
		}	

		cout << "Now it's your opponent's turn.\n";

		//now for the opponent
		vector<int> opponentGuesses;
		//count the number of hits
		numHits = 0;
		multiplier = 1;
		for (int i = 0; i < opponentFleet.fleetSize(); ++i){
			numHits += opponentFleet[i]->getHits();
			multiplier *= opponentFleet[i]->getMult();
		}

		//keep guessing coordinates and firing
		while (opponentGuesses.size() < 2 * numHits * multiplier){
			int x = rand() % 10;
			int y = rand() % 10;

			if (playerFleet.coordinates(x, y).getMark() != 'M'){
				opponentGuesses.push_back(x);
				opponentGuesses.push_back(y);

				playerFleet.coordinates(x, y).recieveHit();
			}
		}

		cout << "All shots have been fired. Here is your fleet:\n";
		playerFleet.display();

		cout << "And here is the guesses that you have made:\n";
		playerGuesses.display();

		playerUp = false;
		opponentUp = false;
		//check every space in both playerFleet and opponentFleet for a space that isn't a hit, miss, or blank
		for (int i = 0; i < 10; ++i){
			for (int j = 0; j < 10; ++j){
				if (playerFleet.coordinates(i, j).getMark() != '-' || playerFleet.coordinates(i, j).getMark() != 'M' || playerFleet.coordinates(i, j).getMark() != 'X')
					playerUp = true;

				if (opponentFleet.coordinates(i, j).getMark() != '-' || opponentFleet.coordinates(i, j).getMark() != 'M' || opponentFleet.coordinates(i, j).getMark() != 'X')
					opponentUp = true;
			}
		}


		//start erasing ships if applicable
		for (int i = 0; i < playerFleet.fleetSize(); ++i){
			if (playerFleet[i]->sunk(playerFleet)){
				playerFleet.removeShip(i);
				cout << "One of your ships has been sunk this round!\n";
			}
		}

		for (int i = 0; i < opponentFleet.fleetSize(); ++i){
			if (opponentFleet[i]->sunk(opponentFleet)){
				opponentFleet.removeShip(i);
				cout << "Congratulations, you have sunk a ship this round!";
			}
		}


	}//end of round loop

	if (playerUp)
		cout << "You've won, congratulations! Come back soon!\n";

	else if (opponentUp)
		cout << "You've lost, better luck next time!\n";

	cin.get();

	return 0;
}