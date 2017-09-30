#pragma once

#include "glfw3.h"


class windowMgr
{
public:
	static void EscKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
	
	
	void Init(GLFWwindow* &win);
	void Update(GLFWwindow* &win);
	void CleanUp(GLFWwindow* &win);

};