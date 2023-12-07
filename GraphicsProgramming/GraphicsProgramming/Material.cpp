#include "Material.h"

// Function to set material properties for a specific material with given specular and shininess values
void Material::MaterialSpecifics(float specular, int shininess) {
	// Define the specular material property (RGB and alpha)
	GLfloat mat_specular[] = { specular, specular, specular, specular };

	// Set the shininess property
	GLfloat Shine = shininess;

	// Set the specular material property using OpenGL function
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	// Set the shininess property using OpenGL function
	glMateriali(GL_FRONT, GL_SHININESS, Shine);
}
