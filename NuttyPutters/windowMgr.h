#pragma once
// Ours
#include "sceneMgr.h"
#include "startScene.h"
#include "secondScene.h"
// Others
#include "glfw3.h"



class windowMgr
{
private:
	// Store singleton instance
	static windowMgr* instance;
	// Private constructor to avoid instancing
	windowMgr();
	// Deconstructor
	~windowMgr();
public:
	// Static singleton access method
	static windowMgr* getInstance();
	// This class creates and deals with the window
	GLFWwindow* win;
	// Track gamestate
	sceneMgr sceneManager;
	// Gamestate scenes
	startScene startSceneMgr;
	secondScene secondSceneMgr;

	// Perform initial window setup
	GLFWwindow* windowMgr::Init();
	// Game update loop
	void Update();
	// On window close
	void CleanUp();
	
};