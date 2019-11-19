#pragma once
#include "ObjectHidden.h"
class InitialStairEvent :
	public ObjectHidden
{
private:
	//Direction Simon has to face when use stair from this special object's position
	int directionY;
	int directionX;

	float stairPositionX;
	float stairPositionY;
public:
	int getDirectionY() { return directionY; }
	int getDirectionX() { return directionX; }
	float getStairPositionX() { return stairPositionX; }
	float getStairPositionY() { return stairPositionY; }
	InitialStairEvent(float x, float y, float w, float h,int directionY,int directionX, float stairPositionX,float stairPositionY);
	~InitialStairEvent();
};

