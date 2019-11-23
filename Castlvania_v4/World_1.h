#pragma once
#include "GameWorld.h"
#include"Map.h"
#include"Camera.h"
#include"Simon.h"
#include"Item.h"
#include"Define.h"

class World_1 :
	public GameWorld
{
private:
	Camera * camera;
	vector<LPGAMEOBJECT> lstObject;
	unordered_map<int, Item*> lstItem;
	Simon * simon;
	int stage;
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

