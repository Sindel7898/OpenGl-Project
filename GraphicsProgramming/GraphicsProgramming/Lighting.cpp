#include "Lighting.h"

void Lighting::Spotlight(GLenum LightName)
{
	glPushMatrix();
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = {0.0f, 0.1f, 0.0f, 1.0f };
	GLfloat Light_Ambient[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Spot_Direction[] = { 0.0f, -1.0f, 0.0f };

	glLightfv(LightName, GL_DIFFUSE, Light_Diffuse);
	glLightfv(LightName, GL_POSITION, Light_Position);
	glLightfv(LightName, GL_AMBIENT, Light_Ambient);
	glLightfv(LightName, GL_SPOT_DIRECTION, Spot_Direction);
	glLightf(LightName, GL_SPOT_CUTOFF, 75.0f);
	glLightf(LightName, GL_SPOT_EXPONENT, 10.0f);
	glEnable(LightName);
	glPopMatrix();

}


void Lighting::ChangingSpotlight(int Switcher)
{

	switch (Switcher)
	{
	default:
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		Alpha = 1.0f;
	break;

	case 1: 
		    r = 1.0f;
	     	g = 0.0f;
		    b = 0.0f;
		    Alpha = 1.0f;
		break;
	
	case 2: 
		r = 1.0f;
		g = 0.0f;
		b = 1.0f;
		Alpha = 1.0f;
		break;

	case 3:
		r = 0.0f;
		g = 0.0f;
		b = 1.0f;
		Alpha = 1.0f;
		break;
	}
	glPushMatrix();
	GLfloat Light_Diffuse[] = { r, g, b, Alpha };
	GLfloat Light_Position[] = { 0.0f, 0.1f, 0.0f, 1.0f };
	GLfloat Light_Ambient[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat Spot_Direction[] = { 0.0f, -1.0f, 0.0f };

	glLightfv(GL_LIGHT6, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT6, GL_POSITION, Light_Position);
	glLightfv(GL_LIGHT6, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, Spot_Direction);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 75.0f);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 10.0f);
	glEnable(GL_LIGHT6);
	glPopMatrix();

}

void Lighting:: RoomLight()
{
	/*glPushMatrix();
	GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 0.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 3.0f, 0.0f, 3.0f, 1.0f };

	glLightfv(GL_LIGHT7, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT7, GL_POSITION, Light_Position);

	glEnable(GL_LIGHT7);
	glPopMatrix();*/
}

