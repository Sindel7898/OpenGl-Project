#include "Lighting.h"

void Lighting::Spotlight()
{
	glPushMatrix();
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = {0.0f, 0.1f, 0.0f, 1.0f };
	GLfloat Light_Ambient[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Spot_Direction[] = { 0.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Spot_Direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 75.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
	glEnable(GL_LIGHT0);
	glPopMatrix();

}


void Lighting::Spotlight()
{
	glPushMatrix();
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 0.0f, 0.1f, 0.0f, 1.0f };
	GLfloat Light_Ambient[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Spot_Direction[] = { 0.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Spot_Direction);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 75.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 10.0f);
	glEnable(GL_LIGHT0);
	glPopMatrix();

}

void Lighting::RoomLight() {

	GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, Light_Position);
	glEnable(GL_LIGHT1);
}

