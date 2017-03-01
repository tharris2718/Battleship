#include <ctime>
#include <cstdlib>
#include "Ships.h"

using namespace std;

//ship constructor; only to be used by child classes 
ship::ship(unsigned int h, const unsigned int m) : numHits(h), multiplier(m) {}

//class raft

//constructor
raft::raft() : base(0, 2) {}



//class battleship

//constructor
battleship::battleship() : base(2, 2) {}