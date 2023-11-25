#include"StartingBuilding.h"


 StartingBuilding::StartingBuilding(){
	 Floor = SOIL_load_OGL_texture(
		 "gfx/checked.png",
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	 Wall = SOIL_load_OGL_texture(
		 "gfx/Wall.png",
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	 Stand = SOIL_load_OGL_texture(
		 "gfx/Stand.png",
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}
void StartingBuilding::Building() {
	
	glScalef(80, 20, 40);
	glTranslatef(0, 0.3, 0);
	glBindTexture(GL_TEXTURE_2D, Wall);
	glBegin(GL_QUADS);

	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	//Right Face
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.75f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	
	glBindTexture(GL_TEXTURE_2D, Floor);
	glBegin(GL_QUADS);
	//Bottom Face
	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, Wall);
	glBegin(GL_QUADS);
	//Left Face
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);


	//Top Face
	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	//Back Face
	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();
	


}


void StartingBuilding::DisplayStand(int x, int z) {
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glScalef(4, 3, 4);
	glTranslatef(-0.4, x, z);
	glBindTexture(GL_TEXTURE_2D, Stand);
	glBegin(GL_QUADS);

	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	//Right Face
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.75f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	//Bottom Face
	glTexCoord2f(0.25f, 0.75f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.75f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.75f, 1.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	//Left Face
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.25f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);


	//Top Face
	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.25f, 0.25f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	//Back Face
	glTexCoord2f(1.0f, 0.25f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.25f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.75f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();
	glPopMatrix();

}