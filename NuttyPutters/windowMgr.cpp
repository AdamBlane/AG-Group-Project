// Externals
#include <iostream>

// Internals
#include "windowMgr.h"

/// windowMgr is a singleton class, accessed by all the scene files
/// It initialises and sets up the window, & contains the main game loop
/// On window close, it runs through closing steps
/// Called from main.cpp

// Private Constructor
windowMgr::windowMgr() { }
// Private Deconstructor
windowMgr::~windowMgr() { }


// Set instance to NULL initially, since it'll be created on demand in main
windowMgr* windowMgr::instance = NULL;

// Return windowMgr singleton instance
windowMgr* windowMgr::getInstance()
{
	// If it doesn't exist, create it
	if (instance == NULL)
		instance = new windowMgr();
	
	// Return created/existing instance
	return instance;
}

// Setup; GLFW stuff, creates window
GLFWwindow* windowMgr::Init()
{
	// Initialise GLFW libraries
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// Create window
	win = glfwCreateWindow(width, height, "Nutty Putters", NULL, NULL);

	//glfwSetWindowSize(win, 2000, 1000);
	//glfwSetWindowPos(win, 0, 0);
	//glfwGetWindowSize(win, &width , &height);
	//glfwGetWindowPos(win, &PosX, &PosY);

	// Check window was created successfully
	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Make window the current context
	glfwMakeContextCurrent(win);

	// Initialise GLEW 
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cout << "Glew failed to initialise!" << std::endl;
	}

	// Initialise max number of meshes any scene uses (game scene probably)
	for (int i = 0; i < 8; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		meshes.push_back(mesh);
	}
	// Initialise all textures, then add to the textures map
	Texture* startBackground = new Texture("..\\NuttyPutters\\Mainmenu\\startBackground.png");
	textures.insert(std::pair<std::string, Texture*>("startBackground", startBackground));
	Texture* startGameBtnSelected = new Texture("..\\NuttyPutters\\Mainmenu\\startSelected.png");
	textures.insert(std::pair<std::string, Texture*>("startGameBtnSelected", startGameBtnSelected));
	Texture* startGameBtnUnselected = new Texture("..\\NuttyPutters\\Mainmenu\\startUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("startGameBtnUnselected", startGameBtnUnselected));
	Texture* loadGameBtnSelected = new Texture("..\\NuttyPutters\\Mainmenu\\loadSelected.png");
	textures.insert(std::pair<std::string, Texture*>("loadGameBtnSelected", loadGameBtnSelected));
	Texture* loadGameBtnUnselected = new Texture("..\\NuttyPutters\\Mainmenu\\loadUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("loadGameBtnUnselected", loadGameBtnUnselected));
	Texture* highscoresBtnSelected = new Texture("..\\NuttyPutters\\Mainmenu\\HighScoreSelected.png");
	textures.insert(std::pair<std::string, Texture*>("highscoresBtnSelected", highscoresBtnSelected));
	Texture* highscoresBtnUnselected = new Texture("..\\NuttyPutters\\Mainmenu\\HighScoreUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("highscoresBtnUnselected", highscoresBtnUnselected));
	Texture* optionsBtnSelected = new Texture("..\\NuttyPutters\\Mainmenu\\optionsSelected.png");
	textures.insert(std::pair<std::string, Texture*>("optionsBtnSelected", optionsBtnSelected));
	Texture* optionsBtnUnselected = new Texture("..\\NuttyPutters\\Mainmenu\\optionsUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("optionsBtnUnselected", optionsBtnUnselected));
	Texture* internetBtnSelected = new Texture("..\\NuttyPutters\\Mainmenu\\InternetSelected.png");
	textures.insert(std::pair<std::string, Texture*>("internetBtnSelected", internetBtnSelected));
	Texture* internetBtnUnselected = new Texture("..\\NuttyPutters\\Mainmenu\\InternetUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("internetBtnUnselected", internetBtnUnselected));
	Texture* exitBtnSelected = new Texture("..\\NuttyPutters\\Mainmenu\\exitSelected.png");
	textures.insert(std::pair<std::string, Texture*>("exitBtnSelected", exitBtnSelected));
	Texture* exitBtnUnselected = new Texture("..\\NuttyPutters\\Mainmenu\\exitUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("exitBtnUnselected", exitBtnUnselected));
	Texture* loadGameBackground = new Texture("..\\NuttyPutters\\highscore\\optbackground.png");
	textures.insert(std::pair<std::string, Texture*>("loadGameBackground", loadGameBackground));


	// Setup start scene
	sceneManager.startScene.Init(win);


	return win;
}

// Switches on current scene, calls on appropriate file to render/read input
void windowMgr::Update()
{	
	// While window is open...
	while (!glfwWindowShouldClose(win))
	{
		// Scene manager (property of winMgr) tracks game state
		switch (sceneManager.curScene)
		{
		// Exit game
		case 0:
			CleanUp();
			break;
		// Start scene
		case 1:
			// Draw content
			sceneManager.startScene.Loop(win);			
			break;
		// Player Select scene
		case 2:
			// Draw content
			sceneManager.playerSelectScene.Loop(win);
			break;
		// Load Game scene
		case 3:
			// Draw content
			sceneManager.loadGameScene.Loop(win);
			break;
		// Highscore scene
		case 4:
			// Draw content
			sceneManager.highscoreScene.Loop(win);
			break;
		// Options scene
		case 5:
			// Draw content
			sceneManager.optionsScene.Loop(win);
			break;
		// Game scene
		case 6:
			// Draw
			sceneManager.gameScene.Loop(win);
			break;
		default: break;
		}

		// DEBUG - for testing, write our current scene
		//std::cout << sceneManager.curScene << std::endl;
	}

		
}

// On window close
void windowMgr::CleanUp()
{
	glfwDestroyWindow(win); // Runs when commented out - why?
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
