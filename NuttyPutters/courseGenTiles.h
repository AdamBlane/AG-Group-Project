#pragma once
// Need access to vec3
#include "include\glm-0.9.8.5\glm\glm\glm.hpp"

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
	vec3 thisCoords, nextCoords;
	// Each tile is identified by a number
	int id;
	// Tiles have a size (10x10 currently)
	float size = 10;
	// Golf ball radius
	float radius = 0.5;
	// Golf ball displacement after hitting boundary
	float displace = 0.25;
	// Direction of travel once this tile is placed
	Direction outDir;
	// Accessor/Mutator of positions
	void SetCoords(vec3 coords) { thisCoords = coords; }
	void SetNextCoords(vec3 coords) { nextCoords = coords; }
	vec3 GetNextCoords() { return nextCoords; }
	vec3 GetThisCoords() { return thisCoords; }

	// Returns true if player is within tile bounds
	bool isPlayerOnTile(vec3 playerPos)
	{
		// Match on x first
		if (playerPos.x > thisCoords.x - 4 && playerPos.x < thisCoords.x + 4)
		{
			// Then on z
			if (playerPos.z > thisCoords.z - 4 && playerPos.z < thisCoords.z + 4)
			{
				// Player is on this tile
				return true;
			}
		}
		return false;
	}

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
	vec3 CheckCollisions(vec3 playerPos, vec3 dir)
	{
	
		// Check on X axis - boundaries either side
		if (playerPos.x > thisCoords.x + (4 - radius)) 
		{
			// Hit boundary, revert x axis
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x -= displace;
		}
		if (playerPos.x < thisCoords.x - (4 - radius))
		{
			// Hit boundary, reflect on x
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x += displace;
		}
		// Check on z axis - just one boundary
		if (playerPos.z < thisCoords.z - (4 - radius))
		{
			// hit, revert z axis
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z += displace;
		}

		return dir;
	}

};

// Straight vertical tile
class StraightTile_V : public BaseTile
{
public:
	StraightTile_V() { id = 1; } 
	~StraightTile_V() {};

	// Checks whether player has hit boundaries of this tile
	vec3 CheckCollisions(vec3 playerPos, vec3 dir)
	{

		// Check on X axis - boundaries either side
		if (playerPos.x > thisCoords.x + (4 - radius))
		{
			// Hit boundary, revert x axis
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x -= displace;
		}
		if (playerPos.x < thisCoords.x - (4 - radius))
		{
			// Hit boundary, revert x axis
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x += displace;
		}
		return dir;
	}
	
};
// Straight horizontal tile
class StraightTile_H : public BaseTile
{
public:
	StraightTile_H() { id = 2; }
	~StraightTile_H() {};

	// Checks whether player has hit boundaries of this tile
	vec3 CheckCollisions(vec3 playerPos, vec3 dir)
	{

		// Check on X axis - boundaries either side
		if (playerPos.z > thisCoords.z + (4 - radius)) 
		{
			// Hit boundary, revert x axis
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z -= displace;
		}
		if (playerPos.z < thisCoords.z - (4 - radius))
		{
			// Hit boundary, revert x axis
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z += displace;
		}

		return dir;
	}
};

// Bottom left corner Tile
class CornerTile_BL : public BaseTile
{
public:
	CornerTile_BL() { id = 3; }
	~CornerTile_BL() {};

	// Checks whether player has hit boundaries of this tile
	vec3 CheckCollisions(vec3 playerPos, vec3 dir)
	{

		// Check on X axis - left boundary
		if (playerPos.x < thisCoords.x - (4 - radius))
		{
			// hit left boundary
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x += displace;
		}

		// Check x axis - left side of cube corner boundary
		if (playerPos.x > thisCoords.x + (4 - radius) && // Far enough to the right on x to hit square
			playerPos.z > thisCoords.z - 5 && // Between upper limit of tile/square
			playerPos.z < thisCoords.z - 4) // and lower limit of square
		{
			// Hit going right, reflect on x
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x -= displace;
		}

		// Check z axis - lower boundary
		if (playerPos.z > thisCoords.z + (4 - radius))
		{
			// hit middle
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z -= displace;
		}
		
		// Check z axis - lower side of cube corner boundary
		if (playerPos.z < thisCoords.z - (4 - radius) && 
			playerPos.x > thisCoords.x + 4 &&
			playerPos.x < thisCoords.x + 5)
		{
			// Hit going up, reflect on z
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z += displace;
		}

		return dir;
	}
};

