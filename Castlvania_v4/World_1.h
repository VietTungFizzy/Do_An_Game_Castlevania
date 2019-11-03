#pragma once
#include "GameWorld.h"
class World_1 :
	public GameWorld
{
public:
	void KeyState(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void Update(DWORD dt);
	void LoadResources();
	void Render();
	World_1();
	~World_1();
};

