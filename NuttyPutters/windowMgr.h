#pragma once

// Externals
#include "glew_glfw.h"

// Internals
#include "sceneMgr.h"

class windowMgr
{
	private:
		// Store singleton instance
		static windowMgr* instance;
		//the window posistion and size
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

		//void set_height(int &value) { height = value; }
		//void set_width(int &value) { width = value; }

		void set_PosX(int &value) { height = value; }
		void set_PosY(int &value) { width = value; }

		int width = 1600, height = 900;
		int PosX, PosY;
		//static int get_height() { return height; }
		//static int get_width() { return height; }

		//static int get_PosX() { return PosX; }
		//static int get_PosY() { return PosY; }
		// Perform initial window setup
		GLFWwindow* windowMgr::Init();
		// Game update loop
		void Update();
		// On window close
		void CleanUp();
};