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

	
	Lighting();
	void Lighting1();
protected:
	Input* input;
};