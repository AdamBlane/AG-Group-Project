// Externals

// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton

/// Start scene contains all render and input data for this scene

// Default constructor
startScene::startScene() { }
// Deconstructor
startScene::~startScene() { }

// Function which gets mouse clicks
void getMouseClick(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		// If clicked on exit button
		if (windowMgr::getInstance()->button_manager == 6)
		{
			// Then exit the app
			windowMgr::getInstance()->sceneManager.changeScene(0);
		}
		// If clicked on internet button
		else if (windowMgr::getInstance()->button_manager == 5)
		{
			// Launch IE 
			ShellExecute(NULL, "open", "http://www.calumtempleton.com", NULL, NULL, SW_SHOWNORMAL);
		}
		// If clicked on any other button, init that scene 
		else if (windowMgr::getInstance()->button_manager != 0)
		{
			// Init the scene based on button manager value (+ 1 since 0 is nothing selected)
			windowMgr::getInstance()->sceneManager.changeScene(windowMgr::getInstance()->button_manager + 1);
		}
	}
}

// Setup; does nothing atm
void startScene::Init(GLFWwindow* win)
{
	// Assign what happens when user clicks
	glfwSetMouseButtonCallback(win, getMouseClick);
	// Reset button manager var for this scene
	windowMgr::getInstance()->button_manager = 0;


	
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
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.0f, 1.0f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f, 1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(0.0f, 0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(0.0f, -0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(0.0f, -0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(0.0f, -1.5f, 0.0f));



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
	// Put all texture reassignments in the input code when that button is pressed
	// Just need to track last 
	switch (windowMgr::getInstance()->button_manager)
	{
			//cases for the buttons to switch to each screen
		case 0:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnSelected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;
		//cases for the buttons to switch to each screen
		case 1:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnSelected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 2:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnSelected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 3:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnSelected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 4:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnSelected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 5:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnSelected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 6:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnSelected"]);	
			break;

	}
	// Keep timer here
	if (glfwGetKey(win, GLFW_KEY_ENTER) && total_time > 4.8f)
	{
		total_time = 0.0f;
		// If selected exit button
		if (windowMgr::getInstance()->button_manager == 6)
		{
			// Then exit the app
			windowMgr::getInstance()->sceneManager.changeScene(0);
		}
		// If selected internet button
		else if (windowMgr::getInstance()->button_manager == 5)
		{
			// Launch IE 
			ShellExecute(NULL, "open", "http://www.calumtempleton.com", NULL, NULL, SW_SHOWNORMAL);
		}
		// If selected any other button, init that scene 
		else if (windowMgr::getInstance()->button_manager != 0)
		{
			// Init the scene based on button manager value (+ 1 since 0 is nothing selected)
			windowMgr::getInstance()->sceneManager.changeScene(windowMgr::getInstance()->button_manager + 1);
		}
	}

	// Need to do this in (!glfw...UP) if (upPressed) { code below }
	// Here just put upPressed = true;
	if (glfwGetKey(win, GLFW_KEY_UP) && total_time >= 3.0f)
	{
		total_time = 0.0f;
		if (windowMgr::getInstance()->button_manager == 1)
		{
			windowMgr::getInstance()->button_manager = 6;
		}
		else
		{
			windowMgr::getInstance()->button_manager--;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_M)) 
	{
		windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f + nasty, 1.5f, 0.0f));
		nasty += 0.1f;
	}
	if (glfwGetKey(win, GLFW_KEY_N))
	{
		windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f + nasty, 1.5f, 0.0f));
		nasty -= 0.1f;
	}
	if (glfwGetKey(win, GLFW_KEY_O))
	{
		cout << windowMgr::getInstance()->meshes.at(1)->GetGeomPos().x << endl;
	}

	// Remove timer on up/down nav
	if (glfwGetKey(win, GLFW_KEY_DOWN))
	{
		downPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_DOWN) && total_time >= 3.0f)
	{
		if (downPressed)
		{
			if (windowMgr::getInstance()->button_manager == 6)
			{
				windowMgr::getInstance()->button_manager = 1;
			}
			else
			{
				windowMgr::getInstance()->button_manager++;
			}

			downPressed = false;
		}
	}

	
	if (total_time < 5.0f)
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

	for (int a = 0; a < 7; a++)
	{
		windowMgr::getInstance()->meshes.at(a)->thisTexture.Bind(0);
		textureShader->Update(startSceneTransform, hudVP);
		windowMgr::getInstance()->meshes.at(a)->Draw();
	}
	


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