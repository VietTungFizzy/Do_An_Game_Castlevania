#include "Simon.h"
#include"Brick.h"
#include"Dagger.h"
#include"InitialStairEvent.h"
void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting)
	{
		if (directionX == RIGHT)
		{
			left = x + SIMON_SITTING_RIGHT_OFFSET_X;
			top = y + SIMON_SITTING_OFFSET_Y;
			right = left + SIMON_SITTING_BBOX_WIDTH;
			bottom = top + SIMON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x + SIMON_SITTING_LEFT_OFFSET_X;
			top = y + SIMON_SITTING_OFFSET_Y;
			right = left + SIMON_SITTING_BBOX_WIDTH;
			bottom = top + SIMON_SITTING_BBOX_HEIGHT;
		}
	}
	else
	{
		if (directionX == RIGHT)
		{
			left = x + SIMON_DIRECTION_RIGHT_OFFSET_X;
			top = y + SIMON_STANDING_OFFSET_Y;
			right = left + SIMON_STANDING_BBOX_WIDTH;
			bottom = top + SIMON_STANDING_BBOX_HEIGHT;
		}
		else
		{
			left = x + SIMON_DIRECTION_LEFT_OFFSET_X;
			top = y + SIMON_STANDING_OFFSET_Y;
			right = left + SIMON_STANDING_BBOX_WIDTH;
			bottom = top + SIMON_STANDING_BBOX_HEIGHT;
		}
		if (isInAir)
		{
			top = y + SIMON_JUMPING_BBOX_OFFSET_Y;
			bottom = top + SIMON_JUMPING_BBOX_HEIGHT;
		}

	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
#pragma region Camera Restraint
	if (x < camera->getBoundaryLeft())
	{
		x = camera->getBoundaryLeft();
	}
	if (x + SIMON_STANDING_BBOX_WIDTH > camera->getBoundaryRight() + SCREEN_WIDTH - 24)
	{
		x = (float)(camera->getBoundaryRight() + SCREEN_WIDTH - 42);
	}
#pragma endregion

#pragma region Process States depend on animation
	if (lstAnimation.at((int)SIMON_ATTACKING_SITTING)->getCurrentFrame() == 3 ||
		lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentFrame() == 3 ||
		lstAnimation.at((int)SIMON_ATTACKING_GO_DOWN_STAIR)->getCurrentFrame() == 3||
		lstAnimation.at((int)SIMON_ATTACKING_GO_UP_STAIR)->getCurrentFrame() == 3)
	{
		isAttacking = false;
		lstAnimation.at((int)SIMON_ATTACKING_SITTING)->setCurrentFrame(-1);
		lstAnimation.at((int)SIMON_ATTACKING_STANDING)->setCurrentFrame(-1);
		lstAnimation.at((int)SIMON_ATTACKING_GO_DOWN_STAIR)->setCurrentFrame(-1);
		lstAnimation.at((int)SIMON_ATTACKING_GO_UP_STAIR)->setCurrentFrame(-1);
	}

	if (lstAnimation.at((int)SIMON_GO_UP_STAIR)->getCurrentFrame() == 2 ||
		lstAnimation.at((int)SIMON_GO_DOWN_STAIR)->getCurrentFrame() == 2)
	{
		isWalking = false;
		lstAnimation.at((int)SIMON_GO_DOWN_STAIR)->setCurrentFrame(-1);
		lstAnimation.at((int)SIMON_GO_UP_STAIR)->setCurrentFrame(-1);
	}
#pragma endregion

#pragma region Process Freeze State
	if (isFreezing)
	{
		if (timeFreezed < SIMON_FREEZE_TIME_MAX)
		{
			timeFreezed += dt;
			return;
		}
		else
			isFreezing = false;
	}
#pragma endregion

#pragma region Process moving and collision
	CGameObject::Update(dt);
	if (isOnStair && !isAutoGo)
	{
		
		if (isWalking)
		{
			vx = SIMON_STEP_ON_STAIR_SPEED * directionX;
			vy = SIMON_STEP_ON_STAIR_SPEED * directionY;
			
		}
		else 
		{
			vx = 0;
			vy = 0;
		}
		collisionWhenSimonOnStair(coObjects);
	}
	else
	{
		vy += SIMON_GRAVITY * dt;
		collisionWithGround(coObjects);
		if (isWalking)
			vx = SIMON_WALKING_SPEED * directionX;
		else vx = 0;
	}
#pragma endregion
	
#pragma region Process Simon weapon
	for (auto i : lstWeapon)
	{
		if (i.second == NULL) continue;
		if (i.second->isOn)
		{
			if (i.second->isWeaponSpawned)
			{
				i.second->isSimonSitting = isSitting;
				if (i.first == MORNING_STAR)
					i.second->SetPosition(x, y);
				i.second->Update(dt, coObjects);
			}
			else
			{
				if (lstAnimation.at((int)SIMON_ATTACKING_SITTING)->getCurrentFrame() == 2 ||
					lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentFrame() == 2)
				{
					i.second->isWeaponSpawned = true;
				}
			}
		}
	}
#pragma endregion

#pragma region Process Auto Go
	if (isAutoGo)
		{
			if (isInAir) return;
			isWalking = true;
			directionX = autoGoDirection;
			if (abs(x - posToGoX) < 1.0f)
			{
				isAutoGo = false;
				isWalking = false;
				directionX = directionAfterAutoGo;
				x = posToGoX;
				y = posToGoY;
			}
		}
#pragma endregion

	
}

