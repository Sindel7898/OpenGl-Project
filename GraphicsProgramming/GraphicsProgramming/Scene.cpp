// Include the Scene header file
#include "Scene.h"

// Scene constructor, initializes OpenGL
// You should add further variables that need to be initialized.
Scene::Scene(Input* in)
{
	// Store a pointer for the input class
	input = in;

	// Initialize OpenGL
	initialiseOpenGL();

	// Other OpenGL/render settings should be applied here.
	// Initialize scene variables

	// Enable 2D textures
	glEnable(GL_TEXTURE_2D);

	// Disable color material
	glDisable(GL_COLOR_MATERIAL);

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Load 3D models with their respective textures
	Teapot.load("models/teapot.obj", "gfx/crate.png");
	NintendoDS.load("models/N_3DS.obj", "gfx/Mt_Rolling3DS_01.png");
	SpaceShip.load("models/spaceship.obj", "gfx/spaceship.JPG");
	lamp.load("models/HangingLamp.obj", "gfx/HangingLamp.png"); 
	Drone.load("models/drone.obj", "gfx/Drone.JPG");
	Radio.load("models/Radio.obj", "gfx/Radio.PNG");
	DocOc.load("models/Doctor Octopus.obj", "gfx/body.PNG");
	// Load skybox textures
	SKYBOX = SOIL_load_OGL_texture(
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	Earth = SOIL_load_OGL_texture(
		"gfx/earth.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);


	SATRUN = SOIL_load_OGL_texture(
		"gfx/DarkEarth.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	SKYBOX1 = SOIL_load_OGL_texture(
		"gfx/skybox1.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	SKYBOX2 = SOIL_load_OGL_texture(
		"gfx/skybox2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	// Initialize IrrKlang sound engine and play 3D music
	ISoundEngine* engine = createIrrKlangDevice();
	ISound* music1 = engine->play3D("Music/jazz.mp3", vec3df(13, 0, 0), true, false, true);
	music1->setVolume(20);
}


void Scene::handleInput(float dt)
{
	// Handle user input

	// Switch between different colors for light 
	if (input->isKeyDown('l') || input->isKeyDown('L')) {
		ColorSwitcher++;

		if (ColorSwitcher > 3) {
			ColorSwitcher = 0;
		}
		input->setKeyUp('l');
		input->setKeyUp('L');
	}

	// Toggle wireframe rendering mode
	if (input->isKeyDown('r') || input->isKeyDown('R')) {
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);

		input->setKeyUp('r');
		input->setKeyUp('R');
		renderType++; 

		if (renderType == 2) {
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			renderType = 0;
		}
	}

	// Toggle roof removal for a building
	if (input->isKeyDown('p') || (input->isKeyDown('P'))) {
		startingBuilding.RoofRemover++;

			if (startingBuilding.RoofRemover > 1) {
				startingBuilding.RoofRemover = 0;
			}
			input->setKeyUp('p');
			input->setKeyUp('P');

	}


	// Switch between different skyboxes
	if (input->isKeyDown('o') || (input->isKeyDown('O'))) {
		SkyBoxChanger++;

		if (SkyBoxChanger > 3) {
			SkyBoxChanger = 1;
		}
		input->setKeyUp('o');
		input->setKeyUp('O');

	}

	if (input->isKeyDown('f') || input->isKeyDown('F')) {
		Switcher = 0;
		input->setKeyUp('f');
		input->setKeyUp('F');
	}


	if (input->isKeyDown('1')) {
		Switcher = 1;
		input->setKeyUp('1');
	}

	if (input->isKeyDown('2')) {
		Switcher = 2;
		input->setKeyUp('2');
	}

	if (input->isKeyDown('3')) {
		Switcher = 3;
		input->setKeyUp('3');
	}


	// Move the camera based on key inputs
	if (input->isKeyDown('w'))
	{

		camera.moveForward(dt);
	}

	if (input->isKeyDown('a'))
	{

		camera.moveLeft(dt);
	}
	if (input->isKeyDown('s'))
	{

		camera.moveBackwords(dt);

	}
	if (input->isKeyDown('d'))
	{

		camera.moveRight(dt);

	}
	if (input->isKeyDown('x'))
	{

		camera.moveDown(dt);
	}
	if (input->isKeyDown('z'))
	{

		camera.moveUp(dt);
	}

	// Control the camera using the mouse
	xDiff = input->getMouseX() - (width / 2);
	yDiff = input->getMouseY() - (height / 2);
	if (xDiff != 0 || yDiff != 0)
	{
		camera.controlMouse(dt, xDiff, yDiff);
	}
	camera.update();

	// Reset the mouse position and hide the cursor
	glutWarpPointer(width / 2, height / 2);
	glutSetCursor(GLUT_CURSOR_NONE);

}



void Scene::update(float dt)
{
	// update scene related variables.
	
		Rotation += 40 * dt;

		if (input->isKeyDown('q') || input->isKeyDown('q')) {
			ReflectionRotaion += 40 * dt;
		}
	
	// Calculate FPS for output
	calculateFPS();
	camera.update();
}


//skybox
void Scene::DrawCube() {
	glPushMatrix();

	//tracks the locaiton of the skybox to the camera
	glTranslatef(camera.getPosX(), camera.getPosY(), camera.getPosZ());


	if (SkyBoxChanger == 1)
	{
		glBindTexture(GL_TEXTURE_2D, SKYBOX);

	}

	if (SkyBoxChanger == 2)
	{
		glBindTexture(GL_TEXTURE_2D, SKYBOX1);
	}

	if (SkyBoxChanger == 3)
	{
		glBindTexture(GL_TEXTURE_2D, SKYBOX2);
	}
    
	glPushMatrix();
	glBegin(GL_QUADS);

	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	//Right Face
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	////Bottom Face
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.75f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	//Left Face
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	//Top Face
	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.5f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	/*Back Face*/
	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glPopMatrix();
	glEnd();
	
}


// reflection surface for the teapot
void Scene::ReflectionFloor() {
	glPushMatrix();
	glScalef(2, 2, 2);
	glTranslatef(-1, 0.25, 6);
	glRotatef(90, 1, 0, 0);

	glBegin(GL_QUADS);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(2.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glPopMatrix();
	glEnd();
}

void Scene::Reflection() {
	// Save the current matrix state
	glPushMatrix();

	// Disable writing to the color buffer and enable stencil testing
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);

	// Set stencil function and operation
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// Disable depth testing and render the reflection floor
	glDisable(GL_DEPTH_TEST);
	ReflectionFloor();

	// Re-enable depth testing and restore color mask
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	// Set stencil function and operation for the reflected objects
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	// Save the matrix state and apply transformations for the reflected teapot
	glPushMatrix();
	glTranslatef(0.8f, -0.1f, 0.6f);
	glScalef(0.05f, 0.05f, 0.05f);
	glRotatef(ReflectionRotaion, 1, 0, 0);
	Teapot.render();
	glPopMatrix();

	// Disable stencil testing, enable blending, and render the reflection floor
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);
	ReflectionFloor();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);

	// Save the matrix state and apply transformations for the second reflected teapot
	glPushMatrix();
	glTranslatef(0.8f, -0.1f, -0.6f);
	glScalef(0.05f, 0.05f, 0.05f);
	glRotatef(ReflectionRotaion, -1, 0, 0);
	Teapot.render();
	glPopMatrix();

	// Restore the original matrix state
	glPopMatrix();
}



