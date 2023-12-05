#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>


class Lighting {
public:
	float r;
	float g;
	float b;
	float Alpha;	
	void Spotlight(GLenum LightName);
	//void Spotlight1();
	void Spotlight1(GLenum LightName);
	void Spotlight2();
	void Spotlight3();
	void Spotlight4();
	void Spotlight5();

	void ChangingSpotlight(int colorSwitcher);
	void RoomLight();
	void sunlight();
	void ChangingSpotlight();
protected:
	Input* input;
};