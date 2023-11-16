#include "Lighting.h"
float Rotation = 0;

Lighting::Lighting() {
	glEnable(GL_LIGHTING);

}


void Lighting::Lighting1(){

	
	glPushMatrix();
	glTranslatef(0, 4, 0);
	GLfloat LightDiffusion[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat LightPosition[] = { 0.0f, 1.0f, -10.0f, 1.0f };
	GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat SpotDirection[] = { 0.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffusion);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 50.0f);
	glEnable(GL_LIGHT0);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	GLfloat mat_diff_blue[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLint shininess = 100;
	GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 0.0 };


	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diff_blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	gluSphere(gluNewQuadric(), 1.0, 100, 40);
	glPopMatrix();
}