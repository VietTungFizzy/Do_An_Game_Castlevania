#pragma once
#include "GameObject.h"
class Weapon :
	public CGameObject
{
protected:
	int directionX;
	bool isCollisionChecked;
public:
	bool isOn;
	bool isSimonSitting;
	bool isWeaponSpawned;
public:
	virtual void InitialAttack(float x, float y,int directionX);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera) =0;
	Weapon();
	~Weapon();
};

