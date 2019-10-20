#pragma once
#include "GameObject.h"
#define BRICK_SPRITE_ID 0
class Brick :
	public CGameObject
{
private:
	LPSPRITE sprite;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	Brick(float x, float y, int w, int h);
	~Brick();
};

