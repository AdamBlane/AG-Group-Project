#include "courseGenerator.h"
#include <stdlib.h>
#include <time.h>


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
	curTilePos = start.findNextTilePos(gridLength, dir);
	
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
void courseGenerator::CheckForCorners()
{
	// Up
	if (dir.going_up)
	{
		// Up to the left
		int checkPosL = curTilePos - 1;
		int Lstatus = gridElements.at(checkPosL);
		if (Lstatus == 0)
		{
			// Up & left grid element is free; add potential tile
			CornerTile_TR cornerTR;
			potentialTiles.push_back(cornerTR);
		}
		// Up to the right
		int checkPosR = curTilePos + 1;
		int Rstatus = gridElements.at(checkPosR);
		if (Rstatus == 0)
		{
			// Up & right grid element is free; add potential tile
			CornerTile_TL cornerTL;
			potentialTiles.push_back(cornerTL);
		}
	}
	// Down
	if (dir.going_down)
	{
		// Down to the left
		int checkPosL = curTilePos - 1;
		int Lstatus = gridElements.at(checkPosL);
		if (Lstatus == 0)
		{
			// Down & left grid element is free; add potential tile
			CornerTile_TR cornerBR;
			potentialTiles.push_back(cornerBR);
		}
		// Down to the right
		int checkPosR = curTilePos + 1;
		int Rstatus = gridElements.at(checkPosR);
		if (Rstatus == 0)
		{
			// Down & right grid element is free; add potential tile
			CornerTile_TL cornerBL;
			potentialTiles.push_back(cornerBL);
		}
	}
	// Left
	if (dir.going_left)
	{
		// Left and Up
		int checkPosL = curTilePos - gridLength;
		int Lstatus = gridElements.at(checkPosL);
		if (Lstatus == 0)
		{
			// Left & up grid element is free; add potential tile
			CornerTile_TR cornerBL;
			potentialTiles.push_back(cornerBL);
		}
		// Left & down
		int checkPosR = curTilePos + gridLength;
		int Rstatus = gridElements.at(checkPosR);
		if (Rstatus == 0)
		{
			// Up & right grid element is free; add potential tile
			CornerTile_TL cornerTL;
			potentialTiles.push_back(cornerTL);
		}
	}
	// Right
	if (dir.going_right)
	{
		// Right and Up
		int checkPosL = curTilePos - gridLength;
		int Lstatus = gridElements.at(checkPosL);
		if (Lstatus == 0)
		{
			// Right & up grid element is free; add potential tile
			CornerTile_TR cornerBR;
			potentialTiles.push_back(cornerBR);
		}
		// Right & down
		int checkPosR = curTilePos + gridLength;
		int Rstatus = gridElements.at(checkPosR);
		if (Rstatus == 0)
		{
			// Up & right grid element is free; add potential tile
			CornerTile_TL cornerTR;
			potentialTiles.push_back(cornerTR);
		}
	}
}


// Checks for available tile types, returns a random tile
void courseGenerator::placeTile()
{
	// Clear potential tiles list from any previous iterations
	potentialTiles.clear();

	// Check for straights, adds any potential straights to possibles list
	CheckForStraights();
	// Check for corners
	CheckForCorners();

	// All potentials added, pick one randomly
	// Initalise random seed
	srand(time(NULL));
	// Number of potentials
	int num = (int)potentialTiles.size();
	// Randomly choose 1 
	int choice = (rand() % num + 1) - 1; // -1 since starting at 1 & using list.size()
	 // Setup tile
	Tile* chosenTile = &potentialTiles.at(choice);
	// It takes the currently looked at position
	chosenTile->setPos(curTilePos);
	// Update grid elements tracker for this position
	gridElements.at(curTilePos) = 1;
	// Update last before overwriting current positions
	lastTilePos = curTilePos;
	// Now tell it to find us the next pos
	curTilePos = chosenTile->findNextTilePos(gridLength, dir);
	// Add to list
	gameTiles.push_back(*chosenTile);
	

}


// Main algorithm function
void courseGenerator::run()
{
	// Until course is built...
	while (gameTiles.size() < courseLimit) // add -1 here to stop just before end is reached, place end manually after?
	{
		// curTilePos is the current grid elemnt to be filled
		// Place a new random tile type in current position
		placeTile();
		// Set direction after last tile placed
		dir.setDir(curTilePos, lastTilePos, gridLength);
		
	}


}
