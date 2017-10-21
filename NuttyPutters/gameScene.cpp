// Externals

// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton
#include <iostream>
#define CHECK_GL_ERROR get_GL_error(__LINE__, __FILE__)

using namespace AllCamera;
/// Game scene holds all data to do with the game

// Default constructor
gameScene::gameScene() { }
// Deconstructor
gameScene::~gameScene() { }


inline bool gameScene::get_GL_error(int line, const std::string &file) {
	// Get the current error
	GLenum error = glGetError();
	// If there is an error display message
	if (error) {
		// Display error
		std::cerr << "OpenGL Error: " << error << std::endl;
		std::cerr << "At line " << line << " in file " << file << std::endl;
		return true;
	}
	return false;
}


// Set number of players this game
void gameScene::setPlayers(unsigned int players)
{
	playerCount = players;
}

// This is called by window manager
// Checks how many players, calls appropriate screenContent method
void gameScene::checkPlayers(GLFWwindow* win)
{
	switch (playerCount)
	{
	case 1:
		screenContent1P(win);
		break;
	case 2:
		screenContent2P(win);
		break;
	default:break;
	}
}



// Draw stuff for 1 player
void gameScene::screenContent1P(GLFWwindow * win)
{
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Camera stuff
	static double ratio_width = quarter_pi<float>() / 1600.0;
	static double ratio_height = (quarter_pi<float>() * (1600 / 900)) / static_cast<float>(1600);
	double current_x, current_y;
	glfwGetCursorPos(win, &current_x, &current_y);
	// Calc delta
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios
	delta_x *=  ratio_width;
	delta_y *= ratio_height * - 1; // -1 to invert on y axis
	// Rotate camera by delta
	freeCam->rotate(delta_x, delta_y);
	freeCam->update(0.001);
	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;
	vec3 pos = vec3(0, 0, 0);
	// Camera controls
	if (glfwGetKey(win, GLFW_KEY_W))
	{
		pos = (vec3(0, 0, WASDSPEED));
	}
	if (glfwGetKey(win, GLFW_KEY_A))
	{
		pos = (vec3(-WASDSPEED, 0, 0));
	}
	if (glfwGetKey(win, GLFW_KEY_S))
	{
		pos = (vec3(0, 0, -WASDSPEED));
	}
	if (glfwGetKey(win, GLFW_KEY_D))
	{
		pos = (vec3(WASDSPEED, 0, 0));
	}
	if (glfwGetKey(win, GLFW_KEY_Q))
	{
		pos = (vec3(0, WASDSPEED, 0));
	}
	if (glfwGetKey(win, GLFW_KEY_E))
	{
		pos = (vec3(0, -WASDSPEED, 0));
	}
	// Move camera by new pos after input
	freeCam->move(pos);

	// Bind texture shader
	textureShader->Bind();
	
	
	// Draw all tiles
	for (auto &t : tiles)
	{
		t.drawTile(textureShader, *freeCam);
	}


	textureShader->Update(shaderTrans, (freeCam->get_Projection() * freeCam->get_View()));
	
	
	glfwSwapBuffers(win);
	glfwPollEvents();
	

}

// Draw stuff for 2 players
void gameScene::screenContent2P(GLFWwindow * win)
{
	float ratio;
	int width, height;

	// Get size of window in case resized
	glfwGetFramebufferSize(win, &width, &height);
	ratio = width / (float)height;
	// Make viewport match window size
	glViewport(0, 0, width / 2, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(win);
	glfwPollEvents();

	// P2
	// Get size of window in case resized
	glfwGetFramebufferSize(win, &width, &height);
	ratio = width / (float)height;
	// Make viewport match window size
	glViewport(width / 2, 0, width / 2, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(win);
	glfwPollEvents();
}

void gameScene::setupTilesToBeDrawn()
{
	// TILE CREATION
	for (auto &t : algTiles)
	{
		if (t.id == 0) // Start
		{
			// Create start tile
			Tile tile(Tile::START, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Start tile needs rotating 180 (should always face down)
			tile.transform.getRot().y = 3.14159;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 1) // Straight V
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 2) // Straight H
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Straight needs rotating by 90, since it's vertical by default
			tile.transform.getRot().y = 1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 3) // Corner BL
		{
			// Create corner tile
			Tile tile(Tile::CORNER, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Corner needs rotating by 90
			tile.transform.getRot().y = 1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 4) // Corner BR
		{
			// Create corner tile
			Tile tile(Tile::CORNER, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Corner needs rotating by 90
			tile.transform.getRot().y = 3.14159;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 5) // Corner TL
		{
			// Create corner tile
			Tile tile(Tile::CORNER, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 6) // Corner TR
		{
			// Create corner tile
			Tile tile(Tile::CORNER, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Corner needs rotating by 90
			tile.transform.getRot().y = -1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 7) // end
		{
			// Create start tile
			Tile tile(Tile::START, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Consult direction to determine how much to rotate
			if (t.outDir.going_up)
			{
				tile.transform.getRot().y = 3.14159;
			}
			else if (t.outDir.going_down)
			{
				// No rotation needed
			}
			else if (t.outDir.going_left)
			{
				tile.transform.getRot().y = -1.5708;
			}
			else if (t.outDir.going_right)
			{
				tile.transform.getRot().y = 1.5708;
			}
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
	}

}

// Input
void gameScene::key_callbacks(GLFWwindow * win, int key, int scancode, int action, int mods)
{
	// Exit; close window
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(0);
	}
}

// Setup scene
void gameScene::Init(GLFWwindow * win)
{
	// Assign input
	glfwSetKeyCallback(win, key_callbacks);
	// This sets up level gen
	// More than 9 tiles has a potential to break it - ask me for deets (too long to type :D)
	courseGenV2 courseGen(6);
	// Runs the alg, returns map of tiles (pos, name)
	algTiles = courseGen.run();
	// DEBUG
	for (auto &t : algTiles)
	{
		cout << t.id << endl;
	}

	// Set GL properties 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Hide cursor
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Get initial cursor pos
	glfwSetCursorPos(win, cursor_x, cursor_y);
	

	// Setup tiles
	setupTilesToBeDrawn();




	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");
	// Setup camera
	freeCam = new free_camera();
	freeCam->set_Posistion(vec3(0, 0, 10));
	freeCam->set_Target(vec3(0, 0, 0));
	freeCam->set_projection(quarter_pi<float>(), (float)1600 / (float)900, 0.414f, 1000.0f);
	
}
