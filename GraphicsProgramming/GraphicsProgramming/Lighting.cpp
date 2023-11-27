#include "Lighting.h"
float Rotation = 0;

Lighting::Lighting() {
	glEnable(GL_LIGHTING);

}

void Lighting::Lighting1(){

	
	glPushMatrix();
	glRotatef(Rotation, 0, 1, 0);
	glTranslatef(0, 10, 0);
	glDisable(GL_COLOR_MATERIAL);

	GLfloat LightDiffusion[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat SpotDirection[] = { 0.0f, -1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffusion);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0f);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	

	
	glScalef(0.1f, 0.1f, 0.1f);
	GLfloat mat_diff_blue[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLint shininess = 100;
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 0.0 };


	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	gluSphere(gluNewQuadric(), 4.0, 100, 40);
}


void Lighting::RoomLight()
{
	glPushMatrix();
	glRotatef(Rotation, 0, 1, 0);
	glTranslatef(0, 10, 0);
	glDisable(GL_COLOR_MATERIAL);

	GLfloat Light_Ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Ambient);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 10);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 10);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 10);
	glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);

	glScalef(0.1f, 0.1f, 0.1f);
	GLfloat mat_diff_blue[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLint shininess = 100;
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 0.0 };


	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	gluSphere(gluNewQuadric(), 4.0, 100, 40);
	glPopMatrix();
}