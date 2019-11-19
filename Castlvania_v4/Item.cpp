#include "Item.h"
#include"Brick.h"

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (effectTimeDisplayed < max(FIRE_TIME_DISPLAY_MAX, SPARK_TIME_DISPLAY_MAX))
	{
		effectTimeDisplayed += dt;
		isItemSpawned = false;
		return;
	}
	else
	{
		
		if (itemTiemDisplayed < ITEM_TIME_DISPLAY_MAX)
		{
			itemTiemDisplayed += dt;
			isItemSpawned = true;
		}
		else
		{
			isOn = false;
			return;
		}
	}

	CGameObject::Update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	std::vector<LPGAMEOBJECT> lstBrick;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Brick*>(coObjects->at(i)))
		{
			lstBrick.push_back(coObjects->at(i));
		}
	}
	CalcPotentialCollisions(&lstBrick, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void Item::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (effectTimeDisplayed >= max(FIRE_TIME_DISPLAY_MAX, SPARK_TIME_DISPLAY_MAX))
	{
		sprite->Draw(pos.x, pos.y, false);
	}
	else
	{
		if (effectTimeDisplayed < FIRE_TIME_DISPLAY_MAX)
			fireAnimation->Render(pos.x, pos.y, false);
		if (effectTimeDisplayed < SPARK_TIME_DISPLAY_MAX)
			spark->Draw(pos.x, pos.y, false);
	}
}

Item::Item()
{
}


Item::~Item()
{
}
