
#include "optionsScene.h"
#include "windowMgr.h"

// Constructor
optionsScene::optionsScene() { }
// Deconstructor
optionsScene::~optionsScene() { }

void optionsScene::Track_Mouse(GLFWwindow *window)
{
	glfwGetCursorPos(window, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);
	cout << windowMgr::getInstance()->mouse_x << " " << windowMgr::getInstance()->mouse_y << endl;
	if ((windowMgr::getInstance()->mouse_x >= 604 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 995 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 59 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 456 * windowMgr::getInstance()->windowScale))
	{
		if (windowMgr::getInstance()->mouse_y <= 200 * windowMgr::getInstance()->windowScale)
		{
			//highlights 1280x720 button
			windowMgr::getInstance()->button_manager = 1;
		}
		else if (windowMgr::getInstance()->mouse_y <= 332 * windowMgr::getInstance()->windowScale)
		{
			//highlights 1600x900 button
			windowMgr::getInstance()->button_manager = 2;
		}
		else
		{
			//highlights highscore button
			windowMgr::getInstance()->button_manager = 3;
		}
	}
	else if ((windowMgr::getInstance()->mouse_x >= 1039 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 1429 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 711 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 839 * windowMgr::getInstance()->windowScale))
	{
		//highlights the back button
		windowMgr::getInstance()->button_manager = 4;
	}
}
void optionsScene::Action(GLFWwindow *win)
{
	//get monitor 
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	//get monitor size in pixels
	const GLFWvidmode *mode = glfwGetVideoMode(primary);
	//cases for changing size of screen
	switch (windowMgr::getInstance()->button_manager)
	{
			// Case 1 - windowed at 1600x900
		case 1:
			windowMgr::getInstance()->width = mode->width / 1.5;
			windowMgr::getInstance()->height = mode->height / 1.5;
			windowMgr::getInstance()->PosX = 100;
			windowMgr::getInstance()->PosY = 100;
			break;
	
			// Case 2 - fullscreen at 1280 x 720
		case 2:
			windowMgr::getInstance()->width = mode->width / 1.2;
			windowMgr::getInstance()->height = mode->height / 1.2;
			windowMgr::getInstance()->PosX = 100;
			windowMgr::getInstance()->PosY = 100;
			break;
			//case 3 fullscreen mouse is broken/viewport issues 
		case 3:
			//Sets window size by calling open gl function
			windowMgr::getInstance()->width = mode->width;
			windowMgr::getInstance()->height = mode->height;
			windowMgr::getInstance()->PosX = 0;
			windowMgr::getInstance()->PosY = 0;
			break;
			// Case 3 - Back button
		case 4:
			windowMgr::getInstance()->sceneManager.changeScene(1);
			break;
	}
	// If window has been re-scaled
	if (windowMgr::getInstance()->button_manager != 4)
	{
		glfwSetWindowSize(win, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
		//sets window postion by calling opengl function - posiotn needs updating as first funtion is just scale
		glfwSetWindowPos(win, windowMgr::getInstance()->PosX, windowMgr::getInstance()->PosY);
		//calls the initalise function again mainly for viewport 
		glViewport(0, 0, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
		windowMgr::getInstance()->setWindowScale(windowMgr::getInstance()->width);
	}
}

void optionsScene::Init(GLFWwindow * win)
{
	//to reformat texutures
	glViewport(0, 0, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
	//resets the button manager
	windowMgr::getInstance()->button_manager = 0;
	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");

	// Setup target camera
	tarCam = new target_camera();
	tarCam->set_Posistion(vec3(0, 0, 5.0f));
	tarCam->set_Target(vec3(0, 0, 0));
	tarCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);

	cout << "Textures before all: " << windowMgr::getInstance()->textures.size() << endl;
	// Doesn't matter which mesh we use so pick first in list - set its scale, pos and texture
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["optionsBackground"]);

	// Perform setup of initial button configs - (un)selected textures
	// Pick next item in meshes list (increment the number by 1 each time)
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f, 1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(2.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(0.0f, 0.3f, 0.0f));
	cout << "Textures after start: " << windowMgr::getInstance()->textures.size() << endl;
}
// Draw stuff
void optionsScene::Loop(GLFWwindow * win)
{
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(win);
	// Update
	Update(win);
	//Tracks Mouse
	Track_Mouse(win);
	// Render
	Render(win);
}

void optionsScene::Input(GLFWwindow* win)
{
	switch (windowMgr::getInstance()->button_manager)
	{
	case 0:
		windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
		break;
	case 1:
		windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnSelected"]);
		windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
		break;
	case 2:
		windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnSelected"]);
		windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
		break;
	case 3:
		windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnSelected"]);
		windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
		break;
	case 4:
		windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
		windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["backBtnSelected"]);
		break;
	}
	if (glfwGetKey(win, GLFW_KEY_ENTER))
	{
		windowMgr::getInstance()->enterPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_ENTER) && total_time >= 5.0f)
	{
		if (windowMgr::getInstance()->enterPressed)
		{
			Action(win);
			windowMgr::getInstance()->enterPressed = false;
		}
	}
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) && total_time >= 5.0f)
	{
		windowMgr::getInstance()->mouseLpressed = true;
	}
	if (!glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		if (windowMgr::getInstance()->mouseLpressed)
		{
			Action(win);
			windowMgr::getInstance()->mouseLpressed = false;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_UP))
	{
		windowMgr::getInstance()->upPressed = true;
	}

	if (!glfwGetKey(win, GLFW_KEY_UP))
	{
		if (windowMgr::getInstance()->upPressed)
		{
			total_time = 0.0f;
			if (windowMgr::getInstance()->button_manager == 1)
			{
				windowMgr::getInstance()->button_manager = 4;
			}
			else
			{
				windowMgr::getInstance()->button_manager--;
			}
			windowMgr::getInstance()->upPressed = false;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_DOWN))
	{
		windowMgr::getInstance()->downPressed = true;
	}

	if (!glfwGetKey(win, GLFW_KEY_DOWN))
	{
		if (windowMgr::getInstance()->downPressed)
		{
			if (windowMgr::getInstance()->button_manager == 4)
			{
				windowMgr::getInstance()->button_manager = 1;
			}
			else if (windowMgr::getInstance()->button_manager == 0)
			{
				windowMgr::getInstance()->button_manager = 4;
			}
			else
			{
				windowMgr::getInstance()->button_manager++;
			}

			windowMgr::getInstance()->downPressed = false;
		}
	}

	while (total_time <= 5.0f)
	{
		total_time += 1.0f;
	}
}

void optionsScene::Update(GLFWwindow* win)
{
	// Update target camera
	tarCam->update(0.00001);
}

void optionsScene::Render(GLFWwindow* win)
{
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = tarCam->get_Projection() * tarCam->get_View();
	glDepthRange(0, 0.01);

	for (int a = 0; a < 5; a++)
	{
		windowMgr::getInstance()->meshes.at(a)->thisTexture.Bind(0);
		textureShader->Update(optionSceneTransform, hudVP);
		windowMgr::getInstance()->meshes.at(a)->Draw();
	}


	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}
