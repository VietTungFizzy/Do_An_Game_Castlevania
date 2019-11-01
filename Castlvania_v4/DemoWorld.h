#pragma once
#include "GameWorld.h"
#include"Map.h"
#include"Camera.h"
#include"Simon.h"
#include"Item.h"
#include"Define.h"

#define OBJECT_HIDDEN_ID_FOR_GO_TO_NEXT_LEVEL 6
#define OBJECT_HIDDEN_ID_FOR_SPECIAL_BONUS 7
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
	void checkCollisionSimonWithObjectHidden();
	DemoWorld();
	~DemoWorld();
};

