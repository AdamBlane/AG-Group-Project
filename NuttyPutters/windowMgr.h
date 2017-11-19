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

		// TODO - what is this? Set pos actually sets height & width?!
		void set_PosX(int &value) { height = value; }
		void set_PosY(int &value) { width = value; }

		// Window width and height values
		int width = 1600, height = 900;
		// TODO - position of what? 
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
		Mesh* arrowMesh;

		// Cameras
		target_camera* HUDtargetCam;
		target_camera* PAUSEtargetCam;
		free_camera* freeCam;
		chase_camera* chaseCam;

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

