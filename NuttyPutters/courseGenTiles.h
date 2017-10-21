#pragma once
// Need access to vec3
#include "include\glm-0.9.8.5\glm\glm\glm.hpp"

using namespace glm;

// This algorithm needs a sense of direction
class Direction
{
public:
	bool going_up;
	bool going_right;
	bool going_down;
	bool going_left;

	Direction();
	~Direction() {};

	void SetDir();
};

// Tiles have a number id
// Start - 0
// Straight_V - 1
// Straight_H - 2
// Corner_BL - 3
// Corner_BR - 4
// Corner_TL - 5
// Corner_TR - 6
// End - 7
// Base class - never needs to be instantiated
class BaseTile
{
public:
	// This tile's position, the next tile's position
	vec3 thisCoords, nextCoords;
	// Each tile is identified by a number
	int id;
	// Tiles have a size (10x10 currently)
	int size = 10;
	// For end piece 
	Direction direction;
	// Accessor/Mutator of positions
	void SetCoords(vec3 coords) { thisCoords = coords; }
	void SetNextCoords(vec3 coords) { nextCoords = coords; }
	vec3 GetNextCoords() { return nextCoords; }
	vec3 GetThisCoords() { return thisCoords; }
};

// Start Tile type, inherits from Tile
class StartTile : public BaseTile
{
public:
	// Constructor
	StartTile()
	{
		id = 0; // Start is 0
		thisCoords = vec3(0, 0, 0); // Always placed in centre
		nextCoords = vec3(0, 0, 10);
	}
	~StartTile() {};
};

// Straight vertical tile
class StraightTile_V : public BaseTile
{
public:
	StraightTile_V() { id = 1; } 
	~StraightTile_V() {};

	void FindNextTileCoords(Direction dir);
};
// Straight horizontal tile
class StraightTile_H : public BaseTile
{
public:
	StraightTile_H() { id = 2; }
	~StraightTile_H() {};

	void FindNextTileCoords(Direction dir);
};

// Bottom left corner Tile
class CornerTile_BL : public BaseTile
{
public:
	CornerTile_BL() { id = 3; }
	~CornerTile_BL() {};

	void FindNextTileCoords(Direction dir);
};

// Bottom right corner Tile
class CornerTile_BR : public BaseTile
{
public:
	CornerTile_BR() { id = 4; }
	~CornerTile_BR() {};

	void FindNextTileCoords(Direction dir);
};

// Top left corner tile
class CornerTile_TL : public BaseTile
{
public:
	CornerTile_TL() { id = 5; }
	~CornerTile_TL() {};

	void FindNextTileCoords(Direction dir);
};

// Top right corner tile
class CornerTile_TR : public BaseTile
{
public:
	CornerTile_TR() { id = 6; }
	~CornerTile_TR() {};

	void FindNextTileCoords(Direction dir);
};

// End tile
class EndTile : public BaseTile
{
public:
	EndTile() { id = 7; }
	~EndTile() {};
};


