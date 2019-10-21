#include "DemoWorld.h"
#include"BigTorch.h"
#include"Brick.h"
#include"ObjectHidden.h"

void DemoWorld::KeyState(BYTE * states)
{
	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
		camera->SetPosition(camera->getX() + 10, camera->getY());
	if(Game::GetInstance()->IsKeyDown(DIK_LEFT))
		camera->SetPosition(camera->getX() - 10, camera->getY());
}

void DemoWorld::OnKeyDown(int KeyCode)
{
}

void DemoWorld::OnKeyUp(int KeyCode)
{
}

void DemoWorld::Update(DWORD dt)
{


	camera->Update(dt);
	simon->Update(dt, &lstObject);
}

void DemoWorld::LoadResources()
{
	MapManager::GetInstance()->setMap(PROLOGUE);
	camera = new Camera(0, MapManager::GetInstance()->getMap()->getMapWidth() - SCREEN_WIDTH);
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
