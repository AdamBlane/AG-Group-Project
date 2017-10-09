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

// Base class - never needs to be instantiated
class Tile
{
public:
	// Position in grid this tile is on
	int position;
	// Position in grid of next tile
	int nextTilePos;
	
	// Accessor/Mutator of positions
	void setPos(int pos) { position = pos; }
	int getPos() { return position;  };
	int getNextPos() { return nextTilePos;  }

	//virtual int findNextTilePos(int gridLength, Direction dir) = 0;

};

// Start Tile type, inherits from Tile abc
class StartTile : public Tile
{
public: 
	StartTile() {};
	~StartTile() {};
	
	
	int findNextTilePos(int gridLength, Direction dir);
};

// Straight horizontal tile
class StraightTile_H : public Tile
{
public:
	StraightTile_H() {};
	~StraightTile_H() {};
	int findNextTilePos(int gridLength, Direction dir);
};

// Straight vertical tile
class StraightTile_V : public Tile
{
public:
	StraightTile_V() {};
	~StraightTile_V() {};
	int findNextTilePos(int gridLength, Direction dir);
};


// Bottom left corner Tile
class CornerTile_BL : public Tile
{
public:
	CornerTile_BL() {};
	~CornerTile_BL() {};
	int findNextTilePos(int gridLength, Direction dir) ;
};

// Bottom right corner Tile
class CornerTile_BR : public Tile
{
public:
	CornerTile_BR() {};
	~CornerTile_BR() {};
	int findNextTilePos(int gridLength, Direction dir) ;
};

// Top left corner tile
class CornerTile_TL : public Tile
{
public:
	CornerTile_TL() {};
	~CornerTile_TL() {};
	int findNextTilePos(int gridLength, Direction dir) ;
};

// Top right corner tile
class CornerTile_TR : public Tile
{
public:
	CornerTile_TR() {};
	~CornerTile_TR() {};
	int findNextTilePos(int gridLength, Direction dir) ;
};

// End tile
//class EndTile : public Tile
//{
//public:
//	EndTile() {};
//	~EndTile() {};
//};