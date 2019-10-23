#include "Weapon.h"



void Weapon::InitialAttack(float x, float y)
{
	isOn = true;
	this->x = x;
	this->y = y;
}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}
