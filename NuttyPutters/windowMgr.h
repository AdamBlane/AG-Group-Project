#pragma once

// Externals
#include "glew_glfw.h"
#include "include\inc\fmod.hpp"
#include <thread>

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
		int width, height;
		// Window offset from top left point of monitor
		int PosX, PosY;
		
		// All textures in the game stored here
		map<std::string, Texture*> textures;
		// This stores images of saved levels
		vector<Texture*> savesImages;
		// General use HUD meshes
		vector<Mesh*> meshes;

		// GAME SCENE UNIQUE MESHES
		Mesh* player1Mesh;
		Mesh* player2Mesh;
		Mesh* p1ArrowMesh;
		Mesh* p2ArrowMesh;

		// All contorller related textures are stored in here
		Texture* buttonsPS[18];
		Texture* buttonsXB[14];
		// All the game functions are stored here with the index being the function and the value being the button number
		int gameFunctions[9];

		// BUTTONS
		// A/Sqaure = 0
		// B/X(PS) = 1
		// X(XB)/Circle = 2
		// Y/Triangle = 3
		// LB/L1 = 4
		// RB/R1 = 5
		// Back/L2 = 6
		// Start/R2 = 7
		// Left Stick Push/Select = 8
		// Right Stick Push/Start = 9
		// DPAD UP/Left Stick Push = 10
		// DPAD LEFT/Right Stick Push = 11
		// DPAD DOWN/PS Button =12
		// DPAD RIGHT/Pad = 13
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
		target_camera* PAUSEtargetCam;
		free_camera* freeCam;
		chase_camera* p1ChaseCam;
		chase_camera* p2ChaseCam;
		// Shaders
		Shader* textureShader;
		Shader* skyboxShader;
		Transform texShaderTransform;

		// AUDIO
		FMOD::System *system;
		FMOD::Sound *menuSelect;	
		// Store all above declared sound effects here
		map<std::string, FMOD::Sound*> soundEffects;

		//Stuff for tiles
		vector<Mesh*> tileMeshes;
		vector<Mesh*> obstacleMeshes;
		vector<Mesh*> planeMeshes;
		map<std::string, Texture*> tileTextures;

		// Perform initial window setup
		GLFWwindow* windowMgr::Init();
		// Populate savesImages vector with image files read from saves folder
		void UpdateSavesImages(string savedImagePath);
		// Ask winMgr to get thread to play given sound
		void PlayThisSound(string sound); // string is key for sfx map
		// Actual thread function that plays the sound
		void ThreadPlaySound(FMOD::System* system, FMOD::Sound* sound);
		// Game update loop
		void Update();
		// On window close
		void CleanUp();
};

