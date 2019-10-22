#pragma once
#include"Define.h"
class Camera
{
	float x, y;
	float boundaryLeft, boundaryRight;
public:
	void SetPosition(float x, float y)	{ this->x = x, this->y = y; }
	float getX()						{ return x; }
	float getY()						{ return y; }
	int getBoundaryLeft()				{ return boundaryLeft; }
	int getBoundaryRight()				{ return boundaryRight; }

	void Update(DWORD dt);
	D3DXVECTOR2 translateWorldToScreen(float xWorld, float yWorld);
	Camera(float boundaryLeft,float boundaryRight);
	~Camera();
};

