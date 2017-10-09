#pragma once

#include <vector>
#include "gameTiles.h"


class courseGenerator
{
public: 
	// Total tiles this course
	int courseLimit;
	// Size of one side of grid, total number of grid elements, centre grid element
	int gridLength, gridSize, centre;
	// Position of newest tile to be placed, and last tile placed
	int curTilePos, lastTilePos;
	// Tracks grid elements' status (taken or empty)
	// int array[gridSize] - need to know gridSize to create this
	std::vector<int> gridElements;
	// To hold game tiles
	std::vector<Tile> gameTiles;
	// Holds potential tiles for curTilePos
	std::vector<Tile> potentialTiles;
	// Need a sense of direction!
	Direction dir; // Set to down in constructor
	
	courseGenerator(int difficulty);
	~courseGenerator() {};

	void CheckForStraights();
	Tile CheckForCorners();

	Tile placeTile();

	void run();
};