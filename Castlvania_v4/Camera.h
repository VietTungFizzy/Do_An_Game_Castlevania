#pragma once
#include"Define.h"

#define CAMERA_MOVING_SPEED 0.12f
class Camera
{
private:
	float x, y;
	float boundaryLeft, boundaryRight;
	float posToGo;
	float savedX;
	float distance;
	float vx;
	
public:
	bool isAutoGo;
	bool isFollowingSimon;
public:
	void SetPosition(float x, float y)	{ this->x = x, this->y = y; }
	float getX()						{ return x; }
	float getY()						{ return y; }
	int getBoundaryLeft()				{ return boundaryLeft; }
	int getBoundaryRight()				{ return boundaryRight; }
	void setBoundary(int left, int right) { this->boundaryLeft = left, this->boundaryRight = right; }

	void Update(DWORD dt);
	D3DXVECTOR2 translateWorldToScreen(float xWorld, float yWorld);
	void setAutoGo(float posToGo);
	Camera(float boundaryLeft,float boundaryRight);
	~Camera();
};

