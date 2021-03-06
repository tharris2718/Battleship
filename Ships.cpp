#include "Ships.h"
#include <iostream>

using namespace std;

//shipShape for ship; not meant to be used...ever
matrix ship::shipShape(){
	cout << "Ship's shipShape function called. Oops!\n";
	return matrix(0);
}

bool ship::goodSet(matrix& m, int a, int b){
	cout << "Ship's goodSet function called. Oops!\n";
	return false;
}

//occupySpace function
void ship::occupySpace(int x, int y){
	spacesOccupied.push_back(x);
	spacesOccupied.push_back(y);
}

//takeHit function
void ship::takeHit(){
	++hitsTaken;
}

//sunk function
bool ship::sunk() const{
	if (hitsTaken < stamina)
		return false;

	else if (hitsTaken == stamina)
		return true;

	else if (hitsTaken > stamina){
		cout << "A ship has taken more hits than it is able to. How?\n";
		return true;
	}
}

//ship default constructor
ship::ship() : numHits(0), multiplier(0), stamina (1), hitsTaken(0) {}

//ship constructor; only to be used by child classes 
ship::ship(int h, int m, int s) : numHits(h), multiplier(m), stamina(s), hitsTaken(0) {}

//class raft

//constructor
raft::raft() : base(0, 2, 1) {}

//returns a 1x1 matrix with an 'R' in the middle
matrix raft::shipShape(){
	matrix m(1);
	m.coordinates(0, 0).setMark('R');

	return m;
}

bool raft::goodSet(matrix& m, int startX, int startY){
	if (m.coordinates(startX, startY).getMark() == '-')
		return true;

	else
		return false;
}



//class battleship

//constructor
battleship::battleship() : base(1, 1, 5) {}

//returns a 5x5 matrix with 'B's lining a random row or column
matrix battleship::shipShape(){
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

//looks through 5 rows and 5 columns after (startX, startY, looking for occupied tiles
bool battleship::goodSet(matrix& m, int startX, int startY){
	bool returnable = true;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; i < 5; ++i)
			if (m.coordinates(startX + i, startY + j).getMark() != '-')
				returnable = false;

	//at this point, the set should be good if the function made it this far
	return returnable;
}


//class boomerang

//constructor
boomerang::boomerang() : base(1, 1, 5) {}

//returns a 3x3 matrix with a random corner and the two sides touching housing the ship
matrix boomerang::shipShape(){
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
	m.coordinates(corner % 3, corner / 3).setMark('O');

	//first, for the horizontal filling
	//if expanding right
	if (!(corner % 3)){
		for (int i = 1; i < 3; ++i){
			m.coordinates((corner % 3) + i, corner / 3).setMark('O');
		}
	}

	//if expanding left
	else{
		for (int i = 1; i < 3; ++i){
			m.coordinates((corner % 3) - i, corner / 3).setMark('O');
		}
	}

	//now for vertical filling
	//if expanding down
	if (corner < 3){
		for (int i = 1; i < 3; ++i){
			m.coordinates(corner % 3, (corner / 3) + i).setMark('O');
		}
	}

	//if expanding up
	else{
		for (int i = 1; i < 3; ++i){
			m.coordinates(corner % 3, (corner / 3) - i).setMark('O');
		}
	}

	//now m should be ready to return
	return m;
}

bool boomerang::goodSet(matrix& m, int startX, int startY){
	bool returnable = true;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (m.coordinates(i + startX, j + startY).getMark() != '-')
				returnable = false;

	return returnable;
}

//class donut

//constructor
donut::donut() : base(2, 1, 8) {}

//returns a 3x3 matrix with all spaces except the middle set to 'D'
matrix donut::shipShape(){
	matrix m(3);

	//for all values of i except 4 (the middle), set the current tile to 'D'
	for (int i = 0; i < 9; ++i)
		if (i != 4)
			m.coordinates(i % 3, i / 3).setMark('D');

	return m;
}

bool donut::goodSet(matrix& m, int startX, int startY){
	bool returnable = true;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (m.coordinates(startX + i,startY + j).getMark() != '-')
				returnable =  false;

	return returnable;
}