void Simon::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	RenderBoundingBox(camera);
#pragma region Weapon
	for (auto i : lstWeapon)
	{
		if (i.second == NULL) continue;
		if (i.second->isOn && i.second->isWeaponSpawned)
		{
			i.second->RenderBoundingBox(camera);
			i.second->Render(camera);
		}
	}
#pragma endregion

	
#pragma region Simon
	if (isFreezing)
	{
		if (isSitting)
		{
			if (isAttacking)
			{
				if (directionX == RIGHT)
					lstAnimation.at((int)SIMON_ATTACKING_SITTING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 5, true, rand() % 256, rand() % 256, rand() % 256);
				else
					lstAnimation.at((int)SIMON_ATTACKING_SITTING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 5, false, rand() % 256, rand() % 256, rand() % 256);
			}
			else
			{
				if (directionX == RIGHT)
					lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y + 5, true, rand() % 256, rand() % 256, rand() % 256);
				else
					lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y + 5, false, rand() % 256, rand() % 256, rand() % 256);
			}
		}
		else
		{
			if (isInAir)
			{
				if (isAttacking)
				{
					if (directionX == RIGHT)
						lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y, true, rand() % 256, rand() % 256, rand() % 256);
					else
						lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y, false, rand() % 256, rand() % 256, rand() % 256);
				}
				else
				{
					if (directionX == RIGHT)
						lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, true, rand() % 256, rand() % 256, rand() % 256);
					else
						lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, false, rand() % 256, rand() % 256, rand() % 256);
				}
			}
			else
				if (isWalking)
				{
					if (directionX == RIGHT)
						lstAnimation.at((int)SIMON_WALKING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 1, true, rand() % 256, rand() % 256, rand() % 256);
					else
						lstAnimation.at((int)SIMON_WALKING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 1, false, rand() % 256, rand() % 256, rand() % 256);
				}
				else
				{
					if (isAttacking)
					{
						if (directionX == RIGHT)
							lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 1, true, rand() % 256, rand() % 256, rand() % 256);
						else
							lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 1, false, rand() % 256, rand() % 256, rand() % 256);
					}
					else
						if (directionX == RIGHT)
							lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y + 1, true, rand() % 256, rand() % 256, rand() % 256);
						else
							lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y + 1, false, rand() % 256, rand() % 256, rand() % 256);
				}
		}
	}
	else
	{
		if (isOnStair && !isAutoGo)
		{
			if (directionY == 1)
			{
				if (isWalking)
				{
					if (directionX == RIGHT)
						lstAnimation.at((int)SIMON_GO_DOWN_STAIR)->Render(pos.x, pos.y, true);
					else
						lstAnimation.at((int)SIMON_GO_DOWN_STAIR)->Render(pos.x, pos.y, false);
				}
				else
				{
					if (isAttacking)
					{
						if (directionX == RIGHT)
							lstAnimation.at((int)SIMON_ATTACKING_GO_DOWN_STAIR)->Render(pos.x, pos.y, true);
						else
							lstAnimation.at((int)SIMON_ATTACKING_GO_DOWN_STAIR)->Render(pos.x, pos.y, false);
					}
					else
						if (directionX == RIGHT)
							lstSprite.at(SIMON_ON_STAIR_GOING_DOWN_SPRITE_ID)->Draw(pos.x, pos.y, true);
						else
							lstSprite.at(SIMON_ON_STAIR_GOING_DOWN_SPRITE_ID)->Draw(pos.x, pos.y, false);
				}
			}
			else
			{
				if (isWalking)
				{
					if (directionX == RIGHT)
						lstAnimation.at((int)SIMON_GO_UP_STAIR)->Render(pos.x, pos.y, true);
					else
						lstAnimation.at((int)SIMON_GO_UP_STAIR)->Render(pos.x, pos.y, false);
				}
				else
				{
					if (isAttacking)
					{
						if (directionX == RIGHT)
							lstAnimation.at((int)SIMON_ATTACKING_GO_UP_STAIR)->Render(pos.x, pos.y, true);
						else
							lstAnimation.at((int)SIMON_ATTACKING_GO_UP_STAIR)->Render(pos.x, pos.y, false);
					}
					else
					{
						if (directionX == RIGHT)
							lstSprite.at(SIMON_ON_STAIR_GOING_UP_SPRITE_ID)->Draw(pos.x, pos.y, true);
						else
							lstSprite.at(SIMON_ON_STAIR_GOING_UP_SPRITE_ID)->Draw(pos.x, pos.y, false);
					}
				}
			}
		}
		else
			if (isSitting)
			{
				if (isAttacking)
				{
					if (directionX == RIGHT)
						lstAnimation.at((int)SIMON_ATTACKING_SITTING)->Render(pos.x, pos.y + 5, true);
					else
						lstAnimation.at((int)SIMON_ATTACKING_SITTING)->Render(pos.x, pos.y + 5, false);
				}
				else
				{
					if (directionX == RIGHT)
						lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y + 5, true);
					else
						lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y + 5, false);
				}

			}
			else
			{
				if (isInAir)
				{
					if (isAttacking)
					{
						if (directionX == RIGHT)
							lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y, true);
						else
							lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y, false);
					}
					else
					{
						if (directionX == RIGHT)
							lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, true);
						else
							lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, false);
					}
				}
				else
					if (isWalking)
					{
						if (directionX == RIGHT)
							lstAnimation.at((int)SIMON_WALKING)->Render(pos.x, pos.y + 1, true);
						else
							lstAnimation.at((int)SIMON_WALKING)->Render(pos.x, pos.y + 1, false);
					}
					else
					{
						if (isAttacking)
						{
							if (directionX == RIGHT)
								lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y + 1, true);
							else
								lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y + 1, false);
						}
						else
							if (directionX == RIGHT)
								lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y + 1, true);
							else
								lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y + 1, false);
					}
			}
	}

