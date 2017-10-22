#include "courseGenV2.h"
#include <random>
#include <chrono>
#include <algorithm>


using namespace std::chrono;

// Course Gen constructor
courseGenV2::courseGenV2(int difficulty)
{
	// Set tile size
	tileSize = 10;

	// Difficulty = number of tiles this course
	courseLimit = difficulty;

	// Create start tile
	StartTile start;

	// Get direction
	dir = start.outDir;

	// Update curCoords tracker
	curTileCoords = start.nextCoords;

	// Add it to game tiles list
	gameTiles.push_back(start);
}

// Main algorithm loop
vector<BaseTile> courseGenV2::run()
{
	// Until course is built...
	// -1 since end tile will be added afterwards
	while ((int)gameTiles.size() < courseLimit - 1)
	{
		PlaceTile();
	}

	// Add end tile manually
	EndTile end;
	end.SetCoords(curTileCoords);
	end.outDir = dir;
	gameTiles.push_back(end);

	// Write seed to file
	ofstream results("results.csv", ofstream::app);
	for (auto &t : gameTiles)
		results << t.id;

	results << endl;


	return gameTiles;
}


void courseGenV2::PlaceTile()
{
	// Search for available tiles
	CheckStraights();
	CheckCorners();

	// Create random engine 	
	default_random_engine rng(random_device{}());
	uniform_int_distribution<int> distribution(0, (int)potentialTiles.size() - 1);
	int choice = distribution(rng);
	// Shuffle potentials list to add yet more randomness!
	random_shuffle(potentialTiles.begin(), potentialTiles.end());

	// Add random choice to game tiles
	gameTiles.push_back(potentialTiles.at(choice));

	// Update current tile position tracker
	curTileCoords = gameTiles.back().GetNextCoords();

	// Update direction for placement of next tile
	dir = gameTiles.back().outDir;

	// Clear potential tiles for next iteration
	potentialTiles.clear();
}

// Adds any available straight tiles to potentials list
void courseGenV2::CheckStraights()
{
	// Must check following tile is free to allow straight (can't lead to dead end)
	// Differences in position between current and next tile
	int zDiff = 0;
	int xDiff = 0;
	bool vertical;
	// Based on direction
	if (dir.going_up)
	{
		zDiff = -tileSize;
		vertical = true;
	}
	else if (dir.going_down)
	{
		zDiff = tileSize;
		vertical = true;
	}
	else if (dir.going_left)
	{
		xDiff = -tileSize;
		vertical = false;
	}
	else if (dir.going_right)
	{
		xDiff = tileSize;
		vertical = false;
	}
	// Up/Down is true
	if (vertical)
	{
		// Find following tile position
		vec3 followingPos = vec3(curTileCoords.x, curTileCoords.y, curTileCoords.z + zDiff);
		// If this pos is free, can add straight
		if (!tilePosTaken(followingPos))
		{
			StraightTile_V straightV;
			// Set position and next tile pos
			straightV.SetCoords(curTileCoords);
			straightV.SetNextCoords(followingPos);
			// Set out direction
			if (dir.going_up)
			{
				// Continue going up
				straightV.outDir.going_up = true;
			}
			else if (dir.going_down)
				// Continue going down
				straightV.outDir.going_down = true;
				
			// Add to list of potential next tiles
			potentialTiles.push_back(straightV);
		}
	}
	// Left/Right is true
	else
	{
		// Find following tile position
		vec3 followingPos = vec3(curTileCoords.x + xDiff, curTileCoords.y, curTileCoords.z);
		// If this pos is free, can add straight
		if (!tilePosTaken(followingPos))
		{
			StraightTile_H straightH;
			// Set position and next tile pos
			straightH.SetCoords(curTileCoords);
			straightH.SetNextCoords(followingPos);
			// Set out direction
			if (dir.going_left)
				straightH.outDir.going_left = true;
			else if (dir.going_right)
				straightH.outDir.going_right = true;
			// Add to list of potential next tiles
			potentialTiles.push_back(straightH);
		}
	}
	// RAMP TESTING
	if (dir.going_down)
	{
		// Following is + 3.8 on y axis (arbitrary atm)
		vec3 followingPos = vec3(curTileCoords.x, curTileCoords.y + 3.8, curTileCoords.z + zDiff);
		if (!tilePosTaken(followingPos))
		{
			UpRampDown ramp;
			ramp.SetCoords(curTileCoords);
			ramp.SetNextCoords(followingPos);
			ramp.outDir.going_down = true;
			potentialTiles.push_back(ramp);
		}
	}
	if (dir.going_up)
	{
		vec3 followingPos = vec3(curTileCoords.x, curTileCoords.y - 3.8, curTileCoords.z + zDiff);
		if (!tilePosTaken(followingPos))
		{
			DownRampDown ramp;
			ramp.SetCoords(curTileCoords);
			ramp.SetNextCoords(followingPos);
			ramp.outDir.going_up = true;
			potentialTiles.push_back(ramp);
		}
	}
	
}

