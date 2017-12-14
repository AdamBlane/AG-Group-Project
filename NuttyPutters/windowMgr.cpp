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


	// ############################ CAMERAS ############################
	// Target camera for hud
	HUDtargetCam = new target_camera();
	HUDtargetCam->set_Posistion(vec3(0, 0, 5.0f));
	HUDtargetCam->set_Target(vec3(0, 0, 0));
	HUDtargetCam->set_projection(quarter_pi<float>(), (float)width / (float)height, 0.414f, 40000.0f);
	

	// ############################ SPLASH SCREEN ############################
	Texture* startBackground = new Texture("..\\NuttyPutters\\Mainmenu\\startBackground.png");
	textures.insert(std::pair<std::string, Texture*>("startBackground", startBackground));

	Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
	meshes.push_back(mesh);



	// Setup start scene
	sceneManager.startScene.FirstTimeInit(win);

	return win;
}

void windowMgr::LoadAssets()
{
	// Spawn and detach spaceship threads
	for (int i = 0; i < threadCount; i++)
	{
		// Create spaceship transform first, add to list
		Transform spaceshipTransform;
		spaceshipTransform.getScale() = vec3(6.0f);
		spaceshipTransforms.push_back(spaceshipTransform);
		// Create thread, pass in i to assign id (lookup index of spaceshipTransforms)
		//thread spaceshipThread(&windowMgr::ThreadSpaceship, this, i);
		//spaceshipThread.detach();
	}

	// Setup skybox shader
	skyboxShader = new Shader("..\\NuttyPutters\\skyShader");
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
	system->createSound("..\\NuttyPutters\\audio\\spaceShipFlyby.wav", FMOD_DEFAULT, 0, &spaceshipPass);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("spaceshipPass", spaceshipPass));
	system->createSound("..\\NuttyPutters\\audio\\wormhole.wav", FMOD_DEFAULT, 0, &wormhole);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("wormhole", wormhole));
	system->createSound("..\\NuttyPutters\\audio\\spaceship_pass.mp3", FMOD_DEFAULT, 0, &spaceshipPass2);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("spaceshipPass2", spaceshipPass2));
	system->createSound("..\\NuttyPutters\\audio\\confirmSound.wav", FMOD_DEFAULT, 0, &confirmSound);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("confirmSound", confirmSound));
	system->createSound("..\\NuttyPutters\\audio\\levelSaved.wav", FMOD_DEFAULT, 0, &levelSavedSound);
	soundEffects.insert(std::pair<std::string, FMOD::Sound*>("levelSavedSound", levelSavedSound));
	// ############################ MESHES ############################
	Mesh* wormholeMesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 10.0f, 10.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
	Mesh* wormholeMesh2 = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 10.0f, 10.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
	wormholeTexture = new Texture("..\\NuttyPutters\\newWormhole.png");
	wormholeMesh->SetTexture(wormholeTexture);
	wormholeMesh2->SetTexture(wormholeTexture);
	wormholeMeshes.push_back(wormholeMesh);
	wormholeMeshes.push_back(wormholeMesh2);

	// 2D Meshes
	// Initialise general use HUD meshes
	for (int i = 0; i < 45; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		meshes.push_back(mesh);
	}
	// Setup player meshes
	for (int i = 0; i < 4; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); 
		p1HUDmeshes.push_back(mesh);
		Mesh* mesh2 = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f);
		p2HUDmeshes.push_back(mesh2);
	}
	// Setup HUD clock meshes
	for (int i = 0; i < 5; i++)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f);
		HUDclockMeshes.push_back(mesh);
	}

	//Meshes used for printing p1 score 
	for (int i = 0; i < 20; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		player1ScoreMeshes.push_back(mesh);
	}

	//Meshes used for printing p2 score 
	for (int i = 0; i < 20; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f);
		player2ScoreMeshes.push_back(mesh);
	}

	// Different scoreboard backgrounds
	for (int i = 0; i < 4; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f);

		winConditionsMeshes.push_back(mesh);
	}

	// Controller meshes used throughout the game
	for (int i = 0; i < 42; ++i)
	{
		Mesh* conmeshes = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		controllerMeshes.push_back(conmeshes);
	}

	// Controller meshes used throughout the game
	for (int i = 0; i < 8; ++i)
	{
		Mesh* startmesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		startGameMeshes.push_back(startmesh);
    }

	// Pause screen meshes
	for (int i = 0; i < 5; i++)
	{
		Mesh* pauseMesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		pauseScreenMeshes.push_back(pauseMesh);
	}

	// Image viewer panel meshes used in load game scene
	for (int i = 0; i < 9; i++)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		imagePanelMeshes.push_back(mesh);
	}
		
	// World clock meshes
	for (int i = 0; i < 5; i++)
	{
		Mesh* mesh = new Mesh(Mesh::RECTANGLE, vec3(0.0f, 2.0f, 0.0f), 5.0f, 5.0f);
		worldClockMeshes.push_back(mesh);
	}

	// 3D Meshes
	// Player meshes
	player1Mesh = new Mesh("..\\NuttyPutters\\sphere.obj");
	player2Mesh = new Mesh("..\\NuttyPutters\\sphere.obj");
	p1ArrowMesh = new Mesh(Mesh::CUBOID, vec3(1.8f, 3.6f, 0.0f), 3.0f, 0.5f, 0.5f);
	p2ArrowMesh = new Mesh(Mesh::CUBOID, vec3(1.8f, 3.6f, 0.0f), 3.0f, 0.5f, 0.5f);
	// Pickup crate meshes - no more than 5 in any given level
	for (int i = 0; i < 8; i++)
	{
		Transform trans;
		pickupCrateTransforms.push_back(trans);
		pickupCrateMeshes.push_back(new Mesh(Mesh::CUBOID, vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f));
	}



	///////////////////// SPACESHIP ///////////////////
	spaceshipTexture = new Texture("..\\NuttyPutters\\DiffuseTexture.png");
	/*spaceShip = new Mesh("..\\NuttyPutters\\DroidFighter.obj");*/
	for (int i = 0; i < 8; i++)
	{
		Mesh* spaceship = new Mesh("..\\NuttyPutters\\DroidFighter.obj");
		spaceship->SetTexture(spaceshipTexture);
		spaceshipMeshes.push_back(spaceship);
	}


	///////////////////// PLANETS ///////////////////
	alienPlanet = new Mesh("..\\NuttyPutters\\sphere.obj");
	alienPlanetTex = new Texture("..\\NuttyPutters\\alienPlanet.png");

	galaxyPlanet = new Mesh("..\\NuttyPutters\\sphere.obj");
	galaxyPlanetTex = new Texture("..\\NuttyPutters\\galaxyPlanet.png");

	gasPlanet = new Mesh("..\\NuttyPutters\\sphere.obj");
	gasPlanetTex = new Texture("..\\NuttyPutters\\gasPlanet.png");


	lavaPlanet = new Mesh("..\\NuttyPutters\\sphere.obj");
	lavaPlanetTex = new Texture("..\\NuttyPutters\\lavaPlanet.png");

	// ############################ TEXTURES ############################

	// START SCENE TEXTURES 
	Texture* startGameBtnSelected = new Texture("..\\NuttyPutters\\Mainmenu\\startSelected.png");
	textures.insert(std::pair<std::string, Texture*>("startGameBtnSelected", startGameBtnSelected));
	Texture* startGameBtnUnselected = new Texture("..\\NuttyPutters\\Mainmenu\\startUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("startGameBtnUnselected", startGameBtnUnselected));
	Texture* startgameSelected = new Texture("..\\NuttyPutters\\startgameSelected.png");
	textures.insert(std::pair<std::string, Texture*>("startgameSelected", startgameSelected));
	Texture* startgameUnselected = new Texture("..\\NuttyPutters\\startgameUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("startgameUnselected", startgameUnselected));
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

	Texture* transBackground = new Texture("..\\NuttyPutters\\trans.png");
	textures.insert(std::pair<std::string, Texture*>("transBackground", transBackground));
	// Read saves file for file names of saves images
	ifstream saves("saves.csv");
	while (!saves.eof())
	{
		string texturePath = "..\\NuttyPutters\\savesImages\\0";
		string seed;
		getline(saves, seed); // TODO prevent this from picking up whitespace/empty cells
		texturePath += seed + ".bmp";
		if (seed != "") // In case it reads cells with only whitespace
		{
			// Check for double 0
			// Create a texture for that image
			Texture* texture = new Texture(texturePath);
			// Add to saves images list
			savesImages.push_back(texture);
			//cout << "Tex added to list: " << texturePath << endl;
		}
	}
	// PLAYER SELECT SCENE TEXTURES
	Texture* playerSelectBackground = new Texture("..\\NuttyPutters\\Mainmenu\\startBackgroundplain.png");
	textures.insert(std::pair<std::string, Texture*>("playerSelectBackground", playerSelectBackground));
	Texture* playersLabel = new Texture("..\\NuttyPutters\\players.png");
	textures.insert(std::pair<std::string, Texture*>("playersLabel", playersLabel));
	Texture* playersSelected = new Texture("..\\NuttyPutters\\playersUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("playersSelected", playersSelected));
	Texture* numberOfLevels = new Texture("..\\NuttyPutters\\numberoflevels.png");
	textures.insert(std::pair<std::string, Texture*>("numberOfLevels", numberOfLevels));
	Texture* numberOfLevelsSelected = new Texture("..\\NuttyPutters\\numberoflevelsUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("numberOfLevelsSelected", numberOfLevelsSelected));
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
	Texture* difficultySelected = new Texture("..\\NuttyPutters\\difficultyUnderlined.png");
	textures.insert(std::pair<std::string, Texture*>("difficultySelected", difficultySelected));
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
	Texture* windowBtnUnselected = new Texture("..\\NuttyPutters\\options\\sixteenUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("windowBtnUnselected", windowBtnUnselected));
	Texture* windowBtnSelected = new Texture("..\\NuttyPutters\\options\\sixteenSelected.png");
	textures.insert(std::pair<std::string, Texture*>("windowBtnSelected", windowBtnSelected));
	Texture* fullscreenBtnUnselected = new Texture("..\\NuttyPutters\\options\\fullscreenUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("fullscreenBtnUnselected", fullscreenBtnUnselected));
	Texture* fullscreenBtnSelected = new Texture("..\\NuttyPutters\\options\\fullscreenSelected.png");
	textures.insert(std::pair<std::string, Texture*>("fullscreenBtnSelected", fullscreenBtnSelected));
	Texture* smallwindowBtnUnselected = new Texture("..\\NuttyPutters\\options\\twelveUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("smallwindowBtnUnselected", smallwindowBtnUnselected));
	Texture* smallwindowBtnSelected = new Texture("..\\NuttyPutters\\options\\twelveSelected.png");
	textures.insert(std::pair<std::string, Texture*>("smallwindowBtnSelected", smallwindowBtnSelected));
	Texture* halfBtnUnselected = new Texture("..\\NuttyPutters\\options\\nineUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("halfBtnUnselected", halfBtnUnselected));
	Texture* halfBtnSelected = new Texture("..\\NuttyPutters\\options\\nineSelected.png");
	textures.insert(std::pair<std::string, Texture*>("halfBtnSelected", halfBtnSelected));
	Texture* thirdBtnSelected = new Texture("..\\NuttyPutters\\options\\sixSelected.png");
	textures.insert(std::pair<std::string, Texture*>("thirdBtnSelected", thirdBtnSelected));
	Texture* thirdBtnUnselected = new Texture("..\\NuttyPutters\\options\\sixUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("thirdBtnUnselected", thirdBtnUnselected));
	// GAME SCENE TEXTURES
	// Skybox textures
	skyboxTexture = new Texture(posXfileName, negXfileName, posYfileName, negYfileName, posZfileName, negZfileName);
	// Skybox mesh must be created after
	skyboxMesh = new Mesh(skyboxTexture);
	// Player textures
	Texture* playerRedTexture = new Texture("..\\NuttyPutters\\p1Tex.png");
	textures.insert(std::pair<std::string, Texture*>("playerRedTexture", playerRedTexture));
	Texture* playerBlueTexture = new Texture("..\\NuttyPutters\\p2Tex.png");
	textures.insert(std::pair<std::string, Texture*>("playerBlueTexture", playerBlueTexture));
	//Arrow Texture
	Texture* arrowRedTexture = new Texture("..\\NuttyPutters\\arrowRedTex.png");
	textures.insert(std::pair<std::string, Texture*>("arrowRedTexture", arrowRedTexture));
	Texture* arrowBlueTexture = new Texture("..\\NuttyPutters\\arrowBlueTex.png");
	textures.insert(std::pair<std::string, Texture*>("arrowBlueTexture", arrowBlueTexture));
	// Pickup crate texture
	pickupCrateTexture = new Texture("..\\NuttyPutters\\powerUpBox.png");
	// HUD label textures
	Texture* xStrokeLbl = new Texture("..\\NuttyPutters\\controller\\X.png");
	textures.insert(std::pair<std::string, Texture*>("xStrokeLbl", xStrokeLbl));
	Texture* playerOneLbl = new Texture("..\\NuttyPutters\\playerone.png");
	textures.insert(std::pair<std::string, Texture*>("playerOneLbl", playerOneLbl));
	Texture* playerTwoLbl = new Texture("..\\NuttyPutters\\playertwo.png");
	textures.insert(std::pair<std::string, Texture*>("playerTwoLbl", playerTwoLbl));
	Texture* powerLbl = new Texture("..\\NuttyPutters\\powerbar.png");
	textures.insert(std::pair<std::string, Texture*>("powerLbl", powerLbl));
	Texture* powerIndicator = new Texture("..\\NuttyPutters\\powerIndicator.png");
	textures.insert(std::pair<std::string, Texture*>("powerIndicator", powerIndicator));
	Texture* powerOutlineLbl = new Texture("..\\NuttyPutters\\powerbar.jpg");
	textures.insert(std::pair<std::string, Texture*>("powerOutlineLbl", powerOutlineLbl));
	Texture* gameSplashScreen = new Texture("..\\NuttyPutters\\loadingscreen.png");
	textures.insert(std::pair<std::string, Texture*>("gameSplashScreen", gameSplashScreen));
	//pause screen textures
	Texture* unpauseBtnUnselected = new Texture("..\\NuttyPutters\\pause\\resumeUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("unpauseBtnUnselected", unpauseBtnUnselected));
	Texture* unpauseBtnSelected = new Texture("..\\NuttyPutters\\pause\\resumeSelected.png");
	textures.insert(std::pair<std::string, Texture*>("unpauseBtnSelected", unpauseBtnSelected));
	Texture* exitgameBtnUnselected = new Texture("..\\NuttyPutters\\pause\\exitUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("exitgameBtnUnselected", exitgameBtnUnselected));
	Texture* exitgameBtnSelected = new Texture("..\\NuttyPutters\\pause\\exitSelected.png");
	textures.insert(std::pair<std::string, Texture*>("exitgameBtnSelected", exitgameBtnSelected));
	Texture* menuBtnUnselected = new Texture("..\\NuttyPutters\\pause\\mainmenuUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("menuBtnUnselected", menuBtnUnselected));
	Texture* menuBtnSelected = new Texture("..\\NuttyPutters\\pause\\mainmenuSelected.png");
	textures.insert(std::pair<std::string, Texture*>("menuBtnSelected", menuBtnSelected));
	Texture* saveBtnUnselected = new Texture("..\\NuttyPutters\\pause\\saveUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("saveBtnUnselected", saveBtnUnselected));
	Texture* saveBtnSelected = new Texture("..\\NuttyPutters\\pause\\saveSelected.png");
	textures.insert(std::pair<std::string, Texture*>("saveBtnSelected", saveBtnSelected));
	Texture* controlsBtnSelected = new Texture("..\\NuttyPutters\\pause\\controlsSelected.png");
	textures.insert(std::pair<std::string, Texture*>("controlsBtnSelected", controlsBtnSelected));
	Texture* controlsBtnUnselected = new Texture("..\\NuttyPutters\\pause\\controlsUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("controlsBtnUnselected", controlsBtnUnselected));
	Texture* backBtnUnselected = new Texture("..\\NuttyPutters\\controller\\backUnselected.png");
	textures.insert(std::pair<std::string, Texture*>("backBtnUnselected", backBtnUnselected));
	Texture* backRed = new Texture("..\\NuttyPutters\\controller\\backred.png");
	textures.insert(std::pair<std::string, Texture*>("backRed", backRed));
	Texture* backBtnSelected = new Texture("..\\NuttyPutters\\controller\\backSelected.png");
	textures.insert(std::pair<std::string, Texture*>("backBtnSelected", backBtnSelected));
	// Timer numbers
	Texture* zeroLbl = new Texture("..\\NuttyPutters\\nzero.png");
	numberTextures.push_back(zeroLbl);
	Texture* oneLbl = new Texture("..\\NuttyPutters\\none.png");
	numberTextures.push_back(oneLbl);
	Texture* twoLbl = new Texture("..\\NuttyPutters\\ntwo.png");
	numberTextures.push_back(twoLbl);
	Texture* threeLbl = new Texture("..\\NuttyPutters\\nthree.png");
	numberTextures.push_back(threeLbl);
	Texture* fourLbl = new Texture("..\\NuttyPutters\\nfour.png");
	numberTextures.push_back(fourLbl);
	Texture* fiveLbl = new Texture("..\\NuttyPutters\\nfive.png");
	numberTextures.push_back(fiveLbl);
	Texture* sixLbl = new Texture("..\\NuttyPutters\\nsix.png");
	numberTextures.push_back(sixLbl);
	Texture* sevenLbl = new Texture("..\\NuttyPutters\\nseven.png");
	numberTextures.push_back(sevenLbl);
	Texture* eightLbl = new Texture("..\\NuttyPutters\\neight.png");
	numberTextures.push_back(eightLbl);
	Texture* nineLbl = new Texture("..\\NuttyPutters\\nnine.png");
	numberTextures.push_back(nineLbl);
	Texture* colonLbl = new Texture("..\\NuttyPutters\\colon.png");
	numberTextures.push_back(colonLbl);

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
	buttonsKeyboardOne[99] = new Texture("..\\NuttyPutters\\controller\\space.png");

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

	//*************XBOX PLAYER ONE *****************//
	// Create an input file object for player one keyboard controls
	ifstream playerOneXboxFile;
	// Open the desired file
	playerOneXboxFile.open("..\\NuttyPutters\\input\\p1XboxController.txt");

	// Check for error when loading the file
	if (playerOneXboxFile.fail())
	{
		// Print to screen
		cout << "Error in opening player one xbox file";
		// Set default values for xbox controller - FUNCTION/BUTTONS
		playerXboxControls[0][0] = 2;
		playerXboxControls[0][1] = 3;
		playerXboxControls[0][2] = 7;
		playerXboxControls[0][3] = 10;
		playerXboxControls[0][4] = 11;
		playerXboxControls[0][5] = 12;
		playerXboxControls[0][6] = 13;
		playerXboxControls[0][7] = 1;
		playerXboxControls[0][8] = 4;
		playerXboxControls[0][9] = 5;
	}

	// For the number of lines in the input file 
	for (int l = 0; l < 10; l++)
	{
		// Assign the psoition, score and name to the arrays from the file
		playerOneXboxFile >> playerXboxControls[0][l];
		//cout << "Controller one " << playerXboxControls[0][l] << endl;
	}

	//*************XBOX PLAYER TWO *****************//
	// Create an input file object for player one keyboard controls
	ifstream playerTwoXboxFile;
	// Open the desired file
	playerTwoXboxFile.open("..\\NuttyPutters\\input\\p2XboxController.txt");

	// Check for error when loading the file
	if (playerTwoXboxFile.fail())
	{
		// Print to screen
		cout << "Error in opening player one xbox file" << endl;
		// Set default values for xbox controller - FUNCTION/BUTTONS
		playerXboxControls[1][0] = 2;
		playerXboxControls[1][1] = 3;
		playerXboxControls[1][2] = 7;
		playerXboxControls[1][3] = 10;
		playerXboxControls[1][4] = 11;
		playerXboxControls[1][5] = 12;
		playerXboxControls[1][6] = 13;
		playerXboxControls[1][7] = 1;
		playerXboxControls[1][8] = 4;
		playerXboxControls[1][9] = 5;
	}

	// For the number of lines in the input file 
	for (int l = 0; l < 10; l++)
	{
		// Assign the psoition, score and name to the arrays from the file
		playerTwoXboxFile >> playerXboxControls[1][l];
		//cout << "Controller two " << playerXboxControls[1][l] << endl;
	}

	//*************KEYBOARD PLAYER ONE *****************//
	// Create an input file object for player one keyboard controls
	ifstream playerOneKeyboardFile;
	// Open the desired file
	playerOneKeyboardFile.open("..\\NuttyPutters\\input\\p1Keyboard.txt");

	// Check for error when loading the file
	if (playerOneKeyboardFile.fail())
	{
		// Print to screen
		cout << "Error in opening player one keyboard file" << endl;
		// Set default values for xbox controller - FUNCTION/BUTTONS
		windowMgr::getInstance()->playerKeyboardControls[0][0] = 81;
		windowMgr::getInstance()->playerKeyboardControls[0][1] = 69;
		windowMgr::getInstance()->playerKeyboardControls[0][2] = 80;
		windowMgr::getInstance()->playerKeyboardControls[0][3] = 87;
		windowMgr::getInstance()->playerKeyboardControls[0][4] = 68;
		windowMgr::getInstance()->playerKeyboardControls[0][5] = 83;
		windowMgr::getInstance()->playerKeyboardControls[0][6] = 65;
		windowMgr::getInstance()->playerKeyboardControls[0][7] = 90;
		windowMgr::getInstance()->playerKeyboardControls[0][8] = 82;
		windowMgr::getInstance()->playerKeyboardControls[0][9] = 70;
	}

	// For the number of lines in the input file 
	for (int l = 0; l < 10; l++)
	{
		// Assign the psoition, score and name to the arrays from the file
		playerOneKeyboardFile >> windowMgr::getInstance()->playerKeyboardControls[0][l];
		// Output them to the screen
		//cout << "Keyboard one " << windowMgr::getInstance()->playerKeyboardControls[0][l] << endl;
	}

	//*************KEYBOARD PLAYER TWO *****************//
	// Create an input file object for player two keyboard controls
	ifstream playerTwoKeyboardFile;
	// Open the desired file
	playerTwoKeyboardFile.open("..\\NuttyPutters\\input\\p2Keyboard.txt");

	// Check for error when loading the file
	if (playerTwoKeyboardFile.fail())
	{
		// Print to screen
		cout << "Error in opening player one keyboard file";
		// Set default values for xbox controller - FUNCTION/BUTTONS
		windowMgr::getInstance()->playerKeyboardControls[1][0] = 72;
		windowMgr::getInstance()->playerKeyboardControls[1][1] = 71;
		windowMgr::getInstance()->playerKeyboardControls[1][2] = 89;
		windowMgr::getInstance()->playerKeyboardControls[1][3] = 73;
		windowMgr::getInstance()->playerKeyboardControls[1][4] = 76;
		windowMgr::getInstance()->playerKeyboardControls[1][5] = 75;
		windowMgr::getInstance()->playerKeyboardControls[1][6] = 74;
		windowMgr::getInstance()->playerKeyboardControls[1][7] = 77;
		windowMgr::getInstance()->playerKeyboardControls[1][8] = 78;
		windowMgr::getInstance()->playerKeyboardControls[1][9] = 79;
	}

	// For the number of lines in the input file 
	for (int l = 0; l < 10; l++)
	{
		// Assign the psoition, score and name to the arrays from the file
		playerTwoKeyboardFile >> windowMgr::getInstance()->playerKeyboardControls[1][l];
		// Output them to the screen
		//cout << "Keyboard 2 " << windowMgr::getInstance()->playerKeyboardControls[1][l] << endl;
	}


	// LOAD HIGHSCORE SCENE TEXTURES
	Texture* loadGameBackground = new Texture("..\\NuttyPutters\\Mainmenu\\startBackground.png");
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
	Texture* highleftLbl = new Texture("..\\NuttyPutters\\Controller\\highleft.png");
	textures.insert(std::pair<std::string, Texture*>("highleftLbl", highleftLbl));
	Texture* highrightLbl = new Texture("..\\NuttyPutters\\Controller\\highright .png");
	textures.insert(std::pair<std::string, Texture*>("highrightLbl", highrightLbl));
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
	Texture* playerOneLblGreen = new Texture("..\\NuttyPutters\\controller\\playeronegreen.png");
	textures.insert(std::pair<std::string, Texture*>("playerOneLblGreen", playerOneLblGreen));
	Texture* playerTwoLblGreen = new Texture("..\\NuttyPutters\\Controller\\playertwogreen.png");
	textures.insert(std::pair<std::string, Texture*>("playerTwoLblGreen", playerTwoLblGreen));
	Texture* playerOneLblRed = new Texture("..\\NuttyPutters\\Controller\\playeronered.png");
	textures.insert(std::pair<std::string, Texture*>("playerOneLblRed", playerOneLblRed));
	Texture* playerTwoLblRed = new Texture("..\\NuttyPutters\\Controller\\playertwoRed.png");
	textures.insert(std::pair<std::string, Texture*>("playerTwoLblRed", playerTwoLblRed));
	Texture* sensitivityLbl = new Texture("..\\NuttyPutters\\Controller\\sensitivity.png");
	textures.insert(std::pair<std::string, Texture*>("sensitivityLbl", sensitivityLbl));
	Texture* selectOptionLbl = new Texture("..\\NuttyPutters\\Controller\\selectoption.png");
	textures.insert(std::pair<std::string, Texture*>("selectOptionLbl", selectOptionLbl));

	//SCORE SCREEN TEXTURES

	//Single player
	Texture* onePlayerScore = new Texture("..\\NuttyPutters\\scoreScreen_onePlayer.png");
	textures.insert(std::pair<std::string, Texture*>("onePlayerScore", onePlayerScore));
	//Multiplayer
	//player 1 wins
	Texture* MultPlayerP1Win = new Texture("..\\NuttyPutters\\scoreScreen_multiP_P1Win.png");
	textures.insert(std::pair<std::string, Texture*>("MultPlayerP1Win", MultPlayerP1Win));
	//player 2 wins
	Texture* MultPlayerP2Win = new Texture("..\\NuttyPutters\\scoreScreen_multiP_P2Win.png");
	textures.insert(std::pair<std::string, Texture*>("MultPlayerP2Win", MultPlayerP2Win));
	//draw
	Texture* MultPlayerDraw = new Texture("..\\NuttyPutters\\scoreScreen_multiP_Draw.png");
	textures.insert(std::pair<std::string, Texture*>("MultPlayerDraw", MultPlayerDraw));


	//Tiles stuff initialized here
	for (int i = 0; i < 80; ++i)
	{
		Mesh* mesh = new Mesh(Mesh::CUBOID, vec3(0.0f, 0.0f, -1.0f), 1.0f, 1.0f, 1.0f); // This scale value is abritray, since it'll always be reset in each scene it's used
		tileMeshes.push_back(mesh);
	}

	for (int i = 0; i < 30; ++i)

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
	Texture* floorGrass = new Texture("..\\NuttyPutters\\floor2.png");
	tileTextures.insert(std::pair<std::string, Texture*>("floorGrass", floorGrass));

	Texture* grassHole = new Texture("..\\NuttyPutters\\endHole2.png");
	tileTextures.insert(std::pair<std::string, Texture*>("grassHole", grassHole));

	Texture* platform = new Texture("..\\NuttyPutters\\platform2.png");
	tileTextures.insert(std::pair<std::string, Texture*>("platform", platform));

	Texture* grassScenery = new Texture("..\\NuttyPutters\\lava.jpg");
	tileTextures.insert(std::pair<std::string, Texture*>("grassScenery", grassScenery));

	Texture* tileWood = new Texture("..\\NuttyPutters\\bond.png");
	tileTextures.insert(std::pair<std::string, Texture*>("tileWood", tileWood));

	Texture* waterBridge = new Texture("..\\NuttyPutters\\water.png");
	tileTextures.insert(std::pair<std::string, Texture*>("waterBridge", waterBridge));

	Texture* bottomBridge = new Texture("..\\NuttyPutters\\bridgeBottom.jpg");
	tileTextures.insert(std::pair<std::string, Texture*>("bottomBridge", bottomBridge));

	// Initialise the controller screen
	ControlsTextureSetup();
	// Setup initial buttons
	ControlsButtonsSetup();
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

	t.detach();
}

// The function which threads execute; plays a given sound effect
void windowMgr::ThreadPlaySound(FMOD::System* system, FMOD::Sound* sound)
{
	// Play the sound! 
	system->playSound(sound, NULL, false, NULL);
}

// Handles spaceship logic
void windowMgr::ThreadSpaceship(int id)
{
	// Spaceship always moves forward. Move until route length is met, 
	// then teleport back to start (negative route length). Route length must be
	// at least width of skybox (500) - rng the extra (within range)

	// Create random engine 	
	default_random_engine rng(random_device{}());
	// Create range for additional route length
	uniform_int_distribution<int> routeLengthDistro(500, 1200);
	// Pick a random value within range, add to the skybox width
	//float routeLength = (float)500 + routeLengthDistro(rng);
	
	float speed = 0.0001f;
	// Spaceship properties - id given is index to look at in spaceshipTransforms
	uniform_int_distribution<int> yPosDistro;
	// Act on id - different behaviours for each (so hacky to have all here)
	if (id == 0)
	{
		// Pick a random value within range, add to the skybox width
		float routeLength = (float)500 + routeLengthDistro(rng);
		// Set y position range
		yPosDistro = uniform_int_distribution<int>(15, 25);
		// randomise y pos within given range
		float yPos = yPosDistro(rng);
		// Set start position (negative route length, randomised y pos)
		spaceshipTransforms[id].getPos() = vec3(-routeLength, yPos, -100.0f);
		// Rotate to face forward (this ship goes up on x)
		spaceshipTransforms[id].getRot().y = 1.5708;
		// Keep this thread alive until the game ends
		bool soundPlaying = false;
		int lastFrameUpdated = 0;
		while (true)
		{
			// If a frame has passed
			if (frameCount > lastFrameUpdated)
			{
				lastFrameUpdated = frameCount;
				
				// Travel until route length reached
				if (spaceshipTransforms[id].getPos().x < routeLength)
				{
					spaceshipTransforms[id].getPos().x += speed;
					cout << "moved" << endl;
				}
				else // Spaceship has travelled farther than route length
				{
					// Teleport to negative route length (prevent turning ship)
					spaceshipTransforms[id].getPos().x = -routeLength;
					// Assign a new route length
					float routeLength = (float)500 + routeLengthDistro(rng);
					// Assign new y position
					yPos = yPosDistro(rng);
					spaceshipTransforms[id].getPos() = vec3(-routeLength, yPos, 0.0f);
					cout << "reset" << endl;
					soundPlaying = false;
				}

				if (sceneManager.curScene == 1 || sceneManager.curScene == 6)
				{
					if (spaceshipTransforms[id].getPos().x > -20 && !soundPlaying)
					{
						cout << spaceshipTransforms[id].getPos().x << endl;
						PlayThisSound("spaceshipPass");
						soundPlaying = true;
					}
				}
			}

		} // end thread while loop
	} // end if id is 1
	else if (id == 1)
	{
		// Pick a random value within range, add to the skybox width
		float routeLength = (float)500 + routeLengthDistro(rng);
		// Set y position range
		yPosDistro = uniform_int_distribution<int>(45, 60);
		// randomise y pos within given range
		float yPos = yPosDistro(rng);
		// Set start pos to route length end point
		spaceshipTransforms[id].getPos() = vec3(routeLength, yPos, 0.0f);
		// Rotate to face forward (this ship goes down on x)
		spaceshipTransforms[id].getRot().y = -1.5708;
		// Keep this thread alive until the game ends
		bool soundPlaying = false;
		int lastFrameUpdated = 0;
		while (true)
		{
		
			if (frameCount > lastFrameUpdated)
			{
				lastFrameUpdated = frameCount;
				// Travel until route length reached
				if (spaceshipTransforms[id].getPos().x > -routeLength)
				{
					spaceshipTransforms[id].getPos().x -= speed;
				}
				else // Spaceship has travelled farther than route length
				{
					// Teleport to negative route length (prevent turning ship)
					spaceshipTransforms[id].getPos().x = routeLength;
					// Assign a new route length
					float routeLength = (float)500 + routeLengthDistro(rng);
					// Assign new y position
					yPos = yPosDistro(rng);
					spaceshipTransforms[id].getPos() = vec3(routeLength, yPos, 0.0f);
				}

				if (sceneManager.curScene == 1 || sceneManager.curScene == 6)
				{
					if (spaceshipTransforms[id].getPos().x > -20 && !soundPlaying)
					{
						cout << spaceshipTransforms[id].getPos().x << endl;
						PlayThisSound("spaceshipPass2");
						soundPlaying = true;
					}
				}
			}
			
		} // end while loop
	} // end id is 1
	else if (id == 2)
	{
		// Pick a random value within range, add to the skybox width
		float routeLength = (float)500 + routeLengthDistro(rng);
		// Set y position range
		yPosDistro = uniform_int_distribution<int>(15, 35);
		// randomise y pos within given range
		float yPos = yPosDistro(rng);
		spaceshipTransforms[id].getPos() = vec3(0.0f, -yPos, -routeLength); // negative y
		// Rotate to face forward (this ship goes down on x)
		//spaceshipTransforms[id].getRot().y = -1.5708;
		// Keep this thread alive until the game ends
		int lastFrameUpdated = 0;
		while (true)
		{
			if (frameCount > lastFrameUpdated)
			{
				lastFrameUpdated = frameCount;
				// Travel until route length reached
				if (spaceshipTransforms[id].getPos().z < routeLength)
				{
					spaceshipTransforms[id].getPos().z += speed;
				}
				else // Spaceship has travelled farther than route length
				{
					// Teleport to negative route length (prevent turning ship)
					spaceshipTransforms[id].getPos().x = -routeLength;
					// Assign a new route length
					float routeLength = (float)500 + routeLengthDistro(rng);
					// Assign new y position
					yPos = yPosDistro(rng);
					spaceshipTransforms[id].getPos() = vec3(0.0f, -yPos, -routeLength);
				}
			}
			
		}
	}
	
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

void windowMgr::ControlsTextureSetup()
{
	windowMgr::getInstance()->button_manager = 0;
	// Set scale, position and size of various meshes - all unique
	// Set background
	windowMgr::getInstance()->controllerMeshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->controllerMeshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->controllerMeshes.at(0)->SetTexture(windowMgr::getInstance()->textures["playerSelectBackground"]);
	// Set action label
	windowMgr::getInstance()->controllerMeshes.at(1)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(1)->SetPos(vec3(-2.7f, 1.39f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(1)->SetTexture(windowMgr::getInstance()->textures["actionLbl"]);
	// Set button label
	windowMgr::getInstance()->controllerMeshes.at(2)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(2)->SetPos(vec3(-1.1f, 1.39f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(2)->SetTexture(windowMgr::getInstance()->textures["buttonLbl"]);
	// Select Fire
	// Set selectfire label
	windowMgr::getInstance()->controllerMeshes.at(3)->SetScale(1.75f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(3)->SetPos(vec3(-2.7f, 1.07f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(3)->SetTexture(windowMgr::getInstance()->textures["selectfireLbl"]);
	// Back Reset
	// Set backreset label
	windowMgr::getInstance()->controllerMeshes.at(5)->SetScale(1.75f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(5)->SetPos(vec3(-2.7f, 0.75f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(5)->SetTexture(windowMgr::getInstance()->textures["backresetLbl"]);
	// Pause
	// Set pause label
	windowMgr::getInstance()->controllerMeshes.at(7)->SetScale(1.0f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(7)->SetPos(vec3(-2.7f, 0.43f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(7)->SetTexture(windowMgr::getInstance()->textures["pauseLbl"]);
	// Arrows
	// Up
	windowMgr::getInstance()->controllerMeshes.at(9)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->controllerMeshes.at(9)->SetPos(vec3(-2.7f, 0.11f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(9)->SetTexture(windowMgr::getInstance()->textures["upLbl"]);
	// Left
	windowMgr::getInstance()->controllerMeshes.at(11)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->controllerMeshes.at(11)->SetPos(vec3(-2.7f, -0.21f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(11)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);
	// Down 
	windowMgr::getInstance()->controllerMeshes.at(13)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->controllerMeshes.at(13)->SetPos(vec3(-2.7f, -0.53f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(13)->SetTexture(windowMgr::getInstance()->textures["downLbl"]);
	// Right
	windowMgr::getInstance()->controllerMeshes.at(15)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->controllerMeshes.at(15)->SetPos(vec3(-2.7f, -0.85f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(15)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);
	// Jump
	windowMgr::getInstance()->controllerMeshes.at(17)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(17)->SetPos(vec3(-2.7f, -1.17f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(17)->SetTexture(windowMgr::getInstance()->textures["jumpLbl"]);
	// Zoom In
	windowMgr::getInstance()->controllerMeshes.at(19)->SetScale(1.8f, 0.3f);
	windowMgr::getInstance()->controllerMeshes.at(19)->SetPos(vec3(-2.7f, -1.50f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(19)->SetTexture(windowMgr::getInstance()->textures["zoomInLbl"]);
	// Zoom Out
	windowMgr::getInstance()->controllerMeshes.at(21)->SetScale(1.8f, 0.3f);
	windowMgr::getInstance()->controllerMeshes.at(21)->SetPos(vec3(-2.7f, -1.82f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(21)->SetTexture(windowMgr::getInstance()->textures["zoomOutLbl"]);
	// Main Menu
	windowMgr::getInstance()->controllerMeshes.at(23)->SetScale(3.0f, 0.5f);
	windowMgr::getInstance()->controllerMeshes.at(23)->SetPos(vec3(2.5f, -1.6f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(23)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
	// Set the player one and player two lbls
	// P1
	windowMgr::getInstance()->controllerMeshes.at(24)->SetScale(2.7f, 0.45f);
	windowMgr::getInstance()->controllerMeshes.at(24)->SetPos(vec3(-2.3f, 1.81f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(24)->SetTexture(windowMgr::getInstance()->textures["playerOneLblGreen"]);
	// P2
	windowMgr::getInstance()->controllerMeshes.at(25)->SetScale(2.7f, 0.45f);
	windowMgr::getInstance()->controllerMeshes.at(25)->SetPos(vec3(0.0f, 1.81f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(25)->SetTexture(windowMgr::getInstance()->textures["playerTwoLblRed"]);
	// Keyboard Label
	windowMgr::getInstance()->controllerMeshes.at(26)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(26)->SetPos(vec3(0.5f, 1.39f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(26)->SetTexture(windowMgr::getInstance()->textures["keyLbl"]);
	// Set selectfire button label controller button
	windowMgr::getInstance()->controllerMeshes.at(4)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(4)->SetPos(vec3(-1.1f, 1.07f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(4)->SetTexture(windowMgr::getInstance()->buttonsXB[2]);
	// Set backreset button label controller button
	windowMgr::getInstance()->controllerMeshes.at(6)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(6)->SetPos(vec3(-1.1f, 0.75f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(6)->SetTexture(windowMgr::getInstance()->buttonsXB[3]);
	// Set pause button label controller button
	windowMgr::getInstance()->controllerMeshes.at(8)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(8)->SetPos(vec3(-1.1f, 0.43f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(8)->SetTexture(windowMgr::getInstance()->buttonsXB[7]);
	// Set up controller button
	windowMgr::getInstance()->controllerMeshes.at(10)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(10)->SetPos(vec3(-1.1f, 0.11f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(10)->SetTexture(windowMgr::getInstance()->buttonsXB[10]);
	// Set left controller button
	windowMgr::getInstance()->controllerMeshes.at(12)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(12)->SetPos(vec3(-1.1f, -0.21f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(12)->SetTexture(windowMgr::getInstance()->buttonsXB[11]);
	// Set down controller button
	windowMgr::getInstance()->controllerMeshes.at(14)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(14)->SetPos(vec3(-1.1f, -0.53f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(14)->SetTexture(windowMgr::getInstance()->buttonsXB[12]);
	// Set right controller button
	windowMgr::getInstance()->controllerMeshes.at(16)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(16)->SetPos(vec3(-1.1f, -0.85f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(16)->SetTexture(windowMgr::getInstance()->buttonsXB[13]);
	// Set jump controller button
	windowMgr::getInstance()->controllerMeshes.at(18)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(18)->SetPos(vec3(-1.1f, -1.17f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(18)->SetTexture(windowMgr::getInstance()->buttonsXB[1]);
	// Set zoom in controller button
	windowMgr::getInstance()->controllerMeshes.at(20)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(20)->SetPos(vec3(-1.1f, -1.50f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(20)->SetTexture(windowMgr::getInstance()->buttonsXB[4]);
	// Set zoom out controller button
	windowMgr::getInstance()->controllerMeshes.at(22)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->controllerMeshes.at(22)->SetPos(vec3(-1.1f, -1.82f, 0.0f));
	windowMgr::getInstance()->controllerMeshes.at(22)->SetTexture(windowMgr::getInstance()->buttonsXB[5]);
	// Select fire keyboard 
	windowMgr::getInstance()->controllerMeshes.at(27)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(27)->SetPos(vec3(0.5f, 1.07f, 0.0f));
	// Back reset keyboard
	windowMgr::getInstance()->controllerMeshes.at(28)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(28)->SetPos(vec3(0.5f, 0.75f, 0.0f));
	// Pause keyboard
	windowMgr::getInstance()->controllerMeshes.at(29)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(29)->SetPos(vec3(0.5f, 0.43f, 0.0f));
	// Up keyboard
	windowMgr::getInstance()->controllerMeshes.at(30)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(30)->SetPos(vec3(0.5f, 0.11f, 0.0f));
	// Left keyboard
	windowMgr::getInstance()->controllerMeshes.at(31)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(31)->SetPos(vec3(0.5f, -0.21f, 0.0f));
	// Down keyboard
	windowMgr::getInstance()->controllerMeshes.at(32)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(32)->SetPos(vec3(0.5f, -0.53f, 0.0f));
	// Right keyboard
	windowMgr::getInstance()->controllerMeshes.at(33)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(33)->SetPos(vec3(0.5f, -0.85f, 0.0f));
	// Jump keyboard
	windowMgr::getInstance()->controllerMeshes.at(34)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(34)->SetPos(vec3(0.5f, -1.17f, 0.0f));
	// Zoom in keyboard
	windowMgr::getInstance()->controllerMeshes.at(35)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(35)->SetPos(vec3(0.5f, -1.49, 0.0f));
	// Zoom out keyboard
	windowMgr::getInstance()->controllerMeshes.at(36)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->controllerMeshes.at(36)->SetPos(vec3(0.5f, -1.81, 0.0f));
	// Select an option label 
	windowMgr::getInstance()->controllerMeshes.at(37)->SetScale(2.0f, 3.2f);
	windowMgr::getInstance()->controllerMeshes.at(37)->SetPos(vec3(2.5f, 0.2, 0.0));
	windowMgr::getInstance()->controllerMeshes.at(37)->SetTexture(windowMgr::getInstance()->textures["selectOptionLbl"]);
}

void windowMgr::ControlsButtonsSetup()
{
	// For all the functions
	for (int allKeyboardFunctions = 0; allKeyboardFunctions < 10; allKeyboardFunctions++)
	{
		if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 32) // space
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[99]);
		}
		if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 44) // comma
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[0]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 45) // minus
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[1]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 46) // full stop
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[2]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 47) // forward slash
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[3]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 48) // num 0
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[4]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 49) // num 1
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[5]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 50) // num 2
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[6]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 51) // num 3
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[7]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 52) // num 4
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[8]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 53) // num 5
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[9]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 54) // num 6
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[10]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 55) // num 7
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[11]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 56) // num 8
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[12]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 57) // num 9
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[13]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 59) // ;
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[14]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 61) // =
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[15]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 65) // A
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[16]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 66) // B
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[17]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 67) // C
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[18]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 68) // D
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[19]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 69) // E
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[20]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 70) // F
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[21]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 71) // G
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[22]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 72) // H
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[23]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 73) // I
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[24]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 74) // J
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[25]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 75) // K
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[26]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 76) // L
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[27]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 77) // M
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[28]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 78) // N
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[29]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 79) // O
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[30]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 80) // P
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[31]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 81) // Q
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[32]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 82) // R
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[33]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 83) // S
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[34]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 84) // T
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[35]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 85) // U
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[36]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 86) // V
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[37]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 87) // W
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[38]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 88) // X
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[39]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 89) // Y
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[40]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 90) // Z
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[41]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 91) // Left Bracket
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[42]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 92) // Back slash
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[43]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 93) // Right bracket
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[44]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 256) // ESC
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[45]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 257) // ETNER
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[46]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 258) // TAB
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[47]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 259) // BACKSPACE
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[48]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 260) // INSERT
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[49]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 261) // DELETE
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[50]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 262) // RIGHT
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[51]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 263) // LEFT
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[52]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 264) // DOWN
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[53]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 265) // UP
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[54]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 266) // PAGE UP
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[55]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 267) // PAGE DOWN
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[56]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 268) // HOME
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[57]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 269) // END
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[58]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 280) // CAPS LOCK
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[59]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 281) // SCROLL LOCK
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[60]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 282) // NUM LOCK
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[61]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 283) // PRINT SCREEN
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[62]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 284) // PASUE
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[63]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 290) // F1
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[64]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 291) // F2
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[65]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 292) // F3
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[66]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 293) // F4
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[67]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 294) // F5
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[68]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 295) // F6
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[69]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 296) // F7
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[70]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 297) // F8
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[71]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 298) // F9
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[72]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 299) // F10
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[73]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 300) // F11
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[74]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 301) // F12
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[75]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 320) // PAD 0
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[76]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 321) // PAD 1
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[77]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 322) // PAD 2
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[78]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 323) // PAD 3
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[79]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 324) // PAD 4
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[80]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 325) // PAD 5
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[81]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 326) // PAD 6
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[82]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 327) // PAD 7
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[83]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 328) // PAD 8
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[84]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 329) // PAD 9
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[85]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 330) // DECIMAL
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[86]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 331) // DIVIDE
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[87]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 332) // MULITPLY
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[88]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 333) // SUBTRACT
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[89]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 334) // ADD
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[90]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 335) // ENTER
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[91]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 336) // EQUAL
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[92]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 340) // LEFT SHIFT
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[92]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 341) // LEFT CONTROL
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[94]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 342) // LEFT ALT
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[95]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 344) // RIGHT SHIFT
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[96]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 345) // RIGHT CONTROL
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[97]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 346) // RIGHT ALT
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[98]);
		}
		else if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][allKeyboardFunctions] == 32) // SPACE
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[99]);
		}
		else  // question marks
		{
			windowMgr::getInstance()->controllerMeshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
		}
	}

	//******CONTROLLER SETUP*************//
	// Create a variable to check if the joy stick is present - 1 means true
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	// If controller is connected 
	if (present == 1)
	{
		// Dected how many buttons the controller has
		int buttonCount;
		const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		// If the amount of buttons detected is equal to 18 then 
		if (buttonCount == 18)
		{
			//cout << "Controller type = PS4! " << endl;
			// For all the fucntions 
			for (int allFunctions = 0; allFunctions < 10; allFunctions++)
			{
				// If the button is 0 then 
				if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 0)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[0]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 1)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[1]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 2)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[2]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 3)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[3]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 4)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[4]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 5)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[5]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 6)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[6]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 7)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[7]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 8)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[8]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 9)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[9]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 10)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[10]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 11)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[11]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 12)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[12]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 13)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[13]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 14)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[14]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 15)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[15]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 16)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[16]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 17)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[17]);
				}
			}
		}
		else
		{
			//cout << "Controller type = XBOX360 OR OTHER! " << endl;
			// Setup the functions/buttons for xbox controller - the function being the index and button being the equal value
			// For all the buttons in the game 
			for (int allFunctions = 0; allFunctions < 10; allFunctions++)
			{
				// If gamefunction equals button 0 then
				if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 0)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[0]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 1)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[1]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 2)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[2]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 3)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[3]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 4)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[4]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 5)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[5]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 6)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[6]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 7)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[7]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 8)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[8]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 9)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[9]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 10)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[10]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 11)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[11]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 12)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[12]);
				}
				else if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][allFunctions] == 13)
				{
					windowMgr::getInstance()->controllerMeshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[13]);
				}
			}
		}
	}
}

