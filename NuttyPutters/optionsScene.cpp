
#include "optionsScene.h"
#include "windowMgr.h"

// Constructor
optionsScene::optionsScene() { }
// Deconstructor
optionsScene::~optionsScene() { }

void optionsScene::Init(GLFWwindow * win)
{
	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");

	// Setup target camera
	tarCam = new target_camera();
	tarCam->set_Posistion(vec3(0, 0, 5.0f));
	tarCam->set_Target(vec3(0, 0, 0));
	tarCam->set_projection(quarter_pi<float>(), (float)1600 / (float)900, 0.414f, 1000.0f);

	// Load HUD information - NOTE TO KEEP ASPECT RATIO, 2.0f = 250 pixels - calulate based on image size
	// Stroke HUD Label setup - Object, Texture, position, X scale, Y scale
	background = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\highscore\\optbackground.png", vec3(0.0, 0.0, -1.0), 9.5f, 5.5f);
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

	// Render
	Render(win);
}


void optionsScene::Input(GLFWwindow* win)
{
	switch (button_manager)
	{
	case 1:
		backButton = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\highscore\\back(1).png", vec3(2.0, -1.5, 0.0), 1.8f, 0.6f);
		break;
	}
	if (glfwGetKey(win, GLFW_KEY_ENTER) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		if (button_manager == 1)
		{
			windowMgr::getInstance()->sceneManager.changeScene(1);
		}
	}
	if (glfwGetKey(win, GLFW_KEY_UP) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		if (button_manager == 1)
		{
			button_manager = 1;
		}
		else
		{
			button_manager--;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_DOWN) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		if (button_manager == 1)
		{
			button_manager = 1;
		}
		else
		{
			button_manager++;
		}
	}
	total_time += 0.5f;
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
	background->thisTexture->Bind(0);
	textureShader->Update(backgroundTrans, hudVP);
	background->Draw();

	backButton->thisTexture->Bind(0);
	textureShader->Update(backButtonTrans, hudVP);
	backButton->Draw();

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}
