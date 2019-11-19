#include "InitialStairEvent.h"

InitialStairEvent::InitialStairEvent(float x, float y, float w, float h, int directionY, int directionX, float stairPositionX, float stairPositionY)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->directionY = directionY;
	this->directionX = directionX;
	this->stairPositionX = stairPositionX;
	this->stairPositionY = stairPositionY;
}

InitialStairEvent::~InitialStairEvent()
{
}
