#include "courseGenerator.h"

// Setup 
courseGenerator::courseGenerator(int difficulty)
{
	// Take in difficulty for this game
	courseLimit = difficulty;
	// Set grid values
	// -1 makes odd number, allows for central tile
	gridLength = (courseLimit * 2) - 1;
	gridSize = gridLength * gridLength;
	// Save centre tile position
	centre = (int)ceil(gridSize / 2);
	// Setup grid elements list
	for (int i = 0; i < gridSize; ++i)
	{
		if (i == centre)
			gridElements.push_back(1);
		else
			gridElements.push_back(0);
	}

	// Place start tile in centre first
	StartTile start;
	start.setPos(centre);

	// That's the last tile placed once alg starts
	lastTilePos = centre;

	// Ask start for next tile pos
	curTilePos = start.findNextTilePos(gridLength);
	
	// Finally, add start tile to gameTiles list
	gameTiles.push_back(start);
	
}

// Used in placeTile, checks for potential straight tiles
void courseGenerator::CheckForStraights()
{
	// Based on direction
	// Up
	if (dir.going_up)
	{
		// Check if pos above this in grid is taken
		int checkPos = curTilePos - gridLength;
		int status = gridElements.at(checkPos);
		if (status == 0)
		{
			// Grid element is free, create a tile 
			StraightTile_V straightV;
			// Add to potentials list
			potentialTiles.push_back(straightV);

		}
		else if (status == 1)
		{
			// Grid element is taken, do nothing
		}
	}
	// Down
	if (dir.going_down)
	{
		int checkPos = curTilePos + gridLength;
		int status = gridElements.at(checkPos);
		if (status == 0)
		{
			// Grid element is free, create a tile
			StraightTile_V straightV;
			// Add to potentials list
			potentialTiles.push_back(straightV);

		}
		else if (status == 1)
		{
			// Grid element is taken, do nothing
		}
	}
	// Right
	if (dir.going_right)
	{
		int checkPos = curTilePos + 1;
		int status = gridElements.at(checkPos);
		if (status == 0)
		{
			// Grid element is free, create a tile
			StraightTile_H straightH;
			// Add to potentials list
			potentialTiles.push_back(straightH);

		}
		else if (status == 1)
		{
			// Grid element is taken, do nothing
		}
	}
	// Left
	if (dir.going_left)
	{
		int checkPos = curTilePos - 1;
		int status = gridElements.at(checkPos);
		if (status == 0)
		{
			// Grid element is free, create a tile
			StraightTile_H straightH;
			// Add to potentials list
			potentialTiles.push_back(straightH);

		}
		else if (status == 1)
		{
			// Grid element is taken, do nothing
		}
	}


}

// Check for all potential corners
Tile courseGenerator::CheckForCorners()
{
	return Tile();
}

// Checks for available tile types, returns a random tile
Tile courseGenerator::placeTile()
{
	// Check for straights, adds any potential straights to possibles list
	CheckForStraights();
	// Check for corners



	return Tile();
}

// Main algorithm function
void courseGenerator::run()
{
	// Until course is built...
	while (gameTiles.size() < courseLimit) // add -1 here to stop just before end is reached, place end manually after?
	{
		// curTilePos is the current grid elemnt to be filled
		// Place a new random tile type in current position

	}


}
