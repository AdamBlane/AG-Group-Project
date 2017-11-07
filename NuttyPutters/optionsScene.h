#pragma once

#include "glew_glfw.h"

class optionsScene
{
public:
	// Default constructor
	optionsScene();
	// Deconstructor
	~optionsScene();

	// Draw stuff
	void Loop(GLFWwindow* win);

	void Input(GLFWwindow* win);

	void Init(GLFWwindow* win);
};