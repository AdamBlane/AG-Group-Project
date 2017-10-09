#include "gameTiles.h"
// ###### DIRECTION ######
// Inital setup for direction; always going down first
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
		going_up = true;
	else { going_up = false; }
	// Down
	if (curTilePos - lastTilePos == gridLength)
		going_down = true;
	else { going_down = false; }
	// Left
	if (curTilePos - lastTilePos == -1)
		going_left = true;
	else { going_left = false; }
	// Right
	if (curTilePos - lastTilePos == 1)
		going_right = true;
	else { going_right = false; }
}
// ###### DIRECTION END ######


// START TILE next tile formula
// Assumes start tile open side always faces down
int StartTile::findNextTilePos(int gridLength, Direction dir) 
{
	nextTilePos = position + gridLength;
	return nextTilePos;
}

// STRAIGHT_H
int StraightTile_H::findNextTilePos(int gridLength, Direction dir)
{
	// Based on direction
	if (dir.going_left)
		nextTilePos = position - 1;
	else if (dir.going_right)
		nextTilePos = position + 1;
	return nextTilePos;
}

// STRAIGH_V
int StraightTile_V::findNextTilePos(int gridLength, Direction dir)
{
	if (dir.going_up)
		nextTilePos = position - gridLength;
	else if (dir.going_down)
		nextTilePos = position + gridLength;
	return nextTilePos;
}

// Bottom left corner
int CornerTile_BL::findNextTilePos(int gridLength, Direction dir)
{
	// Going up or right?
	if (dir.going_up)
		nextTilePos = position - gridLength;
	else if (dir.going_right)
		nextTilePos = position + 1;
	return nextTilePos;
}

// Bottom right corner
int CornerTile_BR::findNextTilePos(int gridLength, Direction dir)
{
	// Going up or left?
	if (dir.going_up)
		nextTilePos = position - gridLength;
	else if (dir.going_left)
		nextTilePos = position - 1;
	return nextTilePos;
}

// Top left corner
int CornerTile_TL::findNextTilePos(int gridLength, Direction dir)
{
	// Going down or right?
	if (dir.going_down)
		nextTilePos = position + gridLength;
	else if (dir.going_right)
		nextTilePos = position + 1;
	return nextTilePos;
}

// Top right corner
int CornerTile_TR::findNextTilePos(int gridLength, Direction dir)
{
	// Going down or left?
	if (dir.going_down)
		nextTilePos = position + gridLength;
	else if (dir.going_left)
		nextTilePos = position - 1;
	return nextTilePos;
}

