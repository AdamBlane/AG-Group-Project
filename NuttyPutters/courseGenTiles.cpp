
#include "courseGenTiles.h"

// THIS file includes collision check functions for each tile type
// These tiles are used in the algorithm to generate a course


// Set coords of this tile
void BaseTile::SetCoords(vec3 coords) {	thisCoords = coords; }

// Set next coords of this tile
void BaseTile::SetNextCoords(vec3 coords) {	nextCoords = coords; }

// Getter of next coords
vec3 BaseTile::GetNextCoords() { return nextCoords; }

// Getter of this coords
vec3 BaseTile::GetThisCoords() { return thisCoords; }

// This is called on each tile; spatial partitioning method
// Returns true if player is on this tile
bool BaseTile::isPlayerOnTile(vec3 playerPos)
{
	// Match on x first
	if (playerPos.x > thisCoords.x - 5 && playerPos.x < thisCoords.x + 5)
	{
		// Then on z
		if (playerPos.z > thisCoords.z - 5 && playerPos.z < thisCoords.z + 5)
		{
			// Player is on this tile
			return true;
		}
	}
	return false;
}

// Collision check for start tile
void StartTile::CheckCollisions(Player &player)
{
	// Check on X axis - boundaries either side
	if (player.transform.getPos().x > thisCoords.x + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// Hit boundary, revert x axis
		player.velocity.x = -player.velocity.x;
	}
	else if (player.transform.getPos().x < thisCoords.x - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// Hit boundary, reflect on x
		player.velocity.x = -player.velocity.x;
	}
	// Check on z axis - just one boundary
	if (player.transform.getPos().z < thisCoords.z - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// hit, revert z axis
		player.velocity.z = -player.velocity.z;

	}
}

// Collision check for straight vertical tile
void StraightTile_V::CheckCollisions(Player &player)
{
	// Check on X axis - boundaries either side
	if (player.transform.getPos().x > thisCoords.x + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// Hit boundary, revert x axis
		player.velocity.x = -player.velocity.x;
	}
	else if (player.transform.getPos().x < thisCoords.x - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// Hit boundary, revert x axis
		player.velocity.x = -player.velocity.x;

	}

}

// Collision check for straight horizontal tile
void StraightTile_H::CheckCollisions(Player &player)
{
	// Check on X axis - boundaries either side
	if (player.transform.getPos().z > thisCoords.z + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// Hit boundary, revert x axis
		player.velocity.z = -player.velocity.z;
	}
	else if (player.transform.getPos().z < thisCoords.z - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// Hit boundary, revert x axis
		player.velocity.z = -player.velocity.z;
	}

}

// Collision check for bottom left corner tile
void CornerTile_BL::CheckCollisions(Player &player)
{
	// Check on X axis - left boundary
	if (player.transform.getPos().x < thisCoords.x - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// hit left boundary
		player.velocity.x = -player.velocity.x;
	}
	// Check x axis - left side of cube corner boundary
	else if (player.transform.getPos().x > thisCoords.x + (4 - radius) && // Far enough to the right on x to hit square
		player.transform.getPos().z > thisCoords.z - 5 && // Between upper limit of tile/square
		player.transform.getPos().z < thisCoords.z - 4) // and lower limit of square
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// Hit going right, reflect on x
		player.velocity.x = -player.velocity.x;
	}
	// Check z axis - lower boundary
	if (player.transform.getPos().z > thisCoords.z + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// hit middle
		player.velocity.z = -player.velocity.z;
	}
	// Check z axis - lower side of cube corner boundary
	else if (player.transform.getPos().z < thisCoords.z - (4 - radius) &&
		player.transform.getPos().x > thisCoords.x + 4 &&
		player.transform.getPos().x < thisCoords.x + 5)
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// Hit going up, reflect on z
		player.velocity.z = -player.velocity.z;
	}

}

