#include"PreceduallyGeneratedShapes.h"

void PrecuduallyGeneratedShapes::Sphere(float r) {
	glPushMatrix();
	glTranslatef(3, 0, 0);
	glBindTexture(GL_TEXTURE_2D, NULL);
	float pi = 3.141592;
	float di = 0.02;
	float dj = 0.04;
	float db = di * 2 * pi;
	float da = dj * pi;


	for (float i = 0; i < 1.0; i += di) //horizonal
		for (float j = 0; j < 1.0; j += dj) //vertical
		{
			float b = i * 2 * pi;      //0     to  2pi
			float a = (j - 0.5) * pi;  //-pi/2 to pi/2


			//normal
			glNormal3f(
				cos(a + da / 2) * cos(b + db / 2),
				cos(a + da / 2) * sin(b + db / 2),
				sin(a + da / 2));

			glBegin(GL_QUADS);
			//P1
			glTexCoord2f(i, j);
			glVertex3f(
				r * cos(a) * cos(b),
				r * cos(a) * sin(b),
				r * sin(a));
			//P2
			glTexCoord2f(i + di, j);//P2
			glVertex3f(
				r * cos(a) * cos(b + db),
				r * cos(a) * sin(b + db),
				r * sin(a));
			//P3
			glTexCoord2f(i + di, j + dj);
			glVertex3f(
				r * cos(a + da) * cos(b + db),
				r * cos(a + da) * sin(b + db),
				r * sin(a + da));
			//P4
			glTexCoord2f(i, j + dj);
			glVertex3f(
				r * cos(a + da) * cos(b),
				r * cos(a + da) * sin(b),
				r * sin(a + da));
		}
	
	glPopMatrix();

}