#pragma once
#include "GameObject.h"
class ObjectHidden :
	public CGameObject
{
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Camera * camera);
	ObjectHidden();
	ObjectHidden(float x, float y, float w, float h);
	~ObjectHidden();
};

