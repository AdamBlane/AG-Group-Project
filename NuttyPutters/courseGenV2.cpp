#include "courseGenV2.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>

using namespace std::chrono;

// Course Gen constructor
courseGenV2::courseGenV2(int difficulty)
{
	// Set tile size
	tileSize = 10;

	// Difficulty = number of tiles this course
	courseLimit = difficulty;

	// Create start tile
	StartTile* start = new StartTile();

	// Get direction
	dir = start->outDir;

	// Update curCoords tracker
	curTileCoords = start->nextCoords;

	// Add it to game tiles list
	gameTiles.push_back(start);
}

// Main algorithm loop
vector<BaseTile*> courseGenV2::run()
{
	// Until course is built...
	// -1 since end tile will be added afterwards
	while ((int)gameTiles.size() < courseLimit - 1)
	{
		PlaceTile();
	}

	// Add end tile manually
	EndTile* end = new EndTile();
	end->SetCoords(curTileCoords);
	end->outDir = dir;
	gameTiles.push_back(end);


	return gameTiles;
}

// Looks for straights/corners and picks one
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
	curTileCoords = gameTiles.back()->GetNextCoords();

	// Update direction for placement of next tile
	dir = gameTiles.back()->outDir;

	// Delete unused potential tiles 
	//for (auto &t : potentialTiles)
	//{
	//	delete(t);
	//}
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
			// Create potential tile types
			Bridge_V* bridge = new Bridge_V();
			StraightTile_V* straightV = new StraightTile_V();
			// Set position and next tile pos
			straightV->SetCoords(curTileCoords);
			bridge->SetCoords(curTileCoords);
			straightV->SetNextCoords(followingPos);
			bridge->SetNextCoords(followingPos);
			// Set out direction
			if (dir.going_up)
			{
				// Continue going up
				straightV->outDir.going_up = true;
				bridge->outDir.going_up = true;
			}
			else if (dir.going_down)
			{
				// Continue going down
				straightV->outDir.going_down = true;
				bridge->outDir.going_down = true;
			}

			// Add to list of potential next tiles
			potentialTiles.push_back(straightV);
			potentialTiles.push_back(bridge);
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
			StraightTile_H* straightH = new StraightTile_H();
			// Set position and next tile pos
			straightH->SetCoords(curTileCoords);
			straightH->SetNextCoords(followingPos);
			// Set out direction
			if (dir.going_left)
				straightH->outDir.going_left = true;
			else if (dir.going_right)
				straightH->outDir.going_right = true;
			// Add to list of potential next tiles
			potentialTiles.push_back(straightH);
		}
	}
	
	// RAMP TESTING
	//if (dir.going_down)
	//{
	//	// Following is + 3.8 on y axis (arbitrary atm)
	//	vec3 followingPos = vec3(curTileCoords.x, curTileCoords.y + 3.8, curTileCoords.z + zDiff);
	//	if (!tilePosTaken(followingPos))
	//	{
	//		UpRampDown* ramp = new UpRampDown();
	//		ramp->SetCoords(curTileCoords);
	//		ramp->SetNextCoords(followingPos);
	//		ramp->outDir.going_down = true;
	//		potentialTiles.push_back(ramp);
	//	}
	//}
	/*if (dir.going_up) // Ignoring this ramp type for now
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
	}*/
	
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
			CornerTile_BL* cornerBL = new CornerTile_BL();
			// Set positions
			cornerBL->SetCoords(curTileCoords);		
			cornerBL->SetNextCoords(followingPosR);
			cornerBL->outDir.going_right = true;
			// Add to potentials list
			potentialTiles.push_back(cornerBL);
		}
		// Bottom right - goes down to the left
		vec3 followingPosL = vec3(curTileCoords.x - tileSize, curTileCoords.y, curTileCoords.z);
		// If free, add corner
		if (!tilePosTaken(followingPosL))
		{
			GapTile* gapTile = new GapTile();
			CornerTile_BR* cornerBR = new CornerTile_BR();
			cornerBR->SetCoords(curTileCoords);
			gapTile->SetCoords(curTileCoords);
			cornerBR->SetNextCoords(followingPosL);
			gapTile->SetNextCoords(followingPosL);
			cornerBR->outDir.going_left = true;
			gapTile->outDir.going_left = true;
			potentialTiles.push_back(cornerBR);
			potentialTiles.push_back(gapTile);
		}
	}
	// Check for top L/R corners
	else if (dir.going_up)
	{
		// Top left - goes up to the right
		vec3 followingPosR = vec3(curTileCoords.x + tileSize, curTileCoords.y, curTileCoords.z);
		if (!tilePosTaken(followingPosR))
		{
			GapTile* gapTile = new GapTile();
			CornerTile_TL* cornerTL = new CornerTile_TL();
			cornerTL->SetCoords(curTileCoords);
			gapTile->SetCoords(curTileCoords);
			cornerTL->SetNextCoords(followingPosR);
			gapTile->SetNextCoords(followingPosR);
			cornerTL->outDir.going_right = true;
			gapTile->outDir.going_right = true;
			potentialTiles.push_back(cornerTL);
			potentialTiles.push_back(gapTile);
		}
		// Top right - goes up to the left
		vec3 followingPosL = vec3(curTileCoords.x - tileSize, curTileCoords.y, curTileCoords.z);
		if (!tilePosTaken(followingPosL))
		{
			CornerTile_TR* cornerTR = new CornerTile_TR();
			cornerTR->SetCoords(curTileCoords);
			cornerTR->SetNextCoords(followingPosL);
			cornerTR->outDir.going_left = true;
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
			CornerTile_TL* cornerTL = new CornerTile_TL();
			cornerTL->SetCoords(curTileCoords);
			cornerTL->SetNextCoords(followingPosD);
			cornerTL->outDir.going_down = true;
			potentialTiles.push_back(cornerTL);
		}
		// Bottom left - goes left and up
		vec3 followingPosU = vec3(curTileCoords.x, curTileCoords.y, curTileCoords.z - tileSize);
		if (!tilePosTaken(followingPosU))
		{
			GapTile* gapTile = new GapTile();
			CornerTile_BL* cornerBL = new CornerTile_BL();
			cornerBL->SetCoords(curTileCoords);
			gapTile->SetCoords(curTileCoords);
			cornerBL->SetNextCoords(followingPosU);
			gapTile->SetNextCoords(followingPosU);
			cornerBL->outDir.going_up = true;
			gapTile->outDir.going_up = true;
			potentialTiles.push_back(cornerBL);
			potentialTiles.push_back(gapTile);
		}
	}
	// Check for right top/bottom
	else if (dir.going_right)
	{
		// Top right - goes right and down
		vec3 followingPosD = vec3(curTileCoords.x, curTileCoords.y, curTileCoords.z + tileSize);
		if (!tilePosTaken(followingPosD))
		{
			GapTile* gapTile = new GapTile();
			CornerTile_TR* cornerTR = new CornerTile_TR();
			cornerTR->SetCoords(curTileCoords);
			gapTile->SetCoords(curTileCoords);
			cornerTR->SetNextCoords(followingPosD);
			gapTile->SetNextCoords(followingPosD);
			cornerTR->outDir.going_down = true;
			gapTile->outDir.going_down = true;
			potentialTiles.push_back(cornerTR);
			potentialTiles.push_back(gapTile);
		}
		// Bottom right - goes right and up
		vec3 followingPosU = vec3(curTileCoords.x, curTileCoords.y, curTileCoords.z - tileSize);
		if (!tilePosTaken(followingPosU))
		{
			CornerTile_BR* cornerBR = new CornerTile_BR();
			cornerBR->SetCoords(curTileCoords);
			cornerBR->SetNextCoords(followingPosU);
			cornerBR->outDir.going_up = true;
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
		if (checkPos == t->thisCoords)
			return true;
	}
	return false;
}

