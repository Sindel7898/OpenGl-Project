#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>

class PrecuduallyGeneratedShapes
{
public:
	
	GLint Earth;
	int m_resolution = 0;
	void Sphere(int resolution);
	float rotation;
	void solarSystem();

};

