#include "Bat.h"

Bat::Bat(float x, float y, int direction, Camera * camera,Simon * simon)
{
	this->x = x;
	this->y = y;
	this->direction = direction;
	this->camera = camera;
	this->simon = simon;
	flyAni = CAnimations::GetInstance()->Get(BAT_FLYING);
	vx = BAT_SPEED_X * direction;
	vy = cosf(BAT_SPEED_Y);
	health = 1;
}

Bat::~Bat()
{
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + BAT_BBOX_WIDTH;
	bottom = top + BAT_BBOX_HEIGHT;
}

void Bat::Render(Camera * camera)
{
	if (health <= 0) return;
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (direction == RIGHT)
		flyAni->Render(pos.x, pos.y, false);
	else
		flyAni->Render(pos.x, pos.y, true);
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (health <= 0) return;

	if (isWithinCamera(camera) == false && isActive)
	{
		health--;
		return;
	}

	if (isActive == false && isWithinCamera(camera))
	{
		isActive = true;
	}

	CGameObject::Update(dt);

	x += dx;
	y += dy;
	
	if (isCollideWithOtherObject(simon))
	{
		health--;
	}
}
