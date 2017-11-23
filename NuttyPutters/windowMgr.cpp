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

	// This is already set in header - unnecessary @ADAM?
	width = 1600, height = 900;
	PosX = 100, PosY = 100;
	// Create window
	win = glfwCreateWindow(width, height, "Nutty Putters", NULL, NULL);
	glfwSetWindowPos(win, PosX, PosY);

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

	// ############################ SHADERS ############################
	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");
	// Setup skybox shader
	skyboxShader = new Shader("..\\NuttyPutters\\skyShader");
	// ############################ CAMERAS ############################
	// Target camera for hud
	HUDtargetCam = new target_camera();
	HUDtargetCam->set_Posistion(vec3(0, 0, 5.0f));
	HUDtargetCam->set_Target(vec3(0, 0, 0));
	HUDtargetCam->set_projection(quarter_pi<float>(), (float)width / (float)height, 0.414f, 1000.0f);
	// Target camera for pause

	// Free camera for in game
	freeCam = new free_camera();
	freeCam->set_Posistion(vec3(0, 10, -10));
	freeCam->rotate(-10.0, 0.0);
	freeCam->set_Target(vec3(0, 0, 0));
	freeCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);
	// Chase camera for in game
	chaseCam = new chase_camera();
	chaseCam->set_pos_offset(vec3(0.0f, 5.0f, -5.0f));
	chaseCam->set_springiness(0.2f);
	chaseCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);

	// ############################ MESHES ############################
	// Initialise general use HUD meshes
	for (int i = 0; i < 24; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		meshes.push_back(mesh);
	}
	// Initialise unique meshes
	// Player meshes
	player1Mesh = new Mesh("..\\NuttyPutters\\sphere.obj");
	arrowMesh = new Mesh(Mesh::CUBOID, vec3(1.8f, 3.6f, 0.0f), 3.0f, 0.5f, 0.5f);

	// ############################ TEXTURES ############################
	// START SCENE TEXTURES 
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
	// LOAD GAME SCENE TEXTURES
	Texture* loadGameBackground = new Texture("..\\NuttyPutters\\grass.png");
	textures.insert(std::pair<std::string, Texture*>("loadGameBackground", loadGameBackground));
	Texture* actionLbl = new Texture("..\\NuttyPutters\\action.png");
	textures.insert(std::pair<std::string, Texture*>("actionLbl", actionLbl));
	Texture* buttonLbl = new Texture("..\\NuttyPutters\\buttonLbl.png");
	textures.insert(std::pair<std::string, Texture*>("buttonLbl", buttonLbl));
	Texture* selectfireLbl = new Texture("..\\NuttyPutters\\selectfire.png");
	textures.insert(std::pair<std::string, Texture*>("selectfireLbl", selectfireLbl));
	Texture* backresetLbl = new Texture("..\\NuttyPutters\\backreset.png");
	textures.insert(std::pair<std::string, Texture*>("backresetLbl", backresetLbl));
	Texture* pauseLbl = new Texture("..\\NuttyPutters\\pause.png");
	textures.insert(std::pair<std::string, Texture*>("pauseLbl", pauseLbl));
	Texture* questionMarkLbl = new Texture("..\\NuttyPutters\\questionmarks.png");
	textures.insert(std::pair<std::string, Texture*>("questionMarkLbl", questionMarkLbl));
	Texture* upLbl = new Texture("..\\NuttyPutters\\up.png");
	textures.insert(std::pair<std::string, Texture*>("upLbl", upLbl));
	Texture* leftLbl = new Texture("..\\NuttyPutters\\left.png");
	textures.insert(std::pair<std::string, Texture*>("leftLbl", leftLbl));
	Texture* downLbl = new Texture("..\\NuttyPutters\\down.png");
	textures.insert(std::pair<std::string, Texture*>("downLbl", downLbl));
	Texture* rightLbl = new Texture("..\\NuttyPutters\\right.png");
	textures.insert(std::pair<std::string, Texture*>("rightLbl", rightLbl));
	Texture* jumpLbl = new Texture("..\\NuttyPutters\\jump.png");
	textures.insert(std::pair<std::string, Texture*>("jumpLbl", jumpLbl));
	Texture* zoomInLbl = new Texture("..\\NuttyPutters\\zoomin.png");
	textures.insert(std::pair<std::string, Texture*>("zoomInLbl", zoomInLbl));
	Texture* zoomOutLbl = new Texture("..\\NuttyPutters\\zoomout.png");
	textures.insert(std::pair<std::string, Texture*>("zoomOutLbl", zoomOutLbl));

	//// LOAD GAME XBOX BUTTON TEXTURES
	buttonsXB[0] = new Texture("..\\NuttyPutters\\aButton.png");
	buttonsXB[1] = new Texture("..\\NuttyPutters\\bButton.png");
	buttonsXB[2] = new Texture("..\\NuttyPutters\\xButton.png");
	buttonsXB[3] = new Texture("..\\NuttyPutters\\yButton.png");
	buttonsXB[4] = new Texture("..\\NuttyPutters\\lb.png");
	buttonsXB[5] = new Texture("..\\NuttyPutters\\rb.png");
	buttonsXB[6] = new Texture("..\\NuttyPutters\\xbback.png");
	buttonsXB[7] = new Texture("..\\NuttyPutters\\xbstart.png");
	buttonsXB[8] = new Texture("..\\NuttyPutters\\psstickleft.png");
	buttonsXB[9] = new Texture("..\\NuttyPutters\\psstickright.png");
	buttonsXB[10] = new Texture("..\\NuttyPutters\\psup.png");
	buttonsXB[11] = new Texture("..\\NuttyPutters\\psleft.png");
	buttonsXB[12] = new Texture("..\\NuttyPutters\\psdown.png");
	buttonsXB[13] = new Texture("..\\NuttyPutters\\psselect.png");
	//// LOAD GAME PLAYSTATION BUTTON TEXTURES
	buttonsPS[0] = new Texture("..\\NuttyPutters\\PSSQUARE.png");
	buttonsPS[1] = new Texture("..\\NuttyPutters\\psx.png");
	buttonsPS[2] = new Texture("..\\NuttyPutters\\pscircle.png");
	buttonsPS[3] = new Texture("..\\NuttyPutters\\pstriangle.png");
	buttonsPS[4] = new Texture("..\\NuttyPutters\\pslone.png");
	buttonsPS[5] = new Texture("..\\NuttyPutters\\psrone.png");
	buttonsPS[6] = new Texture("..\\NuttyPutters\\psltwo.png");
	buttonsPS[7] = new Texture("..\\NuttyPutters\\psrtwo.png");
	buttonsPS[8] = new Texture("..\\NuttyPutters\\psselect.png");
	buttonsPS[9] = new Texture("..\\NuttyPutters\\psstart.png");
	buttonsPS[10] = new Texture("..\\NuttyPutters\\psstickleft.png");
	buttonsPS[11] = new Texture("..\\NuttyPutters\\psstickright.png");
	buttonsPS[12] = new Texture("..\\NuttyPutters\\psbutton.png");
	buttonsPS[13] = new Texture("..\\NuttyPutters\\pspad.png");
	buttonsPS[14] = new Texture("..\\NuttyPutters\\psup.png");
	buttonsPS[15] = new Texture("..\\NuttyPutters\\psleft.png");
	buttonsPS[16] = new Texture("..\\NuttyPutters\\psdown.png");
	buttonsPS[17] = new Texture("..\\NuttyPutters\\psright.png");

	// Read saves file for file names of saves images
	ifstream saves("saves.csv");
	while (!saves.eof())
	{
		string texturePath = "..\\NuttyPutters\\savesImages\\0";
		string seed;
		getline(saves, seed); // TODO prevent this from picking up whitespace/empty cells
		texturePath += seed + ".bmp";
		// Create a texture for that image
		Texture* texture = new Texture(texturePath);
		// Add to saves images list
		savesImages.push_back(texture);
		cout << "Tex added to list: " << texturePath << endl;
	}
	// PLAYER SELECT SCENE TEXTURES
	Texture* playerSelectBackground = new Texture("..\\NuttyPutters\\grass.png");
	textures.insert(std::pair<std::string, Texture*>("playerSelectBackground", playerSelectBackground));
	Texture* playersLabel = new Texture("..\\NuttyPutters\\players.png");
	textures.insert(std::pair<std::string, Texture*>("playersLabel", playersLabel));
	Texture* oneBtnUnselected = new Texture("..\\NuttyPutters\\none.png");
	textures.insert(std::pair<std::string, Texture*>("oneBtnUnselected", oneBtnUnselected));
	Texture* oneBtnSelected = new Texture("..\\NuttyPutters\\noneUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("oneBtnSelected", oneBtnSelected));
	Texture* twoBtnUnselected = new Texture("..\\NuttyPutters\\ntwo.png");
	textures.insert(std::pair<std::string, Texture*>("twoBtnUnselected", twoBtnUnselected));
	Texture* twoBtnSelected = new Texture("..\\NuttyPutters\\ntwoUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("twoBtnSelected", twoBtnSelected));
	Texture* difficultyLabel = new Texture("..\\NuttyPutters\\difficulty.png");
	textures.insert(std::pair<std::string, Texture*>("difficultyLabel", difficultyLabel));
	Texture* easyBtnUnselected = new Texture("..\\NuttyPutters\\easy.png");
	textures.insert(std::pair<std::string, Texture*>("easyBtnUnselected", easyBtnUnselected));
	Texture* easyBtnSelected = new Texture("..\\NuttyPutters\\easyUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("easyBtnSelected", easyBtnSelected));
	Texture* medBtnUnselected = new Texture("..\\NuttyPutters\\med.png");
	textures.insert(std::pair<std::string, Texture*>("medBtnUnselected", medBtnUnselected));
	Texture* medBtnSelected = new Texture("..\\NuttyPutters\\medUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("medBtnSelected", medBtnSelected));
	Texture* hardBtnUnselected = new Texture("..\\NuttyPutters\\hard.png");
	textures.insert(std::pair<std::string, Texture*>("hardBtnUnselected", hardBtnUnselected));
	Texture* hardBtnSelected = new Texture("..\\NuttyPutters\\hardUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("hardBtnSelected", hardBtnSelected));
	Texture* startGameBtnUnselectedPS = new Texture("..\\NuttyPutters\\startgame.png");
	textures.insert(std::pair<std::string, Texture*>("startGameBtnUnselectedPS", startGameBtnUnselectedPS));
	Texture* startGameBtnSelectedPS = new Texture("..\\NuttyPutters\\startgameUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("startGameBtnSelectedPS", startGameBtnSelectedPS));
	Texture* mainMenuBtnUnselected = new Texture("..\\NuttyPutters\\mainmenu.png");
	textures.insert(std::pair<std::string, Texture*>("mainMenuBtnUnselected", mainMenuBtnUnselected));
	Texture* mainMenuBtnSelected = new Texture("..\\NuttyPutters\\mainmenuUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("mainMenuBtnSelected", mainMenuBtnSelected));
	// OPTIONS SCENE TEXTURES
	Texture* optionsBackground = new Texture("..\\NuttyPutters\\highscore\\background.png");
	textures.insert(std::pair<std::string, Texture*>("optionsBackground", optionsBackground));
	Texture* backBtnUnselected = new Texture("..\\NuttyPutters\\highscore\\back.png");
	textures.insert(std::pair<std::string, Texture*>("backBtnUnselected", backBtnUnselected));
	Texture* backBtnSelected = new Texture("..\\NuttyPutters\\highscore\\back(1).png");
	textures.insert(std::pair<std::string, Texture*>("backBtnSelected", backBtnSelected));
	Texture* windowBtnUnselected = new Texture("..\\NuttyPutters\\highscore\\wiw.png");
	textures.insert(std::pair<std::string, Texture*>("windowBtnUnselected", windowBtnUnselected));
	Texture* windowBtnSelected = new Texture("..\\NuttyPutters\\highscore\\wiw(1).png");
	textures.insert(std::pair<std::string, Texture*>("windowBtnSelected", windowBtnSelected));
	Texture* fullscreenBtnUnselected = new Texture("..\\NuttyPutters\\highscore\\full.png");
	textures.insert(std::pair<std::string, Texture*>("fullscreenBtnUnselected", fullscreenBtnUnselected));
	Texture* fullscreenBtnSelected = new Texture("..\\NuttyPutters\\highscore\\full(1).png");
	textures.insert(std::pair<std::string, Texture*>("fullscreenBtnSelected", fullscreenBtnSelected));
	// GAME SCENE TEXTURES
	Texture* playerRedTexture = new Texture("..\\NuttyPutters\\ballRed.jpg");
	textures.insert(std::pair<std::string, Texture*>("playerRedTexture", playerRedTexture));
	Texture* arrowTexture = new Texture("..\\NuttyPutters\\ballBlue.jpg");
	textures.insert(std::pair<std::string, Texture*>("arrowTexture", arrowTexture));


	// Setup start scene
	sceneManager.startScene.Init(win);


	return win;
}

// Called by gameScene.cpp whenever the user saves that level
// Take the saved level seed and ask winMgr to grab the newly made image and add to list
void windowMgr::UpdateSavesImages(string seed)
{
	string texturePath = seed + ".bmp";
	savesImages.push_back(new Texture(texturePath));
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
