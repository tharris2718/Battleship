#include <vector>
#include <memory>
#include <exception>
#include "Tiles_and_Matrices.h"

using namespace std;

//implementations for class tile first
tile::tile() : marker('-') {}

//if the tile is holding a ship, this function will change it's marker to an 'X' and return true
//otherwise, the marker will change to an 'M' and return false
bool tile::recieveHit(){
	if (marker == '-' || marker == 'M'){
		setMark('M');
		return false;
	}

	else if (marker == 'B' || marker == 'O' || marker == 'R' || marker == 'D'){
		setMark('X');
		return true;
	}
}

//changes the marker
void tile::setMark(char c){
	marker = c;
}

//returns the marker
char tile::getMark() const{
	return marker;
}

//now for class matrix

//the default constructor; creates an axa board, and default initializes the fleet vector; ships will be added later
matrix::matrix(const unsigned int a) : fleet() {
	for (unsigned int i = 0; i < a; ++i){
		board->push_back(new tile[a]());
	}
}

/*
  pasteShip function, which takes a smaller matrix with a ship and puts it into the larger game board
  the x-values will represent starting and ending columns (spaces in the outer array) in the matrix that is copying
  the y-values will represent starting and ending rows (spaces in the inner array) in the matrix that is copying
  in short, this copy constructor will be used by the board to paste smaller matrices with single ships onto it...
  the kind of matrices made from shipShape()
*/
void matrix::pasteShip(const matrix& m, unsigned int xi, unsigned int xf, unsigned int yi, unsigned int yf){
	bool placedShip = false;

	for (unsigned int i = 0; i < (xf - xi) * (yf - yi); ++i){
		tile& toRecieve = board[(i % (xf - xi)) + xi][(i / (yf - yi)) + yi];
		tile& toCopy = m[i % (xf - xi)][i / (yf - yi)];

		toRecieve.setMark(toCopy.getMark());

		if (!placedShip){
			switch (toRecieve.getMark()){
			case('B') : { fleet->push_back(new battleship()); placedShip = true; }
			case('O') : { fleet->push_back(new boomerang()); placedShip = true; }
			case('R') : { fleet->push_back(new raft()); placedShip = true; }
			case('D') : { fleet->push_back(new donut()); placedShip = true; }
			}
		}

	}
}