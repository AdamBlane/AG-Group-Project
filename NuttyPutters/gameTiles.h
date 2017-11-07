//#pragma once
//#include <string>
//#include "include\glm-0.9.8.5\glm\glm\glm.hpp"
//
//using namespace std;
//using namespace glm;
//
//// This algorithm needs a sense of direction
//class Direction
//{
//public:
//	bool going_up;
//	bool going_right;
//	bool going_down;
//	bool going_left;
//
//	Direction();
//	~Direction() {};
//
//	void setDir(int curTilePos, int lastTilePos, int gridLength);
//};
//
//// Base class - never needs to be instantiated
//class BaseTile
//{
//public:
//	// Position in grid this tile is on
//	int position;
//	// Position in grid of next tile
//	int nextTilePos;
//	// Positions in global coordinates 
//	vec3 thisCoords, nextCoords;
//	// Name of the tile
//	string name;
//	// For end piece 
//	Direction direction;
//	// Accessor/Mutator of positions
//	void setPos(int pos) { position = pos; }
//	int getPos() { return position;  }
//	int getNextPos() { return nextTilePos;  }
//	void setCoords(vec3 coords) { thisCoords = coords; }
//	vec3 getNextCoords() { return nextCoords;  } 
//	vec3 getThisCoords() { return thisCoords; }
//};
//
//// Start Tile type, inherits from Tile
//class StartTile : public BaseTile
//{
//public:
//	
//
//	StartTile() 
//	{
//		name = "start"; 
//		thisCoords = vec3(0, 0, 0);
//	}
//	~StartTile() {};
//	
//	int findNextTilePos(int gridLength, Direction dir);
//	vec3 findNextTileCoords();
//};
//
//// Straight horizontal tile
//class StraightTile_H : public BaseTile
//{
//public:
//	StraightTile_H() { name = "straight_H"; }
//	~StraightTile_H() {};
//	int findNextTilePos(int gridLength, Direction dir);
//	vec3 findNextTileCoords(Direction dir);
//};
//
//// Straight vertical tile
//class StraightTile_V : public BaseTile
//{
//public:
//	StraightTile_V() { name = "straight_V"; }
//	~StraightTile_V() {};
//	int findNextTilePos(int gridLength, Direction dir);
//	vec3 findNextTileCoords(Direction dir);
//};
//
//
//// Bottom left corner Tile
//class CornerTile_BL : public BaseTile
//{
//public:
//	CornerTile_BL() { name = "corner_BL"; }
//	~CornerTile_BL() {};
//	int findNextTilePos(int gridLength, Direction dir);
//	vec3 findNextTileCoords(Direction dir);
//};
//
//// Bottom right corner Tile
//class CornerTile_BR : public BaseTile
//{
//public:
//	CornerTile_BR() { name = "corner_BR"; }
//	~CornerTile_BR() {};
//	int findNextTilePos(int gridLength, Direction dir);
//	vec3 findNextTileCoords(Direction dir);
//};
//
//// Top left corner tile
//class CornerTile_TL : public BaseTile
//{
//public:
//	CornerTile_TL() { name = "corner_TL"; }
//	~CornerTile_TL() {};
//	int findNextTilePos(int gridLength, Direction dir);
//	vec3 findNextTileCoords(Direction dir);
//};
//
//// Top right corner tile
//class CornerTile_TR : public BaseTile
//{
//public:
//	CornerTile_TR() { name = "corner_TR"; }
//	~CornerTile_TR() {};
//	int findNextTilePos(int gridLength, Direction dir);
//	vec3 findNextTileCoords(Direction dir);
//};
//
//// End tile
//class EndTile : public BaseTile
//{
//public:
//	EndTile() { name = "end"; }
//	~EndTile() {};
//};
//
//
//
//// Notes
//// - I don't need return types for the findNext methods