// Setup game seed based on default/given seed value
vector<int> courseGenV2::SetupSeed(string seed, int courseLength)
{
	// Resulting seeds list
	vector<int> levelSeed;
	// Only get seed from file if not given to us from load game screen
	if (seed == "seed") // it's the default value
	{
		// Insert start
		levelSeed.push_back(0);

		// Seeds file to read
		ifstream seedsFile;
		// Number of available seeds in that file
		int seedsCount;
		// Open seeds file (different file for each difficulty)
		if (courseLength == 8)
		{
			seedsFile.open("seeds8.csv");
			// There are 3000 lines in this file
			seedsCount = 2999;
		}
		else if (courseLength == 12)
		{
			seedsFile.open("seeds12.csv");
			// There are 256 lines in this file
			seedsCount = 255;
		}
		else if (courseLength == 16)
		{
			seedsFile.open("seeds16.csv");
			// There are 66 lines in this file
			seedsCount = 65;
		}
		

		// pick random number in that range
		default_random_engine rng(random_device{}());
		uniform_int_distribution<int> distribution(1, seedsCount);
		int choice = distribution(rng);
		cout << choice << endl;
		// read that line
		string line;
		for (int l = 0; l < choice; ++l)
		{
			getline(seedsFile, line);
		} // last iteration will be on desired line, so line should be correct seed now
		  // parse seed into array
		for (int c = 0; c < line.length(); ++c)
		{
			// Convert each character in string to int
			levelSeed.push_back(line[c] - 48); // Char encoding for digits; ASCII int value is - 48
		}




		//levelSeed.push_back(0);
		//levelSeed.push_back(1);
		//levelSeed.push_back(1);
		//levelSeed.push_back(1);
		//levelSeed.push_back(1);
		//levelSeed.push_back(1);
		//levelSeed.push_back(1);
		//levelSeed.push_back(1);
		//levelSeed.push_back(1);
		//levelSeed.push_back(7);
		//levelSeed.push_back(7);
		//levelSeed.push_back(9);

	} // end if seed is default
	else // this has been given a seed value
	{
		// Prevent this level being saved again
		//levelSaved = true;
		// Parse into ints as above
		for (int c = 0; c < seed.length(); ++c)
		{
			levelSeed.push_back(seed[c] - 48);
		}
	}

	return levelSeed;
}

