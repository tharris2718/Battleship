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
//declare the class ship so that the fleet member variable of matrix knows that it exists
class ship;

#ifndef __TILE_MATRIX__
#define __TILE_MATRIX__

#include <vector>
#include <exception>
#include <iostream>

/*
  Here is the declaration of class tile. It will store only a char member variable and ways to change that char, as well as a return
  function for that char.
*/
class tile{
private:
	char marker;

public:
	//default constructor
	tile();

	//copy constructor just in case
	tile(const tile&);

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

	//the actual board, storing a pointer to a 2D array of tiles
	std::vector<tile*> board;

	//fleet should speak for itself
	/*
	  not sure, but I heard from a past TA that #include'ing h files into eachother can cause problems;
	  will attempt to avoid this by templating fleet, then specifying it as a vector<ship*> whenever possible
	  PS: I may not end up templating this
	*/
	std::vector<ship*> fleet;
public:
	//"default" constructor; default constructs a square number of tiles (depending on input)
	matrix(const int);

	//the real default constructor, for emergency cases
	matrix();

	//copy constructor
	matrix(const matrix&);

	/*
	  copy constructor of sorts; it really pastes a smaller matrix into a larger one
	  the first arg is the matrix to be copied off of; generally, a ship's child's
	  shipShape function

	  args 2 and 3 are the first column of the parent matrix to copy, and delta x
	  args 4 and 5 are the first row of the parent matrix to copy, and delta y
	*/
	void pasteShip(matrix&, int, int, int, int);

	//function coordinates: takes in two ints (x coord, then y coord)
	//and returns the tile at that space
	//fyi, this function only exists because matrix implementations in the cpp files have trouble accessing the board
	tile& coordinates(int x, int y){
		//std::cout << "Checking coordinates " << x << ", " << y << std::endl;

		if (x < board.size() || y < board.size())
			return *(board[y] + x);

		else
			throw std::exception("Improper bounds on matrix coordinates.");
	}

	//display does what you'd think: displays everything to the console
	void display() const;

	//adds a ship to the fleet
	void addShip(ship*);

	//subscript operator; returns ship at the index of fleet specified
	ship* operator[](int);

	//removes a ship from the fleet
	void removeShip(ship*);

	//matrix destructor; destroys the fleet remaining 
	~matrix();
};

#endif