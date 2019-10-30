#include "BigHeart.h"



void BigHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + BIG_HEART_BBOX_WIDTH;
	bottom = top + BIG_HEART_BBOX_HEIGHT;
}


BigHeart::BigHeart(float x, float y)
{
	this->x = x;
	this->y = y;

	fireAnimation = CAnimations::GetInstance()->Get(EFFECT_SPARK);
	spark = CSprites::GetInstance()->Get(EFFECT, SPARK_SPRITE_ID);
	effectTimeDisplayed = 0;
	itemTiemDisplayed = 0;
	isOn = false;
	isItemSpawned = false;
	sprite = CSprites::GetInstance()->Get(ITEM, BIG_HEART_SPRITE_ID);
	vy = ITEM_GRAVITY;
}


BigHeart::~BigHeart()
{
}
