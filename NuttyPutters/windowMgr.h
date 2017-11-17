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
		// General use HUD meshes
		vector<Mesh*> meshes;
		// All textures in the game stored here
		map<std::string, Texture*> textures;
		// Iterator to search through map - apparently don't need this
		//map<std::string, Texture*>::iterator it; // keep in case we do later
		// GAME SCENE UNIQUE MESHES
		Mesh* player1Mesh;
		Mesh* player2Mesh;
		Mesh* arrowMesh;


		// Shaders
		Shader* textureShader;
		Transform texShaderTransform;

		// Perform initial window setup
		GLFWwindow* windowMgr::Init();
		// Game update loop
		void Update();
		// On window close
		void CleanUp();
};