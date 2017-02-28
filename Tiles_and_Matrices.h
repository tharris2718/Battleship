/*
  This header file will hold declarations and explanations for classes
  water tile and matrix:
    1. Class waterTile will be the building block of the "board" of the game;
	   It will be set to a specific character depending on it's status. All tiles will show an '-' by default,
	   signifying that nothing is there. As the user's ships occupy tiles, the character will change: 'B' for Battleship,
	   'O' for Boomerang, 'R' for Raft, and 'D' for doughnut/donut. In addition, tiles occupied by the opponent's (computer's) ships
	   will not be shown, only '-' for unknown or 'M' if the user fired on that space but failed to hit anything. The user's tiles
	   will also display a 'M' if the computer fired on that tile but failed to hit anything. Lastly, a tile will display an 'X'
	   if a ship occupies that tile and has been hit.

	2. Class matrix will be a 2D vector of tiles; though different board sizes and accompanying fleet sizes may be added, the matrix
	   will be a 10x10 board by default. The player will have 2: one to display their fleet, and another to display the hits/misses
	   they scored on the opponent. Though it will not be shown, the opponent will have a matrix of it's own to make sure that it
	   does not fire on a tile that it has already chosen.
*/
#ifndef __TILE_MATRIX__
#define __TILE_MATRIX__

#include <vector>
#include "Ships.h"

/*
  Here is the declaration of class tile. It will store only a char member variable and ways to change that char, as well as a return
  function for that char.
*/
class tile{
private:
	char marker;

public:
	//only a default constructor will be provided; every tile should start with a '-' on it
	tile() : marker('-') {}
	tile(const tile&) = delete;

	//this function will be called when either player fires on it
	//it will change the marker appropriately and return true for a hit, or false for a miss
	bool recieveHit();

	//this function will set the marker to something else; it will be used when the matrix places ships, and to show hits on the
	//opponent by the user
	void setMark(char);

	//returns the marker
	char getMark() const;
};

/*
  Here is the declaration of the class matrix. It will take in a vector of ships for the player's fleet, and it will make its
  own double vector of tiles. In addition, the matrix will handle placing ships, and will delete ships from its vector as they 
  are sunk.
*/
class matrix{
private:

};

#endif