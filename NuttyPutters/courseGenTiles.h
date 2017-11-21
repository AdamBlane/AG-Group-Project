#pragma once
// Need access to vec3
#include "include\glm-0.9.8.5\glm\glm\glm.hpp"
#include "Player.h"

using namespace glm;

// Each tile has a dir as shown
// One direciton bool is set to true, only once
class Direction
{
public:
	bool going_up = false;
	bool going_right = false;
	bool going_down = false;
	bool going_left = false;

	Direction() {};
	~Direction() {};
};


// Tiles have a number id
// Start - 0
// Straight_V - 1
// Straight_H - 2
// Corner_BL - 3
// Corner_BR - 4
// Corner_TL - 5
// Corner_TR - 6
// UpRampDown - 7
// DownRampDown - 8
// End - 9
class BaseTile
{
public:

	// This tile's position, the next tile's position
	vec3 thisCoords;
	vec3 nextCoords;
	// Each tile is identified by a number
	int id;
	// Tiles have a size (10x10 currently)
	float size = 10;
	// Golf ball radius
	float radius = 0.5;
	// Golf ball displacement after hitting boundary
	float displace = 0.0f;
	// Direction of travel once this tile is placed
	Direction outDir;
	// Accessor/Mutator of positions
	void SetCoords(vec3 coords);
	void SetNextCoords(vec3 coords); 
	vec3 GetNextCoords();
	vec3 GetThisCoords();

	
	// Returns true if player is within tile bounds
	bool isPlayerOnTile(vec3 playerPos);

	// Perform collisions checks
	//virtual Player CheckCollisions(Player player) = 0;
};

// Start Tile type, inherits from Tileb
class StartTile : public BaseTile
{
public:
	// Constructor
	StartTile()
	{
		id = 0; // Start is 0
		thisCoords = vec3(0, 0, 0); // Always placed in centre
		nextCoords = vec3(0, 0, 10);
		outDir.going_down = true; // Always facing downwards
	}
	~StartTile() {};


	// Checks whether player has hit boundaries of this tile
	Player CheckCollisions(Player player);
	
};

// Straight vertical tile
class StraightTile_V : public BaseTile
{
public:
	StraightTile_V() { id = 1; } 
	~StraightTile_V() {};

	// Checks whether player has hit boundaries of this tile
	Player CheckCollisions(Player player);
	
};
// Straight horizontal tile
class StraightTile_H : public BaseTile
{
public:
	StraightTile_H() { id = 2; }
	~StraightTile_H() {};

	// Checks whether player has hit boundaries of this tile
	Player CheckCollisions(Player player);

};

// Bottom left corner Tile
class CornerTile_BL : public BaseTile
{
public:
	CornerTile_BL() { id = 3; }
	~CornerTile_BL() {};

	// Checks whether player has hit boundaries of this tile
	Player CheckCollisions(Player player);
	
};

// Bottom right corner Tile
class CornerTile_BR : public BaseTile
{
public:
	CornerTile_BR() { id = 4; }
	~CornerTile_BR() {};

	// Checks whether player has hit boundaries of this tile
	virtual Player CheckCollisions(Player player);
	
};

// Top left corner tile
class CornerTile_TL : public BaseTile
{
public:
	CornerTile_TL() { id = 5; }
	~CornerTile_TL() {};

	// Checks whether player has hit boundaries of this tile
	Player CheckCollisions(Player player);
	
};

// Top right corner tile
class CornerTile_TR : public BaseTile
{
public:
	CornerTile_TR() { id = 6; }
	~CornerTile_TR() {};

	// Checks whether player has hit boundaries of this tile
	Player CheckCollisions(Player player);
	
};

// RAMP - Ramp goes up, placed when course direction is going_down
class UpRampDown : public BaseTile
{
public:
	UpRampDown() { id = 7; }
	~UpRampDown() {};

	// Sets player height based on where it is on ramp
	Player SetPlayerHeight(Player player);

	virtual Player CheckCollisions(Player player) { return player; }

};

// RAMP - Goes down, placed when course dir is going_up
class DownRampDown : public BaseTile
{
public:
	DownRampDown() { id = 8; }
	~DownRampDown() {};

	Player CheckCollisions(Player player) { return player; }
};

// Bridge tile
class Bridge_V : public BaseTile
{
public:
	Bridge_V() { id = 10; }
	~Bridge_V() {};

	Player CheckCollisions(Player player) { return player; }
};

// End tile
class EndTile : public BaseTile
{
public:
	EndTile() { id = 9; }
	~EndTile() {};

	bool ballInHole;

	// Getters
	inline bool getBallInHole() { return ballInHole; }

	// Checks whether player has hit boundaries of this tile
	Player CheckCollisions(Player player);
	
};