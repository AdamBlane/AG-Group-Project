// Externals

// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton

// Default constructor
gameScene::gameScene() { }
// Deconstructor
gameScene::~gameScene() { }

// Setup scene; seed is an optional param passed in by loadGameScene
void gameScene::Init(GLFWwindow* window, int courseLength, string seed)
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
	
	// Record desired course size if no seed given
	courseSize = courseLength;

	// Load game
	LoadGame(seed); 

	// Take alg tiles, turn into render tiles
	SetupTilesToBeDrawn();

	// Setup scenery tiles
	FillScenery();


	playerSelectScene PSS;
	//PSS = playerSelectScene();
	selectedPlayers = PSS.selectedAmountOfPlayers();
	selectedDifficulty = PSS.selectedChosenDifficulty();
	cout << "Players: " << selectedPlayers << " Difficulty: " << selectedDifficulty << endl;

	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");

	// Add the golf ball to scene
	/*golfBallMesh = new Mesh("..\\NuttyPutters\\sphere.obj");
	golfBallTexture = new Texture("..\\NuttyPutters\\ballRed.jpg");
	golfBallTransform.getScale() = vec3(0.5);
	golfBallTransform.getPos() = vec3(0.0, 1.0, 0.0);*/

	// Arrow
	//arrowMesh = new Mesh(Mesh::CUBOID, "..\\NuttyPutters\\box.jpg", vec3(golfBallMesh->getGeomPos().x + 1.8, golfBallMesh->getGeomPos().y + 2.6, golfBallMesh->getGeomPos().z), 3.0f, 0.5f, 0.5f);
	//arrowTexture = new Texture("..\\NuttyPutters\\ballBlue.jpg");
	//arrowTransform.getScale() = vec3(0.5);

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

	tarCam = new target_camera();
	tarCam->set_Posistion(vec3(0, 0, 5.0f));
	tarCam->set_Target(vec3(0, 0, 0));
	tarCam->set_projection(quarter_pi<float>(), (float)1600 / (float)900, 0.414f, 1000.0f);

	// Stroke HUD Label setup
	//strokeLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\zero.png", vec3(-3.0, -1.5, 0.0), 0.5f, 0.5f);
	//// Player HUD Labelsetup
	//playerLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\playerone.png", vec3(-2.75, 1.7, 0.0), 1.0f, 0.25f);
	//// Power HUD Label setup
	//powerLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\power.png", vec3(3.0, -1.375, 0.0), 1.0f, 0.25f);
	//// Power Bar Outline HUD setup
	//powerBarOutlineDisplayMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\powerbar.jpg", vec3(2.5, -1.625, 0.0), 2.0f, 0.25f);
	//// Power Bar HUD setup
	//powerBarMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\ballBlue.jpg", vec3(1.6, -1.625, 0.0), 0.1f, 0.15f);
	//// Centre Bar HUD setup
	//centreInformationHeaderLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\hole1.png", vec3(0.0, 0.8, 0.0), 4.0f, 2.0f);
	//centreInformationFooterOneLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\par4.png", vec3(0.0, -0.5, 0.0), 2.0f, 0.5f);
	//centreInformationFooterTwoLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\timetwo.png", vec3(0.0, -1.0, 0.0), 2.0f, 0.5f);;
	//// Timer HUD setup
	//timerFirstUnitLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\nzero.png", vec3(2.8, 1.7, 0.0), 0.25f, 0.25f);
	//timerSecondUnitLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\ntwo.png", vec3(2.95, 1.7, 0.0), 0.25f, 0.25f);
	//timerThirdUnitLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\nzero.png", vec3(3.15, 1.7, 0.0), 0.25f, 0.25f);
	//timerForthUnitLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\nzero.png", vec3(3.3, 1.7, 0.0), 0.25f, 0.25f);
	//timerColonLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\semiColon.png", vec3(3.05, 1.725, 0.0), 0.25f, 0.25f);
	//// Set the texture of the loading screen
	//loadingMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\loadingscreen.png", vec3(0, 0.0, 0.0), 8.0f, 5.0f);

	// Set the amount of time the user has to complete the hole
	holeTimer = 80;
	
	// Enable alpha blending to allow for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Loads either random level of certain size, or level by seed
