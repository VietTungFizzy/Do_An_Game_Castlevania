#pragma once
#include "GameObject.h"
class ObjectHidden :
	public CGameObject
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	ObjectHidden(float x, float y, float w, float h);
	~ObjectHidden();
};