// Collision check for bottom right corner tile
void CornerTile_BR::CheckCollisions(Player &player)
{
	// Axis seems odd since tile has been rotated
	// Check on X axis - left boundary
	if (player.transform.getPos().x > thisCoords.x + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// hit left boundary
		player.velocity.x = -player.velocity.x;
	}
	// Check x axis - left side of cube corner boundary
	else if (player.transform.getPos().x < thisCoords.x - (4 - radius) && // Far enough to the right on x to hit square
		player.transform.getPos().z > thisCoords.z - 5 && // Between upper limit of tile/square
		player.transform.getPos().z < thisCoords.z - 4) // and lower limit of square
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// Hit going right, reflect on x
		player.velocity.x = -player.velocity.x;
	}
	// Check z axis - lower boundary
	if (player.transform.getPos().z  > thisCoords.z + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// hit middle
		player.velocity.z = -player.velocity.z;
	}
	// Check z axis - lower side of cube corner boundary
	else if (player.transform.getPos().z < thisCoords.z - (4 - radius) &&
		player.transform.getPos().x > thisCoords.x - 5 &&
		player.transform.getPos().x < thisCoords.x - 4)
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// Hit going up, reflect on z
		player.velocity.z = -player.velocity.z;
	}

}

// Collision check for top left corner tile
void CornerTile_TL::CheckCollisions(Player &player)
{
	// Axis seems odd since tile has been rotated
	// Check on X axis - left boundary
	if (player.transform.getPos().x < thisCoords.x - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// hit left boundary
		player.velocity.x = -player.velocity.x;
	}
	// Check x axis - left side of cube corner boundary
	else if (player.transform.getPos().x > thisCoords.x + (4 - radius) && // Far enough to the right on x to hit square
		player.transform.getPos().z > thisCoords.z + 4 && // Between upper limit of tile/square
		player.transform.getPos().z < thisCoords.z + 5) // and lower limit of square
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// Hit going right, reflect on x
		player.velocity.x = -player.velocity.x;
	}
	// Check z axis - lower boundary
	if (player.transform.getPos().z < thisCoords.z - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// hit middle
		player.velocity.z = -player.velocity.z;
	}
	// Check z axis - lower side of cube corner boundary
	else if (player.transform.getPos().z > thisCoords.z + (4 - radius) &&
		player.transform.getPos().x > thisCoords.x + 4 &&
		player.transform.getPos().x < thisCoords.x + 5)
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// Hit going up, reflect on z
		player.velocity.z = -player.velocity.z;
	}

}

// Collision check for top right corner tile
void CornerTile_TR::CheckCollisions(Player &player)
{
	// Axis seems odd since tile has been rotated
	// Check on X axis - right boundary
	if (player.transform.getPos().x > thisCoords.x + (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x + (4 - radius);
		// hit left boundary
		player.velocity.x = -player.velocity.x;
	}
	// Check x axis - left side of cube corner boundary
	else if (player.transform.getPos().x < thisCoords.x - (4 - radius) && // Far enough to the right on x to hit square
		player.transform.getPos().z > thisCoords.z + 4 && // Between upper limit of tile/square
		player.transform.getPos().z < thisCoords.z + 5) // and lower limit of square
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().x = thisCoords.x - (4 - radius);
		// Hit going right, reflect on x
		player.velocity.x = -player.velocity.x;
	}
	// Check z axis - lower boundary
	if (player.transform.getPos().z < thisCoords.z - (4 - radius))
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z - (4 - radius);
		// hit middle
		player.velocity.z = -player.velocity.z;
	}
	// Check z axis - lower side of cube corner boundary
	else if (player.transform.getPos().z > thisCoords.z + (4 - radius) &&
		player.transform.getPos().x > thisCoords.x - 5 &&
		player.transform.getPos().x < thisCoords.x - 4)
	{
		// Move away from boundary so as not to retrigger this
		player.transform.getPos().z = thisCoords.z + (4 - radius);
		// Hit going up, reflect on z
		player.velocity.z = -player.velocity.z;
	}

}

