#include "Fish.h"
#include"Brick.h"
#include"Fireball.h"
Fish::Fish(float x, float y, int direction, Camera * camera, vector<LPGAMEOBJECT> * lstBullet)
{
	this->x = savedX = x;
	this->y = savedY = y;
	this->direction = direction;
	this->camera = camera;
	this->lstBullet = lstBullet;
	health = 1;
	isGoingUp = true;
	isWalking = isShooting = isFireBallCreated = false;
	timeWaited = 0;
	
	walkAni = CAnimations::GetInstance()->Get(FISH_WALKING);
	shootingSprite = CSprites::GetInstance()->Get(FISHER_TILESET, FISH_SHOOTING_SPRITE_ID);
	goUpSprite = CSprites::GetInstance()->Get(FISHER_TILESET, FISH_GO_UP_SPRITE_ID);
}

Fish::~Fish()
{
}

void Fish::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FISH_BBOX_WIDTH;
	bottom = top + FISH_BBOX_HEIGHT;
}

void Fish::Render(Camera * camera)
{
	if (health <= 0) return;
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (isWalking)
	{
		if (direction == RIGHT)
			walkAni->Render(pos.x, pos.y, false);
		else
			walkAni->Render(pos.x, pos.y, true);
	}
	if (isShooting)
	{
		if (direction == RIGHT)
			shootingSprite->Draw(pos.x, pos.y, false);
		else
			shootingSprite->Draw(pos.x, pos.y, true);
	}
	if (isGoingUp)
	{
		if (direction == RIGHT)
			goUpSprite->Draw(pos.x, pos.y, false);
		else
			goUpSprite->Draw(pos.x, pos.y, true);
	}

}

void Fish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (health <= 0) return;

	if (isWithinCamera(camera) == false)
	{
		health--;
		return;
	}

	CGameObject::Update(dt);
	
	if (!isGoingUp) vy += FISH_GRAVITY * dt;
	else vy = FISH_GO_UP_SPEED;
	if (isWalking) vx = FISH_WALKING_SPEED * direction;
	else vx = 0;
	
	

	if (!isGoingUp)
	{
#pragma region Collision with Ground
		std::vector<LPCOLLISIONEVENT> coEvents;
		std::vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		std::vector<LPGAMEOBJECT> lstBrick;
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<Brick*>(coObjects->at(i)))
			{
				lstBrick.push_back(coObjects->at(i));
			}
		}
		CalcPotentialCollisions(&lstBrick, coEvents);

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
#pragma endregion

		if (abs(savedX - x) >= FISH_DISTANCE_HAVE_TO_WALK)
		{
			isWalking = false;
			isShooting = true;
			isFireBallCreated = false;
			timeWaited = GetTickCount();
			savedX = x;
		}

		if (isShooting)
		{
			if (isFireBallCreated == false)
			{
				lstBullet->push_back(new Fireball(x, y, direction));
				isFireBallCreated = true;
			}
			DWORD now = GetTickCount();
			if (now - timeWaited >= FISH_DELAY_TIME_AFTER_SHOOT)
			{
				isShooting = false;
				direction *= -1;
				isWalking = true;
			}
		}
	}
	else
	{
		x += dx;
		y += dy;
		if (abs(savedY - y) >= FISH_DISTENCE_HAVE_TO_GO_UP)
			isGoingUp = false;
	}
}
