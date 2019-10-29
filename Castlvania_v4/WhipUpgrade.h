#pragma once
#include "Item.h"
#define WHIP_UPGRADE_SPRITE_ID 0
#define WHIP_UPGRADE_BBOX_WIDTH 17
#define WHIP_UPGRADE_BBOX_HEIGHT 18

class WhipUpgrade :
	public Item
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	WhipUpgrade(float x, float y);
	~WhipUpgrade();
};

