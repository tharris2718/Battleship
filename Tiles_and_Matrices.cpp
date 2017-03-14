#include <vector>
#include <iostream>
#include <utility>
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

//the "default" constructor; creates an axa board; ships will be added later
matrix::matrix(const int a){
	//fill the board with an axa double vector of tiles
	for (int i = 0; i < a; ++i){
		try{
			board.push_back(new tile[a]());
		}
		catch (exception& e){
			for (tile* t : board)
				delete[] t;

			throw std::exception("Couldn't allocate memory for a new row.\n");
		}
	}
}

//the real default constructor
matrix::matrix(){
	try{
		board.push_back(new tile[0]);
	}
	catch (exception& e){
		throw std::exception("Couldn't add a vector of length 0 to memory. Wow...just wow.");
	}
}

//copy constructor, for the sake of shipShape, which kind of has to return a matrix by copy
//I would use initializer lists, but I think that that may not work as intended, compared to doing things the manual way
matrix::matrix(const matrix& m){
	for (ship* s : m.fleet){
		fleet.push_back(s);
	}

	for (int i = 0; i < m.board.size(); ++i){
		board.push_back(new tile[m.board.size()]);
		for (int j = 0; j < m.board.size(); ++j){
			board[i][j].setMark(m.board[i][j].getMark());
		}
	}
}

/*
  pasteShip function, which takes a smaller matrix with a ship and puts it into the larger game board
  the x-values will represent starting column and length (spaces in the outer array) in the matrix that is copying
  the y-values will represent starting row and height (spaces in the inner array) in the matrix that is copying
*/
void matrix::pasteShip(matrix& m, int xi, int yi, int dx, int dy){

	//if anything is less than 0, we have a problem
	if (xi < 0 || dx < 0 || yi < 0 || dy < 0){
		throw std::exception("Improper bounds on matrix copy.");
		return;
	}

	for (int i = 0; i < dx * dy; ++i){
		tile& toRecieve = board[(i % dx) + xi][(i / dy) + yi];
		tile& toCopy = m.board[i % dx][i / dy];

		toRecieve.setMark(toCopy.getMark());
	}
}

//void display in all its glory
void matrix::display() const{
	for (int j = 0; j < board.size(); ++j){
		for (int i = 0; i < board.size(); ++i){
			tile* curr = board[j];
			cout << (curr + i)->getMark() << " ";
		}	
			//board[j] is the row, and i is the column

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
	cout << "Deleting a matrix of size " << board.size() << endl;

	for (ship* s : fleet)
		delete s;

	for (tile* t : board)
		delete[] t;
		
	//for some reason, delete[] combined with a for each loop is causing errors, so we'll replace it with this
	//maybe deleting from the beginning is causing the errors, so let's start from the end
}