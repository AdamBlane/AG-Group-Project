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
	int selectCooldown, selectCooldownMax = 300;
	// Flags for button presses; logic occurs on release after being pressed
	bool upPressed, downPressed, selectPressed;




	// Main logic loop for this scene
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
