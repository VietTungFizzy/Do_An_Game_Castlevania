#pragma once
#include "GameObject.h"
#define PEBBLE_SPRITE_ID 4
#define PEBBLE_BBOX_WIDTH 7
#define PEBBLE_BBOX_HEIGHT 8
#define PEBBLE_OFFSET_X 3
#define PEBBLE_OFFSET_Y 3
#define PEBBLE_GRAVITY 0.0012f
class Pebble :
	public CGameObject
{
private:
	LPSPRITE sprite;

public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	Pebble(float x, float y, float vx,float vy);
	~Pebble();
};

