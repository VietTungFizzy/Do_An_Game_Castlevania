#pragma once
#include "GameObject.h"
class Weapon :
	public CGameObject
{
protected:
	int direction;
	bool isCollisionChecked;
public:
	bool isOn;
	bool isSimonSitting;
public:
	virtual void InitialAttack(float x, float y,int direction);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera) =0;
	Weapon();
	~Weapon();
};

