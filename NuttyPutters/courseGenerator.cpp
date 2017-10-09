#include "courseGenerator.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Constructor - setup based on given number of course game tiles
courseGenerator::courseGenerator(int difficulty)
{
	
	// Take in difficulty for this game
	courseLimit = difficulty;
	cout << "Course Gen Constructor called, difficulty: " << courseLimit << endl;

	// Set grid values
	// -1 makes odd number, allows for central tile
	gridLength = (courseLimit * 2) - 1;
	// Number of elements in grid
	gridSize = gridLength * gridLength;
	// Save centre tile position
	centre = (int)ceil(gridSize / 2) + 1;
	cout << "Grid Length: " << gridLength << " Size: " << gridSize << " Centre: " << centre << endl;

	cout << "Grid Elements List: ";
	// Setup grid elements list
	for (int i = 0; i < gridSize; ++i)
	{
		// Since start tile is in centre, 
		if (i == centre-1)
		{
			// put 1 for taken
			gridElements.push_back(1);
			cout << "1, ";
		}
		else
		{
			// All others start as empty
			gridElements.push_back(0);
			cout << "0, ";
		}
	}
	cout << ". " << endl;

	// Place start tile in centre first
	StartTile start;
	start.setPos(centre);
	cout << "Start tile position: " << start.getPos() << endl;
	// That's the last tile placed once alg starts
	lastTilePos = centre;

	// Ask start for next tile pos
	curTilePos = start.findNextTilePos(gridLength, dir);
	cout << "Last Tile: " << lastTilePos << "Cur tile pos: " << curTilePos << endl;

	// Finally, add start tile to gameTiles list
	gameTiles.push_back(start);
	cout << "Game tiles list size: " << (int)gameTiles.size() << endl;
}

// Used in placeTile, checks for potential straight tiles
void courseGenerator::CheckForStraights()
{
	cout << "Checking for straights..." << endl;
	// Based on direction
	// Up
	if (dir.going_up)
	{
		// Check if pos above this in grid is taken
		int checkPos = curTilePos - gridLength;
		// Work if in range
		if (checkPos < gridSize && checkPos > 0)
		{
			int status = gridElements.at(checkPos);
			if (status == 0)
			{
				// Grid element is free, create a tile 
				StraightTile_V straightV;
				// Set pos, find next pos
				straightV.setPos(curTilePos);
				straightV.findNextTilePos(gridLength, dir);
				// Add to potentials list
				potentialTiles.push_back(straightV);
				cout << "Straight_V going up potential" << endl;
			}
		}

	}
	// Down
	if (dir.going_down)
	{
		int checkPos = curTilePos + gridLength;
		// Work if in range
		if (checkPos < gridSize && checkPos > 0)
		{
			int status = gridElements.at(checkPos);
			if (status == 0)
			{
				// Grid element is free, create a tile
				StraightTile_V straightV;
				// Set pos, find next pos
				straightV.setPos(curTilePos);
				straightV.findNextTilePos(gridLength, dir);
				// Add to potentials list
				potentialTiles.push_back(straightV);
				cout << "Straight_V going down potential" << endl;
			}
		}

	}
	// Right
	if (dir.going_right)
	{
		int checkPos = curTilePos + 1;
		// Work if in range
		if (checkPos < gridSize && checkPos > 0)
		{
			int status = gridElements.at(checkPos);
			if (status == 0)
			{
				// Grid element is free, create a tile
				StraightTile_H straightH;
				// Set pos, find next pos
				straightH.setPos(curTilePos);
				straightH.findNextTilePos(gridLength, dir);
				// Add to potentials list
				potentialTiles.push_back(straightH);
				cout << "Straight_H going right potential" << endl;
			}
		}

	}
	// Left
	if (dir.going_left)
	{
		int checkPos = curTilePos - 1;
		// Work if in range
		if (checkPos < gridSize && checkPos > 0)
		{
			int status = gridElements.at(checkPos);
			if (status == 0)
			{
				// Grid element is free, create a tile
				StraightTile_H straightH;
				// Set pos, find next pos
				straightH.setPos(curTilePos);
				straightH.findNextTilePos(gridLength, dir);
				// Add to potentials list
				potentialTiles.push_back(straightH);
				cout << "Straight_H going left potential" << endl;
			}
		}

	}

}

