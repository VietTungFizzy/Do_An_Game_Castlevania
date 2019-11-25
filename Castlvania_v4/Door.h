#pragma once
#include "GameObject.h"
#define DOOR_BBOX_WIDTH 16
#define DOOR_BBOX_HEIGHT 32
#define DOOR_ANIMATION_FRAME_FULLY_OPENED 2
#define DOOR_ANIMATION_FRAME_FULLY_CLOSED 2
class Door :
	public CGameObject
{
private:
	LPSPRITE spriteClosed;
	LPSPRITE spriteOpened;
	LPANIMATION animationOpen;
	LPANIMATION animationClose;
public:
	bool isOpen;
	bool isProcessingOpen;
	bool isWaitingSimonGoThrough;
	bool isProcessingClose;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void open();
	void close();
	Door(float x, float y);
	~Door();
};

