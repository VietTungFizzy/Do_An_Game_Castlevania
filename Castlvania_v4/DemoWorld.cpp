#include "DemoWorld.h"
#include"BigTorch.h"
#include"Brick.h"
#include"ObjectHidden.h"

void DemoWorld::KeyState(BYTE * states)
{
	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		simon->Sit();
	}
	if (simon->isAttacking || simon->isSitting || simon->isInAir) return;
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
		}
}

void DemoWorld::OnKeyDown(int KeyCode)
{
	if (simon->isInAir) return;
	if (KeyCode == DIK_X)
	{
		simon->Jump();
	}
}

void DemoWorld::OnKeyUp(int KeyCode)
{
	if (KeyCode == DIK_DOWN)
	{
		float x, y;
		simon->GetPosition(x, y);
		simon->SetPosition(x, y +2);
		simon->isSitting = false;
	}
}

void DemoWorld::Update(DWORD dt)
{	
	simon->Update(dt, &lstObject);
	
	float x, y;
	simon->GetPosition(x, y);
	camera->SetPosition(x - SCREEN_WIDTH / 2 + 30, camera->getY());
	camera->Update(dt);
}

void DemoWorld::LoadResources()
{
	MapManager::GetInstance()->setMap(PROLOGUE);
	camera = new Camera(0, (float)(MapManager::GetInstance()->getMap()->getMapWidth() - SCREEN_WIDTH));
	camera->SetPosition(0, 0);

	std::ifstream input(L"Resources/Map_Prologue_Object_Description.txt");
	int n,objectID,x,y,w,h;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> objectID >> x >> y >> w >> h;
		LPGAMEOBJECT temp;
		switch (objectID)
		{
		case BRICK_OBJ:
			temp = new Brick(x, y, w, h);
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
		lstObject.push_back(temp);
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
	simon->Render(camera);
}

DemoWorld::DemoWorld()
{
	LoadResources();
}


DemoWorld::~DemoWorld()
{
}
