#include "Panther.h"
#include "Brick.h"

Panther::Panther(int type, Simon * simon, Camera * camera)
{
	this->type = type;
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

	switch (type)
	{
	case 1:
		x = PANTHER_1_POSITION_X;
		y = PANTHER_1_POSITION_Y;
		if (direction == RIGHT)
			posToGo = PANTHER_1_AUTO_GO_POSITION_RIGHT;
		else
			posToGo = PANTHER_1_AUTO_GO_POSITION_LEFT;
		break;
	case 2:
		x = PANTHER_2_POSITION_X;
		y = PANTHER_2_POSITION_Y;
		if (direction == RIGHT)
			posToGo = PANTHER_2_AUTO_GO_POSITION_RIGHT_1;
		else
			posToGo = PANTHER_2_AUTO_GO_POSITION_LEFT;
		break;
	case 3:
		x = PANTHER_3_POSITION_X;
		y = PANTHER_3_POSITION_Y;
		if (direction == RIGHT)
			posToGo = PANTHER_3_AUTO_GO_POSITION_RIGHT ;
		else
			posToGo = PANTHER_3_AUTO_GO_POSITION_LEFT;
		break;
	default:
		break;
	}
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
	RenderBoundingBox(camera);
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
			runAni->Render(pos.x, pos.y + 1, true);
		else
			runAni->Render(pos.x, pos.y + 1, false);
	}
	if (isSitting)
	{
		if (direction == RIGHT)
			sittingSprite->Draw(pos.x, pos.y + 1, true);
		else
			sittingSprite->Draw(pos.x, pos.y + 1, false);
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
		float simonX, simonY;
		simon->GetPosition(simonX, simonY);

		if (abs(simonX - x) <= SIMON_DETECTION_RANGE)
		{
			isActive = true;
			isSitting = false;
			isAutoGo = true;
			savedX = x;
			run();
		}
		
	}
	if (isActive)
	{
		float simonX, simonY;
		simon->GetPosition(simonX, simonY);

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

			/*if (nx != 0) vx = 0;*/
			if (ny == -1)
			{
				vy = 0;
				if (isJumping)
				{
					if (x > simonX)
						direction = LEFT;
					else
						direction = RIGHT;
					run();

					if (type == 2 && posToGo == PANTHER_2_AUTO_GO_POSITION_RIGHT_1)
					{
						posToGo = PANTHER_2_AUTO_GO_POSITION_RIGHT_2;
						isAutoGo = true;
						savedX = x;
					}
					isJumping = false;
				}
			}

		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
#pragma endregion

		if (isAutoGo)
		{
			float distanceRunned = abs(x-savedX);
			float distanceHaveToGo = abs(savedX - posToGo);
			if (distanceRunned >= distanceHaveToGo)
			{
				isRunning = false;
				x = posToGo;
				jump();
				isAutoGo = false;
			}
			
		}
		if (Game::GetInstance()->IsKeyDown(DIK_Q))
		{
			jump();
		}
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
	if (isJumping) return;
	isJumping = true;
	vy = PANTHER_JUMPING_SPEED_Y;
	vx = PANTHER_JUMPING_SPEED_X * direction;
}

void Panther::run()
{
	isRunning = true;
	vx = PANTHER_RUNNING_SPEED * direction;
}

