#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
#include <time.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
#include <windows.h>
#include <atlimage.h>
#include <gdiplusimaging.h>

// Internals

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "free_camera.h"
#include "chase_camera.h"
#include "tileBuilder.h"
#include "target_camera.h"
#include "Player.h"
#include "courseGenTiles.h"
#include "UI.h"
#include "Physics.h"
#include "GameLogicMgr.h"


using namespace AllCamera;
using namespace std::chrono;
using namespace std;

class gameScene
{
public:
	// Default constructor
	gameScene();
	// Deconstructor
	~gameScene();



	//Players list
	vector<Player> players;
	// Number of players this game
	int numPlayers = 1;
	// Number of levels this game
	int numLevels = 1;
	// Current level 
	int currentLevel = 0;
	// For loading a new level
	bool changedLevel = false;
	// Total number of tiles per level
	int courseSize;
	// Game ended flag
	bool gameEnded = false;
	// SYSTEMS USED
	// Handles gameplay logic
	GameLogicMgr gameLogicMgr;
	// Handles physics logic
	Physics physicsSystem;

	// GAME VARIABLES
	// List of all level seeds, this is used to create algTiles list
	vector<vector<int>> masterLevelSeeds;
	// List of all level alg tiles, used to determine collisions and spatial partitioning
	// Also used to create Tiles list, which makes up the geometry to be drawn
	vector<vector<BaseTile*>> masterAlgTiles;
	// List of all tile meshes which are rendered
	vector<vector<Tile>> masterTiles;
	// List of all scenery tile meshes which are rendered
	vector<vector<Tile>> masterSceneryTiles;
	// List of pause cam positions and targets for each level
	vector<vec3> pauseCamLevelProperties;
	// Record obstacle data ( tilePos, obType, tilePos, obType etc)
	vector<vector<int>> masterObstacles;
	// List of pickup crate locations for each level
	vector<int> pickupPositionIndices;
	// Holds two wormhole transforms
	vector<Transform> wormholeTransforms;


	vec3 prevPos = vec3(0);

	// Prevent saving same level more than once
	bool levelSaved = false;
	bool continuePressed, resetPressed = false;;

	// Setup GLFW joystick button input - required for doing anything with buttons
	int controllerOneButtonCount;
	const unsigned char *controllerOne;
	int controllerTwoButtonCount;
	const unsigned char *controllerTwo;
	int controllerOneAxisCount;
	const float *controllerOneAxis;
	int controllerTwoAxisCount;
	const float *controllerTwoAxis;

	// Track fps to give dt
	double currentTime = glfwGetTime();
	double accumulator = 0.0;
	double dt;  // This is 60fps


	float total_time = 0.0f;
	int previousMenuItem, currentMenuItem;
	bool paused = false;

	Transform spaceTrans;

	// Camera variables
	double camSpeed = 2.0;
	float  cameraType = 1;
	// TODO - replace these for player members - float chaseCamAngle, p2ChaseCamAngle, // for switching between free/chase cam (default)
	// For finding cursor pos on screen (used for free cam)
	double cursor_x, cursor_y = 0.0;


	// Setup scene. Last seed params is optional; = denotes default value
	// If called from loadGameScene, requires seed value(as string)
	void Init(GLFWwindow* window, int courseLength, int playerCount, int levelCount, string seed = "seed");
	// Loads level of given size; random if no optional seed given
	void LoadGame(string seed);
	// Fills space around level with scenery tiles
	void FillScenery();
	// Translates list of alg tiles (M) into mesh tiles (V)
	void SetupTilesToBeDrawn();
	// Sets up pickup crates for a level
	void SetupPickupCrates();


	// Game loop and its functions
	void Loop(GLFWwindow* window);
	// Player movement fuctions
	void Jump(Player &p);
	void FirePress(Player &p);
	void FireRelease(Player &p);
	void Pause(GLFWwindow* window);
	// Act on controller/keyboard input
	void Input(GLFWwindow* window);
	// Tiles are treated as partitions
	void SpatialPartitioningUpdate();
	// Will load next level if conditions are met
	void CheckLoadNextLevel();
	// Keep clocks ticking, update cameras and positions
	void Update(GLFWwindow* window);
	// Check for player collisions
	void Collisions();
	// Draw stuff
	void Render(GLFWwindow* window);
	//Function to track mouse movements
	void Track_mouse(GLFWwindow* win);
	// Called when on pause screen; enact highlighted choice
	void Click_Or_Enter(GLFWwindow* win, bool pause);
	// Called from pause menu; screenshots and saves current level to file
	void Save_Level(GLFWwindow* win);
	//seperate render for pause screen
	void ChangeTextures(GLFWwindow* win);
};