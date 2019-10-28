#include "Weapon.h"
#include"BigTorch.h"


void Weapon::InitialAttack(float x, float y,int direction)
{
	isOn = true;
	this->x = x;
	this->y = y;
	this->direction = direction;
	isCollisionChecked = false;
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<BigTorch*>(coObjects->at(i)))
		{
			if (coObjects->at(i)->getHealth() > 0)
			{
				if (isCollideWithOtherObject(coObjects->at(i)))
				{
					/*coObjects->at(i)->lostHealth(1);*/
					DebugOut(L"Hit ");
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
