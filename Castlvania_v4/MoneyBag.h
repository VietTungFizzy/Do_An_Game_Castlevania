#pragma once
#include "Item.h"
#define MONEY_BAG_TYPE1_SPRITE_ID 13
#define MONEY_BAG_TYPE2_SPRITE_ID 14
#define MONEY_BAG_TYPE3_SPRITE_ID 15
#define MONEY_BAG_BBOX_WIDTH 14
#define MONEY_BAG_BBOX_HEIGHT 15
class MoneyBag :
	public Item
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	MoneyBag(float x, float y, int type);
	~MoneyBag();
};

