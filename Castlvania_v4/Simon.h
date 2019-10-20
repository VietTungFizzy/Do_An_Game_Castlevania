#pragma once
#include"GameObject.h"
class Simon :
	public CGameObject
{
private:
	int health;
	
public:
	bool isAttacking;
	bool isSitting;
	bool isFreazing;
	bool isWalking;
	bool isHurt;
	bool isInAir;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	Simon();
	~Simon();
};

