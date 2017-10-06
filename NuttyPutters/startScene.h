#pragma once

#include "windowMgr.h"

#include "glfw3.h"



class startScene {
public:
	// Keep reference to parent manager
	windowMgr parent;

	startScene();
	startScene(windowMgr parentMgr);


	void screenContent(GLFWwindow* &win);
	void nextScene_callback(GLFWwindow* win, int key, int scancode, int action, int mods);

};
