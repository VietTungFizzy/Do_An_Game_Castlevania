#include "Brick.h"
#include"Texture.h"
void Brick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + w;
	bottom = top + h;
}

void Brick::Render(Camera * camera)
{
	int frameWidth = CTextures::GetInstance()->Get(BRICK)->getFrameWidth();
	int amount = (int)ceil(w / frameWidth);
	for (int i = 0; i < amount; i++)
	{
		D3DXVECTOR2 pos = camera->translateWorldToScreen(x + i * frameWidth, y);
		sprite->Draw(pos.x, pos.y, false);
	}
}

Brick::Brick(float x, float y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	sprite = CSprites::GetInstance()->Get(BRICK, BRICK_SPRITE_ID);
}

Brick::~Brick()
{
}
