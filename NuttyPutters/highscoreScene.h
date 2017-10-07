#pragma once

#include "glfw3.h"


class highscoreScene
{
public:
	// Default constructor
	highscoreScene();
	// Deconstructor
	~highscoreScene();

	// Draw stuff
	void screenContent(GLFWwindow* win);
	// Input 
	static void key_callbacks(GLFWwindow* win, int key, int scancode, int action, int mods);
	// Setup
	void Init(GLFWwindow* win);
};