#include "ObjectHidden.h"


void ObjectHidden::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + w;
	bottom = top + h;
}

void ObjectHidden::Render(Camera * camera)
{
	RenderBoundingBox(camera);
}

ObjectHidden::ObjectHidden(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	health = -1;
}

ObjectHidden::~ObjectHidden()
{
}
