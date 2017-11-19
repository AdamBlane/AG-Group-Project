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

		// Window width and height values
		int width = 1600, height = 900;
		// position of window 
		int PosX, PosY;
		//for mouse movement when the resoloution changes
		double windowScale = 1.0;

		int button_manager = 0;
		// Store pointers to all meshes and textures required by game
		// These are initialised once on the heap, in the Init() function of winMgr
		vector<Mesh*> meshes;
		map<std::string, Texture*> textures;
		// Iterator to search through map
		//map<std::string, Texture*>::iterator it;
		 
		//gets the window scale on the x axis
		double getWindowScale() const { return windowScale; };
		//sets the window scalon the x axise by dividing by the orignal value
		void setWindowScale(int value) { windowScale = value / 1600.0; }

		// Perform initial window setup
		GLFWwindow* windowMgr::Init();
		// Game update loop
		void Update();
		// On window close
		void CleanUp();
};