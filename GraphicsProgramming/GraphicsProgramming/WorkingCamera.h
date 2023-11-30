#pragma once
#include "Vector3.h"

class Camera {
public:
	Camera();
	Vector3 getPosition();
	Vector3 getLookAtVector();
	Vector3 getUpVector();

	void update(float dt);
	float degToRad(float deg);

protected:
	float pitch;
	float yaw;
	float roll;
	Vector3 currentPosition;
	Vector3 forwardVector;
	Vector3 upVector;
	float speed = 1.0f;
};