#pragma once
#include "Define.h"
class GameWorld
{
public:
	virtual void KeyState(BYTE *states) =0;
	virtual void OnKeyDown(int KeyCode) =0;
	virtual void OnKeyUp(int KeyCode) =0;

	virtual void Update(DWORD dt) =0;
	virtual void LoadResources() = 0;
	virtual void Render() = 0;
	GameWorld();
	~GameWorld();
};

