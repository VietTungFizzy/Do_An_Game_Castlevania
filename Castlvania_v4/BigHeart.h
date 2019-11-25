#pragma once
#include "Item.h"
#define BIG_HEART_SPRITE_ID 1
#define BIG_HEART_BBOX_WIDTH 11
#define BIG_HEART_BBOX_HEIGHT 10
#define BIG_HEART_OFFSET_X 5
#define BIG_HEART_OFFSET_Y 5
class BigHeart :
	public Item
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	BigHeart(float x, float y);
	~BigHeart();
};

