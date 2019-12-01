#include "World_1.h"
#include "Brick.h"
#include "LittleTorch.h"
#include "BreakableBrick.h"
#include "InitialStairEvent.h"
#include "Grid.h"
#include "Door.h"
#include "Ghost.h"
#include "Panther.h"
void World_1::KeyState(BYTE * states)
{
	if (simon->isAttacking || simon->isInAir 
		|| simon->isFreezing || simon->isAutoGo 
		|| isSimonGoNextStage) return;
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
							if (temp->getDirectionY() == DOWN)
							{
								simon->setDirectionY(DOWN);
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

void World_1::OnKeyDown(int KeyCode)
{
	if (simon->isAttacking || simon->isFreezing || simon->isAutoGo || isSimonGoNextStage) return;
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

	if (KeyCode == DIK_TAB)
	{
		stage++;
		if (stage > 2) stage = 0;
		switch (stage)
		{
		case 0:
			simon->SetPosition(10, 10);
			camera->SetPosition(0, 0);
			camera->setBoundary(CAMERA_CONSTRAINT_FOR_STAGE_1_LEFT, CAMERA_CONSTRAINT_FOR_STAGE_1_RIGHT);
			break;
		case 1:
			simon->SetPosition(1550, 10);
			camera->SetPosition(CAMERA_CONSTRAINT_FOR_STAGE_2_LEFT, 0);
			camera->setBoundary(CAMERA_CONSTRAINT_FOR_STAGE_2_LEFT, CAMERA_CONSTRAINT_FOR_STAGE_2_RIGHT);
			break;
		case 2:
			simon->SetPosition(2060, 10);
			camera->SetPosition(CAMERA_CONSTRAINT_FOR_STAGE_3_LEFT, 0);
			camera->setBoundary(CAMERA_CONSTRAINT_FOR_STAGE_3_LEFT, CAMERA_CONSTRAINT_FOR_STAGE_3_RIGHT);
			break;
		default:
			break;
		}
	}
}

void World_1::OnKeyUp(int KeyCode)
{
}

void World_1::Update(DWORD dt)
{
	if (isSimonGoNextStage)
	{
		if (isSimonGoThroughDoor)
		{
			if (camera->isAutoGo == false)
			{
				if (camera->getX() != CAMERA_CONSTRAINT_FOR_STAGE_2_LEFT)
				{
					stage++;
					camera->setAutoGo(CAMERA_CONSTRAINT_FOR_STAGE_2_LEFT);
				}
				else
				{
					Door * temp = NULL;
					for (int i = 0; i < lstObject.size(); i++)
					{
						if (dynamic_cast<Door*>(lstObject[i]))
						{
							temp = dynamic_cast<Door*>(lstObject[i]);
							temp->close();
						}
					}
					camera->setBoundary(CAMERA_CONSTRAINT_FOR_STAGE_2_LEFT, CAMERA_CONSTRAINT_FOR_STAGE_2_RIGHT);
					isSimonGoNextStage = false;
					camera->isFollowingSimon = true;
				}
				
			}
		}
		else
		{
			if (camera->isAutoGo == false)
			{
				Door * temp = NULL;
				for (int i = 0; i < lstObject.size(); i++)
				{
					if (dynamic_cast<Door*>(lstObject[i]))
					{
						temp = dynamic_cast<Door*>(lstObject[i]);
						temp->open();
					}
				}
				if (temp->isWaitingSimonGoThrough)
				{
					float x, y;
					simon->GetPosition(x, y);
					if (x != SIMON_POSITION_WHEN_GO_TO_STAGE_2)
						simon->setAutoWalk(SIMON_POSITION_WHEN_GO_TO_STAGE_2, y, RIGHT);
					else
					{
						isSimonGoThroughDoor = true;
					}
				}
			}
		}
	}

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

	float x, y;
	simon->GetPosition(x, y);
	/*DebugOut(L"X= %f\n", x);*/
	/*DebugOut(L"Y= %f\n", y);*/
	if (camera->isFollowingSimon)
		camera->SetPosition(x - SCREEN_WIDTH / 2 + 30, camera->getY());
	camera->Update(dt);

	processSimonCollideWithObjectHidden();
	processWeaponWithEnemy();
	spawnEnemy();
}

void World_1::LoadResources()
{
	MapManager::GetInstance()->setMap(WORLD_1_GROUND);
	camera = new Camera(CAMERA_CONSTRAINT_FOR_STAGE_1_LEFT, (float)(CAMERA_CONSTRAINT_FOR_STAGE_1_RIGHT - SCREEN_WIDTH));
	camera->SetPosition(0, 0);

	Grid::GetInstance()->setMap(WORLD_1_GROUND);

	simon = new Simon();
	ifstream inputSimonData(L"Resources/Temp.txt");
	if (inputSimonData.is_open())
	{
		inputSimonData.read((char*)&simon, sizeof(simon));
		inputSimonData.close();
		remove("Resources/Temp.txt");
	}
	simon->setCamera(camera);
	stage = 0;
	timeEnemyCreated = 0;
	timeWaveEnded = 0;
	//testing
	simon->SetPosition(929, 10);
}

void World_1::Render()
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
	simon->Render(camera);
}

void World_1::processSimonCollideWithObjectHidden()
{
	for (int i = 0; i < lstObject.size(); i++)
	{
		if (dynamic_cast<ObjectHidden*>(lstObject[i]))
		{
			if (lstObject[i]->getID() == OBJECT_HIDDEN_ID_FOR_GO_TO_STAGE_2)
			{
				if (simon->isCollideWithOtherObject(lstObject[i]) && isSimonGoNextStage ==false)
				{
					isSimonGoNextStage = true;
					isSimonGoThroughDoor = false;
					camera->setAutoGo(CAMERA_POSITION_1_WHEN_SIMON_GO_TO_STAGE_2);
					camera->setBoundary(0, CAMERA_CONSTRAINT_FOR_STAGE_2_RIGHT);
					camera->isFollowingSimon = false;
					simon->isWalking = false;
				}
			}
		}
	}
}

void World_1::processWeaponWithEnemy()
{
	for (auto i : simon->lstWeapon)
	{
		if (i.second == NULL) continue;
		if (i.second->isOn && i.second->isWeaponSpawned)
		{
			for (int j = 0; j < lstEnemy.size(); j++)
			{
				if (i.second->isHit(lstEnemy[j]))
				{
					lstEnemy[j]->lostHealth(1);
				}
			}
		}
	}
}

void World_1::spawnEnemy()
{
	float x, y;
	simon->GetPosition(x, y);
	DWORD now = GetTickCount();
	if (isInWave)
	{
		if (amountEnemy < AMOUNT_ENEMY_MAX_AT_1_TIME)
		{
#pragma region Ghost Area
			if (x <= AREA_ENEMY_SPAWN_1_BOUNDARY_RIGHT && x >= AREA_ENEMY_SPAWN_1_BOUNDARY_LEFT)
			{
				if (now - timeEnemyCreated >= TIME_BETWEEN_SPAWN_2_ENEMY)
				{
					if (camera->getX() - camera->getBoundaryLeft() > GHOST_BBOX_WIDTH)
					{
						int random = rand() % 4;
						if (random == 0)
							lstEnemy.push_back(new Ghost(camera->getX() - GHOST_BBOX_WIDTH, y - 10, RIGHT, camera));
						else
							lstEnemy.push_back(new Ghost(camera->getX() + SCREEN_WIDTH, y - 10, LEFT, camera));
					}
					else
					{
						lstEnemy.push_back(new Ghost(camera->getX() + SCREEN_WIDTH, y - 10, LEFT, camera));
					}
					timeEnemyCreated = now;
					amountEnemy++;

					if (amountEnemy == 3)
					{
						isInWave = false;
					}
				}
			}

			if (x <= AREA_ENEMY_SPAWN_3_BOUNDARY_RIGHT && x >= AREA_ENEMY_SPAWN_3_BOUNDARY_LEFT)
			{
				if ((CAMERA_CONSTRAINT_FOR_STAGE_1_RIGHT - (camera->getX() + SCREEN_WIDTH) > GHOST_BBOX_WIDTH))
				{
					int random = rand() % 4;
					if (random == 0)
						lstEnemy.push_back(new Ghost(camera->getX() - GHOST_BBOX_WIDTH, y - 10, RIGHT, camera));
					else
						lstEnemy.push_back(new Ghost(camera->getX() + SCREEN_WIDTH, y - 10, LEFT, camera));
				}
				else
				{
					lstEnemy.push_back(new Ghost(camera->getX() - GHOST_BBOX_WIDTH, y - 10, RIGHT, camera));
				}
				timeEnemyCreated = now;
				amountEnemy++;

				if (amountEnemy == AMOUNT_ENEMY_MAX_AT_1_TIME)
				{
					isInWave = false;
				}
			}
#pragma endregion

#pragma region Panther Area
			if (x <= AREA_ENEMY_SPAWN_2_BOUNDARY_RIGHT && x >= AREA_ENEMY_SPAWN_2_BOUNDARY_LEFT)
			{
				if (now - timeEnemyCreated >= TIME_BETWEEN_SPAWN_2_ENEMY)
				{
					lstEnemy.push_back(new Panther(1, simon, camera));
					/*lstEnemy.push_back(new Panther(2, simon, camera));
					lstEnemy.push_back(new Panther(3, simon, camera));*/
					timeEnemyCreated = now;
					amountEnemy+= 3;

					if (amountEnemy == AMOUNT_ENEMY_MAX_AT_1_TIME)
					{
						isInWave = false;
					}
				}
			}
#pragma endregion
		}
	}
	else
	{
		if (amountEnemy > 0)
		{
			int temp = 0;
			for (int i = 0; i < lstEnemy.size(); i++)
			{
				if (lstEnemy[i]->getHealth() <= 0)
				{
					temp++;
				}
			}
			if (temp == amountEnemy)
			{
				amountEnemy = 0;
				timeWaveEnded = now;
				lstEnemy.~vector();
			}
		}
		else
			if (now - timeWaveEnded >= TIME_BETWEEN_2_WAVE)
				isInWave = true;
	}
}

World_1::World_1()
{
	LoadResources();
}


World_1::~World_1()
{
}
