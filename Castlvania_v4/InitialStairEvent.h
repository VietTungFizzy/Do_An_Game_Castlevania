#pragma once
#include "ObjectHidden.h"
class InitialStairEvent :
	public ObjectHidden
{
private:
	//Direction Simon has to face when use stair from this special object's position
	int directionY;
	int directionX;
	float stairPosition;
public:
	int getDirectionY() { return directionY; }
	int getDirectionX() { return directionX; }
	float getStairPosition() { return stairPosition; }
	InitialStairEvent(float x, float y, float w, float h,int directionY,int directionX, float stairPosition);
	~InitialStairEvent();
};

