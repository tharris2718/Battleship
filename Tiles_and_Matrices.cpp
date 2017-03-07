#include <vector>
#include <exception>
#include "Tiles_and_Matrices.h"
#include "Ships.h"

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
matrix::matrix(const int a) : board(), fleet() {
	//fill the board with an axa double vector of tiles
	for (int i = 0; i < a; ++i){
		vector<tile> temp;
		for (int i = 0; i < a; ++i)
			temp.push_back(tile());

		board.push_back(temp);
	}
}

//copy constructor, for the sake of the big 4
matrix::matrix(const matrix& m) : board(m.board), fleet(m.fleet) {}

/*
  pasteShip function, which takes a smaller matrix with a ship and puts it into the larger game board
  the x-values will represent starting and ending columns (spaces in the outer array) in the matrix that is copying
  the y-values will represent starting and ending rows (spaces in the inner array) in the matrix that is copying
  in short, this copy constructor will be used by the board to paste smaller matrices with single ships onto it...
  the kind of matrices made from shipShape()
*/
void matrix::pasteShip(matrix& m, int xi, int xf, int yi, int yf){
	bool placedShip = false;

	if (xi < 0 || (xf - xi) < 0 || yi < 0 || (yf - yi) < 0)
		throw std::exception("Improper bounds on matrix copy.");
	

	for (int i = 0; i < (xf - xi) * (yf - yi); ++i){
		tile& toRecieve = board[(i % (xf - xi)) + xi][(i / (yf - yi)) + yi];
		tile& toCopy = m.board[i % (xf - xi)][i / (yf - yi)];

		toRecieve.setMark(toCopy.getMark());

		if (!placedShip){
			//object fleet is the only variable in all classes that uses heap memory, so we're being extra careful
			try{
				switch (toRecieve.getMark()){
				case('B') : { fleet.push_back(new battleship()); placedShip = true; }
				case('O') : { fleet.push_back(new boomerang()); placedShip = true; }
				case('R') : { fleet.push_back(new raft()); placedShip = true; }
				case('D') : { fleet.push_back(new donut()); placedShip = true; }
				}
			}
			catch (exception& e){
				for (ship* s : fleet)
					delete s;

				throw exception("Too little memory on computer...sorry!");
			}
		}

	}
}


//a simple destructor, just delete the ship* in fleet that remain
matrix::~matrix(){
	for (ship* s : fleet)
		delete s;
}