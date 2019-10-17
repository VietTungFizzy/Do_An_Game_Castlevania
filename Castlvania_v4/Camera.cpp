#include "Camera.h"


void Camera::Update(DWORD dt)
{
	if (x < boundaryLeft) x = boundaryLeft;
	if (x > boundaryRight) x = boundaryRight;
}

D3DXVECTOR2 Camera::translateWorldToScreen(float xWorld, float yWorld)
{
	return D3DXVECTOR2(xWorld - x, yWorld - y);
}

Camera::Camera(int boundaryLeft, int boundaryRight)
{
	this->boundaryLeft = boundaryLeft;
	this->boundaryRight = boundaryRight;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
}

Camera::~Camera()
{
}
