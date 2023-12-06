#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)							
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	// Initialise scene variables
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);



	Teapot.load("models/teapot.obj", "gfx/crate.png");
	NintendoDS.load("models/N_3DS.obj", "gfx/Mt_Rolling3DS_01.png");
	SpaceShip.load("models/spaceship.obj", "gfx/spaceship.JPG");
	//lamp.load("models/lamp.obj", "gfx/wood.JPG");
	Drone.load("models/drone.obj", "gfx/Drone.JPG");
	Radio.load("models/Radio.obj", "gfx/Radio.PNG");
	DocOc.load("models/Doctor Octopus.obj", "gfx/body.PNG");





	SKYBOX = SOIL_load_OGL_texture(
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	ISoundEngine* engine = createIrrKlangDevice();
	ISound* music1 = engine->play3D("Music/jazz.mp3", vec3df(13, 0, 0), true, false, true);
	music1->setVolume(20);
}

void Scene::handleInput(float dt)
{
	// Handle user input

	if (input->isKeyDown('l') || input->isKeyDown('L')) {
		ColorSwitcher++;

		if (ColorSwitcher > 3) {
			ColorSwitcher = 0;
		}
		input->setKeyUp('l');
		input->setKeyUp('L');
	}
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

	xDiff = input->getMouseX() - (width / 2);
	yDiff = input->getMouseY() - (height / 2);
	if (xDiff != 0 || yDiff != 0)
	{
		camera.controlMouse(dt, xDiff, yDiff);
	}
	camera.update();

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


void Scene::DrawCube() {
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, SKYBOX);
	if (Switcher == 3) {
		glTranslatef(-40, 90, -10);
	}
	else
	{
		glTranslatef(camera.getPosX(), camera.getPosY(), camera.getPosZ());

	}
	/*skybox.drawSkybox();*/
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
	glPushMatrix();
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);

	ReflectionFloor();


	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);


	glPushMatrix();
	glTranslatef(0.8f, -0.1f, 0.6f);
	glScalef(0.05f, 0.05f, 0.05f);
	glRotatef(ReflectionRotaion, 1, 0, 0);
	Teapot.render();
	glPopMatrix();

	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glColor4f(0.8f, 0.8f, 1.0f, 0.8f);
	ReflectionFloor();
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glPushMatrix();
	glTranslatef(0.8f, -0.1f, -0.6f);
	glScalef(0.05f, 0.05f, 0.05f);
	glRotatef(ReflectionRotaion, -1, 0, 0);
	Teapot.render();
	glPopMatrix();

	glPopMatrix();


}
void Scene::StartingRoom() {

	glPushMatrix();
	startingBuilding.Building();
	glPopMatrix();

	glPushMatrix();
	startingBuilding.DisplayStand(8, 3);
	startingBuilding.DisplayStand(4, 3);
	startingBuilding.ReflectionStand(0, 3);
	//opposite side of building
	startingBuilding.DisplayStand(8, -3);
	startingBuilding.DisplayStand(4, -3);
	startingBuilding.DisplayStand(0, -3);
	glPopMatrix();

	
	glPushMatrix();
	glRotatef(90, 0.2f, 1.0f, 0.0f);
	glTranslatef(12.0f, 1.0f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	material.MaterialSpecifics(1, 60);
	NintendoDS.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24.0f, 1.2f, 13.0f);
	glRotatef(Rotation, 0, 1, 0);
	material.MaterialSpecifics(1, 100);
	DocOc.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24, 2, -12.0);
	glScalef(70.0f, 70.0f, 70.0);
	material.MaterialSpecifics(1, 100);
	Drone.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12, 1, -12);
	glScalef(0.4f, 0.4f, 0.4f);
	material.MaterialSpecifics(1, 100);
	Radio.render();
	glPopMatrix();


	


}

void Scene::RoomSpotlights() {

	glPushMatrix();
	glTranslatef(0.0f, 5.0f, -12.0f);
	lighting.Spotlight(GL_LIGHT0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.0f, -12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.1, 0.1, 0.1);
	lamp.render();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-12.0f, 5.0f, -12.0f);
	lighting.ChangingSpotlight(ColorSwitcher);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12.0f, 4.0f, -12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.1, 0.1, 0.1);
	lamp.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24.0f, 5.0f, -12.0f);
	lighting.Spotlight(GL_LIGHT1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24.0f, 4.0f, -12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.1, 0.1, 0.1);
	lamp.render();
	glPopMatrix();
	

	glPushMatrix();
	glTranslatef(0.0f, 5.0f, 12.0f);
	lighting.Spotlight(GL_LIGHT2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.1, 0.1, 0.1);
	lamp.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12.0f, 5.0f, 12.0f);
	lighting.Spotlight(GL_LIGHT3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-12.0f, 4.0f, 12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.1, 0.1, 0.1);
	lamp.render();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24.0f, 4.0f, 12.0f);
	lighting.Spotlight(GL_LIGHT5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24.0f, 4.0f, 12.0f);
	material.MaterialSpecifics(1, 60);
	glScalef(0.1, 0.1, 0.1);
	lamp.render();
	glPopMatrix();


}
void Scene::OrbitSpaceShips() {
	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(Rotation, 0.0f, 0.0f, 1.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(10 + Rotation, 0.2f, -1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(30 + Rotation, 0.2f, -1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(90 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(100 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(150 + Rotation, 0.2f, -1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(120 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1);
	material.MaterialSpecifics(0.5, 20);
	glRotatef(200 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 1, 1);
	material.MaterialSpecifics(0.5, 20);
	glRotatef(200 + Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(80.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();

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
	glScalef(1.0, 1.0, 1.0);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 0);
	gluSphere(gluNewQuadric(), 0.5, 40, 40);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	// Planet 1 - Blue
	glPushMatrix();
	glTranslatef(-11.6f, 3.5f, 12.0f);
	glScalef(0.7, 0.7, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
	gluSphere(gluNewQuadric(), 0.5, 40, 40);
	glPopMatrix();

	// Planet 2 - Purple
	glPushMatrix();
	glTranslatef(-12.6f, 3.5f, 12.0f);
	glScalef(0.7, 0.7, 0.7);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_purple);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
	gluSphere(gluNewQuadric(), 0.5, 40, 40);
	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

void Scene::cameraSwitcher() {

	if (Switcher == 0) {
		gluLookAt(camera.getPosX(), camera.getPosY(), camera.getPosZ(), camera.getLookAtX(), camera.getLookAtY(), camera.getLookAtZ(), camera.getUpX(), camera.getUpY(), camera.getUpZ());

	}

	if (Switcher == 1) {
		gluLookAt(-40.0f, 10.0f, -10.0f, 0, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
		if (Switcher != 1) {
			gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		}
	}


	if (Switcher == 2) {
		gluLookAt(40.0f, 10.0f, -10.0f, 0, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
		if (Switcher != 2) {
			gluLookAt(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		}
	}
	
	if (Switcher == 3) {
		gluLookAt(-40.0f, 90.0f, -10.0f, 0, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
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

	glPushMatrix();
	//lighting.RoomLight();
	glPopMatrix();


	glPushMatrix();
	solarSystem();
	glPopMatrix();

	glPushMatrix();
	Reflection();
	glPopMatrix();

	glPushMatrix();
	TrasnparentBox();
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

