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

		//for mouse movement when the resoloution changes
		double windowScale = 1.0;
		//sets the window scalon the x axise by dividing by the orignal value
		void setWindowScale(int value) { windowScale = value / 1600.0; }
		// For button navigation across all menu scenes
		int button_manager = 0;
		//track mouse
		double mouse_x, mouse_y;
		double previous_mouse_x, previous_mouse_y;
		// Window width and height values
		int width, height;
		// Window offset from top left point of monitor
		int PosX, PosY;
		// Input - prevent input code from reocurring every frame button is held
		bool upPressed, downPressed, leftPressed, rightPressed, enterPressed;
		bool upCotn, downCotn, leftCotn, rightCotn, enterCotn;
		bool mouseLpressed;
		// Number of threads being used for spaceships
		int threadCount = 3;
		int frameCount = 0;


		// Most textures in the game stored here
		map<std::string, Texture*> textures;
		// All number textures stored here
		vector<Texture*> numberTextures;
		// This stores images of saved levels
		vector<Texture*> savesImages;
		// This stores meshes used in load game image viewer panel
		vector<Mesh*> imagePanelMeshes;
		// General use HUD meshes
		vector<Mesh*> meshes;
		// Player one and two gameplayer meshes; stroke counter and power bar
		vector<Mesh*> p1HUDmeshes;
		vector<Mesh*> p2HUDmeshes;
		// Player one mode game clock meshes
		vector<Mesh*> HUDclockMeshes;

		//Score numbers
		vector<Mesh*> player1ScoreMeshes;
		vector<Mesh*> player2ScoreMeshes;
		vector<Mesh*> winConditionsMeshes;

		// Meshes vector for controller 
		vector<Mesh*> controllerMeshes;
		// Meshes vector for start game scene
		vector<Mesh*> startGameMeshes;
		// Pause screen meshes container
		vector<Mesh*> pauseScreenMeshes;
		
		// 2P variant world clock meshes
		vector<Mesh*> worldClockMeshes;
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

	

        // Spaceship
		Texture* spaceshipTexture;
		vector<Mesh*> spaceshipMeshes;
		vector<Transform> spaceshipTransforms;


		//Planets
		Mesh* alienPlanet;
		Texture* alienPlanetTex;

		Mesh* galaxyPlanet;
		Texture* galaxyPlanetTex;

		Mesh* gasPlanet;
		Texture* gasPlanetTex;

		Mesh* lavaPlanet;
		Texture* lavaPlanetTex;

	  
		// Pickup crates for 2p mode
		vector<Mesh*> pickupCrateMeshes;
		Texture* pickupCrateTexture;
		vector<Transform> pickupCrateTransforms;
		Mesh* ufoMesh;
		Texture* ufoTexture;
		vector<Mesh*> wormholeMeshes;
		Texture* wormholeTexture;
		// All contorller related textures are stored in here
		Texture* buttonsPS[18];
		Texture* buttonsXB[14];
		Texture* buttonsKeyboardOne[99];

		Texture* buttonsKey[99];
		// All the game functions are stored here with the index being the function and the value being the button number
		int gameFunctions[10];
		int gameKeyboardFunctions[10];

		// Various controller arrays which hold the controller information
		int playerXboxControls[2][10];
		int playerKeyboardControls[2][10];
		int controllerPSPOne[10];
		int controllerPSPTwo[10];
		int playerUsingControllerOne = 1;
		int playerOneSensitivity = 5;
		int playerTwoSensitivity = 5;

		// KEYBOARD - One
		// Comma = 0
		// Minus = 1
		// Full stop = 2
		// Forward Slash = 3
		// Num 0 = 4
		// Num 1 = 5
		// Num 2 = 6
		// Num 3 = 7
		// Num 4 = 8
		// Num 5 = 9
		// Num 6 = 10
		// Num 7 = 11
		// Num 8 = 12
		// Num 9 = 13
		// SemiColon ; = 14
		// Equals = = 15
		// A = 16
		// B = 17 
		// C = 18
		// D = 19
		// E = 20
		// F = 21
		// G = 22
		// H = 23
		// I = 24
		// J = 25
		// K = 26
		// L = 27
		// M = 28
		// N = 29
		// O = 30
		// P = 31
		// Q = 32
		// R = 33
		// S = 34
		// T = 35
		// U = 36
		// V = 37
		// W = 38 
		// X = 39
		// Y = 40
		// Z = 41
		// Left bracket [ = 42
		// Back slash = 43
		// Right bracket ] = 44

		// ESC = 45
		// ENTER = 46
		// TAB = 47
		// BACKSPACE = 48
		// INSERT = 49
		// DELETE = 50
		// RIGHT = 51
		// LEFT = 52
		// DOWN = 53
		// UP = 54
		// PAGEUP = 55
		// PAGEDOWN = 56
		// HOME = 57
		// END = 58
		// CAPS = 59
		// SCROLL = 60
		// NUM LOCK = 61
		// PRINT SCREEN = 62 
		// PAUSE = 63
		// F1 = 64
		// F2 = 65
		// F3 = 66
		// F4 = 67
		// F5 = 68
		// F6 = 69
		// F7 = 70 
		// F8 = 71
		// F9 = 72
		// F10 = 73
		// F11 = 74
		// F12 = 75

		// PAD 0 = 76
		// PAD 1 = 77
		// PAD 2 = 78
		// PAD 3 = 79 
		// PAD 4 = 80
		// PAD 5 = 81
		// PAD 6 = 82
		// PAD 7 = 83
		// PAD 8 = 84
		// PAD 9 = 85
		// DECIMAL = 86
		// DIVIDE = 87
		// MULTIPLY = 88
		// SUBTRACT = 89
		// ADD = 90
		// ENTER = 91
		// EQUAL = 92

		// LEFT SHIFT = 93
		// LEFT CONTROL = 94
		// LEFT ALT = 95
		// RIGHT SHIFT = 96
		// RIGHT CONTROL = 97
		// RIGHT ALT = 98

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
		FMOD::Sound *spaceshipPass;
		FMOD::Sound *wormhole;
		FMOD::Sound *spaceshipPass2;
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
		// Loads all game assets
		void LoadAssets();
		// Populate savesImages vector with image files read from saves folder
		void UpdateSavesImages(string savedImagePath);
		// Ask winMgr to get thread to play given sound
		void PlayThisSound(string sound); // string is key for sfx map
		// Actual thread function that plays the sound
		void ThreadPlaySound(FMOD::System* system, FMOD::Sound* sound);
		// Handles spaceship logic
		void ThreadSpaceship(int id);
		// Game update loop
		void Update();
		// On window close
		void CleanUp();

		// FOR CONTROLS
		int playerTab = 1; // Set and keep track of what tab we are on - ie player one or two. One by default.
		int indexAt99 = 0;
		int indexOfButtonPressedPlayer1 = 0; // Used for remapping the keyboard
		int indexOfButtonPressedPlayer2 = 0; // Used for remapping the keyboard
		int indexAtButton = 0; // Used for remapping the keyboard
		int indexAtKey = 0; // Used for remapping the keyboard
		bool isFunctionEmpty = false; // Used for remapping the keyboard
		int indexAt999Player1 = 0; // Used for remapping the keyboard
		int indexAt999Player2 = 0; // Used for remapping the keyboard
		bool isFunctionEmptyKeyboard = false; // Used for remapping the keyboard
		bool keyboardButtonPressed[100] = { false }; // Stores all the booleans for button pressing on keyboard
		bool buttonPressed[18] = { false }; // Stores all the booleans for button pressing on controller
		bool doesUserWantControls = false; // Boolean for the controls menu in game - if set to true and back is pressed return to the game
		bool returnToGame = false;

		int xboxP1FunctionEmpty = false;
		int xboxP2FunctionEmpty = false;
		int keyP1FunctionEmpty = false;
		int keyP2FunctionEmpty = false;
		float total_time = 0.0f;
		bool redTextureSet = false;

		// Setup initial textures
		void ControlsTextureSetup();
		// Setup initial buttons
		void ControlsButtonsSetup();
		// Track mouse
		void ControlsTrackMouse();
		// Track click
		void ControlsTrackClick();
		// Input from keyboard
		void ControlsInputKeyboard();
		// Input from controller
		void ControlsInputController();
		// Update keyboard keys
		void ControlsUpdateKeyboard(int keyboardButtonNumber, int additionalNumber);
};

