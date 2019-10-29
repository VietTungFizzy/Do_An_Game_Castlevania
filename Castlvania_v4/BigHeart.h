#pragma once
#include "Item.h"
#define BIG_HEART_SPRITE_ID 1
#define BIG_HEART_BBOX_WIDTH 12
#define BIG_HEART_BBOX_HEIGHT 10

class BigHeart :
	public Item
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	BigHeart(float x, float y);
	~BigHeart();
};

