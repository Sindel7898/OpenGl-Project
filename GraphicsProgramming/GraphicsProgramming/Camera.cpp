#include "Camera.h"


Camera::Camera() {
	//gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	lookAt = Vector3(0.0f, 0.0f, 0.0f);
	up = Vector3(0.0f, 1.0f, 0.0f);
	position = Vector3(0.0f, 0.0f, 6.0f);

}
void Camera::update()
{

     // Handles rotation: YAW for LEFT to RIGHT, PITCH for UP and DOWN, and Roll for tilting your head
	cosY = cosf(Yaw * 3.1415 / 180);
	sinY = sinf(Yaw * 3.1415 / 180);
	sinP = sinf(Pitch * 3.1415 / 180);
	cosP = cosf(Pitch * 3.1415 / 180);
	cosR = cosf(Roll * 3.1415 / 180);
	sinR = sinf(Roll * 3.1415 / 180);

// Calculate the three vectors for use in gluLookAt:
// Look direction, position, and the up vector.
// This function can also determine the right vector.
	
	lookAt.x = position.x + forward.x;
	lookAt.y = position.y + forward.y;
	lookAt.z = position.z + forward.z;

	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Deriving the Look At Point involves adding the Forward Vector to the Camera position, along with the inclusion of the Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;


	// right vector
	right = forward.cross(up);



}

//move functions
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

//control mouse
void Camera::controlMouse(float dt, int xDiff, int yDiff)
{
// If the variance in X is non-zero, proceed to calculate the Yaw (left to right).

	if (xDiff != 0)
	{
		Yaw += -xDiff * dt * movespeed;
	}
// If the deviation in Y is not equal to 0, compute the Pitch (up and down).

	if (yDiff != 0)
	{
		Pitch -= yDiff * dt * movespeed;
	}
}

//Getter
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
