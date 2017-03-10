#include "Ships.h"

using namespace std;

//shipShape for ship; not meant to be used...ever
matrix& ship::shipShape(){
	return matrix(0);
}

//occupySpace function
void ship::occupySpace(const tile& t){
	spacesOccupied.push_back(t);
}

//sunk function
bool ship::sunk() const{
	for (const tile& t : spacesOccupied){
		if (t.getMark() != 'X')
			return false;
	}
	//if the function made it this far, all tiles have an 'X'
	return true;
}

//ship default constructor
ship::ship() : numHits(0), multiplier(0){}

//ship constructor; only to be used by child classes 
ship::ship(int h, int m) : numHits(h), multiplier(m){}

//class raft

//constructor
raft::raft() : base(0, 2) {}

//returns a 1x1 matrix with an 'R' in the middle
matrix& raft::shipShape(){
	matrix m(1);
	m.coordinates(0, 0).setMark('R');
	return m;
}



//class battleship

//constructor
battleship::battleship() : base(2, 2) {}

//returns a 5x5 matrix with 'B's lining a random row or column
matrix& battleship::shipShape(){
	matrix m(5);
	//determines whether the battleship takes up a row (int = 0) or a column (int = 1)
	int rowsOrCols = rand() % 2;
	//index determines which row/column the battleship is pasted into
	int index = rand() % 5;

	//if the battleship goes in a row
	if (!rowsOrCols){
		for (int i = 0; i < 5; ++i){
			m.coordinates(i, index).setMark('B');
		}
	}

	//if the battleship goes in a column
	else{
		for (int i = 0; i < 5; ++i){
			m.coordinates(index, i).setMark('B');
		}
	}

	//now, return the proper matrix
	return m;
}


//class boomerang

//constructor
boomerang::boomerang() : base(2, 1) {}

//returns a 3x3 matrix with a random corner and the two sides touching housing the ship
matrix& boomerang::shipShape(){
	matrix m(3);
	int corner = rand() % 4;

	/*
	  now, switch corner into a proper place on the matrix, according to the map:
	  0  1  2  
	  3  4  5
	  6  7  8

	  also, the number on the matrix == space[number % dimension][number / dimension]
	*/
	switch (corner){
	case(0) : ;
	case(1) : corner = 2;
	case(2) : corner = 6;
	case(3) : corner = 8;
	}

	//now, if corner % 3 == 0, then the starting corner is on the left (expand right)
	//if corner < 3, then the starting corner is on the top (expand down)
	m.coordinates(corner % 3, corner / 3).setMark('R');

	//first, for the horizontal filling
	//if expanding right
	if (!(corner % 3)){
		for (int i = 1; i < 3; ++i){
			m.coordinates((corner % 3) + i, corner / 3).setMark('R');
		}
	}

	//if expanding left
	else{
		for (int i = 1; i < 3; ++i){
			m.coordinates((corner % 3) - i, corner / 3).setMark('R');
		}
	}

	//now for vertical filling
	//if expanding down
	if (corner < 3){
		for (int i = 1; i < 3; ++i){
			m.coordinates(corner % 3, (corner / 3) + i).setMark('R');
		}
	}

	//if expanding up
	else{
		for (int i = 1; i < 3; ++i){
			m.coordinates(corner % 3, (corner / 3) - i).setMark('R');
		}
	}

	//now m should be ready to return
	return m;
}


//class donut

//constructor
donut::donut() : base(3, 1) {}

//returns a 3x3 matrix with all spaces except the middle set to 'D'
matrix& donut::shipShape(){
	matrix m(3);

	//for all values of i except 4 (the middle), set the current tile to 'D'
	for (int i = 0; i < 9; ++i)
		if (i != 4)
			m.coordinates(i % 3, i / 3).setMark('D');

	return m;
}