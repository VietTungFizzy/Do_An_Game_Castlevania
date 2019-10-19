#include "DemoWorld.h"



void DemoWorld::KeyState(BYTE * states)
{
}

void DemoWorld::OnKeyDown(int KeyCode)
{
}

void DemoWorld::OnKeyUp(int KeyCode)
{
}

void DemoWorld::Update(DWORD dt)
{
}

void DemoWorld::LoadResources()
{
	MapManager::GetInstance()->setMap(PROLOGUE);
	camera = new Camera(0, MapManager::GetInstance()->getMap()->getMapWidth());
	camera->SetPosition(0, 0);
}

void DemoWorld::Render()
{
	MapManager::GetInstance()->getMap()->Render(camera);
}

DemoWorld::DemoWorld()
{
	LoadResources();
}


DemoWorld::~DemoWorld()
{
}