void windowMgr::ControlsTrackMouse()
{
	glfwGetCursorPos(win, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);
	//cout << windowMgr::getInstance()->mouse_x << " " << windowMgr::getInstance()->mouse_y << endl;
	if ((windowMgr::getInstance()->mouse_y >= 13 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 94 * windowMgr::getInstance()->windowScale))
	{
		//this is to highlightplayer 1
		if (windowMgr::getInstance()->mouse_x <= 524 && windowMgr::getInstance()->mouse_x >= 203)
		{
			windowMgr::getInstance()->button_manager = 1;
		}
		//this is to highlight player 2
		else if (windowMgr::getInstance()->mouse_x <= 965 && windowMgr::getInstance()->mouse_x >= 631)
		{
			windowMgr::getInstance()->button_manager = 2;
		}
	}
	//this is for main menu button
	else if ((windowMgr::getInstance()->mouse_x >= 1200 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 1500 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 740 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 850 * windowMgr::getInstance()->windowScale))
	{
		windowMgr::getInstance()->button_manager = 3;
	}
}

void windowMgr::ControlsTrackClick()
{
	// Create the outputFile object
	ofstream outputFileP1Xbox, outputFileP2Xbox, outputFileP1Keyboard, outputFileP2Keyboard;
	switch (windowMgr::getInstance()->button_manager)
	{
	case 1:
		// Update the player one and two meshes based on what players is currently selected
		windowMgr::getInstance()->controllerMeshes.at(24)->SetTexture(windowMgr::getInstance()->textures["playerOneLblGreen"]);
		windowMgr::getInstance()->controllerMeshes.at(25)->SetTexture(windowMgr::getInstance()->textures["playerTwoLblRed"]);
		// Set player tab equal to one as player tab one is currently selected
		playerTab = 1;
		// Play sound on enter button
		windowMgr::getInstance()->PlayThisSound("confirmSound");
		// Call the initiastion menthod for player one
		ControlsButtonsSetup();
		break;
	case 2:
		// Update the player one and two meshes based on what players is currently selected
		windowMgr::getInstance()->controllerMeshes.at(24)->SetTexture(windowMgr::getInstance()->textures["playerOneLblRed"]);
		windowMgr::getInstance()->controllerMeshes.at(25)->SetTexture(windowMgr::getInstance()->textures["playerTwoLblGreen"]);
		// Set player tab equal to two as player tab two is currently selected
		playerTab = 2;
		// Play sound on enter button
		windowMgr::getInstance()->PlayThisSound("confirmSound");
		// Call the initiastion menthod for player two
		ControlsButtonsSetup();
		break;
	case 3:
		// Check to see if the buttons dont have set binding then
		// Find if there are any functions which dont have buttons for player keyboard 0 - KeyP1Function will produce a value other than 10 if a function is empty
		keyP1FunctionEmpty = std::distance(windowMgr::getInstance()->playerKeyboardControls[0], std::find(windowMgr::getInstance()->playerKeyboardControls[0], windowMgr::getInstance()->playerKeyboardControls[0] + 10, 999));

		// PLAYER KEYBOARD 1
		keyP2FunctionEmpty = std::distance(windowMgr::getInstance()->playerKeyboardControls[1], std::find(windowMgr::getInstance()->playerKeyboardControls[1], windowMgr::getInstance()->playerKeyboardControls[1] + 10, 999));

		// XBOX CONTROLLER 0
		xboxP1FunctionEmpty = std::distance(windowMgr::getInstance()->playerXboxControls[0], std::find(windowMgr::getInstance()->playerXboxControls[0], windowMgr::getInstance()->playerXboxControls[0] + 10, 99));

		// XBOX CONTROLLER 1
		xboxP2FunctionEmpty = std::distance(windowMgr::getInstance()->playerXboxControls[1], std::find(windowMgr::getInstance()->playerXboxControls[1], windowMgr::getInstance()->playerXboxControls[1] + 10, 99));

		if ((keyP1FunctionEmpty + keyP2FunctionEmpty + xboxP1FunctionEmpty + xboxP2FunctionEmpty) != 40)
		{
			//windowMgr::getInstance()->controllerMeshes.at(23)->SetTexture(windowMgr::getInstance()->textures["backRed"]);

			windowMgr::getInstance()->controllerMeshes.at(23)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
			cout << "Some functions dont have buttons assigned" << endl;
		}
		// Else if all the actions have buttons then 
		else
		{
			// Play sound on enter button
			windowMgr::getInstance()->PlayThisSound("confirmSound");
			// Set the output file
			outputFileP1Xbox.open("..\\NuttyPutters\\input\\p1XboxController.txt");
			outputFileP2Xbox.open("..\\NuttyPutters\\input\\p2XboxController.txt");
			outputFileP1Keyboard.open("..\\NuttyPutters\\input\\p1Keyboard.txt");
			outputFileP2Keyboard.open("..\\NuttyPutters\\input\\p2Keyboard.txt");
			// Loop through total number of entries 
			for (int l = 0; l < 10; l++)
			{
				// Output the values to the output file
				outputFileP1Xbox << windowMgr::getInstance()->playerXboxControls[0][l] << endl;
				outputFileP2Xbox << windowMgr::getInstance()->playerXboxControls[1][l] << endl;
				outputFileP1Keyboard << windowMgr::getInstance()->playerKeyboardControls[0][l] << endl;
				outputFileP2Keyboard << windowMgr::getInstance()->playerKeyboardControls[1][l] << endl;
				//cout << "Outputting control for controller one " << windowMgr::getInstance()->playerXboxControls[0][l] << endl;
				//cout << "Outputting control for controller two " << windowMgr::getInstance()->playerXboxControls[1][l] << endl;
				//cout << "Outputting control for keyboard one " << windowMgr::getInstance()->playerKeyboardControls[0][l] << endl;
				//cout << "Outputting control for keyboard two " << windowMgr::getInstance()->playerKeyboardControls[1][l] << endl;
			}

			// Check if by pressing the back button, does the app need to return to main menu or the game
			// If reutrn to game is true then
			if (returnToGame)
			{
				// Set does user want controls to false meaning in game scene .cpp the controls render loop will be ignored
				doesUserWantControls = false;
			}
			else
			{
				// Change back to main menu
				windowMgr::getInstance()->sceneManager.changeScene(1);
			}
		}
	}
}

