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
	if (health > 0)
	{
		RenderBoundingBox(camera);
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		if (r < camera->getX() || b < camera->getY() || camera->getX() + SCREEN_WIDTH < l || camera->getY() + SCREEN_HEIGHT < t) return;
		D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
		animation->Render(pos.x, pos.y, false);
	}
}

BigTorch::BigTorch(float x, float y)
{
	this->x = x;
	this->y = y;
	animation = CAnimations::GetInstance()->Get(BIG_TORCH);
	health = 1;
}

BigTorch::~BigTorch()
{
}