// Ramp - set y position of player on ramp accordingly
float UpRampDown::SetPlayerHeight(Player player)
{
	// First find how much to increment y for every 1 in z
	float yInc = thisCoords.y / (size / 2);
	// Then find distance travelled along tile
	float difference = player.transform.getPos().z - thisCoords.z;
	// Make relative to tile coords by adding half size
	float y = yInc * (difference + (size / 2));
	// We now have the exact y position to match in z, so player is level on floor
	// Updating player position manually places him there
	//player.transform.getPos().y = y + 1;

	// This is also dy, which needs to be scaled by dt to add an impulse in y direction
	// this is the alternate; forcibly pushing the player upwards to appear level
	return y + 1; // was return player
}

float DownRampDown::SetPlayerHeight(Player player)
{
	// First find how much to increment y for every 1 in z
	float yInc = thisCoords.y / (size / 2);
	// Then find distance travelled along tile
	float difference = player.transform.getPos().z - thisCoords.z;
	// Make relative to tile coords by adding half size
	float y = yInc * (difference - (size / 2));
	// We now have the exact y position to match in z, so player is level on floor
	// Updating player position manually places him there
	//player.transform.getPos().y = y + 1;

	// This is also dy, which needs to be scaled by dt to add an impulse in y direction
	// this is the alternate; forcibly pushing the player upwards to appear level
	return y + 1; // was return player
}

// Collisions check for end tile
void EndTile::CheckCollisions(Player &player)
{
	// Based on velocity
	if (outDir.going_up)
	{
		// Check on X axis - boundaries either side
		if (player.transform.getPos().x > thisCoords.x + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x + (4 - radius);
			// Hit boundary, revert x axis
			player.velocity.x = -player.velocity.x;
		}
		else if (player.transform.getPos().x < thisCoords.x - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x - (4 - radius);
			// Hit boundary, revert x axis
			player.velocity.x = -player.velocity.x;
		}
		// Check on z axis - just one boundary
		if (player.transform.getPos().z < thisCoords.z - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z - (4 - radius);
			// hit, revert z axis
			player.velocity.z = -player.velocity.z;
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
			player.velocity.x = -player.velocity.x;
		}
		else if (player.transform.getPos().x < thisCoords.x - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x - (4 - radius);
			// Hit boundary, revert x axis
			player.velocity.x = -player.velocity.x;
		}
		// Check on z axis - just one boundary
		if (player.transform.getPos().z > thisCoords.z + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z + (4 - radius);
			// hit, revert z axis
			player.velocity.z = -player.velocity.z;
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
			player.velocity.z = -player.velocity.z;
		}
		else if (player.transform.getPos().z > thisCoords.z + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z + (4 - radius);
			// hit, revert z axis
			player.velocity.z = -player.velocity.z;
		}
		// Check on x - boundary to left
		if (player.transform.getPos().x < thisCoords.x - (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x - (4 - radius);
			// hit, revert on x
			player.velocity.x = -player.velocity.x;
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
			player.velocity.z = -player.velocity.z;
		}
		else if (player.transform.getPos().z > thisCoords.z + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().z = thisCoords.z + (4 - radius);
			// hit, revert on z
			player.velocity.z = -player.velocity.z;
		}
		// Check on x - boundary to right
		if (player.transform.getPos().x > thisCoords.x + (4 - radius))
		{
			// Move away from boundary so as not to retrigger this
			player.transform.getPos().x = thisCoords.x + (4 - radius);
			// hit, reflect on x
			player.velocity.x = -player.velocity.x;
		}
	}
	// Check if over end hole
	if (player.transform.getPos().x > thisCoords.x - 0.75 && player.transform.getPos().x < thisCoords.x + 0.75 &&
		player.transform.getPos().z > thisCoords.z - 0.75 && player.transform.getPos().z < thisCoords.z + 0.75)
	{
		if(length(player.velocity) < 2.0f)
		{
			// Apply gravity
			//player.velocity.y -= 0.2f;
			player.ballInHole = true;
		}
	}

}