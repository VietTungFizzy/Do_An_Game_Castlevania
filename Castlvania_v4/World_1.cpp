#include "World_1.h"
#include"Brick.h"
#include"LittleTorch.h"
#include"BreakableBrick.h"
#include "InitialStairEvent.h"
#include "Grid.h"
void World_1::KeyState(BYTE * states)
{
	if (simon->isAttacking || simon->isInAir || simon->isFreezing || simon->isAutoGo) return;
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
						if (temp->getDirectionY() == -1)
						{
							simon->setDirectionY(-1);
							simon->isOnStair = true;
							float x, y, stairPos;
							simon->GetPosition(x, y);
							stairPos = temp->getStairPositionX();
							if (abs(x - stairPos) >= 1)
								simon->setAutoWalk(stairPos, temp->getStairPositionY(),temp->getDirectionX());
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
							if (temp->getDirectionY() == 1)
							{
								simon->setDirectionY(1);
								simon->isOnStair = true;
								float x, y, stairPos;
								simon->GetPosition(x, y);
								stairPos = temp->getStairPositionX();
								if (abs(x - stairPos) >= 1)
									simon->setAutoWalk(stairPos, temp->getStairPositionY(),temp->getDirectionX());
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
	Grid::GetInstance()->getList(lstObject, lstItem, camera);
	simon->Update(dt, &lstObject);
	for (int i = 0; i < lstObject.size(); i++)
	{
		lstObject.at(i)->Update(dt, &lstObject);
		/*if (lstObject.at(i)->getHealth() == 0)
		{
			lstObject.at(i)->lostHealth(1);
		}*/

	}

	float x, y;
	simon->GetPosition(x, y);
	DebugOut(L"X= %f\n", x);
	/*DebugOut(L"Y= %f\n", y);*/
	camera->SetPosition(x - SCREEN_WIDTH / 2 + 30, camera->getY());
	camera->Update(dt);
	
}

void World_1::LoadResources()
{
	MapManager::GetInstance()->setMap(WORLD_1);
	camera = new Camera(0, (float)(MapManager::GetInstance()->getMap()->getMapWidth() - SCREEN_WIDTH));
	camera->SetPosition(0, 0);

	Grid::GetInstance()->setMap(WORLD_1);

	simon = new Simon();
	ifstream inputSimonData(L"Resources/Data/Temp.txt");
	if (inputSimonData.is_open())
	{
		inputSimonData.read((char*)&simon, sizeof(simon));
		remove("Resources/Data/Temp.txt");
	}
	inputSimonData.close();
	simon->setCamera(camera);
	stage = 0;

	//testing
	simon->SetPosition(1500, 10);
}

void World_1::Render()
{
	MapManager::GetInstance()->getMap()->Render(camera);
	for (int i = 0; i < lstObject.size(); i++)
	{
		lstObject.at(i)->Render(camera);
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
