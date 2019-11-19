#include "Pebble.h"

void Pebble::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + PEBBLE_OFFSET_X;
	top = y + PEBBLE_OFFSET_Y;
	right = x + PEBBLE_BBOX_WIDTH;
	bottom = y + PEBBLE_BBOX_HEIGHT;
}

void Pebble::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	sprite->Draw(pos.x, pos.y, false);
}

void Pebble::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt , coObjects);
	vy += PEBBLE_GRAVITY * dt;
	
	x += dx;
	y += dy;
}

Pebble::Pebble(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	sprite = CSprites::GetInstance()->Get(EFFECT, PEBBLE_SPRITE_ID);
}

Pebble::~Pebble()
{
}
