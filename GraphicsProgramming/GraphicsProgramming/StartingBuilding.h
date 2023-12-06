#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Material.h"

class StartingBuilding {
	public:
	Material material;
	StartingBuilding();
	void DisplayStand(int x, int z);
	void ReflectionStand(int x, int z);
	GLint Floor;
	GLint Wall;
	GLint Stand;
	void Building();
	int RoofRemover = 0 ;
	
};