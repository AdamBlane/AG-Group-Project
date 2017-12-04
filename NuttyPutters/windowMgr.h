#pragma once

// Externals
#include "glew_glfw.h"
#include "include\inc\fmod.hpp"


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
		// All number textures stored here
		vector<Texture*> numberTextures;
		// This stores images of saved levels
		vector<Texture*> savesImages;
		// General use HUD meshes
		vector<Mesh*> meshes;
		// 2P variant world clock meshes
		vector<Mesh*> worldClock;
		// Skybox vars
		Texture* skyboxTexture;
		Mesh* skyboxMesh;
		const string posXfileName = "..\\NuttyPutters\\skyboxes\\left.png";
		const string negXfileName = "..\\NuttyPutters\\skyboxes\\right.png";
		const string posYfileName = "..\\NuttyPutters\\skyboxes\\top.png";
		const string negYfileName = "..\\NuttyPutters\\skyboxes\\bot.png";
		const string posZfileName = "..\\NuttyPutters\\skyboxes\\back.png";
		const string negZfileName = "..\\NuttyPutters\\skyboxes\\front.png";
		// GAME SCENE UNIQUE MESHES
		Mesh* player1Mesh;
		Mesh* player2Mesh;
		Mesh* p1ArrowMesh;
		Mesh* p2ArrowMesh;
		vector<Mesh*> pickupCrateMeshes;
		Texture* pickupCrateTexture;
		vector<Transform> pickupCrateTransforms;

		// Cameras
		target_camera* HUDtargetCam;
		target_camera* PAUSEtargetCam;
		free_camera* freeCam;
		chase_camera* p1ChaseCam;
		chase_camera* p2ChaseCam;
		vector<chase_camera*> chaseCams;
		// Shaders
		Shader* textureShader;
		Shader* skyboxShader;
		Transform texShaderTransform;

		// AUDIO
		FMOD::System *system;
		FMOD::Sound *menuSelect;	
		FMOD::Sound *golfBallPutt;
		FMOD::Sound *golfBallHit;
		FMOD::Sound *golfBallJump;
		FMOD::Sound *golfBallWoodHit;
		FMOD::Sound *getBiggerPowerUp;
		FMOD::Sound *getSmallerPowerUp;
		// Store all above declared sound effects here
		map<std::string, FMOD::Sound*> soundEffects;

		//Stuff for tiles
		vector<Mesh*> tileMeshes;
		vector<Mesh*> obstacleMeshes;
		vector<Mesh*> planeMeshes;
		map<std::string, Texture*> tileTextures;


		//mutex mut;

		// Perform initial window setup
		GLFWwindow* windowMgr::Init();
		// Load textures thread
		void LoadTextures(map<std::string, Texture*> &tileTexs, GLFWwindow* window);
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

