#include "LittleTorch.h"

void LittleTorch::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + 5;
	top = y + 10;
	right = left + LITTLE_TORCH_BBOX_WIDTH;
	bottom = top + LITTLE_TORCH_BBOX_HEIGHT;
}

void LittleTorch::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (health > 0)
	{
		RenderBoundingBox(camera);
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		if (r < camera->getX() || b < camera->getY() || camera->getX() + SCREEN_WIDTH < l || camera->getY() + SCREEN_HEIGHT < t) return;
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
