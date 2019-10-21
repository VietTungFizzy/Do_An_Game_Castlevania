#include "Simon.h"
#include"Brick.h"


void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting)
	{

	}
	else
	{
		if (direction == 1)
		{
			left = x + SIMON_DIRECTION_RIGHT_OFFSET_X;
			top = y + SIMON_OFFSET_Y;
			right = left + SIMON_STANDING_BBOX_WIDTH;
			bottom = top + SIMON_STANDING_BBOX_HEIGHT;
		}
		else
		{
			left = x + SIMON_DIRECTION_LEFT_OFFSET_X;
			top = y + SIMON_OFFSET_Y;
			right = left + SIMON_STANDING_BBOX_WIDTH;
			bottom = top + SIMON_STANDING_BBOX_HEIGHT;
		}
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x < camera->getBoundaryLeft())
	{
		x = camera->getBoundaryLeft();
	}
	if (x + SIMON_STANDING_BBOX_WIDTH > camera->getBoundaryRight())
	{
		x = camera->getBoundaryRight() + SCREEN_WIDTH - SIMON_STANDING_BBOX_WIDTH;
	}

	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


}

void Simon::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	RenderBoundingBox(camera);
	if (isSitting)
	{
		if (isAttacking)
		{
			if (direction == 1)
				lstAnimation.at((int)SIMON_ATTACKING_SITTING)->Render(pos.x, pos.y, true);
			else
				lstAnimation.at((int)SIMON_ATTACKING_SITTING)->Render(pos.x, pos.y, false);

			if (lstAnimation.at((int)SIMON_ATTACKING_SITTING)->getCurrentFrame() == 2)
				isAttacking = false;
		}
		else
		{
			if (direction == 1)
				lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, true);
			else
				lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, false);
		}
	}
	else
	{
		if (isInAir)
		{
			if (isAttacking)
			{
				if (direction == 1)
					lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y, true);
				else
					lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y, false);

				if (lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentFrame() == 2)
					isAttacking = false;
			}
			else
			{
				if (direction == 1)
					lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, true);
				else
					lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, false);
			}
		}
		else
			if (isWalking)
			{
				if (direction == 1)
					lstAnimation.at((int)SIMON_WALKING)->Render(pos.x, pos.y, true);
				else
					lstAnimation.at((int)SIMON_WALKING)->Render(pos.x, pos.y, false);
			}
			else
			{
				if (isAttacking)
				{
					if (direction == 1)
						lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y, true);
					else
						lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y, false);

					if (lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentFrame() == 2)
						isAttacking = false;
				}
				else
					if(direction == 1)
						lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y, true);
					else
						lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y, false);
			}
	}
}

Simon::Simon(Camera * camera)
{
	std::ifstream input(L"Resources/Simon_Graphic.txt");
	int n, tileID, id;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> id;
		lstAnimation.push_back(CAnimations::GetInstance()->Get((AnimationID)id));
	}
	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> tileID >> id;
		lstSprite.push_back(CSprites::GetInstance()->Get(tileID, id));
	}
	input.close();
	direction = -1;
	isSitting = isAttacking = isInAir = isWalking = false;
	x = 10;
	y = 10;
	this->camera = camera;
}


Simon::~Simon()
{
	for (int i = 0; i < lstAnimation.size(); i++)
	{
		lstAnimation[i] = NULL;
		delete lstAnimation[i];
	}
	for (int i = 0; i < lstSprite.size(); i++)
	{
		lstSprite[i] = NULL;
		delete lstSprite[i];
	}
	std::vector<LPANIMATION>().swap(lstAnimation);
	std::vector<LPSPRITE>().swap(lstSprite);
}
