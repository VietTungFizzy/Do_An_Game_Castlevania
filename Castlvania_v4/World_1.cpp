#include "World_1.h"
#include"Brick.h"
#include"LittleTorch.h"
#include"BreakableBrick.h"
#include "InitialStairEvent.h"
void World_1::KeyState(BYTE * states)
{
	if (simon->isAttacking || simon->isInAir || simon->isFreezing || simon->isAutoGo) return;
	if (Game::GetInstance()->IsKeyDown(DIK_UP))
	{
		if (!simon->isOnStair)
		{
			for (int i = 0; i < lstObject[stage].size(); i++)
			{
				if (dynamic_cast<InitialStairEvent*>(lstObject[stage].at(i)))
				{
					if (simon->isCollideWithOtherObject(lstObject[stage].at(i)))
					{
						InitialStairEvent * temp = dynamic_cast<InitialStairEvent*>(lstObject[stage].at(i));
						if (temp->getDirectionY() == -1)
						{
							simon->setDirectionY(-1);
							simon->isOnStair = true;
							float x, y, stairPos;
							simon->GetPosition(x, y);
							stairPos = temp->getStairPosition();
							if (abs(x - stairPos) >= 1)
								simon->setAutoWalk(stairPos, temp->getDirectionX());
							else
							{
								simon->SetPosition(stairPos, y);
								simon->setDirectionX(temp->getDirectionX());
							}
						}
					}
				}
			}
		}
		else
		{
			simon->StepUp();
		}
	}
	else
		if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
		{
			if (!simon->isOnStair)
			{
				bool isSimonUseStair = false;
				for (int i = 0; i < lstObject[stage].size(); i++)
				{
					if (dynamic_cast<InitialStairEvent*>(lstObject[stage].at(i)))
					{
						if (simon->isCollideWithOtherObject(lstObject[stage].at(i)))
						{
							InitialStairEvent * temp = dynamic_cast<InitialStairEvent*>(lstObject[stage].at(i));
							if (temp->getDirectionY() == 1)
							{
								simon->setDirectionY(1);
								simon->isOnStair = true;
								float x, y, stairPos;
								simon->GetPosition(x, y);
								stairPos = temp->getStairPosition();
								if (abs(x - stairPos) >= 1)
									simon->setAutoWalk(stairPos, temp->getDirectionX());
								else
								{
									simon->SetPosition(stairPos, y);
									simon->setDirectionX(temp->getDirectionX());
								}
								isSimonUseStair = true;
							}
						}
					}
				}
				
				if (!isSimonUseStair)
				{
					simon->Sit();
					if (Game::GetInstance()->IsKeyDown(DIK_RIGHT)) simon->setDirectionX(1);
					else if (Game::GetInstance()->IsKeyDown(DIK_LEFT)) simon->setDirectionX(-1);
					return;
				}
			}
			else
			{
				simon->StepDown();
			}
			
		}
		else
		{
			if (!simon->isOnStair)
				simon->StandUp();
		}

	if (simon->isOnStair) return;

	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		simon->isWalking = true;
		simon->setDirectionX(1);
	}
	else
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			simon->isWalking = true;
			simon->setDirectionX(-1);
		}
		else
		{
			simon->isWalking = false;
			simon->StandUp();
		}
}

void World_1::OnKeyDown(int KeyCode)
{
	if (simon->isAttacking || simon->isFreezing || simon->isAutoGo) return;
	if (KeyCode == DIK_A && Game::GetInstance()->IsKeyDown(DIK_UP))
	{
		simon->Attack(simon->getSecondaryWeapon());
	}
	else
		if (KeyCode == DIK_A) simon->Attack(simon->MORNING_STAR);
	if (simon->isInAir) return;
	if (KeyCode == DIK_S)
	{
		simon->Jump();
	}
}

void World_1::OnKeyUp(int KeyCode)
{
}

void World_1::Update(DWORD dt)
{
	simon->Update(dt, &lstObject[stage]);
	for (int i = 0; i < lstObject[stage].size(); i++)
	{
		lstObject[stage].at(i)->Update(dt, &lstObject[stage]);
		if (lstObject[stage].at(i)->getHealth() == 0)
		{
			lstObject[stage].at(i)->lostHealth(1);
		}

	}

	float x, y;
	simon->GetPosition(x, y);
	/*DebugOut(L"X= %f\n", x);*/
	/*DebugOut(L"Y= %f\n", y);*/
	camera->SetPosition(x - SCREEN_WIDTH / 2 + 30, camera->getY());
	camera->Update(dt);
	
}

void World_1::LoadResources()
{
	MapManager::GetInstance()->setMap(WORLD_1);
	camera = new Camera(0, (float)(MapManager::GetInstance()->getMap()->getMapWidth() - SCREEN_WIDTH));
	camera->SetPosition(0, 0);

	std::ifstream input(L"Resources/Map_World_1_Ground_Object.txt");
	int n,totalObject ,objectType, x, y, w, h, type;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> totalObject;
		LPGAMEOBJECT tempObj = NULL;
		vector<LPGAMEOBJECT> tempVector;
		for (int j = 0; j < totalObject; j++)
		{
			float stairPos;
			input >> objectType >> x >> y >> w >> h >> type;
			switch ((ObjectType)objectType)
			{
			case BRICK_OBJ:
				tempObj = new Brick(x, y, w, h, type);
				break;
			case LITTLE_TORCH_OBJ:
				tempObj = new LittleTorch(x, y);
				break;
			case BREAKABLE_BRICK_OBJ:
				tempObj = new BreakableBrick(x, y, w, h, type);
				break;
			case GO_UP_STAIR_OBJ:
				input >> stairPos;
				tempObj = new InitialStairEvent(x, y, w, h, -1, type,stairPos);
				break;
			case GO_DOWN_STAIR_OBJ:
				input >> stairPos;
				tempObj = new InitialStairEvent(x, y, w, h, 1, type, stairPos);
				break;
			default:
				break;
			}
			tempVector.push_back(tempObj);
		}
		lstObject[i] = tempVector;
	}
	input.close();

	simon = new Simon(camera);
	stage = 0;

	//testing
	simon->SetPosition(703, 10);
}

void World_1::Render()
{
	MapManager::GetInstance()->getMap()->Render(camera);
	for (int i = 0; i < lstObject[stage].size(); i++)
	{
		lstObject[stage].at(i)->Render(camera);
	}

	simon->Render(camera);
}

World_1::World_1()
{
	LoadResources();
}


World_1::~World_1()
{
}
