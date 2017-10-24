// Externals
#include <time.h>
#include <iostream>
#include <sstream>
// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton

using namespace AllCamera;


// Default constructor
gameScene::gameScene() { }
// Deconstructor
gameScene::~gameScene() { }


// This is called by window manager
// Checks how many players, calls appropriate screenContent method
void gameScene::checkPlayers(GLFWwindow* win)
{
	switch (playerCount)
	{
	case 1:
		screenContent1P(win);
		break;
	case 2:
		screenContent2P(win);
		break;
	default:break;
	}
}



// Draw stuff for 1 player
void gameScene::screenContent1P(GLFWwindow * win)
{
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// The getRot of golf ball - will this be troublesome? Don't want the camera
	// to rotate along with the ball! 
	chaseCam->move(golfBallTransform.getPos(), golfBallTransform.getRot());
	chaseCam->update(0.00001);

	// Handles all input with camera and player
	Input(win);
	
	// Calculate mvp matrix
	mat4 mvp;
	// If camera type is free camera then
	if (cameraType == 0)
	{
		mvp = freeCam->get_Projection() * freeCam->get_View();
	}
	// Else camera type is chase camera
	else
	{
		mvp = chaseCam->get_Projection() * chaseCam->get_View();
	}

	// Bind texture shader
	textureShader->Bind();
	
	// DRAW all tiles
	for (auto &t : tiles)
	{
		t.drawTile(textureShader, mvp);
	}

	// Draw golf ball
	golfBallTexture->Bind(0);
	textureShader->Update(golfBallTransform, mvp);
	golfBallMesh->Draw();

	// Arrow
	arrowTexture->Bind(0);
	textureShader->Update(arrowTransform, mvp);
	// Rotate the arrow on the Y axis by - camera angle minus 90 degrees
	arrowTransform.setRot(glm::vec3(0, -chaseCamAngle - 1.5708, 0));
	// If ball is not moving draw arrow (ie dont draw arrow when ball moving as not needed)
	if (!golfBallMoving)
	{
		// Draw the arrow
		arrowMesh->Draw();
	}


	// WHAT is shaderTrans - it's never set to anything
	textureShader->Update(shaderTrans, (freeCam->get_Projection() * freeCam->get_View()));
	
	glfwSwapBuffers(win);
	glfwPollEvents();
}