// Sets up alg tiles list
vector<BaseTile*> courseGenV2::SetupAlgTiles(vector<int> levelSeed)
{
	// Resulting alg tiles list
	vector<BaseTile*> algTiles;
	// Start added first (this & next coords already set)
	StartTile* start = new StartTile();
	// Add it to our list
	algTiles.push_back(start);
	// Track currently looked at coords
	vec3 curCoords;
	// Update size tracker
	float size = start->size;
	// For each number in seed array
	for (auto &i : levelSeed)
	{
		// Update current coordinates (next coords of last thing in list) 
		curCoords = algTiles.back()->GetNextCoords();
		switch (i)
		{
			// Straight_V
		case 1:
		{
			// Create tile
			StraightTile_V* straightV = new StraightTile_V();
			// Set its position
			straightV->SetCoords(curCoords);
			// Find next position - based on direction
			if (algTiles.back()->outDir.going_down)
			{
				// The position of next tile in list
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				straightV->SetNextCoords(nextPos);
				// Set dir
				straightV->outDir.going_down = true;
			}
			else if (algTiles.back()->outDir.going_up)
			{
				// The position of next tile in list
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				straightV->SetNextCoords(nextPos);
				// Set dir
				straightV->outDir.going_up = true;
			}
			// Add tile to list, finish (break)
			algTiles.push_back(straightV);
			break;
		}
		// Straight_H
		case 2:
		{
			// Create tile
			StraightTile_H* straightH = new StraightTile_H();
			// Set its position
			straightH->SetCoords(curCoords);
			// Find next position
			if (algTiles.back()->outDir.going_right)
			{
				// Position of next tile in list
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				straightH->SetNextCoords(nextPos);
				// Set dir
				straightH->outDir.going_right = true;
			}
			else if (algTiles.back()->outDir.going_left)
			{
				// Position of next tile in list
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				straightH->SetNextCoords(nextPos);
				// Set dir
				straightH->outDir.going_left = true;
			}
			// Add to list
			algTiles.push_back(straightH);
			break;
		}
		// Corner_BL
		case 3:
		{
			// Create tile
			CornerTile_BL* cornerBL = new CornerTile_BL();
			// Set pos
			cornerBL->SetCoords(curCoords);
			// Find next position
			if (algTiles.back()->outDir.going_down)
			{
				// Last tile was going down; next tile is going right
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				cornerBL->SetNextCoords(nextPos);
				// Set dir
				cornerBL->outDir.going_right = true;
			}
			else if (algTiles.back()->outDir.going_left)
			{
				// Last tile was going left; next tile is going up
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				cornerBL->SetNextCoords(nextPos);
				// Set dir
				cornerBL->outDir.going_up = true;
			}
			// Add to list
			algTiles.push_back(cornerBL);
			break;
		}
		// Corner_BR
		case 4:
		{
			// Create tile
			CornerTile_BR* cornerBR = new CornerTile_BR();
			// Set pos
			cornerBR->SetCoords(curCoords);
			// Find next position
			if (algTiles.back()->outDir.going_down)
			{
				// Last tile was going down; next tile is going left
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				cornerBR->SetNextCoords(nextPos);
				// Set dir
				cornerBR->outDir.going_left = true;
			}
			else if (algTiles.back()->outDir.going_right)
			{
				// Last tile was going right; next tile is going up
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				cornerBR->SetNextCoords(nextPos);
				// Set dir
				cornerBR->outDir.going_up = true;
			}
			// Add to list
			algTiles.push_back(cornerBR);
			break;
		}
		// Corner_TL
		case 5:
		{
			// Create tile
			CornerTile_TL* cornerTL = new CornerTile_TL();
			cornerTL->SetCoords(curCoords);
			// Find next pos
			if (algTiles.back()->outDir.going_up)
			{
				// Last tile was going up; next going right
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				cornerTL->SetNextCoords(nextPos);
				// Set dir
				cornerTL->outDir.going_right = true;
			}
			else if (algTiles.back()->outDir.going_left)
			{
				// Last tile was going left; next tile going down
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				cornerTL->SetNextCoords(nextPos);
				// Set dir
				cornerTL->outDir.going_down = true;
			}
			// Add to list
			algTiles.push_back(cornerTL);
			break;
		}
		// Corner_TR
		case 6:
		{
			// Create tile
			CornerTile_TR* cornerTR = new CornerTile_TR();
			// Set pos
			cornerTR->SetCoords(curCoords);
			// Find next pos
			if (algTiles.back()->outDir.going_right)
			{
				// Last tile going right; next tile going down
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				cornerTR->SetNextCoords(nextPos);
				// Set dir
				cornerTR->outDir.going_down = true;
			}
			else if (algTiles.back()->outDir.going_up)
			{
				// Last tile going up; next tile going left
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				cornerTR->SetNextCoords(nextPos);
				// Set dir
				cornerTR->outDir.going_left = true;
			}
			// Add to list
			algTiles.push_back(cornerTR);
			break;
		}
		// Bridge tile
		case 7:
		{
			// Create tile
			Bridge_V* bridge = new Bridge_V();
			bridge->SetCoords(curCoords);
			// Check direction to find next pos
			vec3 nextPos;
			if (algTiles.back()->outDir.going_down)
			{
				// Find next pos (always know dir is down when 7 is placed)
				nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				bridge->outDir.going_down = true;
			}
			else if (algTiles.back()->outDir.going_up)
			{
				// Find next pos (always know dir is down when 7 is placed)
				nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				bridge->outDir.going_up = true;
			}

			bridge->SetNextCoords(nextPos);		
			algTiles.push_back(bridge);
			break;
		}
		// Gap Tile
		case 8:
		{
			// Create tile & set its coords
			GapTile* gapTile = new GapTile();
			gapTile->SetCoords(curCoords);
			// Need to know direction to determine next pos
			vec3 nextPos;
			if (algTiles.back()->outDir.going_up)
			{
				// Find next pos & set outwards direction
				nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				gapTile->outDir.going_right = true;
			}
			else if (algTiles.back()->outDir.going_down)
			{
				// Find next pos & set outwards direction
				nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				gapTile->outDir.going_left = true;
			}
			else if (algTiles.back()->outDir.going_left)
			{
				// Find next pos & set outwards direction
				nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				gapTile->outDir.going_up = true;
			}
			else if (algTiles.back()->outDir.going_right)
			{
				// Find next pos & set outwards direction
				nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				gapTile->outDir.going_down = true;
			}

			gapTile->SetNextCoords(nextPos);
			algTiles.push_back(gapTile);
			break;
		}
		// End tile
		case 9:
		{
			// Create end tile
			EndTile* end = new EndTile();
			end->SetCoords(curCoords);
			end->outDir = algTiles.back()->outDir;
			algTiles.push_back(end);
			break;
		}

		default: break;
		} // Switch end

	} // for loop create games tiles from alg tiles end

	return algTiles;
}