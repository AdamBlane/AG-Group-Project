#pragma once

#include "glfw3.h"


class startScene
{
public:
	// Default constructor
	startScene();
	// Deconstructor
	~startScene();

	// Draw stuff
	void screenContent(GLFWwindow* win);
	// Input callbacks
	static void nextScene_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
	
	// Applies callbacks, setups up scene
	void Init(GLFWwindow* win);
	
};
