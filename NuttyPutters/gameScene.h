#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
#include <time.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
#include <sstream>
// Internals
#include "courseGenV2.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "free_camera.h"
#include "chase_camera.h"
#include "tileBuilder.h"


using namespace AllCamera;
using namespace std::chrono;

class gameScene
{
public:
	// Default constructor
	gameScene();
	// Deconstructor
	~gameScene();


	// General game variables
	vector<BaseTile> algTiles; // Game tiles list, resulting from Alg (by M)	
	vector<Tile> tiles; // Tile meshes to be rendered, created by V
	vector<Tile> sceneryTiles;
	Shader* textureShader;
	Transform shaderTrans;		
	int currentTile = 0; // Tracks tile player is on 
	float dt = 0.016; // Lock to 60fps
	bool pPressed = false;
	float Pcounter;
	bool levelSaved = false;

	// Cameras
	free_camera* freeCam;	
	float camSpeed = 2.0f; // camSpeed WAS called WASDSPEED
	chase_camera* chaseCam;
	float chaseCamAngle, cameraType;// for switching on/off free/chase cam
	double cursor_x, cursor_y = 0.0;// For finding cursor pos on screen
	
	// Golf ball
	Mesh* golfBallMesh;
	Texture* golfBallTexture;
	Transform golfBallTransform;
	vec3 gbDirection; // Normalised direction vector
	vec3 gbVelocity; // Velocity is dir * speed	
	bool golfBallMoving = false; // Is golf ball moving
	float speed; // Ball speed
	// Arrow
	Mesh* arrowMesh;
	Texture* arrowTexture;
	Transform arrowTransform;
	// Tree
	vector<Mesh*> treeMeshes;
	Texture* treeTexture;
	vector<Transform> treeTransforms;


	// Setup scene
	void Init(GLFWwindow* window);
	// Loads level based on seed
	void LoadGame();
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