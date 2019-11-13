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

void DemoWorld::KeyState(BYTE * states)
{
	if (simon->isAttacking ||  simon->isInAir || simon->isFreezing || simon->isAutoGo) return;
	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->Sit();
		if(Game::GetInstance()->IsKeyDown(DIK_RIGHT)) simon->setDirection(1);
		else if (Game::GetInstance()->IsKeyDown(DIK_LEFT)) simon->setDirection(-1);
		return;
	}
	else
	{
		simon->StandUp();
	}
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		simon->isWalking = true;
		simon->setDirection(1);
	}
	else
		if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			simon->isWalking = true;
			simon->setDirection(-1);
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
	simon->Update(dt, &lstObject);

	if (isSimonWalkingToCastle)
	{
		float x, y;
		simon->GetPosition(x, y);
		if (abs(x - POSITION_TO_STOP_AUTO_WALKING) <= 1.0f)
		{
			WorldManager::GetInstance()->setWorld(new World_1());
			return;
		}
		
	}
	for (int i = 0; i < lstObject.size(); i++)
	{
		lstObject[i]->Update(dt, &lstObject);
		if (lstObject[i]->getHealth() == 0)
		{
			lstItem[i]->isOn = true;
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

	std::ifstream input(L"Resources/Map_Prologue_Object_Description.txt");
	int n,objectType,x,y,w,h,type;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> objectType >> x >> y >> w >> h >> type;
		LPGAMEOBJECT temp = NULL;
		switch (objectType)
		{
		case BRICK_OBJ:
			temp = new Brick(x, y, w, h,type);
			break;
		case BIG_TORCH_OBJ:
			temp = new BigTorch(x, y);
			break;
		case HIDDEN_OBJ:
			temp = new ObjectHidden(x, y,w,h);
			break;
		default:
			break;
		}
		temp->setID(i);
		lstObject.push_back(temp);
	}
	input >> n;
	int objectid, itemType,model;
	for (int i = 0; i < n; i++)
	{
		input >> objectid >> itemType >> x >> y >> model;
		Item * temp = NULL;
		switch (itemType)
		{
		case WHIP_UPGRADE:
			temp = new WhipUpgrade(x, y);
			break;
		case BIG_HEART:
			temp = new BigHeart(x, y);
			break;
		case DAGGER:
			temp = new Dagger_Item(x, y);
			break;
		case SPECIAL_MONEY_BAG:
			temp = new SpecialMoneyBag(x, y);
		default:
			break;
		}
		lstItem[objectid] = temp;
	}
	simon = new Simon(camera);
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
	if (simon->isCollideWithOtherObject(lstObject[OBJECT_HIDDEN_ID_FOR_SPECIAL_BONUS]))
	{
		if(lstItem[OBJECT_HIDDEN_ID_FOR_SPECIAL_BONUS]->isItemSpawned == false)
			lstItem[OBJECT_HIDDEN_ID_FOR_SPECIAL_BONUS]->isOn = true;
	}
	else
	{
		if (simon->isCollideWithOtherObject(lstObject[OBJECT_HIDDEN_ID_FOR_GO_TO_NEXT_LEVEL]))
		{
			simon->setAutoWalk(POSITION_TO_STOP_AUTO_WALKING);
			isSimonWalkingToCastle = true;
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
