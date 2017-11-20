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
		vector<Texture*> savesImages;
		// Iterator to search through map - apparently don't need this
		//map<std::string, Texture*>::iterator it; // keep in case we do later
		// GAME SCENE UNIQUE MESHES
		Mesh* player1Mesh;
		Mesh* player2Mesh;
		Mesh* arrowMesh;

		// All controller information for remappable controls is stored here
		// FUNCTION/BUTTONS
		map<int, int> buttonValues;

		// Cameras
		target_camera* HUDtargetCam;
		free_camera* freeCam;
		chase_camera* chaseCam;
		// Shaders
		Shader* textureShader;
		Shader* skyboxShader;
		Transform texShaderTransform;

		// Perform initial window setup
		GLFWwindow* windowMgr::Init();
		// Populate savesImages vector with image files read from saves folder
		void UpdateSavesImages(string seed);
		// Game update loop
		void Update();
		// On window close
		void CleanUp();
};