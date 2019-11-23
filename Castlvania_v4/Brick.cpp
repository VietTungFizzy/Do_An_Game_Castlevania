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
	RenderBoundingBox(camera);
	int frameWidth = CTextures::GetInstance()->Get(BRICK)->getFrameWidth();
	int frameHeight = CTextures::GetInstance()->Get(BRICK)->getFrameHeight();
	int amountX = (int)ceil(w / frameWidth);
	int amountY = (int)ceil(h / frameHeight);
	for (int i = 0; i < amountX; i++)
	{
		D3DXVECTOR2 pos = camera->translateWorldToScreen(x + i * frameWidth, y);
		sprite->Draw(pos.x, pos.y, false);
	}
	for (int i = 0; i < amountY; i++)
	{
		D3DXVECTOR2 pos = camera->translateWorldToScreen(x , y + i * frameHeight);
		sprite->Draw(pos.x, pos.y, false);
	}
}

Brick::Brick(float x, float y, int w, int h, int type)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	sprite = CSprites::GetInstance()->Get(BRICK, type);
	health = 999;
}

Brick::~Brick()
{
}
