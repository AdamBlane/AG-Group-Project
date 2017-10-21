#include "courseGenV2.h"


// Course Gen constructor
courseGenV2::courseGenV2(int difficulty)
{
	// Difficulty = number of tiles this course
	courseLimit = difficulty;

	// Create start tile
	StartTile start;

	// Update curCoords tracker
	curTileCoords = start.nextCoords;

	// Add it to game tiles list
	gameTiles.push_back(start);
}

// Main algorithm loop
void courseGenV2::run()
{
	// Until course is built...
	// -1 since end tile will be added afterwards
	while ((int)gameTiles.size() < courseLimit - 1)
	{
		// Check availability
		// Random choice
		// Set direction
	}
}


void courseGenV2::PlaceTile()
{
	CheckStraights();
}

// Can we place a straight tile next?
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
		zDiff = -10;
		vertical = true;
	}
	else if (dir.going_down)
	{
		zDiff = 10;
		vertical = true;
	}
	else if (dir.going_left)
	{
		xDiff = -10;
		vertical = false;
	}
	else if (dir.going_right)
	{
		xDiff = 10;
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
			StraightTile_V straightV;
			// Set position and next tile pos
			straightV.SetCoords(curTileCoords);
			straightV.SetNextCoords(followingPos);
			// Add to list of potential next tiles
			potentialTiles.push_back(straightV);
		}
	}
}

void courseGenV2::CheckCorners()
{
	// Check for bottom L/R corners
	if (dir.going_down)
	{
		// Bottom Left - goes down to the right
		vec3 followingPos = vec3(curTileCoords.x + 10, curTileCoords.y, curTileCoords.z);
		// Right
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
