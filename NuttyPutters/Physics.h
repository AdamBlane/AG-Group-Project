#pragma once
#include "Player.h"

class Physics
{
public:
	Physics() {}
	~Physics() {}

	// gravity
	glm::dvec3 gravity = vec3(0.0f, -9.8f, 0.0f);
	// Always multiplied by gravity; either 1/0 & et in ApplyGravity()
	double gravFlag;
	// Margin of error, determines when to stop player
	double epsilon = 0.5;
	// friction
	glm::dvec3 friction;
	double frictionScalar = -15.9;
	// account for aerodynamic drag
	//float drag = 0.9f;

	// Resitance vector
	//glm::vec3 rampUpResistance;
	//float rampRes = -10.9f;


	// R = -gravity * sine(theta) (add theta property to each tile)
	// Apply this to the z axis only



	// All ramps have same angle of 20 degrees 
	// Cosine(20) = 0.93969256961


	// Generates impulse vector for player 
	// (normal usage, uses player members for dir & vel
	void Fire(Player &player, double magnitude);
	void RampResistance(Player &player, double magnitude);
	void Jump(Player &player, double magnitude);
	// Work out whether or not to apply gravity
	void ApplyGravity(Player &player, float floorLevel);
	// Semi-implicit Euler method
	void Integrate(Player &player, double dt, float floorLevel);
};