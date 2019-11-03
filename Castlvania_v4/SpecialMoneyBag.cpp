#include "SpecialMoneyBag.h"
#include"Brick.h"

void SpecialMoneyBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + SPECIAL_MONEY_BAG_BBOX_WIDTH;
	bottom = top + SPECIAL_MONEY_BAG_BBOX_HEIGHT;
}

void SpecialMoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isFinishedRising)
	{
		Item::Update(dt, coObjects);
	}
	else
	{
		CGameObject::Update(dt);
		std::vector<LPGAMEOBJECT> lstBrick;
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<Brick*>(coObjects->at(i)))
			{
				lstBrick.push_back(coObjects->at(i));
			}
		}
		for (UINT i = 0; i < lstBrick.size(); i++) //error potential
		{
			if (!isCollideWithOtherObject(lstBrick[i]))
			{
				isFinishedRising = true;
				vy = ITEM_GRAVITY;
			}
		}
		y += dy;
	}
}

void SpecialMoneyBag::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	animation->Render(pos.x, pos.y, false);
}

SpecialMoneyBag::SpecialMoneyBag(float x, float y)
{
	this->x = x;
	this->y = y;
	animation = CAnimations::GetInstance()->Get(MONEY_BAG);
	effectTimeDisplayed = max(FIRE_TIME_DISPLAY_MAX, SPARK_TIME_DISPLAY_MAX);
	itemTiemDisplayed = 0;
	isOn = false;
	isItemSpawned = false;
	isFinishedRising = false;
	vy = SPECIAL_MONEY_BAG_RISING_SPEED;
}

SpecialMoneyBag::~SpecialMoneyBag()
{
}
