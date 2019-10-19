#pragma once
#include "Define.h"
#include"GameWorld.h"
#include"Texture.h"
#include"Sprite.h"
#include "Map.h"
class WorldManager
{
private:
	GameWorld * world;

public:
	static WorldManager * __instance;
	static WorldManager * GetInstance();
	void KeyState(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Render();
	void Update(DWORD dt);

	void setWorld(GameWorld * newWorld);
	WorldManager();
	~WorldManager();
};

