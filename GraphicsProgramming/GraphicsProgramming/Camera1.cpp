#include "Camera.h"
//majority of code in this are from the video provided on the mylearning space and LOTS AND LOTS of help from the 2 lecturers in the graphics programming module (2023)

Camera::Camera() {
	lookAt = Vector3(0.0f, 0.0f, 0.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
	position = Vector3(0.0f, 0.0f, 6.0f);

}
void Camera::update()
{
		// handle rotation 
		// YAW = LEFT to RIGHT. PITCH = UP and DOWN Roll = tilting your head
	cosY = cosf(Yaw * 3.1415 / 180);
	sinY = sinf(Yaw * 3.1415 / 180);
	sinP = sinf(Pitch * 3.1415 / 180);
	cosP = cosf(Pitch * 3.1415 / 180);
	cosR = cosf(Roll * 3.1415 / 180);
	sinR = sinf(Roll * 3.1415 / 180);

	// Calculate the three vectors to put into  glu Lookat 
	// Look direction, position and the up vector 
	// This function could also calculate the right vector

	lookAt.x = position.x + forward.x;
	lookAt.y = position.y + forward.y;
	lookAt.z = position.z + forward.z;

	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.
	// Up Vector 
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;


	// Side Vector (right)
	right = forward.cross(up);



}

//below functions self explanitory for moving
void Camera::moveForward(float dt)
{
	position.x = position.x + forward.x * dt * movespeed;
	position.z = position.z + forward.z * dt * movespeed;
}
void Camera::moveBackwords(float dt)
{
	position.x = position.x - forward.x * dt * movespeed;
	position.z = position.z - forward.z * dt * movespeed;

}
void Camera::moveLeft(float dt)
{
	position.x = position.x - right.x * dt * movespeed;
	position.z = position.z - right.z * dt * movespeed;
}
void Camera::moveRight(float dt)
{
	position.x = position.x + right.x * dt * movespeed;
	position.z = position.z + right.z * dt * movespeed;
}
void Camera::moveUp(float dt)
{
	position.y = position.y + up.y * dt * movespeed;
}
void Camera::moveDown(float dt)
{
	position.y = position.y - up.y * dt * movespeed;
}

void Camera::setPitchYaw(float pi, float ya)
{
	Pitch = pi;
	Yaw = ya;
}

//Used for controling the mouse
void Camera::controlMouse(float dt, int xDiff, int yDiff)
{
	// if the difference for X is not equal to 0 then calculate the Yaw(left to right)
	if (xDiff != 0)
	{
		Yaw += -xDiff * dt * movespeed;
	}
	// if the difference for Y is not equal to 0 then calculate the Pitch(up and down)
	if (yDiff != 0)
	{
		Pitch -= yDiff * dt * movespeed;
	}
}

//Getters
float Camera::getPosX()
{
	return position.x;
}
float Camera::getPosY()
{
	return position.y;
}
float Camera::getPosZ()
{
	return position.z;
}
float Camera::getLookAtX()
{
	return lookAt.x;
}
float Camera::getLookAtY()
{
	return lookAt.y;
}
float Camera::getLookAtZ()
{
	return lookAt.z;
}
float Camera::getUpX()
{
	return up.x;
}
float Camera::getUpY()
{
	return up.y;
}
float Camera::getUpZ()
{
	return up.z;
}