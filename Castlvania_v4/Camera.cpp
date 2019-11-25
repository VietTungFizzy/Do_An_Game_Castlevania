#include "Camera.h"


void Camera::Update(DWORD dt)
{
	if (isAutoGo)
	{
		float distanceWalked = abs(x - savedX);
		if (distanceWalked >= this->distance)
		{
			x = posToGo;
			isAutoGo = false;
		}
		else
		{
			x += (vx * dt);
		}
	}
	else
	{
		if (x < boundaryLeft) x = boundaryLeft;
		if (x > boundaryRight) x = boundaryRight;
	}
}

D3DXVECTOR2 Camera::translateWorldToScreen(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - x, yWorld - y);
}

void Camera::setAutoGo(float posToGo)
{
	this->posToGo = posToGo;
	isAutoGo = true;
	savedX = x;
	distance = abs(x - posToGo);
	if(this->posToGo - posToGo > 0)
		vx = -CAMERA_MOVING_SPEED;
	else
		vx = CAMERA_MOVING_SPEED;
}

Camera::Camera(float boundaryLeft, float boundaryRight)
{
	this->boundaryLeft = boundaryLeft;
	this->boundaryRight = boundaryRight;
	vx = 0;
	isAutoGo = false;
}

Camera::~Camera()
{
}