void Scene::StartingRoom() {
	// Render the main building
	glPushMatrix();
	startingBuilding.Building();
	glPopMatrix();

	// Render display stands and reflection stand
	glPushMatrix();
	startingBuilding.DisplayStand(8, 3);
	startingBuilding.DisplayStand(4, 3);
	startingBuilding.ReflectionStand(0, 3);
	// Render on the opposite side of the building
	startingBuilding.DisplayStand(8, -3);
	startingBuilding.DisplayStand(4, -3);
	startingBuilding.DisplayStand(0, -3);
	glPopMatrix();

	// Render NintendoDS object
	glPushMatrix();
	glRotatef(90, 0.2f, 1.0f, 0.0f);
	glTranslatef(12.0f, 1.0f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	material.MaterialSpecifics(1, 60);
	NintendoDS.render();
	glPopMatrix();

	// Render Doctor Octopus object
	glPushMatrix();
	glTranslatef(-24.0f, 1.2f, 13.0f);
	glRotatef(Rotation, 0, 1, 0);
	material.MaterialSpecifics(1, 100);
	DocOc.render();
	glPopMatrix();

	// Render Drone object
	glPushMatrix();
	glTranslatef(-24, 2, -12.0);
	glScalef(70.0f, 70.0f, 70.0);
	material.MaterialSpecifics(1, 100);
	Drone.render();
	glPopMatrix();

	// Render Radio object
	glPushMatrix();
	glTranslatef(-12, 1, -12);
	glScalef(0.4f, 0.4f, 0.4f);
	material.MaterialSpecifics(1, 100);
	Radio.render();
	glPopMatrix();
}


void Scene::RoomSpotlights() {
	// Spotlight 1: Above center position
	glPushMatrix();
	glTranslatef(0.0f, 5.0f, -12.0f);
	lighting.Spotlight(GL_LIGHT0);
	glPopMatrix();

	// Lamp for Spotlight 1
	glPushMatrix();
	glTranslatef(0.0f, 14.0f, -12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.03, 0.003, 0.03);
	lamp.render();
	glPopMatrix();

	// Spotlight 2: Above left position
	glPushMatrix();
	glTranslatef(-12.0f, 5.0f, -12.0f);
	lighting.ChangingSpotlight(ColorSwitcher);
	glPopMatrix();

	// Lamp for Spotlight 2
	glPushMatrix();
	glTranslatef(-12.0f, 14.0f, -12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.03, 0.003, 0.03);
	lamp.render();
	glPopMatrix();

	// Spotlight 3: Above far left position
	glPushMatrix();
	glTranslatef(-24.0f, 5.0f, -12.0f);
	lighting.Spotlight(GL_LIGHT1);
	glPopMatrix();

	// Lamp for Spotlight 3
	glPushMatrix();
	glTranslatef(-24.0f, 14.0f, -12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.03, 0.003, 0.03);
	lamp.render();
	glPopMatrix();

	// Spotlight 4: Above center position, opposite side
	glPushMatrix();
	glTranslatef(0.0f, 5.0f, 12.0f);
	lighting.Spotlight(GL_LIGHT2);
	glPopMatrix();

	// Lamp for Spotlight 4
	glPushMatrix();
	glTranslatef(0.0f, 14.0f, 12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.03, 0.003, 0.03);
	lamp.render();
	glPopMatrix();

	// Spotlight 5: Above left position, opposite side
	glPushMatrix();
	glTranslatef(-12.0f, 5.0f, 12.0f);
	lighting.Spotlight(GL_LIGHT3);
	glPopMatrix();

	// Lamp for Spotlight 5
	glPushMatrix();
	glTranslatef(-12.0f, 14.0f, 12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.03, 0.003, 0.03);
	lamp.render();
	glPopMatrix();

	// Spotlight 6: Above far left position, opposite side
	glPushMatrix();
	glTranslatef(-24.0f, 5.0f, 12.0f);
	lighting.Spotlight(GL_LIGHT5);
	glPopMatrix();

	// Lamp for Spotlight 6
	glPushMatrix();
	glTranslatef(-24.0f, 14.0f, 12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.03, 0.003, 0.03);
	lamp.render();
	glPopMatrix();
}

void Scene::OrbitSpaceShips() {
	// Spaceship 1
	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(Rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 2
	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(10 + Rotation, 0.2f, -1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 3
	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(30 + Rotation, 0.2f, -1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 4
	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(90 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 5
	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(100 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 6
	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(150 + Rotation, 0.2f, -1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 7
	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(120 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 8
	glPushMatrix();
	glScalef(1, 1, 1);
	material.MaterialSpecifics(0.5, 20);
	glRotatef(200 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 9
	glPushMatrix();
	glScalef(1, 1, 1);
	material.MaterialSpecifics(0.5, 20);
	glRotatef(200 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(80.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	// Spaceship 10
	glPushMatrix();
	glScalef(1, 1, 1);
	material.MaterialSpecifics(0.5, 20);
	glRotatef(2 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();
}



void Scene::solarSystem()
{
	// Light setup for the sun
	glPushMatrix();
	GLfloat Light_Diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat Light_Position[] = { 0.3, 0.0, 5.7, 1.0f };

	glLightfv(GL_LIGHT4, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT4, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 1);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 1);
	glEnable(GL_LIGHT4);
	glPopMatrix();

	glPushMatrix();
	// Materials
	glDisable(GL_COLOR_MATERIAL);
	GLfloat mat_diff_green[] = { 0.0, 0.6, 0.1, 1.0 };
	GLfloat mat_diff_purple[] = { 0.4, 0.0, 0.7, 1.0 };
	GLfloat mat_diff_blue[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_diff_grey[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat high_shininess = 100;

	// Sun
	glPushMatrix();
	glTranslatef(-12.0f, 3.0f, 12.0f);
	glRotatef(Rotation, 1,0, 0);
	glScalef(0.5, 0.5, 0.5);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 0);
	glBindTexture(GL_TEXTURE_2D, Earth);
	precuduallyGeneratedShapes.Sphere(60); // Function call to render a sphere
	glEnable(GL_LIGHTING);
	glPopMatrix();

	// Planet 1 - Blue
	glPushMatrix();
	glTranslatef(-12.5f, 3.5f, 12.0f);
	glRotatef(Rotation, 0, 1, 0);
	glTranslatef(2.0f, 0, 0);
	glScalef(0.5, 0.5, 0.5);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
	precuduallyGeneratedShapes.Sphere(60); // Function call to render a sphere
	glPopMatrix();

	// Planet 2 - Purple
	glPushMatrix();
	glTranslatef(-13.0f, 3.5f, 12.0f);
	glRotatef(Rotation, 0, 1, 0);
	glTranslatef(0.0f, -1, 0.0);

	glScalef(0.5, 0.5, 0.5);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_purple);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
	precuduallyGeneratedShapes.Sphere(60); // Function call to render a sphere
	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}


void Scene::OutsideSolarSystem()
{
	// Light setup for the sun
	glPushMatrix();
	GLfloat Light_Diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat Light_Position[] = { 0.3, 0.0, 5.7, 1.0f };

	glLightfv(GL_LIGHT4, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT4, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 1);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 1);
	glEnable(GL_LIGHT4);
	glPopMatrix();

	glPushMatrix();
	// Materials
	glDisable(GL_COLOR_MATERIAL);
	GLfloat mat_diff_green[] = { 0.0, 0.6, 0.1, 1.0 };
	GLfloat mat_diff_purple[] = { 0.4, 0.0, 0.7, 1.0 };
	GLfloat mat_diff_blue[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_diff_grey[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat high_shininess = 100;

	// Sun
	glPushMatrix();
	glTranslatef(-10.0f, 29.0f, 4.0f);
	glRotatef(Rotation, 1, 0, 0);
	glScalef(7, 7, 7);
	glDisable(GL_LIGHTING);
	glColor3f(0.1, 0.1, 0.1);
	glBindTexture(GL_TEXTURE_2D, SATRUN);
	precuduallyGeneratedShapes.Sphere(60); // Function call to render a sphere
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Scene::cameraSwitcher() {

	// Switcher == 0: Use the current camera position and orientation
	if (Switcher == 0) {
		gluLookAt(camera.getPosX(), camera.getPosY(), camera.getPosZ(),
			camera.getLookAtX(), camera.getLookAtY(), camera.getLookAtZ(),
			camera.getUpX(), camera.getUpY(), camera.getUpZ());
	}

	// Switcher == 1: Set a specific view for the first scenario
	if (Switcher == 1) {
		gluLookAt(-40.0f, 10.0f, -10.0f, 0, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
		// Reset the view if Switcher is not 1
		if (Switcher != 1) {
			gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		}
	}

	// Switcher == 2: Set a specific view for the second scenario
	if (Switcher == 2) {
		gluLookAt(40.0f, 10.0f, -10.0f, 0, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
		// Reset the view if Switcher is not 2
		if (Switcher != 2) {
			gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		}
	}

	// Switcher == 3: Set a specific view for the third scenario
	if (Switcher == 3) {
		gluLookAt(-7.0f, 1.0f, 18.0f, -10.0, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		// Reset the view if Switcher is not 3
		if (Switcher != 3) {
			gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		}
	}
}



void Scene::TrasnparentBox() {
	glEnable(GL_BLEND);
	glTranslatef(-24, 2, -12.0);
	glScalef(2.5, 2.5, 2.5);
	glColor4f(0.0f, 0.0f, 1.0f, 0.25);
	glBegin(GL_QUADS);
	// Front Face
	glNormal3f(0, 0, -1);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	// Right Face
	glNormal3f(1, 0, 0);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.75f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	// Bottom Face
	glNormal3f(0, -1, 0);
	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	// Left Face
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	// Top Face
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Back Face
	glNormal3f(0, 0, 1);
	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glDisable(GL_BLEND);
	glPopMatrix();
	glEnd();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	cameraSwitcher();
	// Render geometry/scene here -------------------------------------
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	DrawCube();
	glEnable(GL_DEPTH_TEST);
	glPopMatrix();
	RoomSpotlights();
	glPopMatrix();

	glPushMatrix();
	StartingRoom();
    glPopMatrix();

	glPushMatrix();
	OrbitSpaceShips();
	glPopMatrix();

	//glPushMatrix();
	////lighting.RoomLight();
	//glPopMatrix();


	glPushMatrix();
	solarSystem();
	glPopMatrix();

	glPushMatrix();
	Reflection();
	glPopMatrix();

	glPushMatrix();
	TrasnparentBox();
	glPopMatrix();

	glPushMatrix();
	OutsideSolarSystem();
	glPopMatrix();

	

	// End render geometry --------------------------------------
	glEnd();
	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);			
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blending function

}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	//sprintf_s(ObjectLocation,"location: %i, %i, %i", GetObjectForward(), GetObjectRight(), GetObjectUpward());

	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.86f, 1.f, 0.f, 0.f, ObjectLocation);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

