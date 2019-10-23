#include "MorningStar.h"
#include"BigTorch.h"


void MorningStar::InitialAttack(float x, float y,int direction)
{
	Weapon::InitialAttack(x, y);
	this->direction = direction;

}

void MorningStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	switch (level)
	{
	case 0:
		left = x;
		top = y;
		right = left + MORNING_STAR_1_BBOX_WIDTH;
		bottom = top + MORNING_STAR_1_BBOX_HEIGHT;
		break;
	case 1:
		left = x;
		top = y;
		right = left + MORNING_STAR_2_BBOX_WIDTH;
		bottom = top + MORNING_STAR_2_BBOX_HEIGHT;
		break;
	case 2:
		left = x;
		top = y;
		right = left + MORNING_STAR_3_BBOX_WIDTH;
		bottom = top + MORNING_STAR_3_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (lstAnimation[level]->getCurrentFrame() == ANIMATION_LAST_FRAME)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<BigTorch*>(coObjects->at(i)))
			{
				if (isCollideWithOtherObject(coObjects->at(i)))
				{
					coObjects->at(i)->lostHealth(1);
				}
			}
		}
		isOn = false;
	}
}

void MorningStar::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	switch (level)
	{
	case 0:
		if (direction == 1)
			lstAnimation[0]->Render(pos.x, pos.y, true);
		else
			lstAnimation[0]->Render(pos.x, pos.y, false);
		break;
	case 1:
		if (direction == 1)
			lstAnimation[1]->Render(pos.x, pos.y, true);
		else
			lstAnimation[1]->Render(pos.x, pos.y, false);
		break;
	case 2:
		if (direction == 1)
			lstAnimation[2]->Render(pos.x, pos.y, true);
		else
			lstAnimation[2]->Render(pos.x, pos.y, false);
		break;
	}
}

void MorningStar::Upgrade()
{
	if (level == 2) return;
	level++;
}

MorningStar::MorningStar()
{
	for (int i = 0; i < 3; i++)
	{
		int temp = MORNING_STAR_1 + i;
		lstAnimation.push_back(CAnimations::GetInstance()->Get((AnimationID)temp));
	}
	level = 0;
	isOn = false;
}


MorningStar::~MorningStar()
{
}
