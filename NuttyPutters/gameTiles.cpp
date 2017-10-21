#include "gameTiles.h"
#include <iostream>


using namespace std;

// ###### DIRECTION ######
// Constructor - Inital setup for direction; always going down first
Direction::Direction()
{
	going_up = false;
	going_right = false;
	going_down = true;
	going_left = false;
}



// Finds which direction tiles are going in now
void Direction::setDir(int curTilePos, int lastTilePos, int gridLength)
{
	// Up
	if (curTilePos - lastTilePos == -gridLength)
	{
		going_up = true;
		cout << "We're going up!" << endl;
	}
	else { going_up = false; }
	// Down
	if (curTilePos - lastTilePos == gridLength)
	{
		going_down = true;
		cout << "We're going down!" << endl;
	}
	else { going_down = false; }
	// Left
	if (curTilePos - lastTilePos == -1)
	{
		going_left = true;
		cout << "We're going left!" << endl;
	}
	else { going_left = false; }
	// Right
	if (curTilePos - lastTilePos == 1)
	{
		going_right = true;
		cout << "We're going right!" << endl;
	}
	else { going_right = false; }
}
// ###### DIRECTION END ######


// START TILE next tile formula
// Assumes start tile open side always faces down
int StartTile::findNextTilePos(int gridLength, Direction dir) 
{
	// Next tile position in grid
	nextTilePos = position + gridLength;
	return nextTilePos;
}
// Finds next tile global coords
vec3 StartTile::findNextTileCoords()
{
	nextCoords = vec3(0, 0, 10);
	return nextCoords;
}

// STRAIGHT_H next grid pos
int StraightTile_H::findNextTilePos(int gridLength, Direction dir) 
{
	// Based on direction
	if (dir.going_left)
		nextTilePos = position - 1;
	else if (dir.going_right)
		nextTilePos = position + 1;
	return nextTilePos;
}
// SH next coords
vec3 StraightTile_H::findNextTileCoords(Direction dir)
{
	// Based on dir
	if (dir.going_left)
		nextCoords = vec3(thisCoords.x - 10, 0, thisCoords.z);
	else if (dir.going_right)
		nextCoords = vec3(thisCoords.x + 10, 0, thisCoords.z);
	return vec3();
}

// STRAIGH_V grid pos
int StraightTile_V::findNextTilePos(int gridLength, Direction dir) 
{
	if (dir.going_up)
		nextTilePos = position - gridLength;
	else if (dir.going_down)
		nextTilePos = position + gridLength;
	return nextTilePos;
}
// STRAIGHT_V global coords
vec3 StraightTile_V::findNextTileCoords(Direction dir)
{
	if (dir.going_up)
		nextCoords = vec3(thisCoords.x, 0, thisCoords.z - 10);
	if (dir.going_down)
		nextCoords = vec3(thisCoords.x, 0, thisCoords.z + 10);
	return nextCoords;
}

// Bottom left corner grid pos
int CornerTile_BL::findNextTilePos(int gridLength, Direction dir) 
{
	// Going down or left?
	if (dir.going_down)
		nextTilePos = position + 1;
	else if (dir.going_left)
		nextTilePos = position - gridLength;
	return nextTilePos;
}
// Corner_BL global coords
vec3 CornerTile_BL::findNextTileCoords(Direction dir)
{
	if (dir.going_down)
		nextCoords = vec3(thisCoords.x + 10, 0, thisCoords.z);
	else if (dir.going_left)
		nextCoords = vec3(thisCoords.x, 0, thisCoords.z - 10);
	return nextCoords;
}

// Bottom right corner grid pos
int CornerTile_BR::findNextTilePos(int gridLength, Direction dir)
{
	// Going down or right?
	if (dir.going_down)
		nextTilePos = position - 1;
	else if (dir.going_right)
		nextTilePos = position - gridLength;
	return nextTilePos;
}
// Corner BR global coords
vec3 CornerTile_BR::findNextTileCoords(Direction dir)
{
	if (dir.going_down)
		nextCoords = vec3(thisCoords.x - 10, 0, thisCoords.z);
	else if (dir.going_right)
		nextCoords = vec3(thisCoords.x, 0, thisCoords.z - 10);
	return nextCoords;
}

// Top left corner grid pos
int CornerTile_TL::findNextTilePos(int gridLength, Direction dir)
{
	// Going up or left?
	if (dir.going_up)
		nextTilePos = position + 1;
	else if (dir.going_left)
		nextTilePos = position + gridLength;
	return nextTilePos;
}
// Corner TL global coords
vec3 CornerTile_TL::findNextTileCoords(Direction dir)
{
	if (dir.going_up)
		nextCoords = vec3(thisCoords.x + 10, 0, thisCoords.z);
	else if (dir.going_left)
		nextCoords = vec3(thisCoords.x, 0, thisCoords.z + 10);
	return nextCoords;
}

// Top right corner grid pos
int CornerTile_TR::findNextTilePos(int gridLength, Direction dir)
{
	// Going up or right?
	if (dir.going_up)
		nextTilePos = position - 1;
	else if (dir.going_right)
		nextTilePos = position + gridLength;
	return nextTilePos;
}
// Corner TR global coords
vec3 CornerTile_TR::findNextTileCoords(Direction dir)
{
	if (dir.going_up)
		nextCoords = vec3(thisCoords.x - 10, 0, thisCoords.z);
	else if (dir.going_right)
		nextCoords = vec3(thisCoords.x, 0, thisCoords.z + 10);
	return nextCoords;
}

