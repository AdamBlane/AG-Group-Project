// Externals
#include <iostream>
#include <fstream>
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

	// Set default values for window res
	width = 1600, height = 900;
	// This is x and y offset for window creation on monitor (from top left corner)
	// TODO - determine center of screen
	PosX = 100, PosY = 100;
	// Create window
	win = glfwCreateWindow(width, height, "Nutty Putters", NULL, NULL);
	// Center it
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


	// ############################ AUDIO ############################
	// Init fmod system
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
	// Load sounds
	system->createSound("..\\NuttyPutters\\audio\\powerup.wav", FMOD_DEFAULT, 0, &menuSelect);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("menuSelect", menuSelect));


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
	PAUSEtargetCam = new target_camera();
	//PAUSEtargetCam->set_Posistion(vec3(0.0f, 15.0f, 0.0f));
	//PAUSEtargetCam->set_Target(vec3(0, 0, 0));
	PAUSEtargetCam->set_projection(quarter_pi<float>(), (float)width / (float)height, 0.414f, 1000.0f);
	// Free camera for in game
	freeCam = new free_camera();
	freeCam->set_Posistion(vec3(0, 10, -10));
	freeCam->rotate(-10.0, 0.0);
	freeCam->set_Target(vec3(0, 0, 0));
	freeCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);
	// Chase camera for p1 in game
	p1ChaseCam = new chase_camera();
	p1ChaseCam->set_pos_offset(vec3(0.0f, 5.0f, -5.0f));
	p1ChaseCam->set_springiness(0.2f);
	p1ChaseCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width /2 / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);
	// p2 chase cam
	p2ChaseCam = new chase_camera();
	p2ChaseCam->set_pos_offset(vec3(0.0f, 5.0f, -5.0f));
	p2ChaseCam->set_springiness(0.2f);
	p2ChaseCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width /2 / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);

	// ############################ MESHES ############################
	// Initialise general use HUD meshes
	for (int i = 0; i < 37; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		meshes.push_back(mesh);
	}

	// Initialise unique meshes
	// Player meshes
	player1Mesh = new Mesh("..\\NuttyPutters\\sphere.obj");
	player2Mesh = new Mesh("..\\NuttyPutters\\sphere.obj");
	p1ArrowMesh = new Mesh(Mesh::CUBOID, vec3(1.8f, 3.6f, 0.0f), 3.0f, 0.5f, 0.5f);
	p2ArrowMesh = new Mesh(Mesh::CUBOID, vec3(1.8f, 3.6f, 0.0f), 3.0f, 0.5f, 0.5f);
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
	// LOAD HIGHSCORE SCENE TEXTURES
	Texture* loadGameBackground = new Texture("..\\NuttyPutters\\grass.png");
	textures.insert(std::pair<std::string, Texture*>("loadGameBackground", loadGameBackground));
	Texture* actionLbl = new Texture("..\\NuttyPutters\\Controller\\action.png");
	textures.insert(std::pair<std::string, Texture*>("actionLbl", actionLbl));
	Texture* buttonLbl = new Texture("..\\NuttyPutters\\Controller\\buttonLbl.png");
	textures.insert(std::pair<std::string, Texture*>("buttonLbl", buttonLbl));
	Texture* selectfireLbl = new Texture("..\\NuttyPutters\\Controller\\selectfire.png");
	textures.insert(std::pair<std::string, Texture*>("selectfireLbl", selectfireLbl));
	Texture* backresetLbl = new Texture("..\\NuttyPutters\\Controller\\backreset.png");
	textures.insert(std::pair<std::string, Texture*>("backresetLbl", backresetLbl));
	Texture* pauseLbl = new Texture("..\\NuttyPutters\\Controller\\pause.png");
	textures.insert(std::pair<std::string, Texture*>("pauseLbl", pauseLbl));
	Texture* questionMarkLbl = new Texture("..\\NuttyPutters\\questionmarks.png");
	textures.insert(std::pair<std::string, Texture*>("questionMarkLbl", questionMarkLbl));
	Texture* upLbl = new Texture("..\\NuttyPutters\\Controller\\up.png");
	textures.insert(std::pair<std::string, Texture*>("upLbl", upLbl));
	Texture* leftLbl = new Texture("..\\NuttyPutters\\Controller\\left.png");
	textures.insert(std::pair<std::string, Texture*>("leftLbl", leftLbl));
	Texture* downLbl = new Texture("..\\NuttyPutters\\Controller\\down.png");
	textures.insert(std::pair<std::string, Texture*>("downLbl", downLbl));
	Texture* rightLbl = new Texture("..\\NuttyPutters\\Controller\\right.png");
	textures.insert(std::pair<std::string, Texture*>("rightLbl", rightLbl));
	Texture* jumpLbl = new Texture("..\\NuttyPutters\\Controller\\jump.png");
	textures.insert(std::pair<std::string, Texture*>("jumpLbl", jumpLbl));
	Texture* zoomInLbl = new Texture("..\\NuttyPutters\\Controller\\zoomin.png");
	textures.insert(std::pair<std::string, Texture*>("zoomInLbl", zoomInLbl));
	Texture* zoomOutLbl = new Texture("..\\NuttyPutters\\Controller\\zoomout.png");
	textures.insert(std::pair<std::string, Texture*>("zoomOutLbl", zoomOutLbl));

	//// LOAD GAME XBOX BUTTON TEXTURES
	buttonsXB[0] = new Texture("..\\NuttyPutters\\Controller\\aButton.png");
	buttonsXB[1] = new Texture("..\\NuttyPutters\\Controller\\bButton.png");
	buttonsXB[2] = new Texture("..\\NuttyPutters\\Controller\\xButton.png");
	buttonsXB[3] = new Texture("..\\NuttyPutters\\Controller\\yButton.png");
	buttonsXB[4] = new Texture("..\\NuttyPutters\\Controller\\lb.png");
	buttonsXB[5] = new Texture("..\\NuttyPutters\\Controller\\rb.png");
	buttonsXB[6] = new Texture("..\\NuttyPutters\\Controller\\xbback.png");
	buttonsXB[7] = new Texture("..\\NuttyPutters\\Controller\\xbstart.png");
	buttonsXB[8] = new Texture("..\\NuttyPutters\\Controller\\psstickleft.png");
	buttonsXB[9] = new Texture("..\\NuttyPutters\\Controller\\psstickright.png");
	buttonsXB[10] = new Texture("..\\NuttyPutters\\Controller\\psup.png");
	buttonsXB[11] = new Texture("..\\NuttyPutters\\Controller\\psleft.png");
	buttonsXB[12] = new Texture("..\\NuttyPutters\\Controller\\psdown.png");
	buttonsXB[13] = new Texture("..\\NuttyPutters\\Controller\\psright.png");
	//// LOAD GAME PLAYSTATION BUTTON TEXTURES
	buttonsPS[0] = new Texture("..\\NuttyPutters\\Controller\\PSSQUARE.png");
	buttonsPS[1] = new Texture("..\\NuttyPutters\\Controller\\psx.png");
	buttonsPS[2] = new Texture("..\\NuttyPutters\\Controller\\pscircle.png");
	buttonsPS[3] = new Texture("..\\NuttyPutters\\Controller\\pstriangle.png");
	buttonsPS[4] = new Texture("..\\NuttyPutters\\Controller\\pslone.png");
	buttonsPS[5] = new Texture("..\\NuttyPutters\\Controller\\psrone.png");
	buttonsPS[6] = new Texture("..\\NuttyPutters\\Controller\\psltwo.png");
	buttonsPS[7] = new Texture("..\\NuttyPutters\\Controller\\psrtwo.png");
	buttonsPS[8] = new Texture("..\\NuttyPutters\\Controller\\psselect.png");
	buttonsPS[9] = new Texture("..\\NuttyPutters\\Controller\\psstart.png");
	buttonsPS[10] = new Texture("..\\NuttyPutters\\Controller\\psstickleft.png");
	buttonsPS[11] = new Texture("..\\NuttyPutters\\Controller\\psstickright.png");
	buttonsPS[12] = new Texture("..\\NuttyPutters\\Controller\\psbutton.png");
	buttonsPS[13] = new Texture("..\\NuttyPutters\\Controller\\pspad.png");
	buttonsPS[14] = new Texture("..\\NuttyPutters\\Controller\\psup.png");
	buttonsPS[15] = new Texture("..\\NuttyPutters\\Controller\\psleft.png");
	buttonsPS[16] = new Texture("..\\NuttyPutters\\Controller\\psdown.png");
	buttonsPS[17] = new Texture("..\\NuttyPutters\\Controller\\psright.png");

	// Read saves file for file names of saves images
	ifstream saves("saves.csv");
	while (!saves.eof())
	{
		string texturePath = "..\\NuttyPutters\\savesImages\\";
		string seed;
		getline(saves, seed); // TODO prevent this from picking up whitespace/empty cells
		texturePath += seed + ".bmp";
		if (seed != "") // In case it reads cells with only whitespace
		{
			// Create a texture for that image
			Texture* texture = new Texture(texturePath);
			// Add to saves images list
			savesImages.push_back(texture);
			cout << "Tex added to list: " << texturePath << endl;
		}
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
	Texture* playerBlueTexture = new Texture("..\\NuttyPutters\\ballBlue.jpg");
	textures.insert(std::pair<std::string, Texture*>("playerBlueTexture", playerBlueTexture));
	Texture* zeroStrokeLbl = new Texture("..\\NuttyPutters\\zero.png");
	textures.insert(std::pair<std::string, Texture*>("zeroStrokeLbl", zeroStrokeLbl));
	Texture* oneStrokeLbl = new Texture("..\\NuttyPutters\\one.png");
	textures.insert(std::pair<std::string, Texture*>("oneStrokeLbl", oneStrokeLbl));
	Texture* twoStrokeLbl = new Texture("..\\NuttyPutters\\two.png");
	textures.insert(std::pair<std::string, Texture*>("twoStrokeLbl", twoStrokeLbl));
	Texture* threeStrokeLbl = new Texture("..\\NuttyPutters\\three.png");
	textures.insert(std::pair<std::string, Texture*>("threeStrokeLbl", threeStrokeLbl));
	Texture* fourStrokeLbl = new Texture("..\\NuttyPutters\\four.png");
	textures.insert(std::pair<std::string, Texture*>("fourStrokeLbl", fourStrokeLbl));
	Texture* fiveStrokeLbl = new Texture("..\\NuttyPutters\\five.png");
	textures.insert(std::pair<std::string, Texture*>("fiveStrokeLbl", fiveStrokeLbl));
	Texture* sixStrokeLbl = new Texture("..\\NuttyPutters\\six.png");
	textures.insert(std::pair<std::string, Texture*>("sixStrokeLbl", sixStrokeLbl));
	Texture* sevenStrokeLbl = new Texture("..\\NuttyPutters\\seven.png");
	textures.insert(std::pair<std::string, Texture*>("sevenStrokeLbl", sevenStrokeLbl));
	Texture* eightStrokeLbl = new Texture("..\\NuttyPutters\\eight.png");
	textures.insert(std::pair<std::string, Texture*>("eightStrokeLbl", eightStrokeLbl));
	Texture* nineStrokeLbl = new Texture("..\\NuttyPutters\\nine.png");
	textures.insert(std::pair<std::string, Texture*>("nineStrokeLbl", nineStrokeLbl));
	Texture* tenStrokeLbl = new Texture("..\\NuttyPutters\\ten.png");
	textures.insert(std::pair<std::string, Texture*>("tenStrokeLbl", tenStrokeLbl));
	Texture* elevenStrokeLbl = new Texture("..\\NuttyPutters\\eleven.png");
	textures.insert(std::pair<std::string, Texture*>("elevenStrokeLbl", elevenStrokeLbl));
	Texture* twelveStrokeLbl = new Texture("..\\NuttyPutters\\twelve.png");
	textures.insert(std::pair<std::string, Texture*>("twelveStrokeLbl", twelveStrokeLbl));
	Texture* xStrokeLbl = new Texture("..\\NuttyPutters\\x.png");
	textures.insert(std::pair<std::string, Texture*>("xStrokeLbl", xStrokeLbl));
	Texture* playerOneLbl = new Texture("..\\NuttyPutters\\playerone.png");
	textures.insert(std::pair<std::string, Texture*>("playerOneLbl", playerOneLbl));
	Texture* playerTwoLbl = new Texture("..\\NuttyPutters\\playertwo.png");
	textures.insert(std::pair<std::string, Texture*>("playerTwoLbl", playerTwoLbl));
	Texture* powerLbl = new Texture("..\\NuttyPutters\\power.png");
	textures.insert(std::pair<std::string, Texture*>("powerLbl", powerLbl));
	Texture* powerOutlineLbl = new Texture("..\\NuttyPutters\\powerbar.jpg");
	textures.insert(std::pair<std::string, Texture*>("powerOutlineLbl", powerOutlineLbl));
	Texture* gameSplashScreen = new Texture("..\\NuttyPutters\\loadingscreen.png");
	textures.insert(std::pair<std::string, Texture*>("gameSplashScreen", gameSplashScreen));
	// Timer numbers
	Texture* zeroLbl = new Texture("..\\NuttyPutters\\nzero.png");
	textures.insert(std::pair<std::string, Texture*>("zeroLbl", zeroLbl));
	Texture* oneLbl = new Texture("..\\NuttyPutters\\none.png");
	textures.insert(std::pair<std::string, Texture*>("oneLbl", oneLbl));
	Texture* twoLbl = new Texture("..\\NuttyPutters\\ntwo.png");
	textures.insert(std::pair<std::string, Texture*>("twoLbl", twoLbl));
	Texture* threeLbl = new Texture("..\\NuttyPutters\\nthree.png");
	textures.insert(std::pair<std::string, Texture*>("threeLbl", threeLbl));
	Texture* fourLbl = new Texture("..\\NuttyPutters\\nfour.png");
	textures.insert(std::pair<std::string, Texture*>("fourLbl", fourLbl));
	Texture* fiveLbl = new Texture("..\\NuttyPutters\\nfive.png");
	textures.insert(std::pair<std::string, Texture*>("fiveLbl", fiveLbl));
	Texture* sixLbl = new Texture("..\\NuttyPutters\\nsix.png");
	textures.insert(std::pair<std::string, Texture*>("sixLbl", sixLbl));
	Texture* sevenLbl = new Texture("..\\NuttyPutters\\nseven.png");
	textures.insert(std::pair<std::string, Texture*>("sevenLbl", sevenLbl));
	Texture* eightLbl = new Texture("..\\NuttyPutters\\neight.png");
	textures.insert(std::pair<std::string, Texture*>("eightLbl", eightLbl));
	Texture* nineLbl = new Texture("..\\NuttyPutters\\nnine.png");
	textures.insert(std::pair<std::string, Texture*>("nineLbl", nineLbl));
	Texture* semiColonLbl = new Texture("..\\NuttyPutters\\semicolon.png");
	textures.insert(std::pair<std::string, Texture*>("semiColonLbl", semiColonLbl));
	// Game information
	Texture* parFourLbl = new Texture("..\\NuttyPutters\\par4.png");
	textures.insert(std::pair<std::string, Texture*>("parFourLbl", parFourLbl));
	Texture* timeTwoLbl = new Texture("..\\NuttyPutters\\timetwo.png");
	textures.insert(std::pair<std::string, Texture*>("timeTwoLbl", timeTwoLbl));
	Texture* xContinueLbl = new Texture("..\\NuttyPutters\\xcontinue.png");
	textures.insert(std::pair<std::string, Texture*>("xContinueLbl", xContinueLbl));
	Texture* outOfLbl = new Texture("..\\NuttyPutters\\outof.png");
	textures.insert(std::pair<std::string, Texture*>("outOfLbl", outOfLbl));
	Texture* outOfTimeLbl = new Texture("..\\NuttyPutters\\time.png");
	textures.insert(std::pair<std::string, Texture*>("outOfTimeLbl", outOfTimeLbl));
	Texture* outOfStrokesLbl = new Texture("..\\NuttyPutters\\shots.png");
	textures.insert(std::pair<std::string, Texture*>("outOfStrokesLbl", outOfStrokesLbl));
	Texture* saveGameLbl = new Texture("..\\NuttyPutters\\savegame.png");
	textures.insert(std::pair<std::string, Texture*>("saveGameLbl", saveGameLbl));
	Texture* holeLbl = new Texture("..\\NuttyPutters\\hole.png");
	textures.insert(std::pair<std::string, Texture*>("holeLbl", holeLbl));
	Texture* completeLbl = new Texture("..\\NuttyPutters\\complete.png");
	textures.insert(std::pair<std::string, Texture*>("completeLbl", completeLbl));
	Texture* keyLbl = new Texture("..\\NuttyPutters\\Controller\\key.png");
	textures.insert(std::pair<std::string, Texture*>("keyLbl", keyLbl));
	// LOAD KEYBOARD KEYS
	buttonsKeyboardOne = new Texture("..\\NuttyPutters\\controller\\A.png");
	Texture* aLbl = new Texture("..\\NuttyPutters\\controller\\A.png");
	textures.insert(std::pair<std::string, Texture*>("aLbl", aLbl));
	Texture* bLbl = new Texture("..\\NuttyPutters\\controller\\B.png");
	textures.insert(std::pair<std::string, Texture*>("bLbl", bLbl));
	Texture* cLbl = new Texture("..\\NuttyPutters\\controller\\C.png");
	textures.insert(std::pair<std::string, Texture*>("cLbl", cLbl));
	Texture* dLbl = new Texture("..\\NuttyPutters\\controller\\D.png");
	textures.insert(std::pair<std::string, Texture*>("dLbl", dLbl));
	Texture* eLbl = new Texture("..\\NuttyPutters\\controller\\E.png");
	textures.insert(std::pair<std::string, Texture*>("eLbl", eLbl));
	Texture* fLbl = new Texture("..\\NuttyPutters\\controller\\F.png");
	textures.insert(std::pair<std::string, Texture*>("fLbl", fLbl));
	Texture* gLbl = new Texture("..\\NuttyPutters\\controller\\G.png");
	textures.insert(std::pair<std::string, Texture*>("gLbl", gLbl));
	Texture* hLbl = new Texture("..\\NuttyPutters\\controller\\H.png");
	textures.insert(std::pair<std::string, Texture*>("hLbl", hLbl));
	Texture* iLbl = new Texture("..\\NuttyPutters\\controller\\I.png");
	textures.insert(std::pair<std::string, Texture*>("iLbl", iLbl));
	Texture* jLbl = new Texture("..\\NuttyPutters\\controller\\J.png");
	textures.insert(std::pair<std::string, Texture*>("jLbl", jLbl));
	Texture* kLbl = new Texture("..\\NuttyPutters\\controller\\K.png");
	textures.insert(std::pair<std::string, Texture*>("kLbl", kLbl));
	Texture* lLbl = new Texture("..\\NuttyPutters\\controller\\L.png");
	textures.insert(std::pair<std::string, Texture*>("lLbl", lLbl));
	Texture* mLbl = new Texture("..\\NuttyPutters\\controller\\M.png");
	textures.insert(std::pair<std::string, Texture*>("mLbl", mLbl));
	Texture* nLbl = new Texture("..\\NuttyPutters\\controller\\N.png");
	textures.insert(std::pair<std::string, Texture*>("nLbl", nLbl));
	Texture* oLbl = new Texture("..\\NuttyPutters\\controller\\O.png");
	textures.insert(std::pair<std::string, Texture*>("oLbl", oLbl));
	Texture* pLbl = new Texture("..\\NuttyPutters\\controller\\P.png");
	textures.insert(std::pair<std::string, Texture*>("pLbl", pLbl));
	Texture* qLbl = new Texture("..\\NuttyPutters\\controller\\Q.png");
	textures.insert(std::pair<std::string, Texture*>("qLbl", qLbl));
	Texture* rLbl = new Texture("..\\NuttyPutters\\controller\\R.png");
	textures.insert(std::pair<std::string, Texture*>("rLbl", rLbl));
	Texture* sLbl = new Texture("..\\NuttyPutters\\controller\\S.png");
	textures.insert(std::pair<std::string, Texture*>("sLbl", sLbl));
	Texture* tLbl = new Texture("..\\NuttyPutters\\controller\\T.png");
	textures.insert(std::pair<std::string, Texture*>("tLbl", tLbl));
	Texture* uLbl = new Texture("..\\NuttyPutters\\controller\\U.png");
	textures.insert(std::pair<std::string, Texture*>("uLbl", uLbl));
	Texture* vLbl = new Texture("..\\NuttyPutters\\controller\\V.png");
	textures.insert(std::pair<std::string, Texture*>("vLbl", vLbl));
	Texture* wLbl = new Texture("..\\NuttyPutters\\controller\\W.png");
	textures.insert(std::pair<std::string, Texture*>("wLbl", wLbl));
	Texture* xLbl = new Texture("..\\NuttyPutters\\controller\\X.png");
	textures.insert(std::pair<std::string, Texture*>("xLbl", xLbl));
	Texture* yLbl = new Texture("..\\NuttyPutters\\controller\\Y.png");
	textures.insert(std::pair<std::string, Texture*>("yLbl", yLbl));
	Texture* zLbl = new Texture("..\\NuttyPutters\\controller\\Z.png");
	textures.insert(std::pair<std::string, Texture*>("zLbl", zLbl));

	//Tiles stuff initialized here
	for (int i = 0; i < 15; ++i)

	{
		Mesh* mesh = new Mesh(Mesh::CUBOID, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		tileMeshes.push_back(mesh);
	}

	for (int i = 0; i < 15; ++i)

	{
		Mesh* mesh = new Mesh(Mesh::CUBOID, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		obstacleMeshes.push_back(mesh);
	}

	for (int i = 0; i < 2; ++i)

	{
		Mesh* mesh = new Mesh(Mesh::PLANE, vec3(0.0f, 0.0f, -1.0f), 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		planeMeshes.push_back(mesh);
	}

	// Initialise tile textures, then add to map
	Texture* floorGrass = new Texture("..\\NuttyPutters\\grass.png");
	tileTextures.insert(std::pair<std::string, Texture*>("floorGrass", floorGrass));

	Texture* grassHole = new Texture("..\\NuttyPutters\\grassHole.png");
	tileTextures.insert(std::pair<std::string, Texture*>("grassHole", grassHole));

	Texture* grassScenery = new Texture("..\\NuttyPutters\\lava.jpg");
	tileTextures.insert(std::pair<std::string, Texture*>("grassScenery", grassScenery));

	Texture* tileWood = new Texture("..\\NuttyPutters\\box.jpg");
	tileTextures.insert(std::pair<std::string, Texture*>("tileWood", tileWood));

	Texture* waterBridge = new Texture("..\\NuttyPutters\\water.png");
	tileTextures.insert(std::pair<std::string, Texture*>("waterBridge", waterBridge));

	Texture* bottomBridge = new Texture("..\\NuttyPutters\\bridgeBottom.jpg");
	tileTextures.insert(std::pair<std::string, Texture*>("bottomBridge", bottomBridge));



	// Setup start scene
	sceneManager.startScene.Init(win);

	return win;
}

// Called by gameScene.cpp whenever the user saves that level
// Take the saved level seed and ask winMgr to grab the newly made image and add to list
void windowMgr::UpdateSavesImages(string savedImagePath)
{
	savesImages.push_back(new Texture(savedImagePath));
}

// Called from other scenes, given the key for sound map
void windowMgr::PlayThisSound(string sound)
{
	// Get a thread to play the sound, pass in fmod system and given sound
	std::thread t(&windowMgr::ThreadPlaySound, this, system, soundEffects[sound]);

	t.join();
}

// The function which threads execute; plays a given sound effect
void windowMgr::ThreadPlaySound(FMOD::System* system, FMOD::Sound* sound)
{
	// Play the sound! 
	system->playSound(sound, NULL, false, NULL);
}


// Switches on current scene, calls on appropriate file to render/read input
void windowMgr::Update()
{	
	// While window is open...
	while (!glfwWindowShouldClose(win))
	{
		// Update FMOD audio engine
		system->update();

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
