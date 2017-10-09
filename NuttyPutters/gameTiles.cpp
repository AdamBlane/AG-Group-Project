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
int StartTile::findNextTilePos(int gridLength)
{
	nextTilePos = position + gridLength;
	return nextTilePos;
}

// STRAIGHT_H
void StraightTile_H::findNextTilePos(Direction dir)
{
	// Based on direction
	if (dir.going_left)
		nextTilePos = position - 1;
	else if (dir.going_right)
		nextTilePos = position + 1;
}

// STRAIGH_V
void StraightTile_V::findNextTilePos(int gridLength, Direction dir)
{
	if (dir.going_up)
		nextTilePos = position - gridLength;
	else if (dir.going_down)
		nextTilePos = position + gridLength;
}

// Bottom left corner
void CornerTile_BL::findNextTilePos(int gridLength, Direction dir)
{
	// Going up or right?
	if (dir.going_up)
		nextTilePos = position - gridLength;
	else if (dir.going_right)
		nextTilePos = position + 1;
}

// Bottom right corner
void CornerTile_BR::findNextTilePos(int gridLength, Direction dir)
{
	// Going up or left?
	if (dir.going_up)
		nextTilePos = position - gridLength;
	else if (dir.going_left)
		nextTilePos = position - 1;
}

// Top left corner
void CornerTile_TL::findNextTilePos(int gridLength, Direction dir)
{
	// Going down or right?
	if (dir.going_down)
		nextTilePos = position + gridLength;
	else if (dir.going_right)
		nextTilePos = position + 1;
}

// Top right corner
void CornerTile_TR::findNextTilePos(int gridLength, Direction dir)
{
	// Going down or left?
	if (dir.going_down)
		nextTilePos = position + gridLength;
	else if (dir.going_left)
		nextTilePos = position - 1;
}
