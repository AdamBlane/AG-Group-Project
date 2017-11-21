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


	Player player1, player2;
	UI uiMgr;
	Physics physicsSystem;
	//Trying Skybox
	Mesh* sky;
	
	// General game variables
	vector<BaseTile> algTiles; // Game tiles list; these tiles have position data (by M)
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
	int timeRemainingInSeconds = 0, timeRemainingInTenths = 0, timeRemainingInMinutes = 0;
	int timeSinceContinueWasPressed;  // The time since the user has pressed the continue button
	bool hasUserCompletedHole = false; // Boolean which tells the game if the user has completed the hole
	bool hasUserCompletedHoleTextures = false; // Boolean which tells the game to update the textures based on if the user has completed the hole
	bool isUserOutOfTime = false; // Boolean which tells the game if they are out of time
	bool isUserOutOfStrokes = false; // Boolean which tells the game if they are out of strokes
	int timeToThisMethod = 0; // Time to this method - used for countdown HUD
	int tempInt = 0;
	string temp;
	string minutesAsString, tenthsAsString, secondsAsString, timeCombined;

	// Player information
	int selectedDifficulty = 1; // The selected difficulty on the player select screen
	int selectedPlayers = 1; // The amount of players selected on the player select screen
	int playerOneShots = 0; // The amount of shots users one has taken
	int playerTwoShots = 0; // The amount of shots uer two has taken

	// Spatial (tile!) partitioning - tracks which tile player is currently on		
	int currentTile = 0; 
	// Track fps to give dt
	double lastFrame = 0;
	double thisFrame = glfwGetTime();
	float dt = 0.016; // First frame; is reset thereafter
	// Rename
	bool pPressed = false; // Prevent shooting ball again whilst already moving
	float Pcounter; // This is a force counter (TODO: rename)
	bool levelSaved = false; // Prevent saving same level more than once

	// Camera variables
	float camSpeed = 2.0f; 
	float chaseCamAngle, cameraType = 1; // for switching between free/chase cam (default)
    // For finding cursor pos on screen (used for free cam)
	double cursor_x, cursor_y = 0.0; 
	vec3 pauseCamPos, pauseCamTarget;


	//struct player
	//{
	//	Transform transform;
	//	Transform arrowTransform;
	//	vec3 direction;
	//	vec3 velocity;
	//	float speed;
	//	bool isMoving = false;
	//} player1, player2;
	// Player variables
	//Transform player1Transform, arrowTransform;
	//// TODO - will need to rename dir & vel to p1Vel, p2vel etc
	//vec3 gbDirection; // Normalised direction vector
	//vec3 gbVelocity; // Velocity is dir * speed	
	//bool golfBallMoving = false; // Is golf ball moving
	//float speed; // Ball speed

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
	vec3 CheckCollisionsObstacle1(vec3 coords, vec3 playerPos, vec3 dir, float displace, float radius);
	void Render(GLFWwindow* window);
};