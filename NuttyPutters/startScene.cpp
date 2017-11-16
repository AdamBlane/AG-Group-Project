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
	


	cout << "Textures before all: " << windowMgr::getInstance()->textures.size() << endl;
	// Background image will never change so setup here
	// Doesn't matter which mesh we use so pick first in list - set its scale, pos and texture
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["startBackground"]);


	// Perform setup of initial button configs - (un)selected textures
	// Pick next item in meshes list (increment the number by 1 each time)
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f, 1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnSelected"]);

	windowMgr::getInstance()->meshes.at(2)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);

	cout << "Textures after start: " << windowMgr::getInstance()->textures.size() << endl;
	
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
			
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnSelected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			break;

		case 2:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load(1).png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnSelected"]);
			break;

		case 3:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore(1).png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			

			
			break;

		case 4:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options(1).png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
			

			
			break;

		case 5:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet(1).png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit.png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);

			
			break;

		case 6:
			//startGameButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\start.png", vec3(0.0, 1.5, 0.0), 1.8f, 0.6f);
			//loadButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\load.png", vec3(0.0, 0.9, 0.0), 1.8f, 0.6f);
			//highButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\HighScore.png", vec3(0.0, 0.3, 0.0), 1.8f, 0.6f);
			//optButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\options.png", vec3(0.0, -0.3, 0.0), 1.8f, 0.6f);
			//internetButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\Internet.png", vec3(0.0, -0.9, 0.0), 1.8f, 0.6f);
			//exitButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\Mainmenu\\exit(1).png", vec3(0.0, -1.5, 0.0), 1.8f, 0.6f);
		

			
			
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
	if (glfwGetKey(win, GLFW_KEY_DOWN))
	{
		downPressed = true;
	}

	if (!glfwGetKey(win, GLFW_KEY_DOWN))
	{
		if (downPressed)
		{
			if (button_manager == 6)
			{
				button_manager = 1;
			}
			else
			{
				button_manager++;
			}

			downPressed = false;
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


	windowMgr::getInstance()->meshes.at(0)->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	windowMgr::getInstance()->meshes.at(0)->Draw();

	windowMgr::getInstance()->meshes.at(1)->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	windowMgr::getInstance()->meshes.at(1)->Draw();

	windowMgr::getInstance()->meshes.at(2)->thisTexture.Bind(0);
	textureShader->Update(startSceneTransform, hudVP);
	windowMgr::getInstance()->meshes.at(2)->Draw();

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