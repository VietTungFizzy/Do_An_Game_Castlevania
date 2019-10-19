#pragma once
#include "GameWorld.h"
#include"Map.h"
#include"Camera.h"
class DemoWorld :
	public GameWorld
{
private:
	Camera * camera;
	
public:

	void KeyState(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void Update(DWORD dt);
	void LoadResources();
	void Render();

	DemoWorld();
	~DemoWorld();
};