// Adds any available corner tiles to potentials list
void courseGenV2::CheckCorners()
{
	// Check for bottom L/R corners
	if (dir.going_down)
	{
		// Bottom Left - goes down to the right
		vec3 followingPosR = vec3(curTileCoords.x + tileSize, curTileCoords.y, curTileCoords.z);
		// If free, can add corner
		if (!tilePosTaken(followingPosR))
		{
			CornerTile_BL cornerBL;
			// Set positions
			cornerBL.SetCoords(curTileCoords);
			cornerBL.SetNextCoords(followingPosR);
			cornerBL.outDir.going_right = true;
			// Add to potentials list
			potentialTiles.push_back(cornerBL);
		}
		// Bottom right - goes down to the left
		vec3 followingPosL = vec3(curTileCoords.x - tileSize, curTileCoords.y, curTileCoords.z);
		// If free, add corner
		if (!tilePosTaken(followingPosL))
		{
			CornerTile_BR cornerBR;
			cornerBR.SetCoords(curTileCoords);
			cornerBR.SetNextCoords(followingPosL);
			cornerBR.outDir.going_left = true;
			potentialTiles.push_back(cornerBR);
		}
	}
	// Check for top L/R corners
	else if (dir.going_up)
	{
		// Top left - goes up to the right
		vec3 followingPosR = vec3(curTileCoords.x + tileSize, curTileCoords.y, curTileCoords.z);
		if (!tilePosTaken(followingPosR))
		{
			CornerTile_TL cornerTL;
			cornerTL.SetCoords(curTileCoords);
			cornerTL.SetNextCoords(followingPosR);
			cornerTL.outDir.going_right = true;
			potentialTiles.push_back(cornerTL);
		}
		// Top right - goes up to the left
		vec3 followingPosL = vec3(curTileCoords.x - tileSize, curTileCoords.y, curTileCoords.z);
		if (!tilePosTaken(followingPosL))
		{
			CornerTile_TR cornerTR;
			cornerTR.SetCoords(curTileCoords);
			cornerTR.SetNextCoords(followingPosL);
			cornerTR.outDir.going_left = true;
			potentialTiles.push_back(cornerTR);
		}
	}
	// Check for left top/bottom
	else if (dir.going_left)
	{
		// Top left - goes left and down
		vec3 followingPosD = vec3(curTileCoords.x, curTileCoords.y, curTileCoords.z + tileSize);
		if (!tilePosTaken(followingPosD))
		{
			CornerTile_TL cornerTL;
			cornerTL.SetCoords(curTileCoords);
			cornerTL.SetNextCoords(followingPosD);
			cornerTL.outDir.going_down = true;
			potentialTiles.push_back(cornerTL);
		}
		// Bottom left - goes left and up
		vec3 followingPosU = vec3(curTileCoords.x, curTileCoords.y, curTileCoords.z - tileSize);
		if (!tilePosTaken(followingPosU))
		{
			CornerTile_BL cornerBL;
			cornerBL.SetCoords(curTileCoords);
			cornerBL.SetNextCoords(followingPosU);
			cornerBL.outDir.going_up = true;
			potentialTiles.push_back(cornerBL);
		}
	}
	// Check for right top/bottom
	else if (dir.going_right)
	{
		// Top right - goes right and down
		vec3 followingPosD = vec3(curTileCoords.x, curTileCoords.y, curTileCoords.z + tileSize);
		if (!tilePosTaken(followingPosD))
		{
			CornerTile_TR cornerTR;
			cornerTR.SetCoords(curTileCoords);
			cornerTR.SetNextCoords(followingPosD);
			cornerTR.outDir.going_down = true;
			potentialTiles.push_back(cornerTR);
		}
		// Bottom right - goes right and up
		vec3 followingPosU = vec3(curTileCoords.x, curTileCoords.y, curTileCoords.z - tileSize);
		if (!tilePosTaken(followingPosU))
		{
			CornerTile_BR cornerBR;
			cornerBR.SetCoords(curTileCoords);
			cornerBR.SetNextCoords(followingPosU);
			cornerBR.outDir.going_up = true;
			potentialTiles.push_back(cornerBR);
		}
	}
}

// Returns true if the given position is already taken by another tile 
bool courseGenV2::tilePosTaken(vec3 checkPos)
{
	// Loop through existing tiles
	for (auto &t : gameTiles)
	{
		// Check for a match with checkPos
		if (checkPos == t.thisCoords)
			return true;
	}
	return false;
}
