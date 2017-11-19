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
		// position of window 
		int PosX, PosY;
		//for mouse movement when the resoloution changes
		double windowScale = 1.0;
		// For button navigation across all menu scenes
		int button_manager = 0;
		// Store pointers to all meshes and textures required by game
		// These are initialised once on the heap, in the Init() function of winMgr
		// General use HUD meshes
		vector<Mesh*> meshes;
		// All textures in the game stored here
		map<std::string, Texture*> textures;

		// Iterator to search through map
		//map<std::string, Texture*>::iterator it;
		 
		//gets the window scale on the x axis
		double getWindowScale() const { return windowScale; };
		//sets the window scalon the x axise by dividing by the orignal value
		void setWindowScale(int value) { windowScale = value / 1600.0; }

		vector<Texture*> savesImages;
		// Iterator to search through map - apparently don't need this
		//map<std::string, Texture*>::iterator it; // keep in case we do later
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

