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
	if (health <= 0)
	{
		if (!isDoneAfterEffect)
		{
			bool isAllPebblesOutOfCameraSight = true;
			for (int i = 0; i < afterEffect.size(); i++)
			{
				if (afterEffect[i]->isWithinCamera(camera) == true)
				{
					isAllPebblesOutOfCameraSight = false;
					break;
				}
			}
			if (isAllPebblesOutOfCameraSight)
			{
				for (int i = 0; i < afterEffect.size(); i++) delete afterEffect[i];
				isDoneAfterEffect = true;
			}
			else
				for (int i = 0; i < afterEffect.size(); i++)
					afterEffect[i]->Render(camera);
		}
		else
			return;
	}
	else
	{
		RenderBoundingBox(camera);
		if (isWithinCamera(camera) == false) return;

		int frameWidth = CTextures::GetInstance()->Get(BRICK)->getFrameWidth();
		int amount = (int)ceil(w / frameWidth);
		for (int i = 0; i < amount; i++)
		{
			D3DXVECTOR2 pos = camera->translateWorldToScreen(x + i * frameWidth, y);
			sprite->Draw(pos.x, pos.y, false);
		}
	}
}

void BreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(health <= 0 && isDoneAfterEffect == false)
		for (int i = 0; i < afterEffect.size(); i++)
			afterEffect[i]->Update(dt, coObjects);
}

BreakableBrick::BreakableBrick(float x, float y, int w, int h, int type)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	sprite = CSprites::GetInstance()->Get(BRICK, type);
	health = 1;
	afterEffect.push_back(new Pebble(PEBBLE_X(x), PEBBLE_Y(y), PEBBLE_1_VX, PEBBLE_1_VY));
	afterEffect.push_back(new Pebble(PEBBLE_X(x), PEBBLE_Y(y),  PEBBLE_2_VX, PEBBLE_2_VY));
	afterEffect.push_back(new Pebble(PEBBLE_X(x), PEBBLE_Y(y),  PEBBLE_3_VX, PEBBLE_3_VY));
	afterEffect.push_back(new Pebble(PEBBLE_X(x), PEBBLE_Y(y),  PEBBLE_4_VX, PEBBLE_4_VY));
	isDoneAfterEffect =false;
}

BreakableBrick::~BreakableBrick()
{
}
