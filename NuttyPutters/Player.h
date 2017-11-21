#pragma once
#include "Transform.h"

class Player
{
public:
	Transform transform;
	Transform arrowTransform;
	glm::vec3 velocity; // added to position in transform each frame
	glm::vec3 impulse; // direction * power 
	glm::vec3 direction; // dir camera is facing
	float power; // accumulated counter from holding fire
	float mass = 1;
	bool isMoving = false;
	bool onUpRamp = false;
	bool ballInHole = false;
};