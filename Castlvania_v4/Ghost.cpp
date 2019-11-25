#include "Ghost.h"
#include "Brick.h"
Ghost::Ghost(float x, float y, int direction,Camera * camera)
{
	this->x = x;
	this->y = y;
	this->direction = direction;
	this->camera = camera;
	health = 1;
	walkAni = CAnimations::GetInstance()->Get(GHOST_WALKING);
	isActive = false;
}

Ghost::~Ghost()
{
}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + GHOST_BBOX_WIDTH;
	bottom = top + GHOST_BBOX_HEIGHT;
}

void Ghost::Render(Camera * camera)
{
	if (health <= 0) return;
	
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (direction == RIGHT)
		walkAni->Render(pos.x, pos.y, true);
	else
		walkAni->Render(pos.x, pos.y, false);
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

	vy += GHOST_GRAVITY * dt;
	vx = GHOST_WALKING_SPEED * direction;
	CGameObject::Update(dt);

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

		if (nx != 0) direction *= -1;
		if (ny != 0) vy = 0;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion

}
