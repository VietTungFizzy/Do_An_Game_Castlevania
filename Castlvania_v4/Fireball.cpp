#include "Fireball.h"

Fireball::Fireball(float x, float y, int direction)
{
	this->x = x;
	this->y = y;
	this->direction = direction;
	sprite = CSprites::GetInstance()->Get(FIREBALL, FIREBALL_SPRITE_ID);
}

Fireball::~Fireball()
{
}

void Fireball::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void Fireball::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (direction == RIGHT)
		sprite->Draw(pos.x, pos.y, true);
	else
		sprite->Draw(pos.x, pos.y, false);
}

void Fireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}
