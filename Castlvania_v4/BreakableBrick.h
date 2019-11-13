#pragma once
#include "GameObject.h"
class BreakableBrick :
	public CGameObject
{
private:
	LPSPRITE sprite;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	BreakableBrick(float x, float y, int w, int h, int type);
	~BreakableBrick();
};

