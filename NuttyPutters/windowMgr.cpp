// Externals
#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include <future>
#include <mutex>
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
	glfwSetWindowSizeLimits(win, width, height, width,height);

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
	HUDtargetCam->set_projection(quarter_pi<float>(), (float)width / (float)height, 0.414f, 40000.0f);
	// Target camera for pause
	PAUSEtargetCam = new target_camera();
	//PAUSEtargetCam->set_Posistion(vec3(0.0f, 15.0f, 0.0f));
	//PAUSEtargetCam->set_Target(vec3(0, 0, 0));
	PAUSEtargetCam->set_projection(quarter_pi<float>(), (float)width / (float)height, 0.414f, 40000.0f);
	// Free camera for in game
	freeCam = new free_camera();
	freeCam->set_Posistion(vec3(0, 10, -10));
	freeCam->rotate(-10.0, 0.0);
	freeCam->set_Target(vec3(0, 0, 0));
	freeCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 40000.0f);
	// Chase camera for p1 in game
	p1ChaseCam = new chase_camera();
	p1ChaseCam->set_pos_offset(vec3(0.0f, 5.0f, -5.0f));
	p1ChaseCam->set_springiness(0.2f);
	p1ChaseCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 40000.0f);
	chaseCams.push_back(p1ChaseCam);
	// p2 chase cam
	p2ChaseCam = new chase_camera();
	p2ChaseCam->set_pos_offset(vec3(0.0f, 5.0f, -5.0f));
	p2ChaseCam->set_springiness(0.2f);
	p2ChaseCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / 2 / (float)windowMgr::getInstance()->height, 0.414f, 40000.0f);
	chaseCams.push_back(p2ChaseCam);

	// ############################ SPLASH SCREEN ############################
	Texture* startBackground = new Texture("..\\NuttyPutters\\Mainmenu\\startBackground.jpg");
	textures.insert(std::pair<std::string, Texture*>("startBackground", startBackground));

	meshSplash = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used

	// Load game splash screen
	RenderSplashScreen(win);
	// Update hud target camera
	HUDtargetCam->update(0.00001);


	// ############################ AUDIO ############################
	// Init fmod system
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
	// Load sounds
	system->createSound("..\\NuttyPutters\\audio\\powerup.wav", FMOD_DEFAULT, 0, &menuSelect);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("menuSelect", menuSelect));
	system->createSound("..\\NuttyPutters\\audio\\golf-ball-putt.wav", FMOD_DEFAULT, 0, &golfBallPutt);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("golfBallPutt", golfBallPutt));
	system->createSound("..\\NuttyPutters\\audio\\golf-ball-hit.wav", FMOD_DEFAULT, 0, &golfBallHit);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("golfBallHit", golfBallHit));
	system->createSound("..\\NuttyPutters\\audio\\golf-ball-jump.wav", FMOD_DEFAULT, 0, &golfBallJump);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("golfBallJump", golfBallJump));
	system->createSound("..\\NuttyPutters\\audio\\golf-ball-wood-hit.wav", FMOD_DEFAULT, 0, &golfBallWoodHit);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("golfBallWoodHit", golfBallWoodHit));

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
	// Pickup crate meshes - no more than 5 in any given level
	for (int i = 0; i < 5; i++)
	{
		Transform trans;		
		pickupCrateTransforms.push_back(trans);
		pickupCrateMeshes.push_back(new Mesh(Mesh::CUBOID, vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f));
	}
	
	// World clock meshes
	for (int i = 0; i < 5; i++)
	{
		Mesh* mesh = new Mesh(Mesh::CUBOID, vec3(-5.0f + (i * 2.5), 8.0f, 0.0f), 5.0f, 5.0f, 5.0f);
		worldClock.push_back(mesh);
	}

	// ############################ TEXTURES ############################

	// START SCENE TEXTURES 
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
			//cout << "Tex added to list: " << texturePath << endl;
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
	Texture* fullscreenBtnUnselected = new Texture("..\\NuttyPutters\\highscore\\doesitmatter.png");
	textures.insert(std::pair<std::string, Texture*>("fullscreenBtnUnselected", fullscreenBtnUnselected));
	Texture* fullscreenBtnSelected = new Texture("..\\NuttyPutters\\highscore\\no.png");
	textures.insert(std::pair<std::string, Texture*>("fullscreenBtnSelected", fullscreenBtnSelected));
	Texture* smallwindowBtnUnselected = new Texture("..\\NuttyPutters\\highscore\\full.png");
	textures.insert(std::pair<std::string, Texture*>("smallwindowBtnUnselected", smallwindowBtnUnselected));
	Texture* smallwindowBtnSelected = new Texture("..\\NuttyPutters\\highscore\\full(1).png");
	textures.insert(std::pair<std::string, Texture*>("smallwindowBtnSelected", smallwindowBtnSelected));
	Texture* halfBtnUnselected = new Texture("..\\NuttyPutters\\highscore\\half.png");
	textures.insert(std::pair<std::string, Texture*>("halfBtnUnselected", halfBtnUnselected));
	Texture* halfBtnSelected = new Texture("..\\NuttyPutters\\highscore\\half(1).png");
	textures.insert(std::pair<std::string, Texture*>("halfBtnSelected", halfBtnSelected));
	Texture* thirdBtnSelected = new Texture("..\\NuttyPutters\\highscore\\third(1).png");
	textures.insert(std::pair<std::string, Texture*>("thirdBtnSelected", thirdBtnSelected));
	Texture* thirdBtnUnselected = new Texture("..\\NuttyPutters\\highscore\\third.png");
	textures.insert(std::pair<std::string, Texture*>("thirdBtnUnselected", thirdBtnUnselected));
	// GAME SCENE TEXTURES
	// Skybox textures
	skyboxTexture = new Texture(posXfileName, negXfileName, posYfileName, negYfileName, posZfileName, negZfileName);
	// Skybox mesh must be created after
	skyboxMesh = new Mesh(skyboxTexture);
	// Player textures
	Texture* playerRedTexture = new Texture("..\\NuttyPutters\\ballRed.jpg");
	textures.insert(std::pair<std::string, Texture*>("playerRedTexture", playerRedTexture));
	Texture* playerBlueTexture = new Texture("..\\NuttyPutters\\ballBlue.jpg");
	textures.insert(std::pair<std::string, Texture*>("playerBlueTexture", playerBlueTexture));
	// Pickup crate texture
	pickupCrateTexture = new Texture("..\\NuttyPutters\\powerUpBox.png");
	// HUD label textures
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
	//textures.insert(std::pair<std::string, Texture*>("zeroLbl", zeroLbl));
	numberTextures.push_back(zeroLbl);
	Texture* oneLbl = new Texture("..\\NuttyPutters\\none.png");
	//textures.insert(std::pair<std::string, Texture*>("oneLbl", oneLbl));
	numberTextures.push_back(oneLbl);
	Texture* twoLbl = new Texture("..\\NuttyPutters\\ntwo.png");
	//textures.insert(std::pair<std::string, Texture*>("twoLbl", twoLbl));
	numberTextures.push_back(twoLbl);
	Texture* threeLbl = new Texture("..\\NuttyPutters\\nthree.png");
	//textures.insert(std::pair<std::string, Texture*>("threeLbl", threeLbl));
	numberTextures.push_back(threeLbl);
	Texture* fourLbl = new Texture("..\\NuttyPutters\\nfour.png");
	//textures.insert(std::pair<std::string, Texture*>("fourLbl", fourLbl));
	numberTextures.push_back(fourLbl);
	Texture* fiveLbl = new Texture("..\\NuttyPutters\\nfive.png");
	//textures.insert(std::pair<std::string, Texture*>("fiveLbl", fiveLbl));
	numberTextures.push_back(fiveLbl);
	Texture* sixLbl = new Texture("..\\NuttyPutters\\nsix.png");
	//textures.insert(std::pair<std::string, Texture*>("sixLbl", sixLbl));
	numberTextures.push_back(sixLbl);
	Texture* sevenLbl = new Texture("..\\NuttyPutters\\nseven.png");
	//textures.insert(std::pair<std::string, Texture*>("sevenLbl", sevenLbl));
	numberTextures.push_back(sevenLbl);
	Texture* eightLbl = new Texture("..\\NuttyPutters\\neight.png");
	//textures.insert(std::pair<std::string, Texture*>("eightLbl", eightLbl));
	numberTextures.push_back(eightLbl);
	Texture* nineLbl = new Texture("..\\NuttyPutters\\nnine.png");
	//textures.insert(std::pair<std::string, Texture*>("nineLbl", nineLbl));
	numberTextures.push_back(nineLbl);
	Texture* semiColonLbl = new Texture("..\\NuttyPutters\\semicolon.png");
	//textures.insert(std::pair<std::string, Texture*>("semiColonLbl", semiColonLbl));
	numberTextures.push_back(semiColonLbl);
	
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

	// LOAD KEYBOARD KEYS
	buttonsKeyboardOne[0] = new Texture("..\\NuttyPutters\\controller\\comma.png");
	buttonsKeyboardOne[1] = new Texture("..\\NuttyPutters\\controller\\minus.png");
	buttonsKeyboardOne[2] = new Texture("..\\NuttyPutters\\controller\\fullstop.png");
	buttonsKeyboardOne[3] = new Texture("..\\NuttyPutters\\controller\\forwardslash.png");
	buttonsKeyboardOne[4] = new Texture("..\\NuttyPutters\\nzero.png");
	buttonsKeyboardOne[5] = new Texture("..\\NuttyPutters\\none.png");
	buttonsKeyboardOne[6] = new Texture("..\\NuttyPutters\\ntwo.png");
	buttonsKeyboardOne[7] = new Texture("..\\NuttyPutters\\nthree.png");
	buttonsKeyboardOne[8] = new Texture("..\\NuttyPutters\\nfour.png");
	buttonsKeyboardOne[9] = new Texture("..\\NuttyPutters\\nfive.png");
	buttonsKeyboardOne[10] = new Texture("..\\NuttyPutters\\nsix.png");
	buttonsKeyboardOne[11] = new Texture("..\\NuttyPutters\\nseven.png");
	buttonsKeyboardOne[12] = new Texture("..\\NuttyPutters\\neight.png");
	buttonsKeyboardOne[13] = new Texture("..\\NuttyPutters\\nnine.png");
	buttonsKeyboardOne[14] = new Texture("..\\NuttyPutters\\controller\\semicolon.png");
	buttonsKeyboardOne[15] = new Texture("..\\NuttyPutters\\controller\\equals.png");
	buttonsKeyboardOne[16] = new Texture("..\\NuttyPutters\\controller\\A.png");
	buttonsKeyboardOne[17] = new Texture("..\\NuttyPutters\\controller\\B.png");
	buttonsKeyboardOne[18] = new Texture("..\\NuttyPutters\\controller\\C.png");
	buttonsKeyboardOne[19] = new Texture("..\\NuttyPutters\\controller\\D.png");
	buttonsKeyboardOne[20] = new Texture("..\\NuttyPutters\\controller\\E.png");
	buttonsKeyboardOne[21] = new Texture("..\\NuttyPutters\\controller\\F.png");
	buttonsKeyboardOne[22] = new Texture("..\\NuttyPutters\\controller\\G.png");
	buttonsKeyboardOne[23] = new Texture("..\\NuttyPutters\\controller\\H.png");
	buttonsKeyboardOne[24] = new Texture("..\\NuttyPutters\\controller\\I.png");
	buttonsKeyboardOne[25] = new Texture("..\\NuttyPutters\\controller\\J.png");
	buttonsKeyboardOne[26] = new Texture("..\\NuttyPutters\\controller\\K.png");
	buttonsKeyboardOne[27] = new Texture("..\\NuttyPutters\\controller\\L.png");
	buttonsKeyboardOne[28] = new Texture("..\\NuttyPutters\\controller\\M.png");
	buttonsKeyboardOne[29] = new Texture("..\\NuttyPutters\\controller\\N.png");
	buttonsKeyboardOne[30] = new Texture("..\\NuttyPutters\\controller\\O.png");
	buttonsKeyboardOne[31] = new Texture("..\\NuttyPutters\\controller\\P.png");
	buttonsKeyboardOne[32] = new Texture("..\\NuttyPutters\\controller\\Q.png");
	buttonsKeyboardOne[33] = new Texture("..\\NuttyPutters\\controller\\R.png");
	buttonsKeyboardOne[34] = new Texture("..\\NuttyPutters\\controller\\S.png");
	buttonsKeyboardOne[35] = new Texture("..\\NuttyPutters\\controller\\T.png");
	buttonsKeyboardOne[36] = new Texture("..\\NuttyPutters\\controller\\U.png");
	buttonsKeyboardOne[37] = new Texture("..\\NuttyPutters\\controller\\V.png");
	buttonsKeyboardOne[38] = new Texture("..\\NuttyPutters\\controller\\W.png");
	buttonsKeyboardOne[39] = new Texture("..\\NuttyPutters\\controller\\X.png");
	buttonsKeyboardOne[40] = new Texture("..\\NuttyPutters\\controller\\Y.png");
	buttonsKeyboardOne[41] = new Texture("..\\NuttyPutters\\controller\\Z.png");
	buttonsKeyboardOne[42] = new Texture("..\\NuttyPutters\\controller\\leftbracket.png");
	buttonsKeyboardOne[43] = new Texture("..\\NuttyPutters\\controller\\backslash.png");
	buttonsKeyboardOne[44] = new Texture("..\\NuttyPutters\\controller\\rightbracket.png");
	buttonsKeyboardOne[45] = new Texture("..\\NuttyPutters\\controller\\esc.png");
	buttonsKeyboardOne[46] = new Texture("..\\NuttyPutters\\controller\\enter.png");
	buttonsKeyboardOne[47] = new Texture("..\\NuttyPutters\\controller\\tab.png");
	buttonsKeyboardOne[48] = new Texture("..\\NuttyPutters\\controller\\backspace.png");
	buttonsKeyboardOne[49] = new Texture("..\\NuttyPutters\\controller\\insert.png");
	buttonsKeyboardOne[50] = new Texture("..\\NuttyPutters\\controller\\delete.png");
	buttonsKeyboardOne[51] = new Texture("..\\NuttyPutters\\controller\\rightButton.png");
	buttonsKeyboardOne[52] = new Texture("..\\NuttyPutters\\controller\\leftButton.png");
	buttonsKeyboardOne[53] = new Texture("..\\NuttyPutters\\controller\\downButton.png");
	buttonsKeyboardOne[54] = new Texture("..\\NuttyPutters\\controller\\upButton.png");
	buttonsKeyboardOne[55] = new Texture("..\\NuttyPutters\\controller\\pageup.png");
	buttonsKeyboardOne[56] = new Texture("..\\NuttyPutters\\controller\\pagedown.png");
	buttonsKeyboardOne[57] = new Texture("..\\NuttyPutters\\controller\\home.png");
	buttonsKeyboardOne[58] = new Texture("..\\NuttyPutters\\controller\\end.png");
	buttonsKeyboardOne[59] = new Texture("..\\NuttyPutters\\controller\\caps.png");
	buttonsKeyboardOne[60] = new Texture("..\\NuttyPutters\\controller\\scroll.png");
	buttonsKeyboardOne[61] = new Texture("..\\NuttyPutters\\controller\\numlock.png");
	buttonsKeyboardOne[62] = new Texture("..\\NuttyPutters\\controller\\printscreen.png");
	buttonsKeyboardOne[63] = new Texture("..\\NuttyPutters\\controller\\pause.png");
	buttonsKeyboardOne[64] = new Texture("..\\NuttyPutters\\controller\\f1.png");
	buttonsKeyboardOne[65] = new Texture("..\\NuttyPutters\\controller\\f2.png");
	buttonsKeyboardOne[66] = new Texture("..\\NuttyPutters\\controller\\f3.png");
	buttonsKeyboardOne[67] = new Texture("..\\NuttyPutters\\controller\\f4.png");
	buttonsKeyboardOne[68] = new Texture("..\\NuttyPutters\\controller\\f5.png");
	buttonsKeyboardOne[69] = new Texture("..\\NuttyPutters\\controller\\f6.png");
	buttonsKeyboardOne[70] = new Texture("..\\NuttyPutters\\controller\\f7.png");
	buttonsKeyboardOne[71] = new Texture("..\\NuttyPutters\\controller\\f8.png");
	buttonsKeyboardOne[72] = new Texture("..\\NuttyPutters\\controller\\f9.png");
	buttonsKeyboardOne[73] = new Texture("..\\NuttyPutters\\controller\\f10.png");
	buttonsKeyboardOne[74] = new Texture("..\\NuttyPutters\\controller\\f11.png");
	buttonsKeyboardOne[75] = new Texture("..\\NuttyPutters\\controller\\f12.png");
	buttonsKeyboardOne[76] = new Texture("..\\NuttyPutters\\controller\\padzero.png");
	buttonsKeyboardOne[77] = new Texture("..\\NuttyPutters\\controller\\padone.png");
	buttonsKeyboardOne[78] = new Texture("..\\NuttyPutters\\controller\\padtwo.png");
	buttonsKeyboardOne[79] = new Texture("..\\NuttyPutters\\controller\\padthree.png");
	buttonsKeyboardOne[80] = new Texture("..\\NuttyPutters\\controller\\padfour.png");
	buttonsKeyboardOne[81] = new Texture("..\\NuttyPutters\\controller\\padfive.png");
	buttonsKeyboardOne[82] = new Texture("..\\NuttyPutters\\controller\\padsix.png");
	buttonsKeyboardOne[83] = new Texture("..\\NuttyPutters\\controller\\padseven.png");
	buttonsKeyboardOne[84] = new Texture("..\\NuttyPutters\\controller\\padeight.png");
	buttonsKeyboardOne[85] = new Texture("..\\NuttyPutters\\controller\\padnine.png");
	buttonsKeyboardOne[86] = new Texture("..\\NuttyPutters\\controller\\decimal.png");
	buttonsKeyboardOne[87] = new Texture("..\\NuttyPutters\\controller\\divide.png");
	buttonsKeyboardOne[88] = new Texture("..\\NuttyPutters\\controller\\multiply.png");
	buttonsKeyboardOne[89] = new Texture("..\\NuttyPutters\\controller\\subtract.png");
	buttonsKeyboardOne[90] = new Texture("..\\NuttyPutters\\controller\\add.png");
	buttonsKeyboardOne[91] = new Texture("..\\NuttyPutters\\controller\\enter.png");
	buttonsKeyboardOne[92] = new Texture("..\\NuttyPutters\\controller\\equals.png");
	buttonsKeyboardOne[93] = new Texture("..\\NuttyPutters\\controller\\leftshift.png");
	buttonsKeyboardOne[94] = new Texture("..\\NuttyPutters\\controller\\leftcontrol.png");
	buttonsKeyboardOne[95] = new Texture("..\\NuttyPutters\\controller\\leftalt.png");
	buttonsKeyboardOne[96] = new Texture("..\\NuttyPutters\\controller\\rightshift.png");
	buttonsKeyboardOne[97] = new Texture("..\\NuttyPutters\\controller\\rightcontrol.png");
	buttonsKeyboardOne[98] = new Texture("..\\NuttyPutters\\controller\\rightalt.png");

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

	// Setup the functions/buttons for ps4 controller - the function being the index and button being the equal value
	// FUNCTION/BUTTONS
	//windowMgr::getInstance()->gameFunctions[0] = 2;
	//windowMgr::getInstance()->gameFunctions[1] = 3;
	//windowMgr::getInstance()->gameFunctions[2] = 0;
	//windowMgr::getInstance()->gameFunctions[3] = 14;
	//windowMgr::getInstance()->gameFunctions[4] = 15;
	//windowMgr::getInstance()->gameFunctions[5] = 16;
	//windowMgr::getInstance()->gameFunctions[6] = 17;
	//windowMgr::getInstance()->gameFunctions[7] = 1;
	//windowMgr::getInstance()->gameFunctions[8] = 4;
	//windowMgr::getInstance()->gameFunctions[9] = 5;

	// xbox
	// FUNCTION/BUTTONS
	windowMgr::getInstance()->gameFunctions[0] = 2;
	windowMgr::getInstance()->gameFunctions[1] = 3;
	windowMgr::getInstance()->gameFunctions[2] = 7;
	windowMgr::getInstance()->gameFunctions[3] = 10;
	windowMgr::getInstance()->gameFunctions[4] = 11;
	windowMgr::getInstance()->gameFunctions[5] = 12;
	windowMgr::getInstance()->gameFunctions[6] = 13;
	windowMgr::getInstance()->gameFunctions[7] = 1;
	windowMgr::getInstance()->gameFunctions[8] = 4;
	windowMgr::getInstance()->gameFunctions[9] = 5;

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
	Texture* keyLbl = new Texture("..\\NuttyPutters\\Controller\\key.png");
	textures.insert(std::pair<std::string, Texture*>("keyLbl", keyLbl));

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

