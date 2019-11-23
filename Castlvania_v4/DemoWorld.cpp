#include "DemoWorld.h"
#include"WorldManager.h"
#include"World_1.h"
#include"BigTorch.h"
#include"Brick.h"
#include"ObjectHidden.h"
#include"WhipUpgrade.h"
#include"BigHeart.h"
#include"Dagger_Item.h"
#include"SpecialMoneyBag.h"
#include"Grid.h"
void DemoWorld::KeyState(BYTE * states)
{
	if (simon->isAttacking ||  simon->isInAir || simon->isFreezing || simon->isAutoGo) return;
	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->Sit();
		if(Game::GetInstance()->IsKeyDown(DIK_RIGHT)) simon->setDirectionX(1);
		else if (Game::GetInstance()->IsKeyDown(DIK_LEFT)) simon->setDirectionX(-1);
		return;
	}
	else
	{
		simon->StandUp();
	}
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

void DemoWorld::OnKeyDown(int KeyCode)
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

void DemoWorld::OnKeyUp(int KeyCode)
{

}

void DemoWorld::Update(DWORD dt)
{	
	Grid::GetInstance()->getList(lstObject, lstItem, camera);
	simon->Update(dt, &lstObject);

	if (isSimonWalkingToCastle)
	{
		float x, y;
		simon->GetPosition(x, y);
		if (abs(x - POSITION_TO_STOP_AUTO_WALKING_X) <= 1.0f)
		{
			ofstream output(L"Resources/Data/Temp.txt");
			output.write((char*)&simon, sizeof(simon));
			output.close();
			WorldManager::GetInstance()->setWorld(new World_1());
			return;
		}
		
	}
	for (int i = 0; i < lstObject.size(); i++)
	{
		lstObject[i]->Update(dt, &lstObject);
		if (lstObject[i]->getHealth() == 0)
		{
			lstItem[lstObject[i]->getID()]->isOn = true;
			lstObject[i]->lostHealth(1);
		}

	}
	for (pair<int,Item*> element : lstItem)
	{
		if (element.second->isOn)
			element.second->Update(dt, &lstObject);
	}
	float x, y;
	simon->GetPosition(x, y);
	camera->SetPosition(x - SCREEN_WIDTH / 2 + 30, camera->getY());
	camera->Update(dt);

	checkCollisionSimonWithItem();
	checkCollisionSimonWithObjectHidden();
}

void DemoWorld::LoadResources()
{
	MapManager::GetInstance()->setMap(PROLOGUE);
	camera = new Camera(0, (float)(MapManager::GetInstance()->getMap()->getMapWidth() - SCREEN_WIDTH));
	camera->SetPosition(0, 0);
	Grid::GetInstance()->setMap(PROLOGUE);
	
	simon = new Simon();
	simon->setCamera(camera);
}

void DemoWorld::Render()
{
	MapManager::GetInstance()->getMap()->Render(camera);
	for (int i = 0; i < lstObject.size(); i++)
	{
		lstObject[i]->Render(camera);
	}
	for (pair<int, Item*> element : lstItem)
	{
		if (element.second->isOn)
		{
			element.second->RenderBoundingBox(camera);
			element.second->Render(camera);
		}
	}
	simon->Render(camera);
}

void DemoWorld::checkCollisionSimonWithItem()
{
	for (pair<int, Item*> element : lstItem)
	{
		if (element.second->isOn && element.second->isItemSpawned)
		{
			if (simon->isCollideWithOtherObject(element.second))
			{
				if(dynamic_cast<BigHeart*>(element.second))
				{ 
					simon->collectHeart(5);
				}
				if (dynamic_cast<WhipUpgrade*>(element.second))
				{
					simon->upgradeWhip();
				}
				if (dynamic_cast<Dagger_Item *>(element.second))
				{
					simon->setSecondaryWeapon(simon->KNIFE);
				}

				element.second->isOn = false;
			}
		}
	}
}

void DemoWorld::checkCollisionSimonWithObjectHidden()
{
	for (int i = 0; i < lstObject.size(); i++)
	{
		if (dynamic_cast<ObjectHidden*>(lstObject[i]))
		{
			if(simon->isCollideWithOtherObject(lstObject[i]))
				if (lstObject[i]->getID() == OBJECT_HIDDEN_ID_FOR_SPECIAL_BONUS)
				{
					if (lstItem[OBJECT_HIDDEN_ID_FOR_SPECIAL_BONUS]->isItemSpawned == false)
						lstItem[OBJECT_HIDDEN_ID_FOR_SPECIAL_BONUS]->isOn = true;
				}
				else
				{
					if (lstObject[i]->getID() == OBJECT_HIDDEN_ID_FOR_GO_TO_NEXT_LEVEL)
					{
						simon->setAutoWalk(POSITION_TO_STOP_AUTO_WALKING_X, POSITION_TO_STOP_AUTO_WALKING_Y, 1);
						isSimonWalkingToCastle = true;
					}
				}
		}
	}
}

DemoWorld::DemoWorld()
{
	LoadResources();
}


DemoWorld::~DemoWorld()
{
}
