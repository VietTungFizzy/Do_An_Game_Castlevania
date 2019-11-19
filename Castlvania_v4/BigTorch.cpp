#include "BigTorch.h"


void BigTorch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + BIG_TORCH_SPRITE_OFFSET_X;
	top = y;
	right = left + BIG_TORCH_BBOX_WIDTH;
	bottom = top + BIG_TORCH_BBOX_HEIGHT;
}

void BigTorch::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (health > 0)
	{
		RenderBoundingBox(camera);
		if (isWithinCamera(camera) == false) return;
		torchAnimation->Render(pos.x, pos.y, false);
	}
}

BigTorch::BigTorch(float x, float y)
{
	this->x = x;
	this->y = y;
	torchAnimation = CAnimations::GetInstance()->Get(BIG_TORCH);
	health = 1;
}

BigTorch::~BigTorch()
{
}
