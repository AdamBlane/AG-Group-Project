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
	void Loop(GLFWwindow* win);

	void Input(GLFWwindow* win);

	// Setup scene
	void Init(GLFWwindow* win);
};