// Load texture thread function
void windowMgr::LoadTextures(map<std::string, Texture*> &tileTexs, GLFWwindow* window)
{
	glfwMakeContextCurrent(window);

	Texture* floorGrass = new Texture("..\\NuttyPutters\\grass.png");
	tileTexs.insert(std::pair<std::string, Texture*>("floorGrass", floorGrass));

	Texture* grassHole = new Texture("..\\NuttyPutters\\grassHole.png");
	tileTexs.insert(std::pair<std::string, Texture*>("grassHole", grassHole));

	Texture* grassScenery = new Texture("..\\NuttyPutters\\lava.jpg");
	tileTexs.insert(std::pair<std::string, Texture*>("grassScenery", grassScenery));

	Texture* tileWood = new Texture("..\\NuttyPutters\\box.jpg");
	tileTexs.insert(std::pair<std::string, Texture*>("tileWood", tileWood));

	Texture* waterBridge = new Texture("..\\NuttyPutters\\water.png");
	tileTexs.insert(std::pair<std::string, Texture*>("waterBridge", waterBridge));

	Texture* bottomBridge = new Texture("..\\NuttyPutters\\bridgeBottom.jpg");
	tileTexs.insert(std::pair<std::string, Texture*>("bottomBridge", bottomBridge));
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

void windowMgr::RenderSplashScreen(GLFWwindow* win)
{
	glfwMakeContextCurrent(win);
	cout << "Render splash screen" << endl;

	windowMgr::getInstance()->meshSplash->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshSplash->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshSplash->SetTexture(windowMgr::getInstance()->textures["startBackground"]);

	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	windowMgr::getInstance()->meshSplash->thisTexture.Bind(0);
	windowMgr::getInstance()->textureShader->Update(texShaderTransform, hudVP);
	windowMgr::getInstance()->meshSplash->Draw();

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);
	// HUD RENDERING ENDED - THANK YOU AND HAVE A NICE DAY

	// Render any background stuff if required here

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	windowMgr::getInstance()->textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}
