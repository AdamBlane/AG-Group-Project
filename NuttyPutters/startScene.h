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
	void screenContent(GLFWwindow* win);
	// Input 
	static void key_callbacks(GLFWwindow* win, int key, int scancode, int action, int mods);
	// Setup
	void Init(GLFWwindow* win);
	
};
