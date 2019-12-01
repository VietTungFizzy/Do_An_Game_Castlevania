#pragma once
#include "GameObject.h"
#include"Simon.h"
#define BAT_BBOX_WIDTH 16
#define BAT_BBOX_HEIGHT 16
#define BAT_SPEED_X 0.1f
#define BAT_SPEED_Y 0.05f
class Bat :
	public CGameObject
{
private:
	Camera * camera;
	Simon * simon;
	LPANIMATION flyAni;
	int direction;
	bool isActive;
public:
	Bat(float x,float y,int direction,Camera * camera,Simon * simon);
	~Bat();

	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};

