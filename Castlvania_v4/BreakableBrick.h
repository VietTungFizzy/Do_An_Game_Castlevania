#pragma once
#include "GameObject.h"
#include"Pebble.h"
#define PEBBLE_X(x) x + 8
#define PEBBLE_Y(y) y + 8
#define PEBBLE_1_VX -0.15f
#define PEBBLE_1_VY -0.25f
#define PEBBLE_2_VX 0.07f
#define PEBBLE_2_VY -0.22f
#define PEBBLE_3_VX 0.15f
#define PEBBLE_3_VY -0.2f
#define PEBBLE_4_VX 0.1f
#define PEBBLE_4_VY -0.3f
class BreakableBrick :
	public CGameObject
{
private:
	LPSPRITE sprite;
	vector<Pebble*> afterEffect;
	bool isDoneAfterEffect;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	BreakableBrick(float x, float y, int w, int h, int type);
	~BreakableBrick();
};

