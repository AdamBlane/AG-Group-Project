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

		// All contorller related textures are stored in here
		Texture* buttonsPS[17];
		Texture* buttonsXB[4];
		// All the game functions are stored here with the index being the function and the value being the button number
		int gameFunctions[17];

		// BUTTONS
		// A/Sqaure = 0
		// B/X(PS) = 1
		// X(XB)/Circle = 2
		// Y/Triangle = 3
		// /L1 = 4
		// /R1 = 5
		// /L2 = 6
		// /R2 = 7
		// /Select = 8
		// /Start = 9
		// /Left Stick Push = 10
		// /Right Stick Push = 11
		// /PS Button =12
		// /Pad = 13
		// /DPAD UP = 14
		// /DPAD LEFT = 15 
		// /DPAD DOWN = 16
		// /DPAD RIGHT = 17

		// FUCTIONS
		// Select/fire = 0
		// Back/Reset = 1
		// Pause = 2
		// DPAD UP = 3
		// DPAD LEFT = 4
		// DPAD DOWN = 5
		// DPAD RIGHT = 6

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