#pragma endregion
		
}

void Simon::collisionWithGround(vector<LPGAMEOBJECT>* coObjects)
{
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
		if (isInAir)
		{
			isInAir = false;
			y -= 1;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::collisionWhenSimonOnStair(vector<LPGAMEOBJECT>* coObjects)
{
	bool isSimonWantToGetOffStair = false;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<InitialStairEvent*>(coObjects->at(i)) &&
			isCollideWithOtherObject(coObjects->at(i)))
		{
			InitialStairEvent* temp = dynamic_cast<InitialStairEvent*>(coObjects->at(i));
			if (directionY != temp->getDirectionY())
				isSimonWantToGetOffStair = true;
		}
	}
	
	if (isSimonWantToGetOffStair)
	{
		if (directionY == UP)
		{
			y -= 20;
			x += 10;
			dy = INFINITE;
		}
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
			
			isWalking = false;
			isOnStair = false;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		dy = vy * dt;
	}
	else
	{
		
		x += dx;
		y += dy;
		
	}
}

void Simon::Jump()
{
	isInAir = true;
	vy = SIMON_JUMPING_SPEED;
}

void Simon::Sit()
{
	if (isSitting)return;
	vx = 0;
	y -= 6;
	isSitting = true;
	isWalking = false;
}

void Simon::StandUp()
{
	if (isSitting == false) return;
	y += 3;
	isSitting = false;
}

