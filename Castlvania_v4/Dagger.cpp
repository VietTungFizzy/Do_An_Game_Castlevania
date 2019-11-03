#include "Dagger.h"
#include"BigTorch.h"


void Dagger::InitialAttack(float x, float y, int direction)
{
	Weapon::InitialAttack(x, y, direction);
	vx = DAGGER_SPEED * direction;
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + DAGGER_BBOX_WIDTH;
	bottom = top + DAGGER_BBOX_HEIGHT;
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	if (r < camera->getX() || b < camera->getY() || camera->getX() + SCREEN_WIDTH < l || camera->getY() + SCREEN_HEIGHT < t)
	{
		isOn = false;
		return;
	}
	x += dx;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getHealth() > 0)
		{
			if (isCollideWithOtherObject(coObjects->at(i)))
			{
				if (dynamic_cast<BigTorch*>(coObjects->at(i)))
				{
					coObjects->at(i)->lostHealth(1);
					DebugOut(L"Hit ");
					isOn = false;
				}
			}
		}
	}
}

void Dagger::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if(direction == 1)
		sprite->Draw(pos.x, pos.y, false);
	else
		sprite->Draw(pos.x, pos.y, true);
}

Dagger::Dagger(Camera * camera)
{
	sprite = CSprites::GetInstance()->Get(ITEM, DAGGER_SPRITE_ID);
	this->camera = camera;
}


Dagger::~Dagger()
{
}
