#include <vector>
#include <iostream>
#include <exception>
#include "Ships.h"

using namespace std;

//implementations for class tile first
tile::tile() : marker('-') {}

//copy constructor
tile::tile(const tile& t) : marker(t.getMark()) {}

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
  the x-values will represent starting column and length (spaces in the outer array) in the matrix that is copying
  the y-values will represent starting row and height (spaces in the inner array) in the matrix that is copying
*/
void matrix::pasteShip(matrix& m, int xi, int dx, int yi, int dy){

	//if anything is less than 0, we have a problem
	if (xi < 0 || dx < 0 || yi < 0 || dy < 0){
		throw std::exception("Improper bounds on matrix copy.");
		return;
	}

	for (int i = 0; i < dx * dy; ++i){
		tile& toRecieve = board[(i % (dx)) + xi][(i / (dy)) + yi];
		tile& toCopy = m.board[i % (dx)][i / (dy)];

		toRecieve.setMark(toCopy.getMark());
	}
}

//void display in all its glory
void matrix::display() const{
	for (vector<tile> v : board){
		for (tile t : v)
			cout << t.getMark() << " ";

		cout << endl;
	}
}

//addShip adds the specified ship to the fleet
//intended for use with heap ships
void matrix::addShip(ship* s){
	try{
		fleet.push_back(s);
	}
	catch (std::exception& e){
		for (ship* ptr : fleet)
			delete ptr;

		throw std::exception("Failed to allocate memory for a new ship...sorry.");
	}
}

//subscript operator
ship* matrix::operator[](int a){
	return fleet[a];
}

//removeShip function
void matrix::removeShip(ship* s){
	for (auto iter = fleet.begin(); iter != fleet.end(); ++iter){
		if (*iter == s){
			fleet.erase(iter);
			return;
		}
	}

	cout << "Ship not found...\n";
}

//a simple destructor, just delete the ship* in fleet that remain
matrix::~matrix(){
	for (ship* s : fleet)
		delete s;
}