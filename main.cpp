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
		"opponent will guess random tiles until your fleet has been sunk. Good luck!\n\n";

	//stores the player's fleet of ships
	matrix playerFleet(10);

	//stores the computer's fleet of ships
	matrix opponentFleet(10);

	//displays player's hits and misses on the enemy
	matrix playerGuesses(10);


	//now to determine where the battleships go, since they are the largest ship

	//generates a starting index for the x and y values where the battleship starts to appear
	int playBSStartX = rand() % 6;
	int playBSStartY = rand() % 6;

	//roll new starting coords for the opponent
	int oppBSStartX = rand() % 6;
	int oppBSStartY = rand() % 6;

	//add in the player's and opponent's battleships
	playerFleet.addShip(new battleship());
	playerFleet.pasteShip(playerFleet[0]->shipShape(), playBSStartX, playBSStartY, 5, 5);

	opponentFleet.addShip(new battleship());
	opponentFleet.pasteShip(opponentFleet[0]->shipShape(), oppBSStartX, oppBSStartY, 5, 5);

	//next is the boomerang; just going to guess around until we find a 3x3 set of unoccupied tiles
	//could come up with an algorithm to randomly generate starting x and y coords right the first time,
	//but that will get progressively more convoluted as the fleet gets bigger



	return 0;
}