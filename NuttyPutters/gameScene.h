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

	// Track number of players for this game
	unsigned int playerCount;

	// For finding cursor pos on screen
	double cursor_x, cursor_y = 0.0;
	
	// Game tiles list, resulting from Alg (by M)
	vector<BaseTile> algTiles;
	// Tile meshes to be rendered, created by V
	vector<Tile> tiles;
	Shader* textureShader;
	Transform shaderTrans;

	// Cameras
	free_camera* freeCam;	
	float camSpeed = 0.1f; // camSpeed WAS called WASDSPEED
	chase_camera* chaseCam;
	float chaseCamAngle;
	float cameraType; // for switching on/off free/chase cam
	
	// Golf ball
	Mesh* golfBallMesh;
	Texture* golfBallTexture;
	Transform golfBallTransform;
	// Movement of gb
	float golfBallForce, timer, originalForceTimer = 0.0f;

	// Arrow
	Mesh* arrowMesh;
	Texture* arrowTexture;
	Transform arrowTransform;

	// Set player Count
	void setPlayers(unsigned int players) { playerCount = players; }
	// Check player count, draw accordingly
	void checkPlayers(GLFWwindow* win);
	// Draw stuff for 1 player
	void screenContent1P(GLFWwindow* win);
	// Draw for 2 players
	void screenContent2P(GLFWwindow* win);
	// Translates list of alg tiles (M) into mesh tiles (V)
	void setupTilesToBeDrawn();
	// Input
	void Input(GLFWwindow* win);
	static void key_callbacks(GLFWwindow* win, int key, int scancode, int action, int mods);
	// Setup scene
	void Init(GLFWwindow* win);

	// TODO - Loads a level based on given seed
	void LoadGame();
};