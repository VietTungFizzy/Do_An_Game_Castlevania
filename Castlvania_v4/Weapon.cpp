#include "Weapon.h"



void Weapon::InitialAttack(float x, float y,int direction)
{
	isOn = true;
	this->x = x;
	this->y = y;
	this->direction = direction;
}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}
