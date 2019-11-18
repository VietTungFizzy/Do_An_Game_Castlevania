#include "MorningStar.h"


void MorningStar::InitialAttack(float x, float y,int directionX)
{
	Weapon::InitialAttack(x, y,directionX);
	lstAnimation[level]->setCurrentFrame(-1);
}

void MorningStar::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (directionX == 1)
	{
		left = x + ADJUST_BBOX_POSITION_X_SIMON_STAND_RIGHT;
		top = y + ADJUST_BBOX_POSITION_Y_SIMON_STAND_RIGHT;
	}
	else
	{
		left = x + ADJUST_BBOX_POSITION_X_SIMON_STAND_LEFT;
		top = y + ADJUST_BBOX_POSITION_Y_SIMON_STAND_LEFT;
	}
	switch (level)
	{
	case 0:
		right = left + MORNING_STAR_1_BBOX_WIDTH;
		bottom = top + MORNING_STAR_1_BBOX_HEIGHT;
		break;
	case 1:
		top += 2;
		right = left + MORNING_STAR_2_BBOX_WIDTH;
		bottom = top + MORNING_STAR_2_BBOX_HEIGHT;
		break;
	case 2:
		top += 2;
		if (directionX == 1)
			left += 2;
		else
			left -= 15;
		right = left + MORNING_STAR_3_BBOX_WIDTH;
		bottom = top + MORNING_STAR_3_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isSimonSitting)
		y += ADJUST_POSITION_Y_SIMON_SIT;
	else
		y += ADJUST_POSITION_Y_SIMON_STAND;
	if (directionX == 1)
	{
		this->x -= ADJUST_POSITION_X_SIMON_STAND_RIGHT;
	}
	else
	{
		x -= ADJUST_POSITION_X_SIMON_STAND_LEFT;
	}
	if (lstAnimation[level]->getCurrentFrame() == ANIMATION_FRAME_TO_CHECK_COLLSION && isCollisionChecked == false)
	{
		Weapon::Update(dt, coObjects);
		isCollisionChecked = true;
	}
}

void MorningStar::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	switch (level)
	{
	case 0:
		if (directionX == 1)
			lstAnimation[0]->Render(pos.x, pos.y, true);
		else
			lstAnimation[0]->Render(pos.x, pos.y, false);
		break;
	case 1:
		if (directionX == 1)
			lstAnimation[1]->Render(pos.x, pos.y, true);
		else
			lstAnimation[1]->Render(pos.x, pos.y, false);
		break;
	case 2:
		if (directionX == 1)
			lstAnimation[2]->Render(pos.x, pos.y, true);
		else
			lstAnimation[2]->Render(pos.x, pos.y, false);
		break;
	}
	if (lstAnimation[level]->getCurrentFrame() == 3)
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
	level = 2;
	isOn = false;

}


MorningStar::~MorningStar()
{
}
