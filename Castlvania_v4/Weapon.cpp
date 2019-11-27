#include "Weapon.h"
#include"BigTorch.h"
#include"BreakableBrick.h"

void Weapon::InitialAttack(float x, float y,int directionX)
{
	isOn = true;
	isWeaponSpawned = false;
	this->x = x;
	this->y = y;
	this->directionX = directionX;
	isCollisionChecked = false;
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (isHit(coObjects->at(i)))
		{
			if (dynamic_cast<BigTorch*>(coObjects->at(i)) ||
				dynamic_cast<BreakableBrick*>(coObjects->at(i)))
			{
				coObjects->at(i)->lostHealth(1);
			}
		}
	}
}


bool Weapon::isHit(LPGAMEOBJECT obj)
{
	if (obj->getHealth() <= 0 || isOn ==false) return false;
	
	if (isWeaponSpawned && isCollisionChecked == false)
	{
		bool isCollided =  isCollideWithOtherObject(obj);
		if (isCollided) isCollisionChecked = true;
		return isCollided;
	}
	return false;
}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}
