#pragma once

// Others
#include "glfw3.h"

// Forward declare winMgr here - include winMgr.h in secondScene.h
class windowMgr;

class secondScene
{
public:

	// Basic constructor
	secondScene();

	void screenContent(GLFWwindow* win);
	static void backScene_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
	void Init(GLFWwindow* win);
};
