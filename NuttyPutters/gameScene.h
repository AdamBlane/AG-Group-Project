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



using namespace AllCamera;
using namespace std::chrono;


class gameScene
{
public:
	// Default constructor
	gameScene();
	// Deconstructor
	~gameScene();

	//Player player1, player2;
	vector<Player> players;
	UI uiMgr;
	Physics physicsSystem;
	//Trying Skybox
	Mesh* sky;
	
	// General game variables
	vector<BaseTile*> algTiles; // Game tiles list; these tiles have position data (by M)
	vector<Tile> tiles; // Tile meshes to be rendered, created by V
	vector<Tile> sceneryTiles; // sceneryTiles to be rendered
	vector<int> levelSeed; // This course seed; each tile has an int id
	int courseSize; // Total number of tiles this level
	vector<int> obstacles; // Record obstacle data ( tilePos, obType, tilePos, obType etc)

	// Gameplay variables
	// TODO - set these in init to be safe (sometimes not reset in other scenes)
	int timeBeenInScene = 0; // Time from when the scene is fully loaded
	int timeCounter = 0;
	int strokeCounter = 0; // Counts the amount of strokes the player takes
	bool continuePressed = false; // Variable used to see if the user has pressed a key - used for HUDs
	int holeTimer = 0; // The amount time the user to get the ball in the hole
	int timeSinceContinueWasPressed;  // The time since the user has pressed the continue button
	bool hasUserCompletedHole = false; // Boolean which tells the game if the user has completed the hole
	bool hasUserCompletedHoleTextures = false; // Boolean which tells the game to update the textures based on if the user has completed the hole
	bool isUserOutOfTime = false; // Boolean which tells the game if they are out of time
	bool isUserOutOfStrokes = false; // Boolean which tells the game if they are out of strokes
	int timeToThisMethod = 0; // Time to this method - used for countdown HUD
	

	// Player information
	int selectedDifficulty = 1; // The selected difficulty on the player select screen
	int selectedPlayers = 1; // The amount of players selected on the player select screen
	int playerOneShots = 0; // The amount of shots users one has taken
	int playerTwoShots = 0; // The amount of shots uer two has taken


	// Track fps to give dt
	double currentTime = glfwGetTime();
	double accumulator = 0.0;
	float dt = 0.016;  // This is 60fps

	// Fire action variables
	bool p2firePressed = false; // Prevent shooting ball again whilst already moving
	float fireCounter; // This is a force counter (TODO: rename)
	float p2fireCounter;
	bool levelSaved = false; // Prevent saving same level more than once

	// Camera variables
	float camSpeed = 2.0f; 
	float chaseCamAngle, p2ChaseCamAngle, cameraType = 1; // for switching between free/chase cam (default)
    // For finding cursor pos on screen (used for free cam)
	double cursor_x, cursor_y = 0.0; 
	vec3 pauseCamPos, pauseCamTarget;




	// Setup scene. Last seed params is optional; = denotes default value
	// If called from loadGameScene, requires seed value(as string)
	void Init(GLFWwindow* window, int courseLength, string seed = "seed"); 
	// Loads level of given size; random if no optional seed given
	void LoadGame(string seed);
	// Fills space around level with scenery tiles
	void FillScenery();
	// Translates list of alg tiles (M) into mesh tiles (V)
	void SetupTilesToBeDrawn();
	// Game loop and its functions
	void Loop(GLFWwindow* window);
	void Input(GLFWwindow* window);
	void Update(GLFWwindow* window);
	void Collisions();
	void Render(GLFWwindow* window);
};