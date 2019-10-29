#include "MoneyBag.h"

void MoneyBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + MONEY_BAG_BBOX_WIDTH;
	bottom = top + MONEY_BAG_BBOX_HEIGHT;
}

MoneyBag::MoneyBag(float x, float y, int type)
{
	this->x = x;
	this->y = y;
	fireAnimation = CAnimations::GetInstance()->Get(EFFECT_SPARK);
	spark = CSprites::GetInstance()->Get(EFFECT, SPARK_SPRITE_ID);
	effectTimeDisplayed = 0;
	itemTiemDisplayed = 0;
	isOn = true;
	isItemSpawned = false;

	switch (type)
	{
	case 1:
		sprite = CSprites::GetInstance()->Get(ITEM, MONEY_BAG_TYPE1_SPRITE_ID);
		break;
	case 2:
		sprite = CSprites::GetInstance()->Get(ITEM, MONEY_BAG_TYPE2_SPRITE_ID);
		break;
	case 3:
		sprite = CSprites::GetInstance()->Get(ITEM, MONEY_BAG_TYPE3_SPRITE_ID);
		break;
	default:
		DebugOut(L"type khong dung");
		break;
	}
	
	vy = ITEM_GRAVITY;
}

MoneyBag::~MoneyBag()
{
}
