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
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR_MATERIAL);


	Teapot.load("models/teapot.obj", "gfx/crate.png");
	NintendoDS.load("models/N_3DS.obj", "gfx/Mt_Rolling3DS_01.png");
	SpaceShip.load("models/spaceship.obj", "gfx/spaceship.JPG");

	
	SKYBOX = SOIL_load_OGL_texture(
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);


	Earth = SOIL_load_OGL_texture(
		"gfx/crate.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);



}

void Scene::handleInput(float dt)
{
	// Handle user input
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
	
	// Calculate FPS for output
	calculateFPS();
	camera.update();
}


void Scene::DrawCube() {
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, SKYBOX);
	glTranslatef(camera.getPosX(), camera.getPosY(), camera.getPosZ());
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

void Scene::StartingRoom() {

	glPushMatrix();
	startingBuilding.Building();
	glPopMatrix();

	glPushMatrix();
	startingBuilding.DisplayStand(8, 3);
	startingBuilding.DisplayStand(4, 3);
	startingBuilding.DisplayStand(0, 3);
	//opposite side of building
	startingBuilding.DisplayStand(8, -3);
	startingBuilding.DisplayStand(4, -3);
	startingBuilding.DisplayStand(0, -3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glScalef(0.2, 0.2, 0.2);
	Teapot.render();
	glPopMatrix();


	glPushMatrix();
	glRotatef(90, 0.2f, 1.0f, 0.0f);
	glTranslatef(12.0f, 2.0f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	//GLfloat mat_diff_blue[] = { 0.1, 0.5, 0.8, 1.0 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);

	GLfloat mat_diff_blue[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat high_shininess = 100;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, high_shininess);
	material.MaterialSpecifics(1, 60);

	NintendoDS.render();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.f, 0.2f, 1.0f, 0.0f);
	glTranslatef(-12.0f, 4.0f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	SpaceShip.render();
	glPopMatrix();
}

void Scene::Planet() {

	glPushMatrix();
	material.MaterialSpecifics(1, 60);
	glBindTexture(GL_TEXTURE_2D, Earth);
	glTranslatef(80, 10, 5.0f);
	gluSphere(gluNewQuadric(), 6, 300, 300);
	glPopMatrix();

	glPushMatrix();
	material.MaterialSpecifics(0.5, 20);
	glScalef(1, 1, 1);
	glRotatef(Rotation, 0.2f, 1.0f, 0.0f);
	glTranslatef(100.0f, 10.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	SpaceShip.render();
	glPopMatrix();


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

	
}


void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(camera.getPosX(), camera.getPosY(), camera.getPosZ(), camera.getLookAtX(), camera.getLookAtY(), camera.getLookAtZ(), camera.getUpX(), camera.getUpY(), camera.getUpZ());
	// Render geometry/scene here -------------------------------------
	glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	DrawCube();

	glEnable(GL_DEPTH_TEST);
	glPopMatrix();

	glPushMatrix();
	//lighting.Lighting1()
	lighting.RoomLight();
	glPopMatrix();

	glPushMatrix();
	StartingRoom();
    glPopMatrix();

	glPushMatrix();
	Planet();
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
