#pragma once

// Forward declaration
class Direction
{
public:
	bool going_up;
	bool going_right;
	bool going_down;
	bool going_left;

	Direction();
	~Direction() {};

	void setDir(int curTilePos, int lastTilePos, int gridLength);
};

// Abstract base class - this need never be instantiated
class Tile
{
public:
	// Position in grid this tile is on
	int position;
	// Position in grid of next tile
	int nextTilePos;
	
	// Accessor/Mutator of position
	void setPos(int pos) { position = pos; }
	int getPos() { return position;  };

	// Calculate next tile pos; implemented in derived classes
	virtual void findNextTilePos() = 0;
	// Accessor
	int getNextTilePos() { return nextTilePos; }
};

// Start Tile type, inherits from Tile abc
class StartTile : public Tile
{
public: 
	StartTile() {};
	~StartTile() {};
	void findNextTilePos(int gridLength);
};

// Straight horizontal tile
class StraightTile_H : public Tile
{
public:
	StraightTile_H() {};
	~StraightTile_H() {};
	void findNextTilePos(Direction dir);
};

// Straight vertical tile
class StraightTile_V : public Tile
{
public:
	StraightTile_V() {};
	~StraightTile_V() {};
	void findNextTilePos(int gridLength, Direction dir);
};