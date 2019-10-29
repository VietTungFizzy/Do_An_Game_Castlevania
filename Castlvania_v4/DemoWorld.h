#pragma once
#include "GameWorld.h"
#include"Map.h"
#include"Camera.h"
#include"Simon.h"
#include"Item.h"
class DemoWorld :
	public GameWorld
{
private:
	Camera * camera;
	std::vector<LPGAMEOBJECT> lstObject;
	vector<Item * >lstItem;
	Simon * simon;
public:

	void KeyState(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void Update(DWORD dt);
	void LoadResources();
	void Render();

	void createItem(int id,float x, float y);
	DemoWorld();
	~DemoWorld();
};

