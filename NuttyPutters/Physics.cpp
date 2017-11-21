#include "Physics.h"
#include <iostream>

// Impulse vector needs player direction, and magnitude is gained from
// accumulated float value from holding space
Player Physics::AddImpulse(Player player, float magnitude)
{
	// Set player's impulse vector
	player.impulse = player.direction * magnitude;
	// Divide by mass
	player.impulse /= player.mass;
	// Add to velocity
	player.velocity += player.impulse;
	// Reset impulse to zero
	player.impulse.x = 0.0f;
	player.impulse.y = 0.0f;
	player.impulse.z = 0.0f;

	return player;
}

Player Physics::Jump(Player player, float mag)
{
	player.impulse = player.direction;
	player.impulse.y += mag;
	player.velocity += player.impulse;
	player.impulse.x = 0.0f;
	player.impulse.y = 0.0f;
	player.impulse.z = 0.0f;

	return player;
}

// Either be 1 or 0 - 1 if in air, 0 if on floor
// This is always multiplied by gravity
void Physics::ApplyGravity(Player player, float tilePosY, float floorGap)
{
	// Vars used for grav formula
	float Py = player.transform.getPos().y; 
	float Ty = tilePosY;
	float f = floorGap;
	// This will equate to either 0 or 1, thus applying gravity when required 
	gravFlag = ceil((Py - (Ty + f)) / Py);
	if (gravFlag == 1)
		gravity.y = -9.8f;
}


// Using semi-implicit Euler integration method
Player Physics::Integrate(Player player, float dt)
{
	// Work out friction first
	friction = normalize(player.velocity) * frictionScalar;
	// Don't apply to y
	friction.y = 0.0f;
	
	// If gravFlag is 0, then there shouldn't be gravity applied. 
	// Clear any accrued gravity in player velocity
	//player.velocity.y *= gravFlag;
	// TODO when the player hits the floor, reset their vel.y to 0 ONCE
	if (player.transform.getPos().y < 1.0f)
	{
		player.velocity.y = 0.0f;
		player.transform.getPos().y = 1.0f;
	}

	// Multiply gravity by flag to determine whether or not it should affect vel
	gravity *= gravFlag;
	

	// Add all forces together, divide by mass and find value for this timestep (by * dt)
	player.velocity += ((friction + gravity + rampUpResistance) / player.mass) * dt; 
	//std::cout << "V: " << player.velocity.x << ", " << player.velocity.y << ", " << player.velocity.z << std::endl;
	
	// Player velocity will never reach zero, since friction is a percentage of vel
	// Check for when speed (magnitude of velocity) is below epsilon and just stop it
	float magnitude = (player.velocity.x * player.velocity.x) + (player.velocity.z * player.velocity.z);
	if (magnitude < epsilon * epsilon)
		player.velocity.x = player.velocity.z = 0.0f;
		
	// Flip switch if stationary
	if (player.velocity == vec3(0, 0, 0))
		player.isMoving = false;
	else
		player.isMoving = true;


	// When on a ramp
	// return difference between where player SHOULD be on Y and where they actually are on Z
	// times this difference by delta time
	// add this into velocity.y

	// Update position with velocity
	player.transform.getPos() += player.velocity * dt; // WHY * dt twice? 




	return player;
}