#include"PreceduallyGeneratedShapes.h"


void PrecuduallyGeneratedShapes :: Sphere(int resolution)
{
	m_resolution = resolution + 1;

	float theta = (2 * 3.1415) / resolution;
	float delta = 3.1415 / resolution;
	float angle_lon = 0;
	float angle_lat = 0;
	float next_lon = 0;
	float next_lat = 0;


	glBegin(GL_QUADS);

	for (int lon = 0; lon < m_resolution; lon++)
	{
		for (int lat = 0; lat < m_resolution; lat++)
		{
			next_lat = angle_lat + theta;

			//[lat][long]
			glNormal3f(cos(angle_lat) * sin(angle_lon), cos(angle_lon), sin(angle_lat) * sin(angle_lon));
			glVertex3f(cos(angle_lat) * sin(angle_lon), cos(angle_lon), sin(angle_lat) * sin(angle_lon));

			//[lat][long + 1] 
			glNormal3f(cos(next_lat) * sin(angle_lon), cos(angle_lon), sin(next_lat) * sin(angle_lon));
			glVertex3f(cos(next_lat) * sin(angle_lon), cos(angle_lon), sin(next_lat) * sin(angle_lon));

			//[lat + 1][long + 1] 
			glNormal3f(cos(next_lat) * sin(next_lon), cos(next_lon), sin(next_lat) * sin(next_lon));
			glVertex3f(cos(next_lat) * sin(next_lon), cos(next_lon), sin(next_lat) * sin(next_lon));


			//[lat + 1][lon]
			glNormal3f(cos(angle_lat) * sin(next_lon), cos(next_lon), sin(angle_lat) * sin(next_lon));
			glVertex3f(cos(angle_lat) * sin(next_lon), cos(next_lon), sin(angle_lat) * sin(next_lon));


			angle_lat = next_lat;
		}
		angle_lon = next_lon;
		next_lon = angle_lon + delta;
	}
	glEnd();
}


