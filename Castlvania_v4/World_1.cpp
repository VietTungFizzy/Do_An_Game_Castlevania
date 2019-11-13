#include "World_1.h"
#include"Brick.h"
#include"LittleTorch.h"
#include"BreakableBrick.h"

void World_1::KeyState(BYTE * states)
{
}

void World_1::OnKeyDown(int KeyCode)
{
}

void World_1::OnKeyUp(int KeyCode)
{
}

void World_1::Update(DWORD dt)
{
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
			default:
				break;
			}
			tempVector.push_back(tempObj);
		}
		lstObject[i] = tempVector;
	}

	simon = new Simon(camera);
	stage = 0;
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
