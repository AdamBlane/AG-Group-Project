#pragma once

// GLFW
#include "glfw3.h"

class gameScene
{
public:
	// Constructors
	gameScene();
	~gameScene();

	// Draw stuff
	void screenContent(GLFWwindow* win);
	// Input
	static void backScene_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
	// Setup scene
	void Init(GLFWwindow* win);
};