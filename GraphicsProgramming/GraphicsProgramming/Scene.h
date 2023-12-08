// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include <irrKlang.h>
#include "model.h"
#include "Skybox.h"
#include "Camera1.h"
#include"StartingBuilding.h"
#include "Lighting.h"
#include "PreceduallyGeneratedShapes.h"
#include "material.h"
using namespace irrklang;
// for the audio system im using in this project  https://www.ambiera.com/irrklang/
class Scene{

public:
	Skybox skybox;
	Camera camera;
	StartingBuilding startingBuilding;
	Lighting lighting;
	GLint SKYBOX;
	GLint SKYBOX1;
	GLint SKYBOX2;
	GLint Earth;
	GLint SATRUN;
	Model Teapot;
	Model NintendoDS;
	Model SpaceShip;
	PrecuduallyGeneratedShapes precuduallyGeneratedShapes;
	Material material;
	Model lamp;
	Model Halo;
	Model Drone;
	Model Radio;
	Model DocOc;

	int SkyBoxChanger = 1;
	int ColorSwitcher;
	int renderType = 0;


	float right = 0 ;
	float upward = 0 ;
	float forward = 0;
	float ReflectionRotaion;
	int Switcher = 0;
	float Rotation;
	//GLuint SKYBOX;
	float xDiff = 0;
	float yDiff = 0;

	Scene(Input *in);
	void OrbitSpaceShips();
	void solarSystem();
	void OutsideSolarSystem();
	void cameraSwitcher();
	void TrasnparentBox();
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);
	void DrawCube();
	void RoomSpotlights();
	void ReflectionFloor();
	void Reflection();
	void StartingRoom();
protected:
	// configure opengl render pipeline
	void initialiseOpenGL();
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	char ObjectLocation[1000];
};

#endif