void gameScene::LoadGame(string seed)
{
	// Only get seed from file if not given to us from load game screen
	if (seed == "seed") // it's the default value
	{ 
		// Some magic numbers in the following section; for milestone 2, will replace after
		// Insert start
		levelSeed.push_back(0);
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
		for (int c = 0; c < line.length(); ++c)
		{
			// Convert each character in string to int
			levelSeed.push_back(line[c] - 48); // Char encoding for digits; ASCII int value is - 0, or - 48
		}
	} // end if seed is default
	else // this has been given a seed value
	{
		// Parse into ints as above
		for (int c = 0; c < seed.length(); ++c)
		{
			levelSeed.push_back(seed[c] - 48);
		}
	}

	// Start added first (this & next coords already set)
	StartTile start;
	algTiles.push_back(start);
	// Track currently looked at coords
	vec3 curCoords;
	// Update size tracker
	float size = start.size;
	// For each number in seed array
	for (auto &i : levelSeed)
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
				Tile tile(Tile::SCENERY, thisPos, "..\\NuttyPutters\\lava.jpg", "..\\NuttyPutters\\lava.jpg");
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
			Tile tile(Tile::STRAIGHT, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
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
			Tile tile(Tile::STRAIGHT, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
			// Rotate on x
			tile.transform.getRot().x = -0.349066;
			tile.transform.getPos().y -= 1.8;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		if (t.id == 0) // Start
		{
			// Create start tile
			Tile tile(Tile::START, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
			// Start tile needs rotating 180 (should always face down)
			tile.transform.getRot().y = 3.14159;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 1) // Straight V
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 2) // Straight H
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
			// Straight needs rotating by 90, since it's vertical by default
			tile.transform.getRot().y = 1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 3) // Corner BL
		{
			// Create corner tile
			Tile tile(Tile::CORNER, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
			// Corner needs rotating by 90
			tile.transform.getRot().y = 1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 4) // Corner BR
		{
			// Create corner tile
			Tile tile(Tile::CORNER, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
			// Corner needs rotating by 90
			tile.transform.getRot().y = 3.14159;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 5) // Corner TL
		{
			// Create corner tile
			Tile tile(Tile::CORNER, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 6) // Corner TR
		{
			// Create corner tile
			Tile tile(Tile::CORNER, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
			// Corner needs rotating by 90
			tile.transform.getRot().y = -1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 9) // end
		{
			// Create start tile
			Tile tile(Tile::END, t.thisCoords, "..\\NuttyPutters\\grass.png", "..\\NuttyPutters\\woodn.jpg");
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
	// Calculate dt
	lastFrame = thisFrame;
	thisFrame = glfwGetTime();
	dt = (float)(thisFrame - lastFrame);

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

	// If the X button is pressed then continue on with game -used for HUD elements
	if (glfwGetKey(window, GLFW_KEY_X))
	{
		continuePressed = true;
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
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		{
			camSpeed = 10.0f;
		}
		else
		{
			camSpeed = 2.0f;
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

	// Only allow ball movement if continue has been pressed
	if (continuePressed)
	{
		// If P is pressed 
		if (glfwGetKey(window, GLFW_KEY_SPACE))
		{
			if (!golfBallMoving)
			{
				// Start counter
				Pcounter += 0.5f;
				// Update the power bar based on the the Pcounter value 
				powerBarTrans.getPos().x -= (Pcounter/5.0f) * powerBarMesh->getGeomPos().x;
				powerBarTrans.getPos().x += Pcounter /100.0f; // This value has has to be 20 times the dividing value as the scale extends both ways not just in a positive direction
				powerBarTrans.getScale().x += Pcounter/5.0f; // Update the scale based on the Pcounter value

				// SET DIRECTION BASED ON CHASE CAM ANGLE
				// If camera angle is between 0 and 90
				if (chaseCamAngle >= 0 && chaseCamAngle < 1.5708)
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

		// When Space is realesed
		if ((glfwGetKey(window, GLFW_KEY_SPACE)) == false)
		{
			// Only work if space was just released
			if (pPressed)
			{
				golfBallMoving = true;
				// Force to apply is held in counter
				//Pcounter *= 3; // slightly magic number (Pc isn't enough on its own)
				// Apply to speed
				speed += Pcounter;
				//repeat until Pcounter is reset to 0
				while (Pcounter > 0.0)
				{
					//This just inverts the increasing in size and positions done before when P was pressed
					powerBarTrans.getPos().x += (Pcounter / 5.0f) * powerBarMesh->getGeomPos().x;
					powerBarTrans.getPos().x -= Pcounter / 100.0f;
					powerBarTrans.getScale().x -= Pcounter / 5.0f;
					//Decrease Pcounter until reaches 0
					Pcounter -= 0.5;
				}

				// Increment stroke counter by one
				strokeCounter += 1;

				// Switch statement which changes the stroke counter based on how many strokes the player has taken
				switch (strokeCounter)
				{
				case 0:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\zero.png");
					break;
				case 1:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\one.png");
					break;
				case 2:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\two.png");
					break;
				case 3:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\three.png");
					break;
				case 4:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\four.png");
					break;
				case 5:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\five.png");
					break;
				case 6:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\six.png");
					break;
				case 7:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\seven.png");
					break;
				case 8:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\eight.png");
					break;
				case 9:
				//	strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nine.png");
					break;
				case 10:
					//strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\ten.png");
					break;
				case 11:
				//	strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\eleven.png");
					break;
				case 12:
				//	strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\twelve.png");
					break;
				case 13:
				//	strokeLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\x.png");
					break;
				}
				// Flip
				pPressed = false;
			}
		} // End if (p is released)
	}

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

	// Update target camera
	tarCam->update(0.00001);

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

	// If the time been in scene is equal to zero then
	if (timeBeenInScene == 0)
	{
		// Get the amount of time been in scene
		timeBeenInScene = glfwGetTime();
	}
	// Increment time Counter - used for splash screen
	timeCounter++;

	// If the continue button is pressed 
	if (continuePressed)
	{
		// If the time taken to reach this method is zero then
		if (timeToThisMethod == 0)
		{
			// Get the time to this method
			timeToThisMethod = glfwGetTime();
		}
		// Get the time since continue was pressed by taking away the time to this method 
		timeSinceContinueWasPressed = glfwGetTime() - timeToThisMethod;
		// Get the time remaining in seconds by taking away the time the user has to complete the hole 
		timeRemainingInSeconds = holeTimer - timeSinceContinueWasPressed;
		// Get the time in minutes, tenths and seconds - 0M:TS
		timeRemainingInMinutes = timeRemainingInSeconds / 60;
		timeRemainingInTenths = (timeRemainingInSeconds - (timeRemainingInMinutes * 60)) / 10;
		timeRemainingInSeconds = timeRemainingInSeconds - (timeRemainingInMinutes * 60) - (timeRemainingInTenths * 10);
		//cout << "Mins and secs: " << timeRemainingInMinutes << " " << timeRemainingInTenths << " " << timeRemainingInSeconds << endl;

		// Switch statements which update the minutes, tenths and seconds meshes
		switch (timeRemainingInMinutes)
		{
		case 0:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nzero.png");
			break;
		case 1:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\none.png");
			break;
		case 2:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\ntwo.png");
			break;
		case 3:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nthree.png");
			break;
		case 4:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nfour.png");
			break;
		case 5:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nfive.png");
			break;
		case 6:
			//timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nsix.png");
			break;
		case 7:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nseven.png");
			break;
		case 8:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\neight.png");
			break;
		case 9:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nnine.png");
			break;
		default:
		//	timerSecondUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\x.png");
			break;
		}

		switch (timeRemainingInTenths)
		{
		case 0:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nzero.png");
			break;
		case 1:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\none.png");
			break;
		case 2:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\ntwo.png");
			break;
		case 3:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nthree.png");
			break;
		case 4:
			//timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nfour.png");
			break;
		case 5:
			//timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nfive.png");
			break;
		case 6:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nsix.png");
			break;
		case 7:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nseven.png");
			break;
		case 8:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\neight.png");
			break;
		case 9:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nnine.png");
			break;
		default:
		//	timerThirdUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\x.png");
			break;
		}

		switch (timeRemainingInSeconds)
		{
		case 0:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nzero.png");
			break;
		case 1:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\none.png");
			break;
		case 2:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\ntwo.png");
			break;
		case 3:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nthree.png");
			break;
		case 4:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nfour.png");
			break;
		case 5:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nfive.png");
			break;
		case 6:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nsix.png");
			break;
		case 7:
			//timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nseven.png");
			break;
		case 8:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\neight.png");
			break;
		case 9:
			//timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\nnine.png");
			break;
		default:
		//	timerForthUnitLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\x.png");
			break;
		}
	}
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

			// If user hasnt completed hole then - get
			if (!hasUserCompletedHole)
			{
				hasUserCompletedHole = end.getBallInHole();
			}

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
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = tarCam->get_Projection() * tarCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	// If timeCounter - which is a variable that increases as of when the scene has loaded is less than the time been in scene + a value that can be changed then
	if (timeCounter < timeBeenInScene + 300)
	{
		// Display loading screen
		/*loadingMesh->thisTexture->Bind(0);
		textureShader->Update(loadingTrans, hudVP);
		loadingMesh->Draw();*/
	}

	// If the user completes the hole then
	if (hasUserCompletedHole && !hasUserCompletedHoleTextures)
	{
		// Update boolean to true
		hasUserCompletedHoleTextures = true; // To update textures if hole is complete
		// Update textures
	/*	centreInformationHeaderLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\holecomplete.png");
		centreInformationFooterOneLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\savegame.png");
		centreInformationFooterTwoLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\mainmenu.png");*/
	}
	// If the timer is lower than zero sceonds and if user is out of time is false
	if (timeRemainingInSeconds < 0 && !isUserOutOfTime)
	{
		// Update boolean to true
		isUserOutOfTime = true; // Used to notify the game if the user has ran out of time
		// Update textures
		//centreInformationHeaderLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\outoftime.png");
		//centreInformationFooterOneLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\savegame.png");
		//centreInformationFooterTwoLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\mainmenu.png");
	}
	// If the user takes more than 10 strokes and if the user is out of strokes is false
	if (strokeCounter > 12 && !isUserOutOfStrokes)
	{
		// Update boolean to true
		isUserOutOfStrokes = true; // Used to notify the game if the user has run out of strokes
		// Update textures
	/*	centreInformationHeaderLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\outofshots.png");
		centreInformationFooterOneLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\savegame.png");
		centreInformationFooterTwoLabelMesh->thisTexture = new Texture("..\\NuttyPutters\\mainmenu.png");*/
	}

	// If user has completed the hole or if the continue button hasnt been pressed of if the user has run out of time or if the user has run out of strokes
	if (hasUserCompletedHole || !continuePressed || isUserOutOfTime || isUserOutOfStrokes )
	{
		// Update the various centre informatiom elements
		//centreInformationHeaderLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(centreInformationHeaderLabelTrans, hudVP);
		//centreInformationHeaderLabelMesh->Draw();
		//centreInformationFooterOneLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(centreInformationFooterOneLabelTrans, hudVP);
		//centreInformationFooterOneLabelMesh->Draw();
		//centreInformationFooterTwoLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(centreInformationFooterTwoLabelTrans, hudVP);
		//centreInformationFooterTwoLabelMesh->Draw();
	}
	// Else then display remaining gameplay HUDs
	else
	{
		// Bind, update and draw the stroke label HUD
		//strokeLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(strokeLabelTrans, hudVP);
		//strokeLabelMesh->Draw();
		//// Bind, update and draw the player label HUD
		//playerLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(playerLabelTrans, hudVP);
		//playerLabelMesh->Draw();
		//// Bind, update and draw the power label HUD
		//powerLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(powerLabelTrans, hudVP);
		//powerLabelMesh->Draw();
		//// Bind, update and draw the power bar HUD
		//powerBarMesh->thisTexture->Bind(0);
		//textureShader->Update(powerBarTrans, hudVP);
		//powerBarMesh->Draw();
		//// Bind, update and draw the power bar outline HUD
		//powerBarOutlineDisplayMesh->thisTexture->Bind(0);
		//textureShader->Update(powerBarOutlineDisplayTrans, hudVP);
		//powerBarOutlineDisplayMesh->Draw();
		//// Bind, update and draw the timer HUDs
		//timerFirstUnitLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(timerFirstUnitLabelTrans, hudVP);
		//timerFirstUnitLabelMesh->Draw();
		//timerSecondUnitLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(timerSecondUnitLabelTrans, hudVP);
		//timerSecondUnitLabelMesh->Draw();
		//timerThirdUnitLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(timerThirdUnitLabelTrans, hudVP);
		//timerThirdUnitLabelMesh->Draw();
		//timerForthUnitLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(timerForthUnitLabelTrans, hudVP);
		//timerForthUnitLabelMesh->Draw();
		//timerColonLabelMesh->thisTexture->Bind(0);
		//textureShader->Update(timerColonLabelTrans, hudVP);
		//timerColonLabelMesh->Draw();
	}

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);
	// HUD RENDERING ENDED - THANK YOU AND HAVE A NICE DAY

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

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}