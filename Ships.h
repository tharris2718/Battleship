/*
  This header file will define the multitude of ship classes:
    1. ship: purely virtual; all other ship classes will inherit from it
	2. raft: inherits from ship; it only takes up one water tile, and cannot fire. However, while it is alive, it will double they
	   number of hits that other ships in the fleet can make.
	3. battleship: inherits from raft; it will occupy five water tiles in a line. The battleship acts as a flagship; while losing it
	   will not cause the player to lose the game, not having a battleship will cut the player's number of hits in half.
	   Last of all, the battleship can fire twice per turn.
	4. boomerang: inherits from ship; it will make the shape of two full edges of a square (like an L); both boomerang and donut
	   will not multiply the number of available hits the player can make. A boomerang can make 2 hits per turn.
	5. donut: inherits from ship; it will be shaped like a 3x3 square with a hole in the middle. A donut can make 3 hits per turn.
*/

#ifndef __SHIP__
#define __SHIP__

#include <ctime>
#include <cstdlib>
#include "Tiles_and_Matrices.h"

srand(time(nullptr));

/*
  The ship class will be purely virtual. It will have functions declarations to determine what kind of shape it should have.
*/
class ship{
private:
public:
	//the determine shape function will return a matrix that will show 

};

#endif