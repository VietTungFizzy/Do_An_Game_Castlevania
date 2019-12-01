#pragma once
#include "GameObject.h"

#define FIREBALL_BBOX_WIDTH 7
#define FIREBALL_BBOX_HEIGHT 6
#define FIREBALL_MOVING_SPEED 0.21f
#define FIREBALL_SPRITE_ID 0
class Fireball :
	public CGameObject
{
private:
	LPSPRITE sprite;
	int direction;
public:
	Fireball(float x, float y,int direction);
	~Fireball();

	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};

