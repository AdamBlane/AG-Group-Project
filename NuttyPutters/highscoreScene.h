#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
#include <time.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
#include <sstream>
// Internals
#include "Mesh.h"
#include "Transform.h"
#include "target_camera.h"
#include "Shader.h"


class highscoreScene
{
public:
	// Default constructor
	highscoreScene();
	// Deconstructor
	~highscoreScene();

	// Used to lock framerate
	double lastFrame = 0;
	double thisFrame = glfwGetTime();
	float dt = 0.016; // Lock to 60fps

	Transform optionSceneTransform;

	bool buttonPressed[18] = { false };
	bool isFunctionEmpty = false;
	int meshesInScene = 24; // Used so everytime a mesh is added the number doesnt need updating

	// BUTTONS
	// A/Sqaure = 0
	// B/X(PS) = 1
	// X(XB)/Circle = 2
	// Y/Triangle = 3
	// LB/L1 = 4
	// RB/R1 = 5
	// Back/L2 = 6
	// Start/R2 = 7
	// Left Stick Push/Select = 8
	// Right Stick Push/Start = 9
	// DPAD UP/Left Stick Push = 10
	// DPAD LEFT/Right Stick Push = 11
	// DPAD DOWN/PS Button =12
	// DPAD RIGHT/Pad = 13
	// /DPAD UP = 14
	// /DPAD LEFT = 15 
	// /DPAD DOWN = 16
	// /DPAD RIGHT = 17

	// FUCTIONS
	// Select/fire = 0
	// Back/Reset = 1
	// Pause = 2
	// DPAD UP = 3
	// DPAD LEFT = 4
	// DPAD DOWN = 5
	// DPAD RIGHT = 6

	// Draw stuff
	void Loop(GLFWwindow* win);
	// Input 
	void Input(GLFWwindow* win);
	// Setup
	void Init(GLFWwindow* win);
	// Update
	void Update(GLFWwindow* window);
	// Render
	void Render(GLFWwindow* window);
};