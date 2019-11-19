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
		if (coObjects->at(i)->getHealth() > 0)
		{
			if (isCollideWithOtherObject(coObjects->at(i)))
			{
				if (dynamic_cast<BigTorch*>(coObjects->at(i)) ||
					dynamic_cast<BreakableBrick*>(coObjects->at(i)))
				{
				coObjects->at(i)->lostHealth(1);
				}
			}
		}
	}
}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}
