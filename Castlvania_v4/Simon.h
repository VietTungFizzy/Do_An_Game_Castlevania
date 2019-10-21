#pragma once
#include"GameObject.h"
#include"Camera.h"
#define SIMON_GRAVITY 0.12f

//spriteID
#define SIMON_STANDING_SPRITE_ID 0
#define SIMON_SITTING_SPRITE_ID 1

//BBox
#define SIMON_DIRECTION_RIGHT_OFFSET_X 10
#define SIMON_DIRECTION_LEFT_OFFSET_X 6
#define SIMON_OFFSET_Y 2
#define SIMON_STANDING_BBOX_WIDTH 16
#define SIMON_STANDING_BBOX_HEIGHT 30
class Simon :
	public CGameObject
{
private:
	int health,
		direction;
	std::vector<LPANIMATION> lstAnimation;
	std::vector<LPSPRITE> lstSprite;
	Camera * camera;
public:
	bool isAttacking;
	bool isSitting;
	bool isFreazing;
	bool isWalking;
	bool isHurt;
	bool isInAir;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void setDirection(int direction) { this->direction = direction; }


	Simon(Camera * camera);
	~Simon();
};

