#include "playerSelectScene.h"
#include "windowMgr.h"

// Constructor
playerSelectScene::playerSelectScene() { }
// Deconstructor
playerSelectScene::~playerSelectScene() { }

// Setup scene; does nothing atm
void playerSelectScene::Init(GLFWwindow * win)
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
	startGameLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\two.png", vec3(0.0, 0.0, 0.0), 1.0f, 1.0f);
}

// Draw stuff for this scene
void playerSelectScene::Loop(GLFWwindow * win)
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

// Act on user input 
void playerSelectScene::Input(GLFWwindow* win)
{
	// Move back to start scene
	if (glfwGetKey(win, GLFW_KEY_B))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1); // This calls init for scene
	}
	// Move to game scene with 1 player
	if (glfwGetKey(win, GLFW_KEY_1))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(6, courseLength); // This calls init for scene
	}
	
	// TOOD - Have something affect course length here

}

void playerSelectScene::Update(GLFWwindow* win)
{
	// Update target camera
	tarCam->update(0.00001);
}

void playerSelectScene::Render(GLFWwindow* win)
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