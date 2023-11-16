#pragma once
#include "Vector3.h"
#include "Input.h"


class Camera {
public:
	void update();

	Vector3 up;
	Vector3 forward;
	Vector3 lookAt;
	Vector3 position;
	Vector3 right;

	float cosR, cosP, cosY;
	float sinR, sinP, sinY;
	float Roll, Pitch, Yaw;

	float movespeed = 15;


	float getPosX();
	float getPosY();
	float getPosZ();
	float getLookAtX();
	float getLookAtY();
	float getLookAtZ();
	float getUpX();
	float getUpY();
	float getUpZ();
	void CameraMovement(float dt);

	void moveForward(float dt);
	void moveBackwords(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);
	void moveUp(float dt);
	void moveDown(float dt);
	void setPitchYaw(float pi, float ya);
	void controlMouse(float dt, int xDiff, int yDiff);

	Camera();
};