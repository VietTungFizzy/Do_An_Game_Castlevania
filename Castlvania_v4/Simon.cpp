#include "Simon.h"
#include"Brick.h"
#include"Dagger.h"

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting)
	{
		if (direction == 1)
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
		if (direction == 1)
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
	if (x < camera->getBoundaryLeft())
	{
		x = camera->getBoundaryLeft();
	}
	if (x + SIMON_STANDING_BBOX_WIDTH > camera->getBoundaryRight() + SCREEN_WIDTH - 24)
	{
		x = (float)(camera->getBoundaryRight() + SCREEN_WIDTH - 42);
	}

	if (lstAnimation.at((int)SIMON_ATTACKING_SITTING)->getCurrentFrame() == 3 || 
		lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentFrame() == 3)
	{
		isAttacking = false;
	}
	if (isAttacking) DebugOut(L"IsAttacking\n");
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
	CGameObject::Update(dt);

	vy += SIMON_GRAVITY * dt;

	collisionWithGround(coObjects);

	if (isWalking)
		vx = SIMON_WALKING_SPEED * direction;
	else vx = 0;

	for (auto i : lstWeapon)
	{
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

	if (isAutoGo)
	{
		if (isInAir) return;
		isWalking = true;
		direction = autoGoDirection;
	}
}

void Simon::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->translateWorldToScreen(x, y);
	/*RenderBoundingBox(camera);*/
	
#pragma region Simon
	if (isFreezing)
	{
		if (isSitting)
		{
			if (isAttacking)
			{
				if (direction == 1)
					lstAnimation.at((int)SIMON_ATTACKING_SITTING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 5, true, rand() % 256, rand() % 256, rand() % 256);
				else
					lstAnimation.at((int)SIMON_ATTACKING_SITTING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 5, false, rand() % 256, rand() % 256, rand() % 256);
			}
			else
			{
				if (direction == 1)
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
					if (direction == 1)
						lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y, true, rand() % 256, rand() % 256, rand() % 256);
					else
						lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y, false, rand() % 256, rand() % 256, rand() % 256);
				}
				else
				{
					if (direction == 1)
						lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, true, rand() % 256, rand() % 256, rand() % 256);
					else
						lstSprite.at(SIMON_SITTING_SPRITE_ID)->Draw(pos.x, pos.y, false, rand() % 256, rand() % 256, rand() % 256);
				}
			}
			else
				if (isWalking)
				{
					if (direction == 1)
						lstAnimation.at((int)SIMON_WALKING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 1, true, rand() % 256, rand() % 256, rand() % 256);
					else
						lstAnimation.at((int)SIMON_WALKING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 1, false, rand() % 256, rand() % 256, rand() % 256);
				}
				else
				{
					if (isAttacking)
					{
						if (direction == 1)
							lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 1, true, rand() % 256, rand() % 256, rand() % 256);
						else
							lstAnimation.at((int)SIMON_ATTACKING_STANDING)->getCurrentAnimationFrame()->GetSprite()->Draw(pos.x, pos.y + 1, false, rand() % 256, rand() % 256, rand() % 256);
					}
					else
						if (direction == 1)
							lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y + 1, true, rand() % 256, rand() % 256, rand() % 256);
						else
							lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y + 1, false, rand() % 256, rand() % 256, rand() % 256);
				}
		}
	}
	else
		if (isSitting)
		{
			if (isAttacking)
			{
				if (direction == 1)
					lstAnimation.at((int)SIMON_ATTACKING_SITTING)->Render(pos.x, pos.y + 5, true);
				else
					lstAnimation.at((int)SIMON_ATTACKING_SITTING)->Render(pos.x, pos.y + 5, false);
			}
			else
			{
				if (direction == 1)
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
					if (direction == 1)
						lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y, true);
					else
						lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y, false);
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
						lstAnimation.at((int)SIMON_WALKING)->Render(pos.x, pos.y + 1, true);
					else
						lstAnimation.at((int)SIMON_WALKING)->Render(pos.x, pos.y + 1, false);
				}
				else
				{
					if (isAttacking)
					{
						if (direction == 1)
							lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y + 1, true);
						else
							lstAnimation.at((int)SIMON_ATTACKING_STANDING)->Render(pos.x, pos.y + 1, false);
					}
					else
						if (direction == 1)
							lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y + 1, true);
						else
							lstSprite.at(SIMON_STANDING_SPRITE_ID)->Draw(pos.x, pos.y + 1, false);
				}
		}
#pragma endregion
		for (auto i : lstWeapon)
		{
			if (i.second->isOn && i.second->isWeaponSpawned)
			{
				i.second->RenderBoundingBox(camera);
				i.second->Render(camera);
			}
		}
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

void Simon::setAutoWalk(float positionToGo)
{
	isAutoGo = true;
	autoGoDistance = abs(x - positionToGo);
	if (x - positionToGo < 0)
		autoGoDirection = 1;
	else
		autoGoDirection = -1;
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
			lstWeapon[weaponType]->InitialAttack(x, y, direction);
		}
		else
		{
			lstWeapon[weaponType]->InitialAttack(x, y, direction);
			lstWeapon[weaponType]->isWeaponSpawned = true;
		}
		isAttacking = true;
		isWalking = false;
		lstAnimation.at((int)SIMON_ATTACKING_SITTING)->setCurrentFrame(-1);
		lstAnimation.at((int)SIMON_ATTACKING_STANDING)->setCurrentFrame(-1);
	}
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
	switch (weaponType)
	{
	case Simon::KNIFE:
		if (lstWeapon[weaponType] == NULL)
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
	heart = 5;
	isSitting = isAttacking = isWalking = false;
	isInAir = true;
	x = 10;
	y = 10;
	this->camera = camera;
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
