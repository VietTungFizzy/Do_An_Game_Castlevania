#pragma once
#include "GameObject.h"
class Weapon :
	public CGameObject
{
public:
	bool isOn;
public:
	virtual void InitialAttack(float x, float y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) =0;
	virtual void Render(Camera * camera) =0;
	Weapon();
	~Weapon();
};

