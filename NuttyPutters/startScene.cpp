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
	// Load HUD information - NOTE TO KEEP ASPECT RATIO, 2.0f = 250 pixels - calulate based on image size
	// Stroke HUD Label setup - Object, Texture, position, X scale, Y scale
	startGameLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\background.png", vec3(0.0, 0.0, -1.0), 9.5f, 5.5f);
	
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
			startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start(1).png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
		    internetButton  = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			break;

		case 2:
			startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load(1).png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			break;

		case 3:
			startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore(1).png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			break;

		case 4:
			startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options(1).png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			break;

		case 5:
			startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet(1).png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			break;

		case 6:
			startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit(1).png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
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

	// Bind, update and draw the stroke label HUD
	startGameLabelMesh->thisTexture->Bind(0);
	textureShader->Update(startGameLabelTrans, hudVP);
	startGameLabelMesh->Draw();

	startGameButton->thisTexture->Bind(0);
	textureShader->Update(startGameButtonTrans, hudVP);
	startGameButton->Draw();

	exitButton->thisTexture->Bind(0);
	textureShader->Update(exitButtonTrans, hudVP);
	exitButton->Draw();

	highButton->thisTexture->Bind(0);
	textureShader->Update(highButtonTrans, hudVP);
	highButton->Draw();

	internetButton->thisTexture->Bind(0);
	textureShader->Update(internetButtonTrans, hudVP);
	internetButton->Draw();

	optButton->thisTexture->Bind(0);
	textureShader->Update(optButtonTrans, hudVP);
	optButton->Draw();
	
	loadButton->thisTexture->Bind(0);
	textureShader->Update(loadButtonTrans, hudVP);
	loadButton->Draw();

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