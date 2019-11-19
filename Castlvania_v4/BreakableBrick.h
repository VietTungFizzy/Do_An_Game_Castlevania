#pragma once
#include "GameObject.h"
#include"Pebble.h"
class BreakableBrick :
	public CGameObject
{
private:
	LPSPRITE sprite;
	vector<Pebble*> afterEffect;
	bool isAllPebblesOutOfCameraSight;
	bool isDoneAfterEffect;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	BreakableBrick(float x, float y, int w, int h, int type);
	~BreakableBrick();
};