// Bottom right corner Tile
class CornerTile_BR : public BaseTile
{
public:
	CornerTile_BR() { id = 4; }
	~CornerTile_BR() {};

	// Checks whether player has hit boundaries of this tile
	vec3 CheckCollisions(vec3 playerPos, vec3 dir)
	{
		// Axis seems odd since tile has been rotated
		// Check on X axis - left boundary
		if (playerPos.x > thisCoords.x + (4 - radius))
		{
			// hit left boundary
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x -= displace;
		}

		// Check x axis - left side of cube corner boundary
		if (playerPos.x < thisCoords.x - (4 - radius) && // Far enough to the right on x to hit square
			playerPos.z > thisCoords.z - 5 && // Between upper limit of tile/square
			playerPos.z < thisCoords.z - 4) // and lower limit of square
		{
			// Hit going right, reflect on x
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x += displace;
		}

		// Check z axis - lower boundary
		if (playerPos.z > thisCoords.z + (4 - radius))
		{
			// hit middle
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z -= displace;
		}

		// Check z axis - lower side of cube corner boundary
		if (playerPos.z < thisCoords.z - (4 - radius) &&
			playerPos.x > thisCoords.x - 5 &&
			playerPos.x < thisCoords.x - 4)
		{
			// Hit going up, reflect on z
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z += displace;
		}

		return dir;
	}
	
};

// Top left corner tile
class CornerTile_TL : public BaseTile
{
public:
	CornerTile_TL() { id = 5; }
	~CornerTile_TL() {};

	// Checks whether player has hit boundaries of this tile
	vec3 CheckCollisions(vec3 playerPos, vec3 dir)
	{
		// Axis seems odd since tile has been rotated
		// Check on X axis - left boundary
		if (playerPos.x < thisCoords.x - (4 - radius))
		{
			// hit left boundary
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x += displace;
		}

		// Check x axis - left side of cube corner boundary
		if (playerPos.x > thisCoords.x + (4 - radius) && // Far enough to the right on x to hit square
			playerPos.z > thisCoords.z + 4 && // Between upper limit of tile/square
			playerPos.z < thisCoords.z + 5) // and lower limit of square
		{
			// Hit going right, reflect on x
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x -= displace;
		}

		// Check z axis - lower boundary
		if (playerPos.z < thisCoords.z - (4 - radius))
		{
			// hit middle
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z += displace;
		}

		// Check z axis - lower side of cube corner boundary
		if (playerPos.z > thisCoords.z + (4 - radius) &&
			playerPos.x > thisCoords.x + 4 &&
			playerPos.x < thisCoords.x + 5)
		{
			// Hit going up, reflect on z
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z -= displace;
		}

		return dir;
	}
};

// Top right corner tile
class CornerTile_TR : public BaseTile
{
public:
	CornerTile_TR() { id = 6; }
	~CornerTile_TR() {};

	// Checks whether player has hit boundaries of this tile
	vec3 CheckCollisions(vec3 playerPos, vec3 dir)
	{
		// Axis seems odd since tile has been rotated
		// Check on X axis - right boundary
		if (playerPos.x > thisCoords.x + (4 - radius))
		{
			// hit left boundary
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x -= displace;
		}

		// Check x axis - left side of cube corner boundary
		if (playerPos.x < thisCoords.x - (4 - radius) && // Far enough to the right on x to hit square
			playerPos.z > thisCoords.z + 4 && // Between upper limit of tile/square
			playerPos.z < thisCoords.z + 5) // and lower limit of square
		{
			// Hit going right, reflect on x
			dir.x = -dir.x;
			// Move away from boundary so as not to retrigger this
			playerPos.x += displace;
		}

		// Check z axis - lower boundary
		if (playerPos.z < thisCoords.z - (4 - radius))
		{
			// hit middle
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z += displace;
		}

		// Check z axis - lower side of cube corner boundary
		if (playerPos.z > thisCoords.z + (4 - radius) &&
			playerPos.x > thisCoords.x - 5 &&
			playerPos.x < thisCoords.x - 4)
		{
			// Hit going up, reflect on z
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z -= displace;
		}

		return dir;
	}
};

