#include "Panther.h"
#include "Brick.h"

Panther::Panther(float x, float y, Simon * simon, Camera * camera)
{
	this->x = x;
	this->y = y;
	this->simon = simon;
	this->camera = camera;
	runAni = CAnimations::GetInstance()->Get(PANTHER_RUNNING);
	sittingSprite = CSprites::GetInstance()->Get(PANTHER_TILESET, PANTHER_SITTING_SPRITE_ID);
	jumpingSprite = CSprites::GetInstance()->Get(PANTHER_TILESET, PANTHER_JUMPING_SPRITE_ID);
	health = 1;
	isSitting = true;
	isJumping = isRunning = false;

#pragma region Calculate Initial direction based on Simon position
	float simonX, simonY;
	simon->GetPosition(simonX, simonY);
	if (this->x > simonX)
		direction = LEFT;
	else
		direction = RIGHT;
#pragma endregion

}

Panther::~Panther()
{
}

void Panther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + PANTHER_BBOX_WIDTH;
	bottom = top + PANTHER_BBOX_HEIGHT;
}

void Panther::Render(Camera * camera)
{
	if (health <= 0) return;
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	if (isJumping)
	{
		if (direction == RIGHT)
			jumpingSprite->Draw(pos.x, pos.y, true);
		else
			jumpingSprite->Draw(pos.x, pos.y, false);
	}
	if (isRunning)
	{
		if (direction == RIGHT)
			runAni->Render(pos.x, pos.y, true);
		else
			runAni->Render(pos.x, pos.y, false);
	}
	if (isSitting)
	{
		if (direction == RIGHT)
			sittingSprite->Draw(pos.x, pos.y, true);
		else
			sittingSprite->Draw(pos.x, pos.y, false);
	}

}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (health <= 0) return;

	if (isWithinCamera(camera) == false && isActive && !isSitting)
	{
		health--;
		return;
	}

	if (isActive == false && isWithinCamera(camera))
	{
		isActive = true;
	}

	float brickLeftEdge, brickRightEdge;
	brickLeftEdge = 0;
	brickRightEdge = 0;

	CGameObject::Update(dt);
	vy += PANTHER_GRAVITY * dt;

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
		if (ny != 0)
		{
			vy = 0;
			if (isJumping)
			{
				isJumping = false;
				direction *= -1;
				isRunning = true;
			}
		}
		
		float l, t, b, r;
		coEventsResult[0]->obj->GetBoundingBox(l, t, r, b);
		brickLeftEdge = l;
		brickRightEdge = r;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion
	
	float simonX, simonY;
	simon->GetPosition(simonX, simonY);

	float l, t, b, r;
	GetBoundingBox(l, t, r, b);
	if (l <= brickLeftEdge || r >= brickRightEdge)
	{
		jump();
	}
	else
	{
		if (abs(simonX - x) <= SIMON_DETECTION_RANGE)
		{
			isSitting = false;
			run();
		}
	}
	
	if (isSimonReachable())
	{
		if (x > simonX)
			direction = LEFT;
		else
			direction = RIGHT;
	}
}

bool Panther::isSimonReachable()
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	float l1, t1, r1, b1;
	simon->GetBoundingBox(l1, t1, r1, b1);
	if (b >= t1 && r + PANTHER_BBOX_WIDTH_EXTEND >= l1 && t <= b1 && l - PANTHER_BBOX_WIDTH_EXTEND <= r1)
		return true;
	return false;
}

void Panther::jump()
{
	if (!isJumping)
	{
		isJumping = true;
		isRunning = false;
		vy = PANTHER_JUMPING_SPEED_Y;
		vx = PANTHER_JUMPING_SPEED_X * direction;
	}
}

void Panther::run()
{
	isRunning = true;
	isJumping = false;
	vx = PANTHER_RUNNING_SPEED * direction;
}

