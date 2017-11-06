#pragma once
// Externals
#include "glew_glfw.h"
#include <map>
// Internals
#include "courseGenV2.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "free_camera.h"
#include "chase_camera.h"
#include "tileBuilder.h"


using namespace AllCamera;

class gameScene
{
public:
	// Default constructor
	gameScene();
	// Deconstructor
	~gameScene();


	// Game tiles list, resulting from Alg (by M)
	vector<BaseTile> algTiles;
	// Tile meshes to be rendered, created by V
	vector<Tile> tiles;
	Shader* textureShader;
	Transform shaderTrans;
	// Tracks tile player is on 
	// This is the index of algTiles (0 is always start tile)
	int currentTile = 0;

	// Lock to 60fps
	float dt = 0.016;
	// Ball speed
	float speed = 1.0f;
	bool pPressed = false;
	float f = 0.1f;

	// Cameras
	free_camera* freeCam;	
	float camSpeed = 0.1f; // camSpeed WAS called WASDSPEED
	chase_camera* chaseCam;
	float chaseCamAngle, cameraType;// for switching on/off free/chase cam
	double cursor_x, cursor_y = 0.0;// For finding cursor pos on screen
	
	// Golf ball
	Mesh* golfBallMesh;
	Texture* golfBallTexture;
	Transform golfBallTransform;
	// Movement of gb, this is speed data
	float golfBallForce, timer, originalForceTimer = 0.0f;
	// Normalised direction vector
	vec3 gbDirection;
	// Dir * speed resulsts in velocity vector
	vec3 gbVelocity, friction, impulse;
	// Is golf ball moving
	bool golfBallMoving = false, onRamp = false;

	// Arrow
	Mesh* arrowMesh;
	Texture* arrowTexture;
	Transform arrowTransform;



	// Setup scene
	void Init(GLFWwindow* window);
	// Loads level based on seed
	void LoadGame();
	// Translates list of alg tiles (M) into mesh tiles (V)
	void SetupTilesToBeDrawn();
	// Game loop and its functions
	void Loop(GLFWwindow* window);
	void Input(GLFWwindow* window);
	void Update(GLFWwindow* window);
	void Collisions();
	void Render(GLFWwindow* window);
};