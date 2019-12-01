#include "World_1_Water.h"
#include"Map.h"
#include"Grid.h"
#include"InitialStairEvent.h"

World_1_Water::World_1_Water()
{
	LoadResources();
}


World_1_Water::~World_1_Water()
{
}

void World_1_Water::KeyState(BYTE * states)
{
	if (simon->isAttacking || simon->isInAir
		|| simon->isFreezing || simon->isAutoGo) return;
	if (Game::GetInstance()->IsKeyDown(DIK_UP))
	{
		if (!simon->isOnStair)
		{
			for (int i = 0; i < lstObject.size(); i++)
			{
				if (dynamic_cast<InitialStairEvent*>(lstObject.at(i)))
				{
					if (simon->isCollideWithOtherObject(lstObject.at(i)))
					{
						InitialStairEvent * temp = dynamic_cast<InitialStairEvent*>(lstObject.at(i));
						if (temp->getDirectionY() == UP)
						{
							simon->setDirectionY(UP);
							simon->isOnStair = true;
							float x, y, stairPos;
							simon->GetPosition(x, y);
							stairPos = temp->getStairPositionX();
							if (abs(x - stairPos) >= 1)
								simon->setAutoWalk(stairPos, temp->getStairPositionY(), temp->getDirectionX());
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
				for (int i = 0; i < lstObject.size(); i++)
				{
					if (dynamic_cast<InitialStairEvent*>(lstObject.at(i)))
					{
						if (simon->isCollideWithOtherObject(lstObject.at(i)))
						{
							InitialStairEvent * temp = dynamic_cast<InitialStairEvent*>(lstObject.at(i));
							if (temp->getDirectionY() == DOWN)
							{
								simon->setDirectionY(DOWN);
								simon->isOnStair = true;
								float x, y, stairPos;
								simon->GetPosition(x, y);
								stairPos = temp->getStairPositionX();
								if (abs(x - stairPos) >= 1)
									simon->setAutoWalk(stairPos, temp->getStairPositionY(), temp->getDirectionX());
								else
								{
									simon->SetPosition(stairPos, temp->getStairPositionY());
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
		simon->setDirectionX(RIGHT);
	}
	else
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			simon->isWalking = true;
			simon->setDirectionX(LEFT);
		}
		else
		{
			simon->isWalking = false;
			simon->StandUp();
		}
}

void World_1_Water::OnKeyDown(int KeyCode)
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

void World_1_Water::OnKeyUp(int KeyCode)
{
}

void World_1_Water::Update(DWORD dt)
{
	Grid::GetInstance()->getList(lstObject, lstItem, camera);
	simon->Update(dt, &lstObject);
	simon->collisionWithEnenmy(&lstEnemy);
	for (int i = 0; i < lstObject.size(); i++)
	{
		lstObject.at(i)->Update(dt, &lstObject);

	}

	for (int i = 0; i < lstEnemy.size(); i++)
	{
		lstEnemy[i]->Update(dt, &lstObject);
	}

	for (int i = 0; i < lstBullet.size(); i++)
	{
		lstBullet[i]->Update(dt);
	}
	float x, y;
	simon->GetPosition(x, y);
	/*DebugOut(L"X= %f\n", x);*/
	/*DebugOut(L"Y= %f\n", y);*/
	if (camera->isFollowingSimon)
		camera->SetPosition(x - SCREEN_WIDTH / 2 + 30, camera->getY());
	camera->Update(dt);
}

void World_1_Water::LoadResources()
{
	MapManager::GetInstance()->setMap(WORLD_1_WATER);
	camera = new Camera(0, (float)(MapManager::GetInstance()->getMap()->getMapWidth() - SCREEN_WIDTH));
	camera->SetPosition(0, 0);

	Grid::GetInstance()->setMap(WORLD_1_WATER);

	simon = new Simon();
	ifstream inputSimonData(L"Resources/Temp.txt");
	if (inputSimonData.is_open())
	{
		inputSimonData.read((char*)&simon, sizeof(simon));
		inputSimonData.close();
		remove("Resources/Temp.txt");
	}
	simon->setCamera(camera);

	simon->SetPosition(0,0);
}

void World_1_Water::Render()
{
	MapManager::GetInstance()->getMap()->Render(camera);
	for (int i = 0; i < lstObject.size(); i++)
	{
		lstObject.at(i)->Render(camera);
	}

	for (int i = 0; i < lstEnemy.size(); i++)
	{
		lstEnemy.at(i)->Render(camera);
	}
	for (int i = 0; i < lstBullet.size(); i++)
	{
		lstBullet[i]->Render(camera);
	}
	simon->Render(camera);
}
