#pragma once

// GLFW
#include "glfw3.h"

class playerSelectScene
{
public:
	// Constructors
	playerSelectScene();
	~playerSelectScene();

	// Draw stuff
	void screenContent(GLFWwindow* win);
	// Input
	static void key_callbacks(GLFWwindow* win, int key, int scancode, int action, int mods);
	// Setup scene
	void Init(GLFWwindow* win);
};