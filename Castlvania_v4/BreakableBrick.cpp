#include "BreakableBrick.h"
#include"Texture.h"
void BreakableBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + w;
	bottom = top + h;
}

void BreakableBrick::Render(Camera * camera)
{
	if (health <= 0) return;

	RenderBoundingBox(camera);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	if (r < camera->getX() || b < camera->getY() || camera->getX() + SCREEN_WIDTH < l || camera->getY() + SCREEN_HEIGHT < t) return;

	int frameWidth = CTextures::GetInstance()->Get(BRICK)->getFrameWidth();
	int amount = (int)ceil(w / frameWidth);
	for (int i = 0; i < amount; i++)
	{
		D3DXVECTOR2 pos = camera->translateWorldToScreen(x + i * frameWidth, y);
		sprite->Draw(pos.x, pos.y, false);
	}
}

BreakableBrick::BreakableBrick(float x, float y, int w, int h, int type)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	sprite = CSprites::GetInstance()->Get(BRICK, type);
	health = 1;
}

BreakableBrick::~BreakableBrick()
{
}