void Simon::StepUp()
{
	isWalking = true;
	if (directionY == DOWN)
		directionX *= -1;
	directionY = UP;
}

void Simon::StepDown()
{
	isWalking = true;
	if (directionY == UP)
		directionX *= -1;
	directionY = DOWN;
}

void Simon::Attack(WeaponType weaponType)
{
	if (weaponType == NO_SECONDARY_WEAPON) return;
	if (lstWeapon[weaponType]->isOn == false)
	{
		if (weaponType != MORNING_STAR)
		{
			if (weaponType == STOP_WATCH)
			{
				if (heart < 5) return;
				else heart -= 5;
			}
			else
				if (heart < 1) return;
				else heart -= 1;
			lstWeapon[weaponType]->InitialAttack(x, y, directionX);
		}
		else
		{
			lstWeapon[weaponType]->InitialAttack(x, y, directionX);
			lstWeapon[weaponType]->isWeaponSpawned = true;
		}
		isAttacking = true;
		isWalking = false;
		
	}
}

void Simon::setAutoWalk(float positionToGoX, float positionToGoY, int directionAfterAutoGo)
{
	this->posToGoX = positionToGoX;
	this->posToGoY = positionToGoY;
	this->directionAfterAutoGo = directionAfterAutoGo;
	isAutoGo = true;
	if (x - positionToGoX < 0)
		autoGoDirection = 1;
	else
		autoGoDirection = -1;
}

void Simon::upgradeWhip()
{
	MorningStar * temp = dynamic_cast<MorningStar*>(lstWeapon[MORNING_STAR]);
	temp->Upgrade();
	isFreezing = true;
	vx = 0;
	vy = 0;
	timeFreezed = 0;
}

void Simon::setSecondaryWeapon(WeaponType weaponType)
{
	delete lstWeapon[weaponType];
	lstWeapon[weaponType] = NULL;
	switch (weaponType)
	{
	case Simon::KNIFE:
		lstWeapon[weaponType] = new Dagger(camera);
		break;
	case Simon::AXE:
		break;
	case Simon::HOLY_WATER:
		break;
	case Simon::BOOMERANG:
		break;
	case Simon::STOP_WATCH:
		break;
	default:
		break;
	}
	currentSecondaryWeaponType = weaponType;
}

Simon::WeaponType Simon::getSecondaryWeapon()
{
	return currentSecondaryWeaponType;
}

void Simon::setCamera(Camera * camera)
{
	this->camera = camera;
	if (lstWeapon[currentSecondaryWeaponType] == NULL) return;
	switch (currentSecondaryWeaponType)
	{
	case Simon::KNIFE:
		{	
			Dagger * temp = dynamic_cast<Dagger*>(lstWeapon[currentSecondaryWeaponType]);
			temp->setCamera(camera);
		}
		break;
	case Simon::AXE:
		break;
	case Simon::HOLY_WATER:
		break;
	case Simon::BOOMERANG:
		break;
	default:
		break;
	}
}

Simon::Simon()
{
	std::ifstream input(L"Resources/Loader/Simon_Graphic.txt");
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

	directionX = LEFT;
	heart = 5;
	isSitting = isAttacking = isWalking = false;
	isInAir = true;

	lstWeapon[MORNING_STAR] = new MorningStar();
	currentSecondaryWeaponType = NO_SECONDARY_WEAPON;
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
