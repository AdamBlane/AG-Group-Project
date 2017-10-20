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
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static double ratio_width = quarter_pi<float>() / 1600.0;
	static double ratio_height = (quarter_pi<float>() * (1600 / 900)) / static_cast<float>(1600);
	double current_x, current_y;
	glfwGetCursorPos(win, &current_x, &current_y);
	// Calc delta
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - current_y;
	// Multiply deltas by ratios
	delta_x = delta_x * ratio_width;
	delta_y = delta_y * ratio_height * - 1; // -1 to invert on y axis
	// Rotate camera by delta
	freeCam->rotate(delta_x, delta_y);
	freeCam->update(0.001);
	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;
	vec3 pos = vec3(0, 0, 0);

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
	CHECK_GL_ERROR;
	textureShader->Bind();
	textureWood->Bind(0);

	textureShader->Update(trans1, (freeCam->get_Projection() * freeCam->get_View()));
	CHECK_GL_ERROR;
	mesh->Draw();
	std::cout << "Mesh (" << mesh->getPos().x << ", " << mesh->getPos().y << ", " << mesh->getPos().z << std::endl;
	freeCam->move(pos);
	std::cout << freeCam->get_Posistion().x << ", " << freeCam->get_Posistion().y << ", " << freeCam->get_Posistion().z << std::endl;
	freeCam->update(0.00001);
	glfwSwapBuffers(win);
	glfwPollEvents();
	CHECK_GL_ERROR;

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

// Input
void gameScene::key_callbacks(GLFWwindow * win, int key, int scancode, int action, int mods)
{
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
	// Generate level, int param = game tiles in course
	if (setup == false)
	{
		//courseGenerator courseGen(5);
		//setup = true;
		//courseGen.run();
		// Running alg should return a list or similar of all game tiles
		// that need to be rendered, to pass to a render function here
	}


	CHECK_GL_ERROR;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(win, cursor_x, cursor_y);
	CHECK_GL_ERROR;
	// Create our cuboid
	mesh = new Mesh(Mesh::CUBOID, vec3(0.0f, 0.0f, 0.0f), 10.0f, 2.0f, 5.0f);
	
	textureShader = new Shader("..\\NuttyPutters\\textureShader");
	textureWood = new Texture("..\\NuttyPutters\\box.jpg");
	CHECK_GL_ERROR;

	freeCam = new free_camera();
	freeCam->set_Posistion(vec3(0, 0, 10));
	freeCam->set_Target(vec3(0, 0, 0));
	freeCam->set_projection(quarter_pi<float>(), (float)1600 / (float)900, 0.414f, 1000.0f);
	CHECK_GL_ERROR;
}
