#pragma once
#include "Item.h"
#define DAGGER_ITEM_SPRITE_ID 2
#define DAGGER_ITEM_BBOX_WIDTH 17
#define DAGGER_ITEM_BBOX_HEIGHT 9
class Dagger_Item :
	public Item
{
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Dagger_Item(float x, float y);
	~Dagger_Item();
};