// RAMP - Ramp goes up, placed when course direction is going_down
class UpRampDown : public BaseTile
{
public:
	UpRampDown() { id = 7; }
	~UpRampDown() {};

	// Sets player height based on where it is on ramp
	vec3 SetPlayerHeight(vec3 playerPos)
	{
		// First find how much to increment y for every 1 in z
		float yInc = thisCoords.y / (size / 2);
		// Then find distance travelled along tile
		float difference = playerPos.z - thisCoords.z;
		// Make relative to tile coords by adding half size
		float y = yInc * (difference + (size / 2));
		// Update player pos
		playerPos.y = y + 1;

		return playerPos;
	}
};

// RAMP - Goes down, placed when course dir is going_up
class DownRampDown : public BaseTile
{
public:
	DownRampDown() { id = 8; }
	~DownRampDown() {};
};

// Bridge tile
class Bridge_V : public BaseTile
{
public:
	Bridge_V() { id = 10; }
	~Bridge_V() {};


};

// End tile
class EndTile : public BaseTile
{
public:
	EndTile() { id = 9; }
	~EndTile() {};

	// Checks whether player has hit boundaries of this tile
	vec3 CheckCollisions(vec3 playerPos, vec3 dir )
	{
		// Based on direction
		if (outDir.going_up)
		{
			// Check on X axis - boundaries either side
			if (playerPos.x > thisCoords.x + (4 - radius)) 
			{
				// Hit boundary, revert x axis
				dir.x = -dir.x;
				// Move away from boundary so as not to retrigger this
				playerPos.x -= displace;
			}
			if (playerPos.x < thisCoords.x - (4 - radius))
			{
				// Hit boundary, revert x axis
				dir.x = -dir.x;
				// Move away from boundary so as not to retrigger this
				playerPos.x += displace;
			}
			// Check on z axis - just one boundary
			if (playerPos.z < thisCoords.z - (4 - radius))
			{
				// hit, revert z axis
				dir.z = -dir.z;
				// Move away from boundary so as not to retrigger this
				playerPos.z += displace;
			}
		}
		else if (outDir.going_down)
		{
			// Check on X axis - boundaries either side
			if (playerPos.x > thisCoords.x + (4 - radius) || playerPos.x < thisCoords.x - (4 - radius))
			{
				// Hit boundary, revert x axis
				dir.x = -dir.x;
				// Move away from boundary so as not to retrigger this
				playerPos.x -= displace;
			}

			// Check on z axis - just one boundary
			if (playerPos.z > thisCoords.z + (4 - radius))
			{
				// hit, revert z axis
				dir.z = -dir.z;
				// Move away from boundary so as not to retrigger this
				playerPos.z -= displace;
			}
		}
		else if (outDir.going_left)
		{
			// Check on z axis - boundaries either side
			if (playerPos.z < thisCoords.z - (4 - radius) || playerPos.z > thisCoords.z + (4 - radius))
			{
				dir.z = -dir.z;
				// Move away from boundary so as not to retrigger this
				playerPos.z += displace;
			}
			// Check on x - boundary to left
			if (playerPos.x < thisCoords.x - (4 - radius))
			{
				dir.x = -dir.x;
				// Move away from boundary so as not to retrigger this
				playerPos.x += displace;
			}
		}
		else if (outDir.going_right)
		{
			// Check on z axis - boundaries either side
			if (playerPos.z < thisCoords.z - (4 - radius) || playerPos.z > thisCoords.z + (4 - radius))
			{
				dir.z = -dir.z;
				// Move away from boundary so as not to retrigger this
				playerPos.z += displace;
			}
			// Check on x - boundary to right
			if (playerPos.x > thisCoords.x + (4 - radius))
			{
				dir.x = -dir.x;
				// Move away from boundary so as not to retrigger this
				playerPos.x -= displace;
			}
		}


		// Check if over end hole
		if (playerPos.x > thisCoords.x - 0.75 && playerPos.x < thisCoords.x + 0.75 &&
			playerPos.z > thisCoords.z - 0.75 && playerPos.z < thisCoords.z + 0.75)
		{
			// Apply gravity
			dir.y -= 0.2f;
		}


		return dir;
	}
};