#include "WhipUpgrade.h"

void WhipUpgrade::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + WHIP_UPGRADE_BBOX_WIDTH;
	bottom = top + WHIP_UPGRADE_BBOX_HEIGHT;
}

WhipUpgrade::WhipUpgrade(float x, float y)
{
	this->x = x;
	this->y = y;

	fireAnimation = CAnimations::GetInstance()->Get(EFFECT_SPARK);
	spark = CSprites::GetInstance()->Get(EFFECT, SPARK_SPRITE_ID);
	effectTimeDisplayed = 0;
	itemTiemDisplayed = 0;
	isOn = false;
	isItemSpawned = false;

	sprite = CSprites::GetInstance()->Get(ITEM, WHIP_UPGRADE_SPRITE_ID);
	vy = ITEM_GRAVITY;
}

WhipUpgrade::~WhipUpgrade()
{
}
