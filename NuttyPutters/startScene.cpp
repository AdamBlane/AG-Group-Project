// Externals

// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton

/// Start scene contains all render and input data for this scene

// Default constructor
startScene::startScene() { }

// Deconstructor
startScene::~startScene() { }

// Setup; does nothing atm
void startScene::Init(GLFWwindow* win)
{
	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");

	// Setup target camera
	tarCam = new target_camera();
	tarCam->set_Posistion(vec3(0, 0, 5.0f));
	//tarCam->set_Target(vec3(0, 0, 0));
	tarCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);
	
	// Background image will never change so setup here
	// Assign mesh to this scene's pointer
	background = windowMgr::getInstance()->meshes.at(0); // Doesn't matter which mesh we use so pick first in list
	// Set it to the correct size we need for the bg
	background->SetScale(9.0f, 5.0f);
	// Make sure it's centered
	background->SetPos(vec3(0.0f, 0.0f, -1.0f));
	// Grab the texture we need
	backgroundTex = windowMgr::getInstance()->textures["startBackground"];
	// Finally, assign the found texture to its mesh
	background->SetTexture(backgroundTex);

	// Perform setup of initial button configs - (un)selected textures
	startGameButton = windowMgr::getInstance()->meshes.at(1); // Next available mesh in list
	startGameButton->SetScale(1.8f, 0.6f); // Standard button scale used
	startGameButton->SetPos(vec3(0.0f, 1.5f, 0.0f));
	startGameBtnSelected = windowMgr::getInstance()->textures["startGameBtnSelected"];
	startGameBtnUnselected = windowMgr::getInstance()->textures["startGameBtnUnselected"];
	startGameButton->SetTexture(startGameBtnSelected);

	loadGameButton = windowMgr::getInstance()->meshes.at(2);
	loadGameButton->SetScale(1.8f, 0.6f);
	loadGameButton->SetPos(vec3(0.0f, 0.9f, 0.0f));
	loadGameBtnSelected = windowMgr::getInstance()->textures["loadGameBtnSelected"];
	loadGameBtnUnselected = windowMgr::getInstance()->textures["loadGameBtnUnselected"];
	loadGameButton->SetTexture(loadGameBtnUnselected);

	highscoresButton = windowMgr::getInstance()->meshes.at(3);
	highscoresButton->SetScale(1.8f, 0.6f);
	highscoresButton->SetPos(vec3(0.0f, 0.3f, 0.0f));
	highscoresBtnSelected = windowMgr::getInstance()->textures["highscoresBtnSelected"];
	highscoresBtnUnselected = windowMgr::getInstance()->textures["highscoresBtnUnselected"];
	highscoresButton->SetTexture(highscoresBtnUnselected);

	optionsButton = windowMgr::getInstance()->meshes.at(4);
	optionsButton->SetScale(1.8f, 0.6f);
	optionsButton->SetPos(vec3(0.0f, -0.3f, 0.0f));
	optionsBtnSelected = windowMgr::getInstance()->textures["optionsBtnSelected"];
	optionsBtnUnselected = windowMgr::getInstance()->textures["optionsBtnUnselected"];
	optionsButton->SetTexture(optionsBtnUnselected);

	internetButton = windowMgr::getInstance()->meshes.at(5);
	internetButton->SetScale(1.8f, 0.6f);
	internetButton->SetPos(vec3(0.0f, -0.9f, 0.0f));
	internetBtnSelected = windowMgr::getInstance()->textures["internetBtnSelected"];
	internetBtnUnselected = windowMgr::getInstance()->textures["internetBtnUnselected"];
	internetButton->SetTexture(internetBtnUnselected);

	exitButton = windowMgr::getInstance()->meshes.at(6);
	exitButton->SetScale(1.8f, 0.6f);
	exitButton->SetPos(vec3(0.0f, -1.5f, 0.0f));
	exitBtnSelected = windowMgr::getInstance()->textures["exitBtnSelected"];
	exitBtnUnselected = windowMgr::getInstance()->textures["exitBtnUnselected"];
	exitButton->SetTexture(exitBtnUnselected);
}

void startScene::Loop(GLFWwindow* win)
{
	// Calculate dt
	lastFrame = thisFrame;
	thisFrame = glfwGetTime();
	dt = (float)(thisFrame - lastFrame);

	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(win);

	// Update
	Update(win);

	// Render
	Render(win);
}

// Act on input
void startScene::Input(GLFWwindow * win)
{
	switch (button_manager)
	{
		//cases for the buttons to switch to each screen
		case 1:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start(1).png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
		 //   internetButton  = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			// Only need these 3 for now when using keyboard to navigate - 
			// When using mouse would need to use more
			
			startGameButton->SetTexture(startGameBtnSelected);
			loadGameButton->SetTexture(loadGameBtnUnselected);
			exitButton->SetTexture(exitBtnUnselected);
			break;

		case 2:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load(1).png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			
			startGameButton->SetTexture(startGameBtnUnselected);
			loadGameButton->SetTexture(loadGameBtnSelected);
			highscoresButton->SetTexture(highscoresBtnUnselected);
			break;

		case 3:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore(1).png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			
			loadGameButton->SetTexture(loadGameBtnUnselected);
			highscoresButton->SetTexture(highscoresBtnSelected);
			optionsButton->SetTexture(optionsBtnUnselected);
			
			break;

		case 4:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options(1).png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			
			highscoresButton->SetTexture(highscoresBtnUnselected);
			optionsButton->SetTexture(optionsBtnSelected);
			internetButton->SetTexture(internetBtnUnselected);
			
			break;

		case 5:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet(1).png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			
			optionsButton->SetTexture(optionsBtnUnselected);
			internetButton->SetTexture(internetBtnSelected);
			exitButton->SetTexture(exitBtnUnselected);
			
			break;

		case 6:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit(1).png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
		
			startGameButton->SetTexture(startGameBtnUnselected);
			internetButton->SetTexture(internetBtnUnselected);
			exitButton->SetTexture(exitBtnSelected);
			
			
			break;

	}
	if (glfwGetKey(win, GLFW_KEY_ENTER) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		if (button_manager == 6)
		{
			windowMgr::getInstance()->sceneManager.changeScene(0);

		}
		else if (button_manager == 5)
		{
			ShellExecute(NULL, "open", "http://www.calumtempleton.com", NULL, NULL, SW_SHOWNORMAL);
		}
		else
		{
			windowMgr::getInstance()->sceneManager.changeScene(button_manager + 1);
		}

	}


	if (glfwGetKey(win, GLFW_KEY_UP) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		if (button_manager == 1)
		{
			button_manager = 6;
		}
		else
		{
			button_manager--;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_DOWN) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		if (button_manager == 6)
		{
			button_manager = 1;
		}
		else
		{
			button_manager++;
		}
	}
	total_time += 1.0f;
}

void startScene::Update(GLFWwindow* win)
{
	// Update target camera
	tarCam->update(0.00001);
}

void startScene::Render(GLFWwindow* win)
{
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = tarCam->get_Projection() * tarCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	// Bind, update and draw HUD elements
	background->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	background->Draw();

	startGameButton->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	startGameButton->Draw();

	loadGameButton->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	loadGameButton->Draw();

	highscoresButton->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	highscoresButton->Draw();

	optionsButton->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	optionsButton->Draw();

	internetButton->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	internetButton->Draw();

	exitButton->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	exitButton->Draw();

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);
	// HUD RENDERING ENDED - THANK YOU AND HAVE A NICE DAY

	// Render any background stuff if required here

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}