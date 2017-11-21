
#include "courseGenTiles.h"

// THIS file includes collision check functions for each tile type
// These tiles are used in the algorithm to generate a course


// Set coords of this tile
void BaseTile::SetCoords(vec3 coords) {	thisCoords = coords; }

// Set next coords of this tile
void BaseTile::SetNextCoords(vec3 coords) {	thisCoords = coords; }

// Getter of next coords
vec3 BaseTile::GetNextCoords() { return nextCoords; }

// Getter of this coords
vec3 BaseTile::GetThisCoords() { return thisCoords; }

// This is called on each tile; spatial partitioning method
// Returns true if player is on this tile
bool BaseTile::isPlayerOnTile(vec3 playerPos)
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


// Collision check for start tile
// TODO - edit displace value
Player StartTile::CheckCollisions(Player player)
{
	// Check on X axis - boundaries either side
	if (player.transform.getPos().x > thisCoords.x + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x;
		// Hit boundary, revert x axis
		player.direction.x = -player.direction.x;
	}
	else if (player.transform.getPos().x < thisCoords.x - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x;
		// Hit boundary, reflect on x
		player.direction.x = -player.direction.x;
	}
	// Check on z axis - just one boundary
	if (player.transform.getPos().z < thisCoords.z - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z;
		// hit, revert z axis
		player.direction.z = -player.direction.z;

	}

	return player;
}

// Collision check for straight vertical tile
Player StraightTile_V::CheckCollisions(Player player)
{
	// Check on X axis - boundaries either side
	if (player.transform.getPos().x > thisCoords.x + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// Hit boundary, revert x axis
		player.direction.x = -player.direction.x;
	}
	else if (player.transform.getPos().x < thisCoords.x - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// Hit boundary, revert x axis
		player.direction.x = -player.direction.x;

	}
	return player;
}

// Collision check for straight horizontal tile
Player StraightTile_H::CheckCollisions(Player player)
{
	// Check on X axis - boundaries either side
	if (player.transform.getPos().z > thisCoords.z + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// Hit boundary, revert x axis
		player.direction.z = -player.direction.z;
	}
	else if (player.transform.getPos().z < thisCoords.z - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// Hit boundary, revert x axis
		player.direction.z = -player.direction.z;
	}

	return player;
}

// Collision check for bottom left corner tile
Player CornerTile_BL::CheckCollisions(Player player)
{
	// Check on X axis - left boundary
	if (player.transform.getPos().x < thisCoords.x - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// hit left boundary
		player.direction.x = -player.direction.x;
	}
	// Check x axis - left side of cube corner boundary
	else if (player.transform.getPos().x > thisCoords.x + (4 - radius) && // Far enough to the right on x to hit square
		player.transform.getPos().z > thisCoords.z - 5 && // Between upper limit of tile/square
		player.transform.getPos().z < thisCoords.z - 4) // and lower limit of square
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// Hit going right, reflect on x
		player.direction.x = -player.direction.x;
	}
	// Check z axis - lower boundary
	if (player.transform.getPos().z > thisCoords.z + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// hit middle
		player.direction.z = -player.direction.z;
	}
	// Check z axis - lower side of cube corner boundary
	else if (player.transform.getPos().z < thisCoords.z - (4 - radius) &&
		player.transform.getPos().x > thisCoords.x + 4 &&
		player.transform.getPos().x < thisCoords.x + 5)
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// Hit going up, reflect on z
		player.direction.z = -player.direction.z;
	}

	return player;
}

// Collision check for bottom right corner tile
Player CornerTile_BR::CheckCollisions(Player player)
{
	// Axis seems odd since tile has been rotated
	// Check on X axis - left boundary
	if (player.transform.getPos().x > thisCoords.x + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// hit left boundary
		player.direction.x = -player.direction.x;
	}
	// Check x axis - left side of cube corner boundary
	else if (player.transform.getPos().x < thisCoords.x - (4 - radius) && // Far enough to the right on x to hit square
		player.transform.getPos().z > thisCoords.z - 5 && // Between upper limit of tile/square
		player.transform.getPos().z - 4) // and lower limit of square
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// Hit going right, reflect on x
		player.direction.x = -player.direction.x;
	}
	// Check z axis - lower boundary
	if (player.transform.getPos().z  > thisCoords.z + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// hit middle
		player.direction.z = -player.direction.z;
	}
	// Check z axis - lower side of cube corner boundary
	else if (player.transform.getPos().z < thisCoords.z - (4 - radius) &&
		player.transform.getPos().x > thisCoords.x - 5 &&
		player.transform.getPos().x < thisCoords.x - 4)
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// Hit going up, reflect on z
		player.direction.z = -player.direction.z;

	}
	return player;
}

// Collision check for top left corner tile
Player CornerTile_TL::CheckCollisions(Player player)
{
	// Axis seems odd since tile has been rotated
	// Check on X axis - left boundary
	if (player.transform.getPos().x < thisCoords.x - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// hit left boundary
		player.direction.x = -player.direction.x;
	}
	// Check x axis - left side of cube corner boundary
	else if (player.transform.getPos().x > thisCoords.x + (4 - radius) && // Far enough to the right on x to hit square
		player.transform.getPos().z > thisCoords.z + 4 && // Between upper limit of tile/square
		player.transform.getPos().z < thisCoords.z + 5) // and lower limit of square
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// Hit going right, reflect on x
		player.direction.x = -player.direction.x;
	}
	// Check z axis - lower boundary
	if (player.transform.getPos().z < thisCoords.z - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// hit middle
		player.direction.z = -player.direction.z;
	}
	// Check z axis - lower side of cube corner boundary
	else if (player.transform.getPos().z > thisCoords.z + (4 - radius) &&
		player.transform.getPos().x > thisCoords.x + 4 &&
		player.transform.getPos().x < thisCoords.x + 5)
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// Hit going up, reflect on z
		player.direction.z = -player.direction.z;
	}
	return player;
}

