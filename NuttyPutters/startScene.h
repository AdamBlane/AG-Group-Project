#pragma once

// GLFW
#include "glew_glfw.h"


class startScene
{
public:
	// Default constructor
	startScene();
	// Deconstructor
	~startScene();

	// Draw stuff
	void Loop(GLFWwindow* win);
	// Input 
	void Input(GLFWwindow* win);
	// Setup
	void Init(GLFWwindow* win);
	
};
