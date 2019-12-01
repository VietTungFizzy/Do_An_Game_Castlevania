#pragma once
#include "GameWorld.h"
#include"Camera.h"
#include"Item.h"
#include"Simon.h"
class World_1_Water :
	public GameWorld
{
private:
	Camera * camera;
	vector<LPGAMEOBJECT> lstObject;
	unordered_map<int, Item*> lstItem;
	vector<LPGAMEOBJECT> lstEnemy;
	vector<LPGAMEOBJECT> lstBullet;
	Simon * simon;


public:
	World_1_Water();
	~World_1_Water();

	void KeyState(BYTE * states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void Update(DWORD dt);
	void LoadResources();
	void Render();
};

