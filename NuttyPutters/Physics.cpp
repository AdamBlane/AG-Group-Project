#include "Physics.h"
#include <iostream>

// Impulse vector needs player direction, and magnitude is gained from
// accumulated float value from holding space
void Physics::Fire(Player &player, double magnitude)
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
void Physics::RampResistance(Player &player, double magnitude)
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
void Physics::Jump(Player &player, double magnitude)
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
	//float Ty = floorLevel - 1; // Player position on floor subtract floor gap
//	float f = 1; // Floor gap
	// This will equate to either 0 or 1, thus applying gravity when required 
	//gravFlag = ceil((Py - abs(Ty + f)) / Py);
	
	// If player position subtract floor level is 0, player is on/under floor
	if (Py - floorLevel <= 0)
	{

		gravFlag = 0;
		player.jumpCounter = 0; // Or this function returns 1/0 which is always * by jC
	}
	else
	{
		gravFlag = 1;
		gravity.y = -9.8f;
		//cout << "In air: " << Py - floorLevel << endl;
	}
	
	// If the player has since fallen through the hole and is near bottom of skybox 
	if (Py < -489.0f)
	{
		// Tp to side
		//player.transform.getPos().x = 480.0f;
		// Teleport player to top of skybox
		player.transform.getPos().y = 480.0f;
		// Reduce accrued gravity
		//player.velocity.y = -1.0;
		// clear vel and reset position
		player.velocity.x = player.velocity.z = 0.0;
		player.transform.getPos().x = player.transform.getPos().z = 0.0;
		// reset ball in hole
		player.ballInHole = false;
		// player is now falling
		player.isFalling = true;
	}

	// If it's a 1, player is in the air
	//if (gravFlag == 1)
	//	// Ensure gravity is correct 
	//	gravity.y = -9.8f;
	//// Otherwise, player is at floor level
	//else
	//{
	//	gravFlag = 0; // In case of -1
	//	
	//}


}


// Using semi-implicit Euler integration method
void Physics::Integrate(Player &player, double dt, float floorLevel)
{
	// Work out friction first
	friction = normalize(player.velocity) * frictionScalar;
	// Don't apply to y
	friction.y = 0.0;
	
	// If the player has reached end hole, set new lower floor level
	// THIS ISN'T PHYSICS YO
	//if (player.ballInHole)
	//{
	//	// Set lower floot limit
	//	floorLevel = -490.0f;
	//	// Apply and set gravity
	//	// TODO REMOVE THIS SHIT
	//	gravFlag = 1;
	//	gravity.y = -9.8;
	//}


	// MORE NOT PHYSICS
	if (player.transform.getPos().y < floorLevel && !player.ballInHole)
	{
		// Move to floor level
		player.transform.getPos().y = floorLevel;

		// Bounce with enough downwards force
		if (abs(player.velocity.y) > epsilon)
		{
			// Don't bounce if falling onto new level
			if (player.isFalling)
			{
				// Just stop!
				player.velocity.y = 0.0;
				player.isFalling = false;
			}
			// Remove some velocity from damping
			else
			{
				player.velocity.y *= 0.5;
				player.velocity.y /= player.mass;
			}
			// Reverse y direction; bounce
			player.velocity.y = -player.velocity.y;
		}
		// Not enough downwards force; stop bouncing
		else
		{
			player.velocity.y = 0.0;
		}
	}
	
	// If the goes below the ground, reset its position to floor level and clear any accrued gravity
	

	// Multiply gravity by flag to determine whether or not it should affect vel
	gravity *= gravFlag;

	// Add all forces together, divide by mass and find value for this timestep (by * dt)
	player.velocity += ((friction + gravity) / player.mass) * dt; 
	
	
	// Player velocity will never reach zero, since friction is a percentage of vel
	// Check for when speed (magnitude of velocity) is below epsilon and just stop it
	float magnitude = (player.velocity.x * player.velocity.x) + (player.velocity.z * player.velocity.z);
	if (magnitude < epsilon * epsilon)
		player.velocity.x = player.velocity.z = 0.0;
		
	// Flip switch if stationary
	if (player.velocity == dvec3(0, 0, 0))
		player.isMoving = false;
	

	//std::cout << "V " << player.velocity.x << ", " << player.velocity.y << ", " << player.velocity.z << std::endl;


	// Update position with velocity
	player.transform.getPos() += player.velocity * dt; 


}