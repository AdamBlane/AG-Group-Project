#pragma once
// Externals
#include "glew_glfw.h"

// Internals
#include "courseGenerator.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "free_camera.h"
#include "Camera.h"
#include "tileBuilder.h"
#define CHECK_GL_ERROR get_GL_error(__LINE__, __FILE__)

using namespace AllCamera;

class gameScene
{
public:
	// Default constructor
	gameScene();
	// Deconstructor
	~gameScene();

	inline bool get_GL_error(int line, const std::string &file);
	// Track number of players for this game
	unsigned int playerCount;

	bool setup = false;

	// For finding cursor pos on screen
	double cursor_x, cursor_y = 0.0;
	
	Mesh* mesh;
	Tile* startTile;
	Tile* straightTile;
	Shader* textureShader;
	//Texture* textureWood;
	free_camera* freeCam;
	Transform trans1;
	Transform startTileTrans;
	Transform straightTileTrans;
	float WASDSPEED = 0.1f;
	

	// Set player Count
	void setPlayers(unsigned int players);
	

	// Check player count, draw accordingly
	void checkPlayers(GLFWwindow* win);
	// Draw stuff for 1 player
	void screenContent1P(GLFWwindow* win);
	// Draw for 2 players
	void screenContent2P(GLFWwindow* win);


	// Input
	static void key_callbacks(GLFWwindow* win, int key, int scancode, int action, int mods);
	// Setup scene
	void Init(GLFWwindow* win);
};