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

	// BUTTONS
	// A/Sqaure = 0
	// B/X(PS) = 1
	// X(XB)/Circle = 2
	// Y/Triangle = 3
	// /L1 = 4
	// /R1 = 5
	// /L2 = 6
	// /R2 = 7
	// /Select = 8
	// /Start = 9
	// /Left Stick Push = 10
	// /Right Stick Push = 11
	// /PS Button =12
	// /Pad = 13
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