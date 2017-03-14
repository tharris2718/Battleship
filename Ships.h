/*
  This header file will define the multitude of ship classes:
    1. ship: all other ship classes will inherit from it; not meant to be constructed
	2. raft: inherits from ship; it only takes up one water tile, and cannot fire. However, while it is alive, it will double they
	   number of hits that other ships in the fleet can make.
	3. battleship: inherits from ship; it will occupy five water tiles in a line. The battleship acts as a flagship; while losing it
	   will not cause the player to lose the game, not having a battleship will cut the player's number of hits in half.
	   Last of all, the battleship can fire twice per turn.
	4. boomerang: inherits from ship; it will make the shape of two full edges of a square (like an L); both boomerang and donut
	   will not multiply the number of available hits the player can make. A boomerang can make 2 hits per turn.
	5. donut: inherits from ship; it will be shaped like a 3x3 square with a hole in the middle. A donut can make 3 hits per turn.
*/

#ifndef __SHIP__
#define __SHIP__

#include "Tiles_and_Matrices.h"

//the ship class
class ship{

private:
	//stores the number of hits
	int numHits;
	//for rafts and battleships, multiplier will be set to 2; for others, 1
	int multiplier;

	//keeps track of exactly what tiles a ship occupies on any given board
	//when all tiles have mark 'X', the ship will know it's dead
	std::vector<tile> spacesOccupied;

public:
	/*
	  the determine shape function will return a matrix that will show the shape of the ship
	  does not return a matrix& because a stack matrix will be created inside, and will perish once the function is over
	*/
	virtual matrix shipShape();

	//adds the tile provided to spacesOccupied
	void occupySpace(tile);

	//returns true if all tiles in spacesOccupied have mark 'X', or false otherwise
	bool sunk() const;

	//goodSet will take in a matrix to check, a starting xvalue, and a starting y value, and check if the spaces may be occupied
	virtual bool goodSet(matrix&, int, int);

	//default constructor: just sets both params to 0
	ship();

	//first arg will be the number of hits the ship can make; second will be the multiplier
	ship(int, int);

	int getHits() const { return numHits; }
	int getMult() const { return multiplier; }
};

//the raft class
class raft : public ship{
private:
	ship base;
public:
	//will return a 1x1 matrix with an 'R' in the middle
	virtual matrix shipShape();

	virtual bool goodSet(matrix&, int, int);

	//will have a ship base object, but that's about it
	raft();
	raft(const raft&) = delete;
};

//the battleship class
class battleship : public ship{
private:
	ship base;
public:
	//will return a 5x5 matrix with the battleship in a random row OR column
	virtual matrix shipShape();

	virtual bool goodSet(matrix&, int, int);

	//similar to raft's default constructor
	battleship();
	battleship(const battleship&) = delete;
};

//the boomerang class
class boomerang : public ship{
private:
	ship base;
public:
	//will return a 3x3 matrix, with the boomerang in a random corner and extending 2 tiles in either direction
	virtual matrix shipShape();

	virtual bool goodSet(matrix&, int, int);

	//similar to raft's default constructor
	boomerang();
	boomerang(const boomerang&) = delete;
};

//the donut class
class donut : public ship{
private:
	ship base;
public:
	//will return a 3x3 matrix, with the donut taking up every tile except the middle one
	virtual matrix shipShape();

	virtual bool goodSet(matrix&, int, int);

	//similar to raft's default constructor
	donut();
	donut(const donut&) = delete;
};

#endif