#pragma once
#include "Transform.h"

class Player
{
public:
	Transform transform;
	Transform arrowTransform;
	glm::vec3 velocity;
	glm::vec3 direction;
	float speed;
	bool isMoving = false;
	bool ballInHole = false;
};