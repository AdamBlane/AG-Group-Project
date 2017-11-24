

#include "highscoreScene.h"
#include "windowMgr.h" // to access singleton

// Constructor
highscoreScene::highscoreScene() { }
// Deconstructor
highscoreScene::~highscoreScene() { }

void highscoreScene::Track_Mouse(GLFWwindow *window)
{
	glfwGetCursorPos(window, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);

	if ((windowMgr::getInstance()->mouse_x >= 1039 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 1429 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 711 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 839 * windowMgr::getInstance()->windowScale))
	{
		//highlights the back button
		windowMgr::getInstance()->button_manager = 1;
	}
	else
	{
		//highlights nothing
		windowMgr::getInstance()->button_manager = 0;
	}
}

void highscoreScene::Init(GLFWwindow * win)
{
	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");

	// Setup target camera
	tarCam = new target_camera();
	tarCam->set_Posistion(vec3(0, 0, 5.0f));
	tarCam->set_Target(vec3(0, 0, 0));
	tarCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);

	windowMgr::getInstance()->button_manager = 0;

	cout << "Textures before all: " << windowMgr::getInstance()->textures.size() << endl;
	// Background image will never change so setup here
	// Doesn't matter which mesh we use so pick first in list - set its scale, pos and texture
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["loadGameBackground"]);

	windowMgr::getInstance()->meshes.at(1)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(2.0f, -1.5f, 0.0f));

}


// Draw stuff
void highscoreScene::Loop(GLFWwindow * win)
{
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(win);

	// Update
	Update(win);
	//track mouse 
	Track_Mouse(win);
	// Render
	Render(win);
}
void highscoreScene::Action(GLFWwindow* win)
{
	if (windowMgr::getInstance()->button_manager == 1)
	{
		windowMgr::getInstance()->sceneManager.changeScene(1);

	}
}

void highscoreScene::Input(GLFWwindow* win)
{
	switch (windowMgr::getInstance()->button_manager)
	{
		case 0:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
			break;
		case 1:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["backBtnSelected"]);
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
				windowMgr::getInstance()->button_manager = 1;
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
			if (windowMgr::getInstance()->button_manager == 1)
			{
				windowMgr::getInstance()->button_manager = 1;
			}
			else if (windowMgr::getInstance()->button_manager == 0)
			{
				windowMgr::getInstance()->button_manager = 1;
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

void highscoreScene::Update(GLFWwindow* win)
{
	// Update target camera
	tarCam->update(0.00001);
}

void highscoreScene::Render(GLFWwindow* win)
{
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = tarCam->get_Projection() * tarCam->get_View();

	
	glDepthRange(0, 0.01);

	for (int a = 0; a < 2; a++)
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


