#pragma once
#include "GameObject.h"
#define GHOST_BBOX_WIDTH 16
#define GHOST_BBOX_HEIGHT 32
#define GHOST_WALKING_SPEED 0.06f
#define GHOST_GRAVITY 0.005f
class Ghost :
	public CGameObject
{
private:
	LPANIMATION walkAni;
	int direction;
	Camera* camera;

	bool isActive;
public:
	Ghost(float x, float y, int direction,Camera * camera);
	~Ghost();

	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};

