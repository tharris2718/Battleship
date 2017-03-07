#include <iostream>


using namespace std;

int main(){
	//get the rules out of the way

	cout << "Hello and welcome to a modified version of battleship.\n" <<
		"In case you are not familiar with the rules, in this game you start with a fleet of ships.\n" <<
		"Unfortunately, so does your opponent (the computer). The aim of the game is to guess where your opponent's\n" <<
		" ships are and sink them all, before your opponent does! Press enter to continue.\n";

	cin.get();

	cout << "Here's your standard fleet for a 10x10 board:\n" <<
		"1 raft, which takes up one space, fires 0 times per turn and doubles your fleet's number of available hits\n" <<
		"1 battleship, which occupies 5 spaces in a line, fires twice per turn, and also doubles your fleet's firepower\n" <<
		"1 boomerang, which looks like an \'L\' three spaces high, and three spaces long; it can fire twice per turn\n" <<
		"1 donut, which is a 3x3 square with a hole in the middle; it can fire thrice per turn\n" <<
		"Ready to continue? Press enter or something...";

	cin.get();

	cout <<	"Now for the board: all spaces will look like a \'-\' by default. If you fire on a space and hit something,\n" <<
		"or if your opponent does the same, the space will display an \'X\'. If you or your opponent fire on a space and\n" <<
		"miss, the space will display an \'M\'. A space on your side of the board will display an \'R\' to denote a raft, \n" <<
		"a \'B\' for a battleship, an \'R\' for a boomerang, or a \'D\' for a donut.";






	return 0;
}