void windowMgr::ControlsInputKeyboard()
{
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		windowMgr::getInstance()->mouseLpressed = true;
	}

	if (!glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		if (windowMgr::getInstance()->mouseLpressed)
		{
			windowMgr::getInstance()->ControlsTrackClick();
			windowMgr::getInstance()->mouseLpressed = false;
		}
	}

	// If key is pressed and boolean equals false then set bool to true
	if (glfwGetKey(win, GLFW_KEY_COMMA) && !keyboardButtonPressed[0])
	{
		keyboardButtonPressed[0] = true;
	}

	// If key is no longer pressed and bool is true then
	if (!glfwGetKey(win, GLFW_KEY_COMMA) && keyboardButtonPressed[0])
	{
		ControlsUpdateKeyboard(0, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_MINUS) && !keyboardButtonPressed[1])
	{
		keyboardButtonPressed[1] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_MINUS) && keyboardButtonPressed[1])
	{
		ControlsUpdateKeyboard(1, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_PERIOD) && !keyboardButtonPressed[2])
	{
		keyboardButtonPressed[2] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_PERIOD) && keyboardButtonPressed[2])
	{
		ControlsUpdateKeyboard(2, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_SLASH) && !keyboardButtonPressed[3])
	{
		keyboardButtonPressed[3] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_SLASH) && keyboardButtonPressed[3])
	{
		ControlsUpdateKeyboard(3, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_0) && !keyboardButtonPressed[4])
	{
		keyboardButtonPressed[4] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_0) && keyboardButtonPressed[4])
	{
		ControlsUpdateKeyboard(4, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_1) && !keyboardButtonPressed[5])
	{
		keyboardButtonPressed[5] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_1) && keyboardButtonPressed[5])
	{
		ControlsUpdateKeyboard(5, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_2) && !keyboardButtonPressed[6])
	{
		keyboardButtonPressed[6] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_2) && keyboardButtonPressed[6])
	{
		ControlsUpdateKeyboard(6, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_3) && !keyboardButtonPressed[7])
	{
		keyboardButtonPressed[7] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_3) && keyboardButtonPressed[7])
	{
		ControlsUpdateKeyboard(7, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_4) && !keyboardButtonPressed[8])
	{
		keyboardButtonPressed[8] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_4) && keyboardButtonPressed[8])
	{
		ControlsUpdateKeyboard(8, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_5) && !keyboardButtonPressed[9])
	{
		keyboardButtonPressed[9] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_5) && keyboardButtonPressed[9])
	{
		ControlsUpdateKeyboard(9, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_6) && !keyboardButtonPressed[10])
	{
		keyboardButtonPressed[10] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_6) && keyboardButtonPressed[10])
	{
		ControlsUpdateKeyboard(10, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_7) && !keyboardButtonPressed[11])
	{
		keyboardButtonPressed[11] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_7) && keyboardButtonPressed[11])
	{
		ControlsUpdateKeyboard(11, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_8) && !keyboardButtonPressed[12])
	{
		keyboardButtonPressed[12] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_8) && keyboardButtonPressed[12])
	{
		ControlsUpdateKeyboard(12, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_9) && !keyboardButtonPressed[13])
	{
		keyboardButtonPressed[13] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_9) && keyboardButtonPressed[13])
	{
		ControlsUpdateKeyboard(13, 44);
	}

	if (glfwGetKey(win, GLFW_KEY_SEMICOLON) && !keyboardButtonPressed[14])
	{
		keyboardButtonPressed[14] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_SEMICOLON) && keyboardButtonPressed[14])
	{
		ControlsUpdateKeyboard(14, 45);
	}

	if (glfwGetKey(win, GLFW_KEY_EQUAL) && !keyboardButtonPressed[15])
	{
		keyboardButtonPressed[15] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_EQUAL) && keyboardButtonPressed[15])
	{
		ControlsUpdateKeyboard(15, 46);
	}

	if (glfwGetKey(win, GLFW_KEY_A) && !keyboardButtonPressed[16])
	{
		keyboardButtonPressed[16] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_A) && keyboardButtonPressed[16])
	{
		ControlsUpdateKeyboard(16, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_B) && !keyboardButtonPressed[17])
	{
		keyboardButtonPressed[17] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_B) && keyboardButtonPressed[17])
	{
		ControlsUpdateKeyboard(17, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_C) && !keyboardButtonPressed[18])
	{
		keyboardButtonPressed[18] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_C) && keyboardButtonPressed[18])
	{
		ControlsUpdateKeyboard(18, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_D) && !keyboardButtonPressed[19])
	{
		keyboardButtonPressed[19] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_D) && keyboardButtonPressed[19])
	{
		ControlsUpdateKeyboard(19, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_E) && !keyboardButtonPressed[20])
	{
		keyboardButtonPressed[20] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_E) && keyboardButtonPressed[20])
	{
		ControlsUpdateKeyboard(20, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_F) && !keyboardButtonPressed[21])
	{
		keyboardButtonPressed[21] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F) && keyboardButtonPressed[21])
	{
		ControlsUpdateKeyboard(21, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_G) && !keyboardButtonPressed[22])
	{
		keyboardButtonPressed[22] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_G) && keyboardButtonPressed[22])
	{
		ControlsUpdateKeyboard(22, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_H) && !keyboardButtonPressed[23])
	{
		keyboardButtonPressed[23] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_H) && keyboardButtonPressed[23])
	{
		ControlsUpdateKeyboard(23, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_I) && !keyboardButtonPressed[24])
	{
		keyboardButtonPressed[24] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_I) && keyboardButtonPressed[24])
	{
		ControlsUpdateKeyboard(24, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_J) && !keyboardButtonPressed[25])
	{
		keyboardButtonPressed[25] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_J) && keyboardButtonPressed[25])
	{
		ControlsUpdateKeyboard(25, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_K) && !keyboardButtonPressed[26])
	{
		keyboardButtonPressed[26] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_K) && keyboardButtonPressed[26])
	{
		ControlsUpdateKeyboard(26, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_L) && !keyboardButtonPressed[27])
	{
		keyboardButtonPressed[27] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_L) && keyboardButtonPressed[27])
	{
		ControlsUpdateKeyboard(27, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_M) && !keyboardButtonPressed[28])
	{
		keyboardButtonPressed[28] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_M) && keyboardButtonPressed[28])
	{
		ControlsUpdateKeyboard(28, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_N) && !keyboardButtonPressed[29])
	{
		keyboardButtonPressed[29] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_N) && keyboardButtonPressed[29])
	{
		ControlsUpdateKeyboard(29, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_O) && !keyboardButtonPressed[30])
	{
		keyboardButtonPressed[30] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_O) && keyboardButtonPressed[30])
	{
		ControlsUpdateKeyboard(30, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_P) && !keyboardButtonPressed[31])
	{
		keyboardButtonPressed[31] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_P) && keyboardButtonPressed[31])
	{
		ControlsUpdateKeyboard(31, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_Q) && !keyboardButtonPressed[32])
	{
		keyboardButtonPressed[32] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_Q) && keyboardButtonPressed[32])
	{
		ControlsUpdateKeyboard(32, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_R) && !keyboardButtonPressed[33])
	{
		keyboardButtonPressed[33] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_R) && keyboardButtonPressed[33])
	{
		ControlsUpdateKeyboard(33, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_S) && !keyboardButtonPressed[34])
	{
		keyboardButtonPressed[34] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_S) && keyboardButtonPressed[34])
	{
		ControlsUpdateKeyboard(34, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_T) && !keyboardButtonPressed[35])
	{
		keyboardButtonPressed[35] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_T) && keyboardButtonPressed[35])
	{
		ControlsUpdateKeyboard(35, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_U) && !keyboardButtonPressed[36])
	{
		keyboardButtonPressed[36] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_U) && keyboardButtonPressed[36])
	{
		ControlsUpdateKeyboard(36, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_V) && !keyboardButtonPressed[37])
	{
		keyboardButtonPressed[37] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_V) && keyboardButtonPressed[37])
	{
		ControlsUpdateKeyboard(37, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_W) && !keyboardButtonPressed[38])
	{
		keyboardButtonPressed[38] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_W) && keyboardButtonPressed[38])
	{
		ControlsUpdateKeyboard(38, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_X) && !keyboardButtonPressed[39])
	{
		keyboardButtonPressed[39] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_X) && keyboardButtonPressed[39])
	{
		ControlsUpdateKeyboard(39, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_Y) && !keyboardButtonPressed[40])
	{
		keyboardButtonPressed[40] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_Y) && keyboardButtonPressed[40])
	{
		ControlsUpdateKeyboard(40, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_Z) && !keyboardButtonPressed[41])
	{
		keyboardButtonPressed[41] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_Z) && keyboardButtonPressed[41])
	{
		ControlsUpdateKeyboard(41, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT_BRACKET) && !keyboardButtonPressed[42])
	{
		keyboardButtonPressed[42] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT_BRACKET) && keyboardButtonPressed[42])
	{
		ControlsUpdateKeyboard(42, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_BACKSLASH) && !keyboardButtonPressed[43])
	{
		keyboardButtonPressed[43] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_BACKSLASH) && keyboardButtonPressed[43])
	{
		ControlsUpdateKeyboard(43, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT_BRACKET) && !keyboardButtonPressed[44])
	{
		keyboardButtonPressed[44] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT_BRACKET) && keyboardButtonPressed[44])
	{
		ControlsUpdateKeyboard(44, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_ESCAPE) && !keyboardButtonPressed[45])
	{
		keyboardButtonPressed[45] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_ESCAPE) && keyboardButtonPressed[45])
	{
		ControlsUpdateKeyboard(45, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_ENTER) && !keyboardButtonPressed[46])
	{
		keyboardButtonPressed[46] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_ENTER) && keyboardButtonPressed[46])
	{
		ControlsUpdateKeyboard(46, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_TAB) && !keyboardButtonPressed[47])
	{
		keyboardButtonPressed[47] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_TAB) && keyboardButtonPressed[47])
	{
		ControlsUpdateKeyboard(47, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_BACKSPACE) && !keyboardButtonPressed[48])
	{
		keyboardButtonPressed[48] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_BACKSPACE) && keyboardButtonPressed[48])
	{
		ControlsUpdateKeyboard(48, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_INSERT) && !keyboardButtonPressed[49])
	{
		keyboardButtonPressed[49] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_INSERT) && keyboardButtonPressed[49])
	{
		ControlsUpdateKeyboard(49, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_DELETE) && !keyboardButtonPressed[50])
	{
		keyboardButtonPressed[50] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_DELETE) && keyboardButtonPressed[50])
	{
		ControlsUpdateKeyboard(50, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT) && !keyboardButtonPressed[51])
	{
		keyboardButtonPressed[51] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT) && keyboardButtonPressed[51])
	{
		ControlsUpdateKeyboard(51, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT) && !keyboardButtonPressed[52])
	{
		keyboardButtonPressed[52] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT) && keyboardButtonPressed[52])
	{
		ControlsUpdateKeyboard(52, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_DOWN) && !keyboardButtonPressed[53])
	{
		keyboardButtonPressed[53] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_DOWN) && keyboardButtonPressed[53])
	{
		ControlsUpdateKeyboard(53, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_UP) && !keyboardButtonPressed[54])
	{
		keyboardButtonPressed[54] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_UP) && keyboardButtonPressed[54])
	{
		ControlsUpdateKeyboard(54, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_PAGE_UP) && !keyboardButtonPressed[55])
	{
		keyboardButtonPressed[55] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_PAGE_UP) && keyboardButtonPressed[55])
	{
		ControlsUpdateKeyboard(55, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_PAGE_DOWN) && !keyboardButtonPressed[56])
	{
		keyboardButtonPressed[56] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_PAGE_DOWN) && keyboardButtonPressed[56])
	{
		ControlsUpdateKeyboard(56, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_HOME) && !keyboardButtonPressed[57])
	{
		keyboardButtonPressed[57] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_HOME) && keyboardButtonPressed[57])
	{
		ControlsUpdateKeyboard(57, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_END) && !keyboardButtonPressed[58])
	{
		keyboardButtonPressed[58] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_END) && keyboardButtonPressed[58])
	{
		ControlsUpdateKeyboard(58, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_CAPS_LOCK) && !keyboardButtonPressed[59])
	{
		keyboardButtonPressed[59] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_CAPS_LOCK) && keyboardButtonPressed[59])
	{
		ControlsUpdateKeyboard(59, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_SCROLL_LOCK) && !keyboardButtonPressed[60])
	{
		keyboardButtonPressed[60] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_SCROLL_LOCK) && keyboardButtonPressed[60])
	{
		ControlsUpdateKeyboard(60, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_NUM_LOCK) && !keyboardButtonPressed[61])
	{
		keyboardButtonPressed[61] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_NUM_LOCK) && keyboardButtonPressed[61])
	{
		ControlsUpdateKeyboard(61, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_NUM_LOCK) && !keyboardButtonPressed[62])
	{
		keyboardButtonPressed[62] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_NUM_LOCK) && keyboardButtonPressed[62])
	{
		ControlsUpdateKeyboard(62, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_PAUSE) && !keyboardButtonPressed[63])
	{
		keyboardButtonPressed[63] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_PAUSE) && keyboardButtonPressed[63])
	{
		ControlsUpdateKeyboard(63, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_F1) && !keyboardButtonPressed[64])
	{
		keyboardButtonPressed[64] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F1) && keyboardButtonPressed[64])
	{
		ControlsUpdateKeyboard(64, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F2) && !keyboardButtonPressed[65])
	{
		keyboardButtonPressed[65] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F2) && keyboardButtonPressed[65])
	{
		ControlsUpdateKeyboard(65, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F3) && !keyboardButtonPressed[66])
	{
		keyboardButtonPressed[66] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F3) && keyboardButtonPressed[66])
	{
		ControlsUpdateKeyboard(66, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F4) && !keyboardButtonPressed[67])
	{
		keyboardButtonPressed[67] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F4) && keyboardButtonPressed[67])
	{
		ControlsUpdateKeyboard(67, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F5) && !keyboardButtonPressed[68])
	{
		keyboardButtonPressed[68] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F5) && keyboardButtonPressed[68])
	{
		ControlsUpdateKeyboard(68, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F6) && !keyboardButtonPressed[69])
	{
		keyboardButtonPressed[69] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F6) && keyboardButtonPressed[69])
	{
		ControlsUpdateKeyboard(69, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F7) && !keyboardButtonPressed[70])
	{
		keyboardButtonPressed[70] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F7) && keyboardButtonPressed[70])
	{
		ControlsUpdateKeyboard(70, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F8) && !keyboardButtonPressed[71])
	{
		keyboardButtonPressed[71] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F8) && keyboardButtonPressed[71])
	{
		ControlsUpdateKeyboard(71, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F9) && !keyboardButtonPressed[72])
	{
		keyboardButtonPressed[72] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F9) && keyboardButtonPressed[72])
	{
		ControlsUpdateKeyboard(72, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F10) && !keyboardButtonPressed[73])
	{
		keyboardButtonPressed[73] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F10) && keyboardButtonPressed[73])
	{
		ControlsUpdateKeyboard(73, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F11) && !keyboardButtonPressed[74])
	{
		keyboardButtonPressed[74] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F11) && keyboardButtonPressed[74])
	{
		ControlsUpdateKeyboard(74, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F12) && !keyboardButtonPressed[75])
	{
		keyboardButtonPressed[75] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F12) && keyboardButtonPressed[75])
	{
		ControlsUpdateKeyboard(75, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_0) && !keyboardButtonPressed[76])
	{
		keyboardButtonPressed[76] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_0) && keyboardButtonPressed[76])
	{
		ControlsUpdateKeyboard(76, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_1) && !keyboardButtonPressed[77])
	{
		keyboardButtonPressed[77] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_1) && keyboardButtonPressed[77])
	{
		ControlsUpdateKeyboard(77, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_2) && !keyboardButtonPressed[78])
	{
		keyboardButtonPressed[78] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_2) && keyboardButtonPressed[78])
	{
		ControlsUpdateKeyboard(78, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_3) && !keyboardButtonPressed[79])
	{
		keyboardButtonPressed[79] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_3) && keyboardButtonPressed[79])
	{
		ControlsUpdateKeyboard(79, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_4) && !keyboardButtonPressed[80])
	{
		keyboardButtonPressed[80] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_4) && keyboardButtonPressed[80])
	{
		ControlsUpdateKeyboard(80, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_5) && !keyboardButtonPressed[81])
	{
		keyboardButtonPressed[81] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_5) && keyboardButtonPressed[81])
	{
		ControlsUpdateKeyboard(81, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_6) && !keyboardButtonPressed[82])
	{
		keyboardButtonPressed[82] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_6) && keyboardButtonPressed[82])
	{
		ControlsUpdateKeyboard(82, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_7) && !keyboardButtonPressed[83])
	{
		keyboardButtonPressed[83] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_7) && keyboardButtonPressed[83])
	{
		ControlsUpdateKeyboard(83, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_8) && !keyboardButtonPressed[84])
	{
		keyboardButtonPressed[84] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_8) && keyboardButtonPressed[84])
	{
		ControlsUpdateKeyboard(84, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_9) && !keyboardButtonPressed[85])
	{
		keyboardButtonPressed[85] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_9) && keyboardButtonPressed[85])
	{
		ControlsUpdateKeyboard(85, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_DECIMAL) && !keyboardButtonPressed[86])
	{
		keyboardButtonPressed[86] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_DECIMAL) && keyboardButtonPressed[86])
	{
		ControlsUpdateKeyboard(86, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_DIVIDE) && !keyboardButtonPressed[87])
	{
		keyboardButtonPressed[87] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_DIVIDE) && keyboardButtonPressed[87])
	{
		ControlsUpdateKeyboard(87, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_MULTIPLY) && !keyboardButtonPressed[88])
	{
		keyboardButtonPressed[88] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_MULTIPLY) && keyboardButtonPressed[88])
	{
		ControlsUpdateKeyboard(88, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_SUBTRACT) && !keyboardButtonPressed[89])
	{
		keyboardButtonPressed[89] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_SUBTRACT) && keyboardButtonPressed[89])
	{
		ControlsUpdateKeyboard(89, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_ADD) && !keyboardButtonPressed[90])
	{
		keyboardButtonPressed[90] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_ADD) && keyboardButtonPressed[90])
	{
		ControlsUpdateKeyboard(90, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_ENTER) && !keyboardButtonPressed[91])
	{
		keyboardButtonPressed[91] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_ENTER) && keyboardButtonPressed[91])
	{
		ControlsUpdateKeyboard(91, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_EQUAL) && !keyboardButtonPressed[92])
	{
		keyboardButtonPressed[92] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_EQUAL) && keyboardButtonPressed[92])
	{
		ControlsUpdateKeyboard(92, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) && !keyboardButtonPressed[93])
	{
		keyboardButtonPressed[93] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) && keyboardButtonPressed[93])
	{
		ControlsUpdateKeyboard(93, 247);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) && !keyboardButtonPressed[94])
	{
		keyboardButtonPressed[94] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) && keyboardButtonPressed[94])
	{
		ControlsUpdateKeyboard(94, 247);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT_ALT) && !keyboardButtonPressed[95])
	{
		keyboardButtonPressed[95] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT_ALT) && keyboardButtonPressed[95])
	{
		ControlsUpdateKeyboard(95, 247);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT) && !keyboardButtonPressed[96])
	{
		keyboardButtonPressed[96] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT) && keyboardButtonPressed[96])
	{
		ControlsUpdateKeyboard(96, 247);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) && !keyboardButtonPressed[97])
	{
		keyboardButtonPressed[97] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) && keyboardButtonPressed[97])
	{
		ControlsUpdateKeyboard(97, 247);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT_ALT) && !keyboardButtonPressed[98])
	{
		keyboardButtonPressed[98] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT_ALT) && keyboardButtonPressed[98])
	{
		ControlsUpdateKeyboard(98, 247);
	}

	if (glfwGetKey(win, GLFW_KEY_SPACE) && !keyboardButtonPressed[99])
	{
		keyboardButtonPressed[99] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_SPACE) && keyboardButtonPressed[99])
	{
		ControlsUpdateKeyboard(99, -67);
	}
}

