#pragma once
#include "Item.h"
#define SPECIAL_MONEY_BAG_BBOX_WIDTH 14
#define SPECIAL_MONEY_BAG_BBOX_HEIGHT 15
#define SPECIAL_MONEY_BAG_RISING_SPEED -0.15f
class SpecialMoneyBag :
	public Item
{
private:
	bool isFinishedRising;
	LPANIMATION animation;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	SpecialMoneyBag(float x, float y);
	~SpecialMoneyBag();
};