// Draw stuff for 2 players
void gameScene::screenContent2P(GLFWwindow * win)
{
	float ratio;
	int width, height;

	// Get size of window in case resized
	glfwGetFramebufferSize(win, &width, &height);
	ratio = width / (float)height;
	// Make viewport match window size
	glViewport(0, 0, width / 2, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(win);
	glfwPollEvents();

	// P2
	// Get size of window in case resized
	glfwGetFramebufferSize(win, &width, &height);
	ratio = width / (float)height;
	// Make viewport match window size
	glViewport(width / 2, 0, width / 2, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 1.f, 1.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(win);
	glfwPollEvents();
}

void gameScene::setupTilesToBeDrawn()
{
	// TILE CREATION
	for (auto &t : algTiles)
	{
		// Ramp testing
		// Ramp up when dir is down
		if (t.id == 7)
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Rotate on x
			tile.transform.getRot().x = -0.349066;		 
			tile.transform.getPos().y += 1.8;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		// Ramp down when dir is up
		if (t.id == 8)
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Rotate on x
			tile.transform.getRot().x = -0.349066;
			tile.transform.getPos().y -= 1.8;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		if (t.id == 0) // Start
		{
			// Create start tile
			Tile tile(Tile::START, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Start tile needs rotating 180 (should always face down)
			tile.transform.getRot().y = 3.14159;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 1) // Straight V
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 2) // Straight H
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Straight needs rotating by 90, since it's vertical by default
			tile.transform.getRot().y = 1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 3) // Corner BL
		{
			// Create corner tile
			Tile tile(Tile::CORNER, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Corner needs rotating by 90
			tile.transform.getRot().y = 1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 4) // Corner BR
		{
			// Create corner tile
			Tile tile(Tile::CORNER, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Corner needs rotating by 90
			tile.transform.getRot().y = 3.14159;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 5) // Corner TL
		{
			// Create corner tile
			Tile tile(Tile::CORNER, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 6) // Corner TR
		{
			// Create corner tile
			Tile tile(Tile::CORNER, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Corner needs rotating by 90
			tile.transform.getRot().y = -1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 9) // end
		{
			// Create start tile
			Tile tile(Tile::START, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
			// Consult direction to determine how much to rotate
			if (t.outDir.going_up)
			{
				tile.transform.getRot().y = 3.14159;
			}
			else if (t.outDir.going_down)
			{
				// No rotation needed
			}
			else if (t.outDir.going_left)
			{
				tile.transform.getRot().y = -1.5708;
			}
			else if (t.outDir.going_right)
			{
				tile.transform.getRot().y = 1.5708;
			}
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
	}

}

void gameScene::Input(GLFWwindow* win)
{
	// Free cam stuff
	static double ratio_width = quarter_pi<float>() / 1600.0;
	static double ratio_height = (quarter_pi<float>() * (1600 / 900)) / static_cast<float>(1600);
	double current_x, current_y;
	glfwGetCursorPos(win, &current_x, &current_y);
	// Calc delta
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios
	delta_x *= ratio_width;
	delta_y *= ratio_height * -1; // -1 to invert on y axis
	// Rotate camera by delta
	freeCam->rotate(delta_x, delta_y);
	freeCam->update(0.001);
	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;

	// If button one is pressed change to free camera
	if (glfwGetKey(win, GLFW_KEY_1))
	{
		// Set camera version to free camera
		cout << "Free Camera selected" << endl;
		cameraType = 0;
		// Set the free cam position to where the chasecam stopped moving for debugging can me changed later
		freeCam->set_Posistion(chaseCam->get_Posistion());
	}

	// If button two is pressed change to chase camera
	if (glfwGetKey(win, GLFW_KEY_2))
	{
		// Set camera version to chase camera
		cout << "Chase Camera selected" << endl;
		cameraType = 1;
	}

	// Free cam controls
	if (cameraType == 0)
	{
		// Create vector to apply to current cam pos
		vec3 freeCamPos = vec3(0, 0, 0);

		// Camera controls
		if (glfwGetKey(win, GLFW_KEY_W))
		{
			freeCamPos = (vec3(0, 0, camSpeed));
		}
		if (glfwGetKey(win, GLFW_KEY_A))
		{
			freeCamPos = (vec3(-camSpeed, 0, 0));
		}
		if (glfwGetKey(win, GLFW_KEY_S))
		{
			freeCamPos = (vec3(0, 0, -camSpeed));
		}
		if (glfwGetKey(win, GLFW_KEY_D))
		{
			freeCamPos = (vec3(camSpeed, 0, 0));
		}
		if (glfwGetKey(win, GLFW_KEY_Q))
		{
			freeCamPos = (vec3(0, camSpeed, 0));
		}
		if (glfwGetKey(win, GLFW_KEY_E))
		{
			freeCamPos = (vec3(0, -camSpeed, 0));
		}

		// Move camera by new pos after input
		freeCam->move(freeCamPos);
	}
	// Chase cam controls
	else if (cameraType == 1)
	{
		// If ball is not moving then allow for angle on chase camera to be changed
		if (!golfBallMoving)
		{
			// controls in the chase camera 
			if (glfwGetKey(win, GLFW_KEY_D))
			{
				//function to rotate 
				chaseCam->yaw_it(camSpeed / 5);
				// Decrease chase camera angle (out of 360 degrees)
				chaseCamAngle -= (camSpeed / 5);
			}
			if (glfwGetKey(win, GLFW_KEY_A))
			{
				chaseCam->neg_yaw_it(camSpeed / 5);
				// Increase chase camera angle (out of 360 degrees)
				chaseCamAngle += (camSpeed / 5);
			}
		}
		if (glfwGetKey(win, GLFW_KEY_S))
		{
			chaseCam->neg_pitch_it(camSpeed / 5, golfBallTransform.getPos(), chaseCam->get_Posistion(), chaseCam->get_pos_offset().y);
		}
		if (glfwGetKey(win, GLFW_KEY_W))
		{
			chaseCam->pitch_it(camSpeed / 5, golfBallTransform.getPos(), chaseCam->get_Posistion(), chaseCam->get_pos_offset().y);
		}
		if (glfwGetKey(win, GLFW_KEY_Q))
		{
			//function to rotate 
			chaseCam->zoom_out(camSpeed / 5);
		}
		if (glfwGetKey(win, GLFW_KEY_E))
		{
			chaseCam->zoom_in(camSpeed / 5);
		}
	}

	// If chase camera angle is greater than 360 reset to 0
	if (chaseCamAngle > 6.28319)
	{
		chaseCamAngle = 0.0;
	}
	// If chase camera angle is less than 0 then reset to 360
	else if (chaseCamAngle < 0)
	{
		chaseCamAngle = 6.28319;
	}
	// Print the camera angle
	cout << "Camera angle: " << chaseCamAngle << endl;

	// Player
	// If P is pressed 
	if (glfwGetKey(win, GLFW_KEY_P))
	{
		// Add value to the force
		golfBallForce += 0.01;
		// Create a ball movement time
		timer = golfBallForce * 10;
		// Get the original force timer value which is used to slow down the ball
		originalForceTimer = golfBallForce * timer;
	}

	// When P is realesed
	if ((glfwGetKey(win, GLFW_KEY_P)) == false)
	{
		// If the ball is still moving forward
		if ((golfBallForce * timer) > 0)
		{
			// Set golf ball moving to true
			golfBallMoving = true;

			// If the golf ball force (static value) multiplied by the timer (decreasing value) is lower than the original force timer dived by 32 then
			if ((golfBallForce * timer) < ((originalForceTimer) / 32))
			{
				//cout << "Last 32rd" << endl;
				// Set the timer decreasing to a lower value
				timer -= 0.005;
			}

			else if ((golfBallForce * timer) < ((originalForceTimer) / 16))
			{
				//cout << "Last 16th" << endl;
				timer -= 0.01;
			}
			else if ((golfBallForce * timer) < ((originalForceTimer) / 8))
			{
				//cout << "Last 8th" << endl;
				timer -= 0.02;
			}
			else if ((golfBallForce * timer) < ((originalForceTimer) / 4))
			{
				//cout << "Last 4th" << endl;
				timer -= 0.03;
			}
			else if ((golfBallForce * timer) < ((originalForceTimer) / 2))
			{
				//cout << "Last Half" << endl;
				timer -= 0.04;
			}
			else
			{
				timer -= 0.05;
				//cout << "Normal" << endl;
			}

			// If camera angle is between 0 and 90
			if (chaseCamAngle > 0 && chaseCamAngle < 1.5708)
			{
				// Update the golf ball position and the arrow position
				// x = -sin(theta), z = cos(theta)
				golfBallTransform.getPos() += vec3(-sin(chaseCamAngle) * golfBallForce * timer, 0.0, cos(chaseCamAngle) * golfBallForce * timer);
				arrowTransform.getPos() += vec3(-sin(chaseCamAngle) * golfBallForce * timer, 0.0, cos(chaseCamAngle) * golfBallForce * timer);
				golfBallTransform.getRot() += vec3(-sin(chaseCamAngle) * golfBallForce * timer, 0.0, cos(chaseCamAngle) * golfBallForce * timer);
			}
			// If camera angle is between 90 and 180
			else if (chaseCamAngle > 1.5709 && chaseCamAngle < 3.14159)
			{
				// x = -cos(theta - 90), z = -sin(theta - 90)
				golfBallTransform.getPos() += vec3(-cos(chaseCamAngle - 1.5708) * golfBallForce * timer, 0.0, -sin(chaseCamAngle - 1.5708) * golfBallForce * timer);
				arrowTransform.getPos() += vec3(-cos(chaseCamAngle - 1.5708) * golfBallForce * timer, 0.0, -sin(chaseCamAngle - 1.5708) * golfBallForce * timer);
				golfBallTransform.getRot() += vec3(-cos(chaseCamAngle - 1.5708) * golfBallForce * timer, 0.0, -sin(chaseCamAngle - 1.5708) * golfBallForce * timer);
			}
			// If camera angle is between 180 and 270
			else if (chaseCamAngle > 3.1416 && chaseCamAngle < 4.71239)
			{
				// x = sin(theta - 180), z = -cos(theta - 180)
				golfBallTransform.getPos() += vec3(sin(chaseCamAngle - 3.1416) * golfBallForce * timer, 0.0, -cos(chaseCamAngle - 3.1416) * golfBallForce * timer);
				arrowTransform.getPos() += vec3(sin(chaseCamAngle - 3.1416) * golfBallForce * timer, 0.0, -cos(chaseCamAngle - 3.1416) * golfBallForce * timer);
				golfBallTransform.getRot() += vec3(sin(chaseCamAngle - 3.1416) * golfBallForce * timer, 0.0, -cos(chaseCamAngle - 3.1416) * golfBallForce * timer);
			}
			// If camera angle is anything else
			else if (chaseCamAngle > 4.724 && chaseCamAngle < 6.28319)
			{
				// x = cos(theta - 270), z = sin(theta- 270)
				golfBallTransform.getPos() += vec3(cos(chaseCamAngle - 4.71239) * golfBallForce * timer, 0.0, sin(chaseCamAngle - 4.71239) * golfBallForce * timer);
				arrowTransform.getPos() += vec3(cos(chaseCamAngle - 4.71239) * golfBallForce * timer, 0.0, sin(chaseCamAngle - 4.71239) * golfBallForce * timer);
				golfBallTransform.getRot() += vec3(cos(chaseCamAngle - 4.71239) * golfBallForce * timer, 0.0, sin(chaseCamAngle - 4.71239) * golfBallForce * timer);
			}
		}
		// Else if the ball is stationary
		else
		{
			// Reset the values of the ball
			golfBallForce = 0.0;
			golfBallMoving = false;
		}
	}

}

// Input - since real time controls don't seem to fit here (problem with accessing member vars)
// Let's scrap this function and add the exit code to update control funciton
void gameScene::key_callbacks(GLFWwindow * win, int key, int scancode, int action, int mods)
{
	// Exit; close window
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(0);
	}

}

// Setup scene
void gameScene::Init(GLFWwindow * win)
{	
	// Set GL properties 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Hide cursor
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Get initial cursor pos
	glfwSetCursorPos(win, cursor_x, cursor_y);
	// Assign input
	glfwSetKeyCallback(win, key_callbacks);


	// This sets up level gen
	// More than 9 tiles has a potential to break it - ask me for deets (too long to type :D)
	courseGenV2 courseGen(9);
	// Runs the alg, returns map of tiles (pos, name)
	algTiles = courseGen.run();
	// Setup tiles
	setupTilesToBeDrawn();

	//LoadGame();
	for (auto &t : algTiles)
	{
		cout << t.id << endl;
	}

	//for (int i = 0; i < 1000; ++i)
	//{
	//	courseGenV2 cg(6);
	//	cg.run();
	//}
	//cout << "done" << endl;

	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");


	// Add the golf ball to scene
	golfBallMesh = new Mesh("..\\NuttyPutters\\sphere.obj");
	//golfBallMesh = new Mesh(Mesh::CUBOID, "..\\NuttyPutters\\box.jpg", vec3(0.0f, 2.0f, 0.0f), 2.0f, 2.0f, 2.0f);
	golfBallTexture = new Texture("..\\NuttyPutters\\ballRed.jpg");
	golfBallTransform.getScale() = vec3(0.5);
	golfBallTransform.getPos() = vec3(0.0, 1.0, 0.0);

	// Arrow
	arrowMesh = new Mesh(Mesh::CUBOID, "..\\NuttyPutters\\box.jpg", vec3(golfBallMesh->getGeomPos().x + 1.8, golfBallMesh->getGeomPos().y + 2.6, golfBallMesh->getGeomPos().z), 3.0f, 0.5f, 0.5f);
	arrowTexture = new Texture("..\\NuttyPutters\\ballBlue.jpg");
	arrowTransform.getScale() = vec3(0.5);


	// Setup cameras
	freeCam = new free_camera();
	freeCam->set_Posistion(vec3(0, 10, -10));
	freeCam->rotate(-10.0, 0.0);
	freeCam->set_Target(vec3(0, 0, 0));
	freeCam->set_projection(quarter_pi<float>(), (float)1600 / (float)900, 0.414f, 1000.0f);

	chaseCam = new chase_camera();
	chaseCam->set_target_pos(vec3(golfBallTransform.getPos()));
	chaseCam->set_pos_offset(vec3(0.0f, 5.0f, -5.0f));
	chaseCam->set_springiness(0.2f);
	chaseCam->set_projection(quarter_pi<float>(), (float)1600 / (float)900, 0.414f, 1000.0f);
}


// TODO Loads a level based on a seed
void gameScene::LoadGame()
{
	// In order to draw a level, we need:
	// Tile ID, Tile position
	// For end tile, need direction (to know how much to rotate)
	// ^ Unless there are 4 end tile types :p
	string tileInfo = "0:0.0.0, 1:0.0.10, 1:0.0.20, 9:0.0.30";

	


}