void windowMgr::ControlsInputController()
{
	// Create a variable to check if the joy stick is present - 1 means true
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	// Dected how many buttons the controller has
	int buttonCount;
	const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	// If controller is connected 
	if (present == 1)
	{
		// If the amount of buttons detected is equal to 18 then - ps4 configurations
		if (buttonCount == 18)
		{
			// For loop which checks to see if buttons are pressed - i buttons
			for (int buttonNumber = 0; buttonNumber < 18; buttonNumber++)
			{
				// If button i is pressed then set corresponding boolean to true
				if (GLFW_PRESS == buttons[buttonNumber] && !buttonPressed[buttonNumber])
				{
					buttonPressed[buttonNumber] = true;
				}

				// If a button has just been pressed and is longer being pressed then
				if (buttonPressed[buttonNumber] && !GLFW_PRESS == buttons[buttonNumber])
				{
					// If there is an empty function then
					if (isFunctionEmpty)
					{
						// Find the index of the gameFunction which has a value of 99
						indexAt99 = std::distance(windowMgr::getInstance()->playerXboxControls[playerTab - 1], std::find(windowMgr::getInstance()->playerXboxControls[playerTab - 1], windowMgr::getInstance()->playerXboxControls[playerTab - 1] + 10, 99));
						// Find the index of the game function whih is assigned to the button that has just been pressed
						indexAtButton = std::distance(windowMgr::getInstance()->playerXboxControls[playerTab - 1], std::find(windowMgr::getInstance()->playerXboxControls[playerTab - 1], windowMgr::getInstance()->playerXboxControls[playerTab - 1] + 10, buttonNumber));
						// Check if button just pressed has a function assigned to it
						if (buttonNumber == windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAtButton])
						{
							// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
							windowMgr::getInstance()->controllerMeshes.at(4 + (indexAtButton * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAtButton] = 99;
						}

						// Make the original empty function equal to the button
						windowMgr::getInstance()->playerXboxControls[0][indexAt99] = buttonNumber;
						windowMgr::getInstance()->controllerMeshes.at(4 + (indexAt99 * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[buttonNumber]);

						// Check if a function is equal to 99
						if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][0] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][1] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][2] == 99 ||
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][3] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][4] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][5] == 99 ||
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][6] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][7] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][8] == 99 ||
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][9] == 99)
						{
							isFunctionEmpty = true; // Set bool to true if a function is empty
						}
						else
						{
							isFunctionEmpty = false; // Set bool to false if no function is empty
						}
					}
					else
					{
						// Find the function index where the button has been pressed
						indexAtButton = std::distance(windowMgr::getInstance()->playerXboxControls[playerTab - 1], std::find(windowMgr::getInstance()->playerXboxControls[playerTab - 1], windowMgr::getInstance()->playerXboxControls[playerTab - 1] + 10, buttonNumber));
						// If function is assigned to a button then
						if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAtButton] == buttonNumber)
						{
							// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
							windowMgr::getInstance()->controllerMeshes.at(4 + (indexAtButton * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAtButton] = 99;
							// Set is Function Empty to true
							isFunctionEmpty = true;
						}
					}
					// Reset button pressed
					buttonPressed[buttonNumber] = false;
				}
			}
		}
		else
		{
			// For loop which checks to see if buttons are pressed
			for (int buttonNumber = 0; buttonNumber < 14; buttonNumber++)
			{
				// If button is pressed then set corresponding boolean to true
				if (GLFW_PRESS == buttons[buttonNumber] && !buttonPressed[buttonNumber])
				{
					buttonPressed[buttonNumber] = true;
					//cout << "Button Pressed on Xbox: " << buttonNumber << endl;
				}

				// If a button has just been pressed and is longer being pressed then
				if (buttonPressed[buttonNumber] && !GLFW_PRESS == buttons[buttonNumber])
				{
					// If there is an empty function then
					if (isFunctionEmpty)
					{
						// Find the index of the gameFunction which has a value of 99
						indexAt99 = std::distance(windowMgr::getInstance()->playerXboxControls[playerTab - 1], std::find(windowMgr::getInstance()->playerXboxControls[playerTab - 1], windowMgr::getInstance()->playerXboxControls[playerTab - 1] + 10, 99));
						// Find the index of the game function whih is assigned to the button that has just been pressed
						indexAtButton = std::distance(windowMgr::getInstance()->playerXboxControls[playerTab - 1], std::find(windowMgr::getInstance()->playerXboxControls[playerTab - 1], windowMgr::getInstance()->playerXboxControls[playerTab - 1] + 10, buttonNumber));
						// Check if button just pressed has a function assigned to it
						if (buttonNumber == windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAtButton])
						{
							// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
							windowMgr::getInstance()->controllerMeshes.at(4 + (indexAtButton * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAtButton] = 99;
						}

						// Make the original empty function equal to the button
						windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAt99] = buttonNumber;
						windowMgr::getInstance()->controllerMeshes.at(4 + (indexAt99 * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[buttonNumber]);

						// Check if a function is equal to 99
						if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][0] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][1] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][2] == 99 ||
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][3] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][4] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][5] == 99 ||
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][6] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][7] == 99 || windowMgr::getInstance()->playerXboxControls[playerTab - 1][8] == 99 ||
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][9] == 99)
						{
							isFunctionEmpty = true; // Set bool to true if a function is empty
						}
						else
						{
							isFunctionEmpty = false; // Set bool to false if no function is empty
						}
					}
					else
					{
						indexAtButton = std::distance(windowMgr::getInstance()->playerXboxControls[playerTab - 1], std::find(windowMgr::getInstance()->playerXboxControls[playerTab - 1], windowMgr::getInstance()->playerXboxControls[playerTab - 1] + 10, buttonNumber));
						// If function is assigned to a button then
						if (windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAtButton] == buttonNumber)
						{
							// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
							windowMgr::getInstance()->controllerMeshes.at(4 + (indexAtButton * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
							windowMgr::getInstance()->playerXboxControls[playerTab - 1][indexAtButton] = 99;
							// Set is Function Empty to true
							isFunctionEmpty = true;
						}
						// Else then user wants to return to the pervious screen
						else
						{
							// Work out the previous screen - if return to game is true then set variable to true to continue with game
							if (returnToGame)
							{
								// Set does user want controls to false meaning in game scene .cpp the controls render loop will be ignored
								doesUserWantControls = false;
							}
							else
							{
								// Change back to main menu
								windowMgr::getInstance()->sceneManager.changeScene(1);
							}
						}
					}

					// Reset button pressed
					buttonPressed[buttonNumber] = false;
				}
			}
		}
	}
}

