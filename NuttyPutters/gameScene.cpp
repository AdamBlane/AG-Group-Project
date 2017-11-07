// Externals

// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton

// Default constructor
gameScene::gameScene() { }
// Deconstructor
gameScene::~gameScene() { }

// Setup scene
void gameScene::Init(GLFWwindow* window)
{
	// Set GL properties 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Get initial cursor pos
	glfwSetCursorPos(window, cursor_x, cursor_y);

	// LEVEL GEN
	//courseGenV2 cg(12);
	//algTiles = cg.run();



	LoadGame(); // optional parameter of seed
	// Take alg tiles, turn into render tiles
	SetupTilesToBeDrawn();

	// Setup scenery tiles
	FillScenery();

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

// Loads a level based on given seed
void gameScene::LoadGame()
{
	// Only get seed from file if not given to us from load game screen
	
	// Seed chosen is found in file
	// Some magic numbers in the following section; for milestone 2, will replace after
	// Seed is a list of numbers, which refer to tile type
	int seed[12];
	// Insert start
	seed[0] = 0;
	// Open seeds file 
	ifstream seedsFile("res12.csv");
	// find how many lines in seed file (hardcoded for now)
	int seedsCount = 341;
	// pick random number in that range
	default_random_engine rng(random_device{}());
	uniform_int_distribution<int> distribution(0, seedsCount);
	int choice = distribution(rng);
	// read that line
	string line;
	for (int l = 0; l < choice; ++l)
	{
		getline(seedsFile, line);
	} // last iteration will be on desired line, so line should be correct seed now
	// parse seed into array
	for (int i = 0; i < 11; ++i)
	{
		seed[i+1] = line[i] - 48;
	}
	
	//int seed[] = { 1, 1, 1, 1, 1, 1, 1, 1, 9 };

	// Start added first (this & next coords already set)
	StartTile start;
	algTiles.push_back(start);
	// Track currently looked at coords
	vec3 curCoords;
	// Update size tracker
	float size = start.size;
	// For each number in seed array
	for (auto &i : seed)
	{
		// Update current coordinates (next coords of last thing in list) 
		curCoords = algTiles.back().GetNextCoords();

		switch (i)
		{
			// Straight_V
		case 1:
		{
			// Create tile
			StraightTile_V straightV;
			// Set its position
			straightV.SetCoords(curCoords);
			// Find next position - based on direction
			if (algTiles.back().outDir.going_down)
			{
				// The position of next tile in list
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				straightV.SetNextCoords(nextPos);
				// Set dir
				straightV.outDir.going_down = true;
			}
			else if (algTiles.back().outDir.going_up)
			{
				// The position of next tile in list
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				straightV.SetNextCoords(nextPos);
				// Set dir
				straightV.outDir.going_up = true;
			}
			// Add tile to list, finish (break)
			algTiles.push_back(straightV);
			break;
		}
		// Straight_H
		case 2:
		{
			// Create tile
			StraightTile_H straightH;
			// Set its position
			straightH.SetCoords(curCoords);
			// Find next position
			if (algTiles.back().outDir.going_right)
			{
				// Position of next tile in list
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				straightH.SetNextCoords(nextPos);
				// Set dir
				straightH.outDir.going_right = true;
			}
			else if (algTiles.back().outDir.going_left)
			{
				// Position of next tile in list
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				straightH.SetNextCoords(nextPos);
				// Set dir
				straightH.outDir.going_left = true;
			}

			// Add to list
			algTiles.push_back(straightH);
			break;
		}
		// Corner_BL
		case 3:
		{
			// Create tile
			CornerTile_BL cornerBL;
			// Set pos
			cornerBL.SetCoords(curCoords);
			// Find next position
			if (algTiles.back().outDir.going_down)
			{
				// Last tile was going down; next tile is going right
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				cornerBL.SetNextCoords(nextPos);
				// Set dir
				cornerBL.outDir.going_right = true;
			}
			else if (algTiles.back().outDir.going_left)
			{
				// Last tile was going left; next tile is going up
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				cornerBL.SetNextCoords(nextPos);
				// Set dir
				cornerBL.outDir.going_up = true;
			}
			// Add to list
			algTiles.push_back(cornerBL);
			break;
		}
		// Corner_BR
		case 4:
		{
			// Create tile
			CornerTile_BR cornerBR;
			// Set pos
			cornerBR.SetCoords(curCoords);
			// Find next position
			if (algTiles.back().outDir.going_down)
			{
				// Last tile was going down; next tile is going left
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				cornerBR.SetNextCoords(nextPos);
				// Set dir
				cornerBR.outDir.going_left = true;
			}
			else if (algTiles.back().outDir.going_right)
			{
				// Last tile was going right; next tile is going up
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				cornerBR.SetNextCoords(nextPos);
				// Set dir
				cornerBR.outDir.going_up = true;
			}
			// Add to list
			algTiles.push_back(cornerBR);
			break;
		}
		// Corner_TL
		case 5:
		{
			// Create tile
			CornerTile_TL cornerTL;
			cornerTL.SetCoords(curCoords);
			// Find next pos
			if (algTiles.back().outDir.going_up)
			{
				// Last tile was going up; next going right
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				cornerTL.SetNextCoords(nextPos);
				// Set dir
				cornerTL.outDir.going_right = true;
			}
			else if (algTiles.back().outDir.going_left)
			{
				// Last tile was going left; next tile going down
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				cornerTL.SetNextCoords(nextPos);
				// Set dir
				cornerTL.outDir.going_down = true;
			}
			// Add to list
			algTiles.push_back(cornerTL);
			break;
		}
		// Corner_TR
		case 6:
		{
			// Create tile
			CornerTile_TR cornerTR;
			// Set pos
			cornerTR.SetCoords(curCoords);
			// Find next pos
			if (algTiles.back().outDir.going_right)
			{
				// Last tile going right; next tile going down
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				cornerTR.SetNextCoords(nextPos);
				// Set dir
				cornerTR.outDir.going_down = true;
			}
			else if (algTiles.back().outDir.going_up)
			{
				// Last tile going up; next tile going left
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				cornerTR.SetNextCoords(nextPos);
				// Set dir
				cornerTR.outDir.going_left = true;
			}
			// Add to list
			algTiles.push_back(cornerTR);
			break;
		}
		// UpRampDown
		case 7:
		{
			// Create tile
			UpRampDown upRamp;
			upRamp.SetCoords(curCoords);
			// Find next pos (always know dir is down when 7 is placed)
			vec3 nextPos = vec3(curCoords.x, curCoords.y + 3.8, curCoords.z + size);
			upRamp.SetNextCoords(nextPos);
			upRamp.outDir.going_down = true;
			algTiles.push_back(upRamp);
			break;
		}
		// DownRampDown
		case 8:
		{
			// Create tile
			DownRampDown downRamp;
			downRamp.SetCoords(curCoords);
			// Find next pos (always know dir is up with tile 8)
			vec3 nextPos = vec3(curCoords.x, curCoords.y - 3.8, curCoords.z - size);
			downRamp.SetNextCoords(nextPos);
			downRamp.outDir.going_up = true;
			algTiles.push_back(downRamp);
			break;
		}

		// End tile
		case 9:
		{
			// Create end tile
			EndTile end;
			end.SetCoords(curCoords);
			end.outDir = algTiles.back().outDir;
			algTiles.push_back(end);
			break;
		}


		} // Switch end

	} // for loop end

}

// Populates scenery tiles
void gameScene::FillScenery()
{
	// Get boundary positions of level tiles in x and z
	float xMax = 0;
	float xMin = 0;
	float zMax = 0; 
	float zMin = 0;
	for (auto &t : algTiles)
	{
		if (t.thisCoords.x > xMax)
			xMax = t.thisCoords.x;
		if (t.thisCoords.x < xMin)
			xMin = t.thisCoords.x;

		if (t.thisCoords.z > zMax)
			zMax = t.thisCoords.z;
		if (t.thisCoords.z < zMin)
			zMin = t.thisCoords.z;
	}
	// Add another tile's width to boundaries
	xMin -= 10; // To add another layer to the boundary, add 10 to each value
	zMin -= 20;
	xMax += 20;
	zMax += 10;

	// Starting in corner, fill with scenery tile if not already filled by level tile
	// Z
	for (int zPos = zMax; zPos > zMin; zPos -= 10) // 10 = tile size
	{
		// Work in rows; every x for a single z
		for (int xPos = xMin; xPos < xMax; xPos += 10)
		{
			vec3 thisPos = vec3(xPos, 0.0f, zPos); // Not dealing with ramps for now
			cout << thisPos.x << ", " << thisPos.z << endl;
			// Check if this pos is already taken by a level tile
			bool posTaken = false;
			// Contains search; there will only be one match
			for (int i = 0; i < algTiles.size(); ++i)
			{
				if (algTiles.at(i).thisCoords == thisPos)
				{
					// We have a match
					posTaken = true;
				}
			}
			// If able to create a scenery tile...
			if (!posTaken)
			{
				// Create straight tile
				//Mesh lava(Mesh::QUAD, "..\\NuttyPutters\\box.jpg", thisPos, 10.0f, 10.0f, 10.0f);
				Tile tile(Tile::STRAIGHT, "..\\NuttyPutters\\lava.jpg", "..\\NuttyPutters\\lava.jpg", thisPos);		
				//tile.transform.getRot().x = -0.785398;
				// Add to list of tiles to be rendered
				sceneryTiles.push_back(tile);


			}
		} // end x block
	} // end z block
}

// Creates tile classes to be drawn
void gameScene::SetupTilesToBeDrawn()
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
			Tile tile(Tile::END, "..\\NuttyPutters\\grass.jpg", "..\\NuttyPutters\\box.jpg", t.thisCoords);
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

// Main game loop 
void gameScene::Loop(GLFWwindow* window)
{
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(window);

	// Update
	Update(window);

	// Collisions
	Collisions();

	// Render
	Render(window);

}

// Act on input
void gameScene::Input(GLFWwindow* window)
{
	// Exit
	if (glfwGetKey(window, GLFW_KEY_B))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(0);	
		cout << "Pressed B" << endl;
	}
	// Pause
	if (glfwGetKey(window, GLFW_KEY_P))
	{
		cout << "game paused" << endl;
		bool paused = true;
		while (paused)
		{			
			// Change scene bg colour while paused? 

			// Need this or we get stuck in loop
			glfwPollEvents();
			// Save this level (move this code later to end of game, so we can save score with it)
			if (glfwGetKey(window, GLFW_KEY_S))
			{
				// Only save this level once
				if (!levelSaved)
				{
					// Open file to append level seed 
					ofstream saves("saves.csv", ofstream::app);
					// ID of each tile makes up seed
					for (auto &t : algTiles)
					{
						saves << t.id;
					}
					saves << endl;
					cout << "Level saved" << endl;
					levelSaved = true;
				}

			}

			// Unpause
			if (glfwGetKey(window, GLFW_KEY_U))
			{
				paused = false;
				break;		
			}
		} // end while paused
		cout << "Unpaused" << endl;
	} // end pause

	// If button one is pressed change to free camera
	if (glfwGetKey(window, GLFW_KEY_1))
	{
		// Set camera version to free camera
		cout << "Free Camera selected" << endl;
		cameraType = 0;
		// Set the free cam position to where the chasecam stopped moving for debugging can me changed later
		freeCam->set_Posistion(chaseCam->get_Posistion());
	}

	// If button two is pressed change to chase camera
	if (glfwGetKey(window, GLFW_KEY_2))
	{
		// Set camera version to chase camera
		cout << "Chase Camera selected" << endl;
		cameraType = 1;
	}

	// FREE CAM controls
	if (cameraType == 0)
	{
		// Create vector to apply to current cam pos
		vec3 freeCamPos = vec3(0, 0, 0);

		// Camera controls
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			freeCamPos = (vec3(0, 0, camSpeed * dt));
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			freeCamPos = (vec3(-camSpeed * dt, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			freeCamPos = (vec3(0, 0, -camSpeed * dt));
		}
		if (glfwGetKey(window, GLFW_KEY_D))
		{
			freeCamPos = (vec3(camSpeed * dt, 0, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_Q))
		{
			freeCamPos = (vec3(0, camSpeed * dt, 0));
		}
		if (glfwGetKey(window, GLFW_KEY_E))
		{
			freeCamPos = (vec3(0, -camSpeed * dt, 0));
		}

		// Move camera by new pos after input
		freeCam->move(freeCamPos);
	}
	// CHASE CAM controls
	else if (cameraType == 1)
	{
		// If ball is not moving then allow for angle on chase camera to be changed
		if (!golfBallMoving)
		{
			// controls in the chase camera 
			if (glfwGetKey(window, GLFW_KEY_D))
			{
				//function to rotate 
				chaseCam->yaw_it(camSpeed * dt * 0.5);
				// Decrease chase camera angle (out of 360 degrees)
				chaseCamAngle -= (camSpeed * dt * 0.5);
			}
			if (glfwGetKey(window, GLFW_KEY_A))
			{
				chaseCam->neg_yaw_it(camSpeed * dt * 0.5);
				// Increase chase camera angle (out of 360 degrees)
				chaseCamAngle += (camSpeed * dt * 0.5);
			}
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			chaseCam->neg_pitch_it(camSpeed * dt * 0.5, golfBallTransform.getPos(), chaseCam->get_Posistion(), chaseCam->get_pos_offset().y);
		}
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			chaseCam->pitch_it(camSpeed * dt * 0.5, golfBallTransform.getPos(), chaseCam->get_Posistion(), chaseCam->get_pos_offset().y);
		}
		if (glfwGetKey(window, GLFW_KEY_Q))
		{
			//function to rotate 
			chaseCam->zoom_out(camSpeed * dt * 0.5);
		}
		if (glfwGetKey(window, GLFW_KEY_E))
		{
			chaseCam->zoom_in(camSpeed * dt * 0.5);
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
	}


	// PLAYER
	// If P is pressed 
	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		if (!golfBallMoving)
		{
			// Start counter
			Pcounter += 0.5f;

			// SET DIRECTION BASED ON CHASE CAM ANGLE
			// If camera angle is between 0 and 90
			if (chaseCamAngle > 0 && chaseCamAngle < 1.5708)
			{
				// Update the golf ball position and the arrow position
				// x = -sin(theta), z = cos(theta)
				// Separate below statement into direction = vec3(-sin, 0, cos) (normalise)		
				gbDirection = normalize(vec3(-sin(chaseCamAngle), 0.0, cos(chaseCamAngle)));
			}
			// If camera angle is between 90 and 180
			else if (chaseCamAngle > 1.5709 && chaseCamAngle < 3.14159)
			{
				// x = -cos(theta - 90), z = -sin(theta - 90)
				gbDirection = normalize(vec3(-cos(chaseCamAngle - 1.5708), 0.0, -sin(chaseCamAngle - 1.5708)));

			}
			// If camera angle is between 180 and 270
			else if (chaseCamAngle > 3.1416 && chaseCamAngle < 4.71239)
			{
				// x = sin(theta - 180), z = -cos(theta - 180)
				gbDirection = normalize(vec3(sin(chaseCamAngle - 3.1416), 0.0, -cos(chaseCamAngle - 3.1416)));

			}
			// If camera angle is anything else
			else if (chaseCamAngle > 4.724 && chaseCamAngle < 6.28319)
			{
				// x = cos(theta - 270), z = sin(theta- 270)
				gbDirection = normalize(vec3(cos(chaseCamAngle - 4.71239), 0.0, sin(chaseCamAngle - 4.71239)));

			}

			pPressed = true;
		}

	}

	// When P is realesed
	if ((glfwGetKey(window, GLFW_KEY_SPACE)) == false)
	{
		// Only work if p was just released
		if (pPressed)
		{
			golfBallMoving = true;
			// Force to apply is held in counter
			//Pcounter *= 3; // slightly magic number (Pc isn't enough on its own)
			// Apply to speed
			speed += Pcounter;
			// Reset
			Pcounter = 0;
			// Flip
			pPressed = false;
		} 	
	} // End if (p is released)

}

// Update positions
void gameScene::Update(GLFWwindow* window)
{
	// Free cam stuff
	static double ratio_width = quarter_pi<float>() / 1600.0;
	static double ratio_height = (quarter_pi<float>() * (1600 / 900)) / static_cast<float>(1600);
	double current_x, current_y;
	glfwGetCursorPos(window, &current_x, &current_y);
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

	// The getRot of golf ball - will this be troublesome? Don't want the camera
	// to rotate along with the ball! 
	chaseCam->move(golfBallTransform.getPos(), golfBallTransform.getRot());
	chaseCam->update(0.00001);

	// PLAYER UPDATE
	// Velocity is direction by speed by delta time
	gbVelocity = (gbDirection * speed);
	// Apply friction when moving
	if (speed > 0 + 0.5) // this magic number is epsilon
	{
		speed -= speed * 0.03; // this magic number is friction
		 // Rotation is cross product of direction and up
		vec3 rot = normalize(cross(normalize(gbDirection), vec3(0.0f, 1.0f, 0.0f)));
		rot *=  speed *  dt;
		golfBallTransform.getRot() += -rot;
	}
	// Prevent it moving forever
	else 
	{
		speed = 0;
		golfBallMoving = false;
	}
	// Lock to frame rate
	gbVelocity *= dt;

	// Update positions of ball and arrow
	golfBallTransform.getPos() += gbVelocity;
	arrowTransform.getPos() += gbVelocity;

	
}


// Tracks current tile player is on (TODO improve performance)
// Calls collision checking code of tile player is on
void gameScene::Collisions()
{
	
	int tileTracker = 0;
	// Check which tile player is on (do this every n frames, not each tick)
	for (auto &t : algTiles)
	{
		// if (t.isPlayerOnTile)
		  // currentTile = tileTracker
		// if not, tileTracker++
		if (t.isPlayerOnTile(golfBallTransform.getPos()))
		{
			currentTile = tileTracker;
		}
		else
			tileTracker++;
	}
	//cout << "Current tile: " << algTiles.at(currentTile).id << "at (" << algTiles.at(currentTile).thisCoords.x << ", " << algTiles.at(currentTile).thisCoords.x << ") " << " : " << currentTile << "pos: " << golfBallTransform.getPos().x << ", " << golfBallTransform.getPos().y << ", " << golfBallTransform.getPos().z  << endl;

	// Switch on the currentTile 
	switch (algTiles.at(currentTile).id)
	{
			// On start tile
		case 0:
		{
			// Need to do this to access start only methods (which includes col check)
			//onRamp = false;
			StartTile start;
			gbDirection = start.CheckCollisions(golfBallTransform.getPos(), gbDirection);
			break;
		}
		// On straight V tile
		case 1:
		{
			//onRamp = false;
			StraightTile_V straightV;
			straightV.SetCoords(algTiles.at(currentTile).GetThisCoords());
			// Ensure don't go through floor
			golfBallTransform.setPos(straightV.SetPlayerHeight(golfBallTransform.getPos()));
			gbDirection = straightV.CheckCollisions(golfBallTransform.getPos(), gbDirection);
			break;
		}
		// On straight H tile
		case 2:
		{
			//onRamp = false;
			StraightTile_H straightH;
			straightH.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = straightH.CheckCollisions(golfBallTransform.getPos(), gbDirection);
			break;
		}
		// On corner_BL tile
		case 3:
		{
			//onRamp = false;
			CornerTile_BL cornerBL;
			cornerBL.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = cornerBL.CheckCollisions(golfBallTransform.getPos(), gbDirection);
			break;
		}
		// On corner_BR tile
		case 4:
		{
			//onRamp = false;
			CornerTile_BR cornerBR;
			cornerBR.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = cornerBR.CheckCollisions(golfBallTransform.getPos(), gbDirection);
			break;
		}
		// On corner_TL tile
		case 5:
		{
			//onRamp = false;
			CornerTile_TL cornerTL;
			cornerTL.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = cornerTL.CheckCollisions(golfBallTransform.getPos(), gbDirection);
			break;
		}
		// On corner_TR tile
		case 6:
		{
			//onRamp = false;
			CornerTile_TR cornerTR;
			cornerTR.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = cornerTR.CheckCollisions(golfBallTransform.getPos(), gbDirection);
			break;
		}
		// Up ramp tile
		case 7:
		{
			UpRampDown ramp;
			ramp.SetCoords(algTiles.at(currentTile).GetThisCoords());
			ramp.thisCoords.y += 1.8;
			// Set player height
			golfBallTransform.setPos(ramp.SetPlayerHeight(golfBallTransform.getPos()));
			//onRamp = true;
			break;
		}
		// End tile
		case 9:
		{
			//onRamp = false;
			EndTile end;
			end.SetCoords(algTiles.at(currentTile).GetThisCoords());
			end.outDir = algTiles.at(currentTile).outDir;
			gbDirection = end.CheckCollisions(golfBallTransform.getPos(), gbDirection, speed);
			
			break;
		}
	}
}

// Draw stuff
void gameScene::Render(GLFWwindow* window)
{
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

	// DRAW all level tiles
	for (auto &t : tiles)
	{
		t.drawTile(textureShader, mvp);
	}
	// DRAW all scenery tiles
	for (auto &t : sceneryTiles)
	{
		t.drawTile(textureShader, mvp);
	}
	// Draw all trees
	//for (int i = 0; i < treeMeshes.size(); ++i)
	//{
	//	treeMeshes.at(i)->Draw();
	//	textureShader->Update(treeTransforms.at(i), mvp);
	//}
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

	glfwSwapBuffers(window);
	glfwPollEvents();
}