// Collision check for top right corner tile
Player CornerTile_TR::CheckCollisions(Player player)
{
	// Axis seems odd since tile has been rotated
	// Check on X axis - right boundary
	if (player.transform.getPos().x > thisCoords.x + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// hit left boundary
		player.direction.x = -player.direction.x;
	}
	// Check x axis - left side of cube corner boundary
	else if (player.transform.getPos().x < thisCoords.x - (4 - radius) && // Far enough to the right on x to hit square
		player.transform.getPos().z > thisCoords.z + 4 && // Between upper limit of tile/square
		player.transform.getPos().z < thisCoords.z + 5) // and lower limit of square
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// Hit going right, reflect on x
		player.direction.x = -player.direction.x;
	}
	// Check z axis - lower boundary
	if (player.transform.getPos().z < thisCoords.z - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// hit middle
		player.direction.z = -player.direction.z;
	}
	// Check z axis - lower side of cube corner boundary
	else if (player.transform.getPos().z > thisCoords.z + (4 - radius) &&
		player.transform.getPos().x > thisCoords.x - 5 &&
		player.transform.getPos().x < thisCoords.x - 4)
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// Hit going up, reflect on z
		player.direction.z = -player.direction.z;
	}
	return player;
}

// Ramp - set y position of player on ramp accordingly
Player UpRampDown::SetPlayerHeight(Player player)
{
	// First find how much to increment y for every 1 in z
	float yInc = thisCoords.y / (size / 2);
	// Then find distance travelled along tile
	float difference = player.transform.getPos().z - thisCoords.z;
	// Make relative to tile coords by adding half size
	float y = yInc * (difference + (size / 2));
	// Update player pos
	player.transform.getPos().y = y + 1;

	return player;
}

// Collisions check for end tile
Player EndTile::CheckCollisions(Player player)
{
	// Based on direction
	if (outDir.going_up)
	{
		// Check on X axis - boundaries either side
		if (player.transform.getPos().x > thisCoords.x + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x + (4 - radius);
			// Hit boundary, revert x axis
			player.direction.x = -player.direction.x;
		}
		else if (player.transform.getPos().x < thisCoords.x - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x - (4 - radius);
			// Hit boundary, revert x axis
			player.direction.x = -player.direction.x;
		}
		// Check on z axis - just one boundary
		if (player.transform.getPos().z < thisCoords.z - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z - (4 - radius);
			// hit, revert z axis
			player.direction.z = -player.direction.z;
		}
	}
	else if (outDir.going_down)
	{
		// Check on X axis - boundaries either side
		if (player.transform.getPos().x > thisCoords.x + (4 - radius)) 
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x + (4 - radius);
			// Hit boundary, revert x axis
			player.direction.x = -player.direction.x;
		}
		else if (player.transform.getPos().x < thisCoords.x - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x - (4 - radius);
			// Hit boundary, revert x axis
			player.direction.x = -player.direction.x;
		}
		// Check on z axis - just one boundary
		if (player.transform.getPos().z > thisCoords.z + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z + (4 - radius);
			// hit, revert z axis
			player.direction.z = -player.direction.z;
		}
	}
	else if (outDir.going_left)
	{
		// Check on z axis - boundaries either side
		if (player.transform.getPos().z < thisCoords.z - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z - (4 - radius);
			// hit, revert z axis
			player.direction.z = -player.direction.z;
		}
		else if (player.transform.getPos().z > thisCoords.z + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z + (4 - radius);
			// hit, revert z axis
			player.direction.z = -player.direction.z;
		}
		// Check on x - boundary to left
		if (player.transform.getPos().x < thisCoords.x - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x - (4 - radius);
			// hit, revert on x
			player.direction.x = -player.direction.x;
		}
	}
	else if (outDir.going_right)
	{
		// Check on z axis - boundaries either side
		if (player.transform.getPos().z < thisCoords.z - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z - (4 - radius);
			// hit, revert on z
			player.direction.z = -player.direction.z;
		}
		else if (player.transform.getPos().z > thisCoords.z + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z + (4 - radius);
			// hit, revert on z
			player.direction.z = -player.direction.z;
		}
		// Check on x - boundary to right
		if (player.transform.getPos().x > thisCoords.x + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x + (4 - radius);
			// hit, reflect on x
			player.direction.x = -player.direction.x;
		}
	}
	// Check if over end hole
	if (player.transform.getPos().x > thisCoords.x - 0.75 && player.transform.getPos().x < thisCoords.x + 0.75 &&
		player.transform.getPos().z > thisCoords.z - 0.75 && player.transform.getPos().z < thisCoords.z + 0.75)
	{
		if(player.speed < 2.0f)
		{
			// Apply gravity
			player.direction.y -= 0.2f;
			ballInHole = true;
		}
	}
	return player;
}