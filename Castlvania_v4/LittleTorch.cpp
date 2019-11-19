#include "LittleTorch.h"

void LittleTorch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + LITTLE_TORCH_OFFSET_X;
	top = y + LITTLE_TORCH_OFFSET_Y;
	right = left + LITTLE_TORCH_BBOX_WIDTH;
	bottom = top + LITTLE_TORCH_BBOX_HEIGHT;
}

void LittleTorch::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (health > 0)
	{
		//RenderBoundingBox(camera);
		if (isWithinCamera(camera) == false) return;
		animation->Render(pos.x, pos.y, false);
	}
}

LittleTorch::LittleTorch(float x, float y)
{
	this->x = x;
	this->y = y;
	health = 1;
	animation = CAnimations::GetInstance()->Get(LITTLE_TORCH);
}

LittleTorch::~LittleTorch()
{
}
