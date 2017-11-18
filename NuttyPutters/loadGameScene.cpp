#include "loadGameScene.h"
#include "windowMgr.h"


// Constructor
loadGameScene::loadGameScene() { }
// Deconstructor
loadGameScene::~loadGameScene() { }

// Setup scene; display choice saved games
void loadGameScene::Init(GLFWwindow* win)
{
	// Set initial button press bools to false
	upPressed = downPressed = leftPressed = rightPressed = enterPressed = false;
	// Set initial values for navigation variables
	lastImageSelected = currentImageSelected = savesImagesIndex = enterCooldown =  0;
	// Set initial current page value
	currentPage = 1;

	// Set background mesh properties
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["loadGameBackground"]);

	// Set image viewer properties
	// Create image meshes
	int images = windowMgr::getInstance()->savesImages.size(); // Total number of saves images to show
	int imCount = 1;
	// Setup meshes
	for (int x = -1; x < 2; ++x)
	{
		for (int y = 1; y > -2; --y)
		{
			float xPos, yPos;
			xPos = (x*w);
			yPos = (y*h);
			windowMgr::getInstance()->meshes.at(imCount)->SetPos(vec3(xPos, yPos, 0));
			windowMgr::getInstance()->meshes.at(imCount)->SetScale(w, h);
			imCount++;
		}
	}
	
	// Set image meshes with saved image textures - up to limit of 9 per 'page'
	int limit;
	if (windowMgr::getInstance()->savesImages.size() > 9)
		limit = 9;
	else
		limit = windowMgr::getInstance()->savesImages.size();

	for (int i = 0; i < limit; i++)
	{
		windowMgr::getInstance()->meshes.at(diff + i)->SetTexture(windowMgr::getInstance()->savesImages.at(i));
	}
	
	// Show first image as selected
	windowMgr::getInstance()->meshes.at(diff)->SetScale(selectedW, selectedH);

	// Calculate total number images, and number of pages required
	totalImages = (float)windowMgr::getInstance()->savesImages.size();
	pageCount = ceil(totalImages / 9);


	// Read all saved seeds
	ifstream saves("saves.csv");

	// Read all saved games as strings
	while (!saves.eof())
	{
		string line;
		getline(saves, line);
		if(line != "") // if not whitespace cell read
			seeds.push_back(line); // store in seeds list
	}

}

// Main loop
void loadGameScene::Loop(GLFWwindow* win)
{
	// Input
	Input(win);
	//upadate
	Update(win);
	// Render
	Render(win);


}

// Redraws next/last page of images onto image viewer meshes
void loadGameScene::NextPage()
{
	// Set last image mesh selected
	lastImageSelected = currentImageSelected;
	// Reset currentImageSelected to start
	currentImageSelected = 0;
	// We're on next page
	currentPage++;
	// Set saves image index
	savesImagesIndex = (currentPage - 1) * 9;


	// Find limit for this page - difference between savesImagesIndex and total images
	int limit = totalImages - savesImagesIndex;
	// Imposed limit of 9 image meshes
	if (limit > 9)
		limit = 9;

	// Draw the next set of saves image textures
	for (int i = 0; i < limit; ++i)
	{
		// 1 + since background is taken, at 0
		windowMgr::getInstance()->meshes.at(diff + i)->SetTexture(windowMgr::getInstance()->savesImages.at(savesImagesIndex + i));
	}

	// Clear the rest from previous page
	for (int i = limit; i < 9; ++i)
	{
		windowMgr::getInstance()->meshes.at(diff + i)->SetTexture(windowMgr::getInstance()->textures["startBackground"]);
	}
}

// Load previous page of images
void loadGameScene::LastPage()
{
	// Set last image mesh selected
	lastImageSelected = currentImageSelected;
	// Reset current image mesh value to end
	currentImageSelected = 8;
	// Were on the previous page
	currentPage--;
	// Set the images index
	savesImagesIndex = ((currentPage - 1) * 9) + 8;


	// We know there is a full page of images to show, from curIndex - 8 to curIndex
	for (int i = savesImagesIndex - 8; i < savesImagesIndex + 1; ++i)
	{
		windowMgr::getInstance()->meshes.at(diff + i)->SetTexture(windowMgr::getInstance()->savesImages.at(i));
	}
}