// Check for all potential corners
void courseGenerator::CheckForCorners()
{
	cout << "Checking for corners..." << endl;
	// Up
	if (dir.going_up)
	{
		// Up to the left
		int checkPosL = curTilePos - 1;
		// Work if in range
		if (checkPosL < gridSize && checkPosL > 0)
		{
			int Lstatus = gridElements.at(checkPosL);
			if (Lstatus == 0)
			{
				// Up & left grid element is free; add potential tile
				CornerTile_TR cornerTR;
				// Set positions
				cornerTR.setPos(curTilePos);
				cornerTR.findNextTilePos(gridLength, dir);
				potentialTiles.push_back(cornerTR);
				cout << "Corner_TR going up and left potential" << endl;
			}
		}

		// Up to the right
		int checkPosR = curTilePos + 1;
		if (checkPosR < gridSize && checkPosR > 0)
		{
			int Rstatus = gridElements.at(checkPosR);
			if (Rstatus == 0)
			{
				// Up & right grid element is free; add potential tile
				CornerTile_TL cornerTL;
				// Set positions
				cornerTL.setPos(curTilePos);
				cornerTL.findNextTilePos(gridLength, dir);
				potentialTiles.push_back(cornerTL);
				cout << "Corner_TL going up and right potential" << endl;
			}

		}
	}
	// Down
	if (dir.going_down)
	{
		// Down to the left
		int checkPosL = curTilePos - 1;
		if (checkPosL < gridSize && checkPosL > 0)
		{
			int Lstatus = gridElements.at(checkPosL);
			if (Lstatus == 0)
			{
				// Down & left grid element is free; add potential tile
				CornerTile_BR cornerBR;
				// Set positions
				cornerBR.setPos(curTilePos);
				cornerBR.findNextTilePos(gridLength, dir);
				potentialTiles.push_back(cornerBR);
				cout << "Corner_BR going down and left potential" << endl;
			}
		}

		// Down to the right
		int checkPosR = curTilePos + 1;
		if (checkPosR < gridSize && checkPosR > 0)
		{
			int Rstatus = gridElements.at(checkPosR);
			if (Rstatus == 0)
			{
				// Down & right grid element is free; add potential tile
				CornerTile_BL cornerBL;
				// Set positions
				cornerBL.setPos(curTilePos);
				cornerBL.findNextTilePos(gridLength, dir);
				potentialTiles.push_back(cornerBL);
				cout << "Corner_BL going down and right potential" << endl;
			}
		}

	}
	// Left
	if (dir.going_left)
	{
		// Left and Up
		int checkPosL = curTilePos - gridLength;
		if (checkPosL < gridSize && checkPosL > 0)
		{
			int Lstatus = gridElements.at(checkPosL);
			if (Lstatus == 0)
			{
				// Left & up grid element is free; add potential tile
				CornerTile_BL cornerBL;
				// Set positions
				cornerBL.setPos(curTilePos);
				cornerBL.findNextTilePos(gridLength, dir);
				potentialTiles.push_back(cornerBL);
				cout << "Corner_BL going left and up potential" << endl;
			}
		}

		// Left & down
		int checkPosR = curTilePos + gridLength;
		if (checkPosR < gridSize && checkPosR > 0)
		{
			int Rstatus = gridElements.at(checkPosR);
			if (Rstatus == 0)
			{
				// Up & right grid element is free; add potential tile
				CornerTile_TL cornerTL;
				// Set positions
				cornerTL.setPos(curTilePos);
				cornerTL.findNextTilePos(gridLength, dir);
				potentialTiles.push_back(cornerTL);
				cout << "Corner_TL going up and right potential" << endl;
			}
		}

	}
	// Right
	if (dir.going_right)
	{
		// Right and Up
		int checkPosL = curTilePos - gridLength;
		if (checkPosL < gridSize && checkPosL > 0)
		{
			int Lstatus = gridElements.at(checkPosL);
			if (Lstatus == 0)
			{
				// Right & up grid element is free; add potential tile
				CornerTile_BR cornerBR;
				// Set positions
				cornerBR.setPos(curTilePos);
				cornerBR.findNextTilePos(gridLength, dir);
				potentialTiles.push_back(cornerBR);
				cout << "Corner_BR going right and up potential" << endl;
			}
		}

		// Right & down
		int checkPosR = curTilePos + gridLength;
		if (checkPosR < gridSize && checkPosR > 0)
		{
			int Rstatus = gridElements.at(checkPosR);
			if (Rstatus == 0)
			{
				// Right & down grid element is free; add potential tile
				CornerTile_TR cornerTR;
				// Set positions
				cornerTR.setPos(curTilePos);
				cornerTR.findNextTilePos(gridLength, dir);
				potentialTiles.push_back(cornerTR);
				cout << "Corner_TR going right and down potential" << endl;
			}
		}

	}
}


// Randomly decides which tile to place, based on all potential tile types
void courseGenerator::placeTile()
{
	cout << "Placing tile..." << endl;
	// Check for straights, adds any potential straights to possibles list
	CheckForStraights();
	// Check for corners, add any potentials to list
	CheckForCorners();
	
	// All potentials added, pick one randomly
	cout << "All potentials added, list size: " << (int)potentialTiles.size() << endl;

	// Randomly choose 1 
	auto millis = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	default_random_engine rng(static_cast<unsigned int>(millis.count()));
	uniform_int_distribution<int> distribution(0, (int)potentialTiles.size() - 1);
	int choice = distribution(rng);
	cout << "Random choice is number " << choice << endl;

	// Add to back of game tiles list
	if ((int)potentialTiles.size() < 1)
	{
		cout << "Problem" << endl;
	}
	gameTiles.push_back(potentialTiles.at(choice));			
	cout << "Added to game Tiles, new size: " << (int)gameTiles.size() << endl;
	// Update grid elements tracker for this position								 
	gridElements.at(curTilePos - 1) = 1;
	cout << "Updated entry in grid Elements at " << curTilePos << " to " << gridElements.at(curTilePos -1) << endl;
	// Update last pos before overwriting current positions
	lastTilePos = curTilePos;
	cout << "Last tile pos updated to " << lastTilePos << endl;
	// Get new curPos from last tile just placed
	curTilePos = gameTiles.back().getNextPos();
	cout << "New tile pos is " << curTilePos << endl;
	// Clear potential tiles list for next iteration
	potentialTiles.clear();
	cout << "Potentials cleared, size now : " << (int)potentialTiles.size() << endl;
}


// Main algorithm function
void courseGenerator::run()
{
	cout << "Starting algorithm loop..." << endl;
	// Until course is built...
	while ((int)gameTiles.size() < courseLimit - 1) // add -1 here to stop just before end is reached, place end manually after?
	{
		cout << "Algorithm loop iteration " << (int)gameTiles.size() << endl;
		// curTilePos is the current grid elemnt to be filled
		// Place a new random tile type in current position
		placeTile();
		// Set direction after last tile placed
		dir.setDir(curTilePos, lastTilePos, gridLength);
		cout << "Alg loop end, game tiles at " << (int)gameTiles.size() << endl;
	}

	// Add End tile manually here
}
