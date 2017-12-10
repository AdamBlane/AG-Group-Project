#pragma once
#include "Transform.h"
#include <string>

using namespace std;

class Player
{
public:
	Player() {}
	Player(string inputConfigFilePath);
	~Player() {}

	// Physics related properties
	Transform transform;
	Transform arrowTransform;
	glm::dvec3 velocity; // added to position in transform each frame
	glm::dvec3 impulse; // direction * power 
	glm::dvec3 direction; // dir camera is facing
	double power; // accumulated counter from holding fire
	bool powerIncreasing = true; // is power accumulator increasing/decreasing
	double mass = 1.2;
	double radius = 0.5;

	// Movement
	int currentTile = 0; // For spatial partitioning
	int jumpCounter = 0;
	float floorLevel;
	bool isMoving = false; // Physics is only applied when moving
	bool ballInHole = false; // Has the player reached end hole
	bool isFalling = false;
	double chaseCamAngle;
	 
	// Gameplay
	int id;
	int strokeCounter = 0;
	int currentPowerup = 0;
	int totalTime = 0;
	int finalScore = 0;
	bool gameOver = false;
	// Input
	// Action isPressed flags
	bool firePressed, firePressedC;
	bool jumpPressed, jumpPressedC;
	bool upPressed, upPressedC;
	bool downPressed, downPressedC;
	bool leftPressed, leftPressedC;
	bool rightPressed, rightPressedC;
	bool zoomInPressed, zoomInPressedC;
	bool zoomOutPressed, zoomOutPressedC;

	// Keyboard input members
	int fireButtton, jumpButton, upButton,
		downButton, leftButton, rightButton,
		zoomInButton, zoomOutButton;
	int fireButtonC;
};