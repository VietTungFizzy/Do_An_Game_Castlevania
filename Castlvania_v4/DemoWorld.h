#pragma once
#include "GameWorld.h"
#include"Map.h"
#include"Camera.h"
#include"Simon.h"
#include"Item.h"
#include"Define.h"
class DemoWorld :
	public GameWorld
{
private:
	Camera * camera;
	std::vector<LPGAMEOBJECT> lstObject;
	unordered_map<int,Item*> lstItem;
	Simon * simon;
public:

	void KeyState(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void Update(DWORD dt);
	void LoadResources();
	void Render();

	void checkCollisionSimonWithItem();
	DemoWorld();
	~DemoWorld();
};

