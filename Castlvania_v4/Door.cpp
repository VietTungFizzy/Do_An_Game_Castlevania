#include "Door.h"



void Door::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + DOOR_BBOX_WIDTH;
	bottom = top + DOOR_BBOX_HEIGHT;
}

void Door::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (isOpen)
	{
		if (isProcessingOpen)
			animationOpen->Render(pos.x, pos.y, false);

		if (isWaitingSimonGoThrough)
			spriteOpened->Draw(pos.x, pos.y, false);

		if(isProcessingClose)
			animationClose->Render(pos.x, pos.y, false);
	}
	else
	{
		spriteClosed->Draw(pos.x, pos.y, false);
	}
}

void Door::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isOpen) return;
	if (animationOpen->getCurrentFrame() == DOOR_ANIMATION_FRAME_FULLY_OPENED)
	{
		isWaitingSimonGoThrough = true;
		isProcessingOpen = false;
	}
	if (animationClose->getCurrentFrame() == DOOR_ANIMATION_FRAME_FULLY_CLOSED)
	{
		isProcessingClose = false;
		isOpen = false;
	}
}

void Door::open()
{
	isOpen = true;
	isProcessingOpen = true;
}

void Door::close()
{
	isProcessingClose = true;
	isWaitingSimonGoThrough = false;
}

Door::Door(float x, float y)
{
	this->x = x;
	this->y = y;
	isOpen = false;
	isProcessingOpen = false;
	spriteClosed = CSprites::GetInstance()->Get(DOOR_TILESET, 0);
	spriteOpened = CSprites::GetInstance()->Get(DOOR_TILESET, 2);
	animationOpen = CAnimations::GetInstance()->Get(DOOR_OPEN);
	animationClose = CAnimations::GetInstance()->Get(DOOR_CLOSE);
	animationClose->setCurrentFrame(-1);
	animationOpen->setCurrentFrame(-1);
}

Door::~Door()
{
}
