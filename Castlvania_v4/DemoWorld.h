#pragma once
#include "GameWorld.h"
class DemoWorld :
	public GameWorld
{
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

