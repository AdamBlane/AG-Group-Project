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
#include "courseGenV2.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "free_camera.h"
#include "chase_camera.h"
#include "tileBuilder.h"
#include "target_camera.h"

using namespace AllCamera;
using namespace std::chrono;

class gameScene
{
public:
	// Default constructor
	gameScene();
	// Deconstructor
	~gameScene();

	//Trying Skybox
	Mesh* sky;
	
	// General game variables
	vector<BaseTile> algTiles; // Game tiles list; these tiles have position data (by M)
	vector<Tile> tiles; // Tile meshes to be rendered, created by V
	vector<Tile> sceneryTiles; // sceneryTiles to be rendered
	vector<int> levelSeed; // This course seed; each tile has an int id
	int courseSize; // Total number of tiles this level
	vector<int> obstacles; // Record obstacle data ( tilePos, obType, tilePos, obType etc)

	
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
	float chaseCamAngle, cameraType; // for switching between free/chase cam
    // For finding cursor pos on screen (used for free cam)
	double cursor_x, cursor_y = 0.0; 

	// Player variables
	Transform player1Transform, arrowTransform;
	// TODO - will need to rename dir & vel to p1Vel, p2vel etc
	vec3 gbDirection; // Normalised direction vector
	vec3 gbVelocity; // Velocity is dir * speed	
	bool golfBallMoving = false; // Is golf ball moving
	float speed; // Ball speed

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