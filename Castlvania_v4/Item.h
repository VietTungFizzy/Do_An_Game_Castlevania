#pragma once
#include "GameObject.h"
class Item :
	public CGameObject
{
private:
	LPSPRITE sprite;
public:
	Item();
	~Item();
};

