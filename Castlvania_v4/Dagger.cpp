#include "Dagger.h"
#include"BigTorch.h"


void Dagger::InitialAttack(float x, float y, int direction)
{
	Weapon::InitialAttack(x, y, direction);

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
	if (isCollisionChecked == false)
	{
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
		isCollisionChecked = true;
	}
}

void Dagger::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	sprite->Draw(pos.x, pos.y, false);
}

Dagger::Dagger()
{
	sprite = CSprites::GetInstance()->Get(ITEM, DAGGER_SPRITE_ID);
	vx = DAGGER_SPEED;
	this->camera = camera;
}


Dagger::~Dagger()
{
}