void windowMgr::ControlsUpdateKeyboard(int keyboardButtonNumber, int additionalNumber)
{
	if (isFunctionEmptyKeyboard) // Check if there is an empty keyboard function
	{
		// Find the index of the gameKeyboardFunctions which has a value of 999
		indexAt999Player1 = std::distance(windowMgr::getInstance()->playerKeyboardControls[0], std::find(windowMgr::getInstance()->playerKeyboardControls[0], windowMgr::getInstance()->playerKeyboardControls[0] + 10, 999));
		indexAt999Player2 = std::distance(windowMgr::getInstance()->playerKeyboardControls[1], std::find(windowMgr::getInstance()->playerKeyboardControls[1], windowMgr::getInstance()->playerKeyboardControls[1] + 10, 999));
		// Check if the button which has just been pressed has a function assigned to it and find the index
		indexOfButtonPressedPlayer1 = std::distance(windowMgr::getInstance()->playerKeyboardControls[0], std::find(windowMgr::getInstance()->playerKeyboardControls[0], windowMgr::getInstance()->playerKeyboardControls[0] + 10, keyboardButtonNumber + additionalNumber));
		indexOfButtonPressedPlayer2 = std::distance(windowMgr::getInstance()->playerKeyboardControls[1], std::find(windowMgr::getInstance()->playerKeyboardControls[1], windowMgr::getInstance()->playerKeyboardControls[1] + 10, keyboardButtonNumber + additionalNumber));
		
		// If player tab equals one then 
		if (playerTab == 1)
		{
			// If value is 10 for indexOfButtonPressed for both arrays then that means the button just pressed is not assigned to the function - set the button pressed to the empty function
			if (indexOfButtonPressedPlayer1 == 10 && indexOfButtonPressedPlayer2 == 10)
			{
				windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][indexAt999Player1] = keyboardButtonNumber + additionalNumber;
				windowMgr::getInstance()->controllerMeshes.at(27 + indexAt999Player1)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[keyboardButtonNumber]);
			}
		}
		// else if player tab equals two then
		else
		{
			// If value is 10 for indexOfButtonPressed for both arrays then that means the button just pressed is not assigned to the function - set the button pressed to the empty function
			if (indexOfButtonPressedPlayer2 == 10 && indexOfButtonPressedPlayer1 == 10)
			{
				windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][indexAt999Player2] = keyboardButtonNumber + additionalNumber;
				windowMgr::getInstance()->controllerMeshes.at(27 + indexAt999Player2)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[keyboardButtonNumber]);
			}
		}

		// Check if a function is equal to 99
		if (windowMgr::getInstance()->playerKeyboardControls[0][0] == 999 || windowMgr::getInstance()->playerKeyboardControls[0][1] == 999 || windowMgr::getInstance()->playerKeyboardControls[0][2] == 999 ||
			windowMgr::getInstance()->playerKeyboardControls[0][3] == 999 || windowMgr::getInstance()->playerKeyboardControls[0][4] == 999 || windowMgr::getInstance()->playerKeyboardControls[0][5] == 999 ||
			windowMgr::getInstance()->playerKeyboardControls[0][6] == 999 || windowMgr::getInstance()->playerKeyboardControls[0][7] == 999 || windowMgr::getInstance()->playerKeyboardControls[0][8] == 999 ||
			windowMgr::getInstance()->playerKeyboardControls[0][9] == 999 || windowMgr::getInstance()->playerKeyboardControls[1][0] == 999 || windowMgr::getInstance()->playerKeyboardControls[1][1] == 999 || windowMgr::getInstance()->playerKeyboardControls[1][2] == 999 ||
			windowMgr::getInstance()->playerKeyboardControls[1][3] == 999 || windowMgr::getInstance()->playerKeyboardControls[1][4] == 999 || windowMgr::getInstance()->playerKeyboardControls[1][5] == 999 ||
			windowMgr::getInstance()->playerKeyboardControls[1][6] == 999 || windowMgr::getInstance()->playerKeyboardControls[1][7] == 999 || windowMgr::getInstance()->playerKeyboardControls[1][8] == 999 ||
			windowMgr::getInstance()->playerKeyboardControls[1][9] == 999)
		{
			isFunctionEmptyKeyboard = true; // Set bool to true if a function is empty
			//cout << "A function is empty!" << endl;
		}
		else
		{
			isFunctionEmptyKeyboard = false; // Set bool to false if no function is empty
			//cout << "No functions are empty!" << endl;
		}
	}
	else
	{
		// Find the function index where the button has been pressed
		indexAtKey = std::distance(windowMgr::getInstance()->playerKeyboardControls[playerTab - 1], std::find(windowMgr::getInstance()->playerKeyboardControls[playerTab - 1], windowMgr::getInstance()->playerKeyboardControls[playerTab - 1] + 10, keyboardButtonNumber + additionalNumber));
		// If function is assigned to a button then
		if (windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][indexAtKey] == keyboardButtonNumber + additionalNumber)
		{
			// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
			windowMgr::getInstance()->controllerMeshes.at(27 + indexAtKey)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
			windowMgr::getInstance()->playerKeyboardControls[playerTab - 1][indexAtKey] = 999;
			// Set is Function Empty to true
			isFunctionEmptyKeyboard = true;
		}
	}

	keyboardButtonPressed[keyboardButtonNumber] = false;
}