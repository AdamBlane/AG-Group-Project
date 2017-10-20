#pragma once

#include <vector>
#include <map>
// Definitions for all game tiles and direction classes
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
	// Tracks grid elements' status (taken as 1 or empty as 0)
	std::vector<int> gridElements;
	// To hold game tiles for this course
	std::vector<BaseTile> gameTiles;
	// Holds potential tiles for the current tile pos being looked at
	std::vector<BaseTile> potentialTiles;
	// Need a sense of direction!
	// Set to down in constructor
	Direction dir;
	
	courseGenerator(int difficulty);
	~courseGenerator() {};

	void CheckForStraights();
	void CheckForCorners();
	void placeTile();
	
	vector<BaseTile> run();
};