#include "WorkingCamera.h"

void Camera::update(float dt) {
	float cosR, cosP, cosY;
	float sinR, sinP, sinY;

	cosP = cosf(degToRad(pitch));
	cosY = cosf(degToRad(yaw));
	cosR = cosf(degToRad(roll));

	sinP = sinf(degToRad(pitch));
	sinY = sinf(degToRad(yaw));
	sinR = sinf(degToRad(roll));


	forwardVector.x = sinY * cosP;
	forwardVector.y = sinP;
	forwardVector.z = cosP * -cosY;

	upVector.x = -cosY * sinR - sinY * sinP * cosR;
	upVector.y = cosP * cosR;
	upVector.z = -sinY * sinR - sinP * cosR * -cosY;
}

float Camera::degToRad(float deg) {
	return(deg * 3.1415 / 180);
}