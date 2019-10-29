#include "Dagger_Item.h"

void Dagger_Item::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + DAGGER_ITEM_BBOX_WIDTH;
	bottom = top + DAGGER_ITEM_BBOX_HEIGHT;
}

Dagger_Item::Dagger_Item(float x, float y)
{
	this->x = x;
	this->y = y;
	fireAnimation = CAnimations::GetInstance()->Get(EFFECT_SPARK);
	spark = CSprites::GetInstance()->Get(EFFECT, DAGGER_ITEM_SPRITE_ID);
	effectTimeDisplayed = 0;
	itemTiemDisplayed = 0;
	isOn = true;
	isItemSpawned = false;
	vy = ITEM_GRAVITY;
}

Dagger_Item::~Dagger_Item()
{
}
