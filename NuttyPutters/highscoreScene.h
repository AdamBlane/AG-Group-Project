#pragma once

#include "glew_glfw.h"


class highscoreScene
{
public:
	// Default constructor
	highscoreScene();
	// Deconstructor
	~highscoreScene();

	
	void Loop(GLFWwindow* win);

	void Input(GLFWwindow* win);
	// Setup
	void Init(GLFWwindow* win);
};