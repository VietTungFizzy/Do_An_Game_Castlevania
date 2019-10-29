#pragma once
#include "GameObject.h"
#define SPARK_SPRITE_ID 0
#define SPARK_TIME_DISPLAY_MAX 150
#define FIRE_TIME_DISPLAY_MAX 300
#define ITEM_TIME_DISPLAY_MAX 3000
#define ITEM_GRAVITY 0.25f
class Item :
	public CGameObject
{
protected:
	LPSPRITE sprite;
	LPANIMATION fireAnimation;
	LPSPRITE spark;
	DWORD effectTimeDisplayed,
			itemTiemDisplayed;
public:
	bool isOn;
	bool isItemSpawned;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) =0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	Item();
	~Item();
};

