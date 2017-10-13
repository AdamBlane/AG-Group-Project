#pragma once

// GLFW
#include "glew_glfw.h"


class loadGameScene
{
public:
	// Default constructor
	loadGameScene();
	// Deconstructor
	~loadGameScene();

	// Draw stuff
	void screenContent(GLFWwindow* win);
	// Input 
	static void key_callbacks(GLFWwindow* win, int key, int scancode, int action, int mods);
	// Setup scene
	void Init(GLFWwindow* win);
};