// Resizes the current and last selected image mesh
void loadGameScene::ResizeCurLastSelected()
{
	// Resize this and last choice
	windowMgr::getInstance()->meshes.at(diff + currentImageSelected)->SetScale(selectedW, selectedH);
	windowMgr::getInstance()->meshes.at(diff + lastImageSelected)->SetScale(w, h);
}

// Act on input
void loadGameScene::Input(GLFWwindow* win)
{
	// B goes back to main menu screen
	if (glfwGetKey(win, GLFW_KEY_B))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}

	// TESTING SOUND
	if (glfwGetKey(win, GLFW_KEY_S))
	{
		windowMgr::getInstance()->PlayThisSound("menuSelect");
	}

	// IMAGE MESH NAVIGATION
	// Go back/up an image mesh
	if (glfwGetKey(win, GLFW_KEY_UP))
	{
		upPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_UP))
	{
		// Only if left was just released...
		if (upPressed)
		{	
			// Have we reached first image mesh? 
			if (currentImageSelected == 0)
			{
				// Is there a page before to show?
				if (currentPage > 1)
				{
					// Show last page
					LastPage();
					// Resize this and last choice
					ResizeCurLastSelected();
				}
			}
			// Reduce current seed count if not at min
			else if (currentImageSelected > 0)
			{
				lastImageSelected = currentImageSelected;
				currentImageSelected--;
				savesImagesIndex--;
				cout << "Current: " << currentImageSelected << " Last: " << lastImageSelected << endl;
				// Resize this and last choice
				ResizeCurLastSelected();
			}


			upPressed = false;
		}
	}

	// Go along/down an image mesh
	if (glfwGetKey(win, GLFW_KEY_DOWN))
	{
		downPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_DOWN))
	{
		if (downPressed)
		{
			// Have we reached last image mesh?
			if (currentImageSelected == 8)
			{
				// Is there another page to show? 
				if (currentPage < (int)pageCount)
				{
					// Show next page
					NextPage();
					// Resize this and last choice
					ResizeCurLastSelected();
				}
			}
			// Increment current seed count if not at last image mesh
			else if (currentImageSelected < 8)
			{
				lastImageSelected = currentImageSelected;
				currentImageSelected++;
				savesImagesIndex++;
				cout << "Current: " << currentImageSelected << " Last: " << lastImageSelected << endl;
				// Resize this and last choice
				ResizeCurLastSelected();
			}



			downPressed = false;
		}

	}
	
	// View next page
	if (glfwGetKey(win, GLFW_KEY_RIGHT))
	{
		rightPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT))
	{
		if (rightPressed)
		{
			if (currentPage < (int)pageCount)
			{
				// Show last page
				NextPage();
				// Resize this and last choice
				ResizeCurLastSelected();
			}

		}
		rightPressed = false;
	}
	// View last page
	if (glfwGetKey(win, GLFW_KEY_LEFT))
	{
		leftPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT))
	{
		if (leftPressed)
		{
			if (currentPage > 1)
			{
				// Show last page
				LastPage();
				// Resize this and last choice
				ResizeCurLastSelected();
			}

		}
		leftPressed = false;
	}
	// Select this level to load
	if (glfwGetKey(win, GLFW_KEY_ENTER) && enterCooldown > enterCooldownMax)
	{
		enterPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_ENTER))
	{
		if (enterPressed)
		{
			enterPressed = false; // Suspect this is unnecessary
			// Current seed is index of seeds list, send as optional param
			windowMgr::getInstance()->sceneManager.changeScene(6, 12, seeds.at(savesImagesIndex)); // 12 is mandatory course lenght (to be disregarded dw)		
		}
	}
	
}

// Update 
void loadGameScene::Update(GLFWwindow* win)
{
	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);
	
	// To ensure enter doesn't trigger just after loading this scene
	if (enterCooldown < enterCooldownMax + 5) // 5 is epsilon
	{
		enterCooldown++;
	}
}

// Draw stuff
void loadGameScene::Render(GLFWwindow* win)
{
	// Calculate hud view*projection
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();
	// Set depth range, for HUD style rendering effect
	glDepthRange(0, 0.01);
	// Render all meshes & their textures
	// iter limit is slightly magic - number of meshes this scene requires
	for (int i = 0; i < 10; i++)
	{
		windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
		windowMgr::getInstance()->meshes.at(i)->Draw();
	}

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	windowMgr::getInstance()->textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}
