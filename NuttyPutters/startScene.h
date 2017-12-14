#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
#include <time.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>

// Internals
#include "Mesh.h"
#include "Transform.h"
#include "target_camera.h"
#include "Shader.h"

class startScene
{
public:
	// Default constructor
	startScene() {}
	// Deconstructor
	~startScene() {}
  


	//Route length for 2 spaceships
	float routeLength1;
	float routeLength2;
	float speed;
	float yPos1;
	float yPos2;
	bool soundPlaying = false;
	// Render splash screen or not
	bool loaded = false;

	// Used to lock framerate
	double lastFrame = 0;
	double thisFrame = glfwGetTime();
	float dt = 0.016; // Lock to 60fps for first frame

	// Used for navigating through menu options
	float total_time = 5.0f;

	int previousMenuItem, currentMenuItem;

	// Used for navigating through menu options
	// ID number determines which button should be highlighted
	// 1 - Play
	// 2 - Load
	// 3 - Highscore
	// 4 - Options
	// 5 - Internet
	// 6 - Exit
	int button_manager = 1;
	// Enforce time delay before select may be pressed upon loading this scene
	int selectCooldown, selectCooldownMax = 250;
	// Flags for button presses; logic occurs on release after being pressed
	bool upPressed, downPressed, selectPressed;

	// Setup GLFW joystick button input - required for doing anything with buttons
	int controllerOneButtonCount;
	const unsigned char *controllerOne;
	int controllerOneAxisCount;
	const float *controllerOneAxis;


	// Main logic loop for this scene
	void Loop(GLFWwindow* win);
	// Input 
	void Input(GLFWwindow* win);
	// First time setup; show splash screen & load assets
	void FirstTimeInit(GLFWwindow* win);
	// Setup
	void Init(GLFWwindow* win);
	// Update
	void Update(GLFWwindow* window);
	// Render
	//Tracks Mouse
	void Track_Mouse(GLFWwindow* win);
	void Render(GLFWwindow* window);
	// For mouse button actions
	void Click_or_Enter(GLFWwindow* window);
	//to track and change textures
	void ChangeTexutes(GLFWwindow* win);
};
