# Battleship
A game of battleship

This game of battleship will use a total of 7 classes:
  1. Tile, which acts as a single "space" on the board. It mainly knows how to keeps a character representing what ship (if any)
     occupies it, as well how to change itself to either an 'X' for a hit or a ' ' for a miss as a player fires on it.
  2. Matrix, which is basically a 2D vector of tiles, and a collection of ships. It's main responsibility is to keep track 
     of what ships it contains, as well as allowing smaller matrices to paste themselves onto a larger matrix.
  3. Ship, which acts as a base class for all following classes. It stores a number of basic member variables for all ships, as well
     as a function to tell if a derived class object has been sunk. In addition, ship has a couple of virtual functions that are ONLY
     implemented in derived classes: goodSet to make sure that ships do not overlap, and shipShape, returning a matrix with any kind of
     ship inside, which can then be pasted onto a larger matrix.
  4. Raft, which occupies one tile, makes no hits, but can double all hits made by other ships.
  5. Battleship, which occupies five tiles in a line, and can make 1 hit per turn.
  6. Boomerang, which occupies 5 tiles forming the shape of a boomerang, and can make 1 hit per turn.
  7. Donut, which occupies a 3x3 square of tiles (minus the center), and makes 2 hits per turn.
  
For a typical game, each player will start will a 10x10 matrix containing one of each ship. Tiles occupied by a Raft will be marked with
an 'R', Battleship with a 'B', Boomerang with an 'O', and Donut with a 'D'. 
  
For specifics on classes tile and matrix, see the Tiles_and_Matrices h and cpp files.
For specifics o all other classes, see the Ships h and cpp files.

  Other than that, the game is simple: you must guess tiles to hit until your opponent's fleet has been sunk,
and your opponent will do the same. The opponent will guess tiles at random, and if you, while using this program, want a challenge, doing
the same thing is recommended. 

  Each player starts with 8 hits to make; to make a single hit, enter in a pair of numbers between 0 and 9 inclusive when prompted. 
Acceptable formats include (x, y), x, y, or simly x y. On the other hand, xy will likely be confused with a number > 9; 
re-entering numbers to replace such ones is not allowed, so enter your numbers carefully. 
As long as each number is separated by something, such as a space or a comma, entering coordinates should go smoothly. 
  Just as a friendly PSA, be sure to enter twice as many numbers as you have hits to make. If you enter too few numbers, 
you will be prompted again to enter more; if for whatever reason you stopped half-way through entering a set of coordinates 
(i.e. you gave an x value without a y value), be sure to continue by first completing whatever coordinate you were in the process of 
entering. If you enter too many numbers, the excess ones will be used for the next round. 
For example, if your guesses will not be effected on a round-by-round basis, you may enter
enough coordinates to go through 3 rounds (24 coordinates in total, assuming no ship sinks) without stopping.

  Finally, the game will end when one player has no ships left; the other player automatically wins.
As of now, there is a mercy rule in place: if a player has only their raft remaining, that player can no longer make any hits, so the
other player wins by default.
