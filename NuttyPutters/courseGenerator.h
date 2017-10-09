#pragma once

#include <vector>
#include "gameTiles.h"


class courseGenerator
{
public: 
	// Total tiles this course
	int courseLimit;
	// Size of one side of grid, & rotal number of grid elements
	int gridLength, gridSize;
	// Position of newest tile to be placed, and last tile placed
	int curTilePos, lastTilePos;
	// Tracks grid elements' status (taken or empty)
	// int array[gridSize] - need to know gridSize to create this
	std::vector<int> gridElements;
	// To hold game tiles
	std::vector<Tile> gameTiles;

	// Need a sense of direction!
	Direction dir;
	
	courseGenerator(int difficulty);
	~courseGenerator() {};

	void run();
};