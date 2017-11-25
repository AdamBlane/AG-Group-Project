#include "Physics.h"
#include <iostream>

// Impulse vector needs player direction, and magnitude is gained from
// accumulated float value from holding space
void Physics::Fire(Player &player, float magnitude)
{
	// Impulse normal is direction. The impulse is scaled by magnitude
	player.impulse = player.direction * magnitude;
	// Divide by mass
	player.impulse /= player.mass;
	// Add to velocity
	player.velocity += player.impulse;
	// Reset impulse to zero
	player.impulse.x = 0.0f;
	player.impulse.y = 0.0f;
	player.impulse.z = 0.0f;

}


// Impulse vector responsible for pushing player back down ramp
void Physics::RampResistance(Player &player, float magnitude)
{
	// Manually set direction to -z for going back down ramps (they're always going up +z!)
	player.impulse.z += magnitude;
	// Divide by mass
	player.impulse.z /= player.mass;
	// Add to velocity
	player.velocity += player.impulse;
	// Clear impulse after
	player.impulse.x = 0.0f;
	player.impulse.y = 0.0f;
	player.impulse.z = 0.0f;

}


// Jump
void Physics::Jump(Player &player, float magnitude)
{
	// Manually set direction to y for jumping up
	player.impulse.y += magnitude;
	// Divide by mass
	player.impulse.y /= player.mass;
	// Add to velocity
	player.velocity += player.impulse;
	// Clear impulse after
	player.impulse.x = 0.0f;
	player.impulse.y = 0.0f;
	player.impulse.z = 0.0f;

}


// Either be 1 or 0 - 1 if in air, 0 if on floor
// This is always multiplied by gravity
void Physics::ApplyGravity(Player &player, float floorLevel)
{
	// Vars used for grav formula
	float Py = player.transform.getPos().y; 
	float Ty = floorLevel - 1; // Player position on floor subtract floor gap
	float f = 1; // Floor gap
	// This will equate to either 0 or 1, thus applying gravity when required 
	gravFlag = ceil((Py - (Ty + f)) / Py);
	if (gravFlag == 1)
		gravity.y = -9.8f;
	else
		gravFlag = 0; // Got -1 before :(

}


// Using semi-implicit Euler integration method
void Physics::Integrate(Player &player, float dt, float floorLevel)
{
	// Work out friction first
	friction = normalize(player.velocity) * frictionScalar;
	// Don't apply to y
	friction.y = 0.0f;
	
	// If the player has reached end hole, set new lower floor level
	if (player.ballInHole)
	{
		// Set lower floot limit
		floorLevel = -500.0f;
		// Apply and set gravity
		gravFlag = 1;
		gravity.y = -9.8f;
	}
	// If the player has since fallen through the hole and is near bottom of skybox
	if (player.transform.getPos().y < -490.0f)
	{
		// Teleport playyer to top of skybox
		player.transform.getPos().y = 480.0f;
		// clear vel and reset position
		player.velocity.x = player.velocity.z = 0.0f;
		player.transform.getPos().x = player.transform.getPos().z = 0.0f;
		// reset ball in hole
		player.ballInHole = false;
		// player is now falling
		player.isFalling = true;
	}
	
	// If the goes below the ground, reset its position to floor level and clear any accrued gravity
	if (player.transform.getPos().y < floorLevel) // This 1.0f should be (floor level)
	{
		// Move to floor level
		player.transform.getPos().y = floorLevel;
		
		// Bounce with enough downwards force
		if (abs(player.velocity.y) > epsilon)
		{
			// Reverse y direction; bounce
			player.velocity.y = -player.velocity.y;
			// Remove some velocity from damping
			if (player.isFalling)
			{
				player.velocity.y = 0.0f;
				player.isFalling = false;
			}
				
			else
				player.velocity.y *= 0.5f;
			//player.velocity.y /= player.mass;
		}
		// Not enough downwards force; stop bouncing
		else
		{
			player.velocity.y = 0.0f;		
		}

		
	}

	// Multiply gravity by flag to determine whether or not it should affect vel
	gravity *= gravFlag;

	// Add all forces together, divide by mass and find value for this timestep (by * dt)
	player.velocity += ((friction + gravity) / player.mass) * dt; 
	
	
	// Player velocity will never reach zero, since friction is a percentage of vel
	// Check for when speed (magnitude of velocity) is below epsilon and just stop it
	float magnitude = (player.velocity.x * player.velocity.x) + (player.velocity.z * player.velocity.z);
	if (magnitude < epsilon * epsilon)
		player.velocity.x = player.velocity.z = 0.0f;
		
	// Flip switch if stationary
	if (player.velocity == vec3(0, 0, 0))
		player.isMoving = false;
	

	//std::cout << "V " << player.velocity.x << ", " << player.velocity.y << ", " << player.velocity.z << std::endl;


	// Update position with velocity
	player.transform.getPos() += player.velocity * dt; // WHY * dt twice? 

}