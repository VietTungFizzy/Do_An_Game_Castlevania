#include "MorningStar.h"
#include"BigTorch.h"


void MorningStar::InitialAttack(float x, float y,int direction)
{
	Weapon::InitialAttack(x, y,direction);
	lstAnimation[level]->setCurrentFrame(-1);

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
	this->x -= 12;
	this->y += 5;
	if (lstAnimation[level]->getCurrentFrame() == ANIMATION_FRAME_TO_CHECK_COLLSION)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->getHealth() > 0)
			{
				if (dynamic_cast<BigTorch*>(coObjects->at(i)))
				{
					if (isCollideWithOtherObject(coObjects->at(i)))
					{
						coObjects->at(i)->lostHealth(1);
					}
				}
			}
		}
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
	if (lstAnimation[level]->getCurrentFrame() == 2)
		isOn = false;
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
