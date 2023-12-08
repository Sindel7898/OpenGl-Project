#include "PreceduallyGeneratedShapes.h"

// Function to generate and render a textured sphere using OpenGL
void PrecuduallyGeneratedShapes::Sphere(int resolution)
{
    // Adjust the resolution to ensure the correct number of divisions
    m_resolution = resolution + 1;

    // Calculate angular increments for longitude and latitude
    float theta = (2 * 3.1415) / resolution;
    float delta = 3.1415 / resolution;

    // Initialize angles for longitude and latitude
    float angle_lon = 0;
    float angle_lat = 0;
    float next_lon = 0;
    float next_lat = 0;
    //
    // Begin rendering with OpenGL QUADS
    glBegin(GL_QUADS);

    // Nested loops to iterate over latitude and longitude divisions
    for (int lon = 0; lon < m_resolution; lon++)
    {
        for (int lat = 0; lat < m_resolution; lat++)
        {
            // Calculate the next latitude angle
            next_lat = angle_lat + theta;

            // Calculate texture coordinates based on normalized latitude and longitude
            float texCoordLon = static_cast<float>(lon) / (m_resolution - 1);
            float texCoordLat = static_cast<float>(lat) / (m_resolution - 1);

            // Set texture coordinates for the current quad
            glTexCoord2f(texCoordLon, texCoordLat);
            glTexCoord2f(texCoordLon + 1.0f / (m_resolution - 1), texCoordLat);
            glTexCoord2f(texCoordLon + 1.0f / (m_resolution - 1), texCoordLat + 1.0f / (m_resolution - 1));
            glTexCoord2f(texCoordLon, texCoordLat + 1.0f / (m_resolution - 1));

            // Set normals for the vertices of the quad
            glNormal3f(cos(angle_lat) * sin(angle_lon), cos(angle_lon), sin(angle_lat) * sin(angle_lon));
            glNormal3f(cos(next_lat) * sin(angle_lon), cos(angle_lon), sin(next_lat) * sin(angle_lon));
            glNormal3f(cos(next_lat) * sin(next_lon), cos(next_lon), sin(next_lat) * sin(next_lon));
            glNormal3f(cos(angle_lat) * sin(next_lon), cos(next_lon), sin(angle_lat) * sin(next_lon));

            // Set vertices for the quad
            glVertex3f(cos(angle_lat) * sin(angle_lon), cos(angle_lon), sin(angle_lat) * sin(angle_lon));
            glVertex3f(cos(next_lat) * sin(angle_lon), cos(angle_lon), sin(next_lat) * sin(angle_lon));
            glVertex3f(cos(next_lat) * sin(next_lon), cos(next_lon), sin(next_lat) * sin(next_lon));
            glVertex3f(cos(angle_lat) * sin(next_lon), cos(next_lon), sin(angle_lat) * sin(next_lon));

            // Update latitude angle for the next iteration
            angle_lat = next_lat;
        }

        // Update longitude angles for the next iteration
        angle_lon = next_lon;
        next_lon = angle_lon + delta;
    }

    // End rendering
    glEnd();
}
