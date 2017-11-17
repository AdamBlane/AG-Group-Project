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

		// TODO - what is this? Set pos actually sets height & width?!
		void set_PosX(int &value) { height = value; }
		void set_PosY(int &value) { width = value; }

		// Window width and height values
		int width = 1600, height = 900;
		// TODO - position of what? 
		int PosX, PosY;
		
		// Store pointers to all meshes and textures required by game
		// These are initialised once on the heap, in the Init() function of winMgr
		vector<Mesh*> meshes;
		map<std::string, Texture*> textures;
		// Iterator to search through map
		//map<std::string, Texture*>::iterator it;
		 


		// Perform initial window setup
		GLFWwindow* windowMgr::Init();
		// Game update loop
		void Update();
		// On window close
		void CleanUp();
};