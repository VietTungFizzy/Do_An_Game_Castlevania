#pragma once
#include "GameObject.h"

#define FISH_BBOX_WIDTH 16
#define FISH_BBOX_HEIGHT 32
#define FISH_SHOOTING_SPRITE_ID 0
#define FISH_GO_UP_SPRITE_ID 2
#define FISH_WALKING_SPEED 0.01f
#define FISH_GO_UP_SPEED -0.4f
#define FISH_GRAVITY 0.01f
#define FISH_DISTANCE_HAVE_TO_WALK 100.0f
#define FISH_DISTENCE_HAVE_TO_GO_UP 200.0f
#define FISH_DELAY_TIME_AFTER_SHOOT 700
class Fish :
	public CGameObject
{
private:
	Camera * camera;
	LPANIMATION walkAni;
	LPSPRITE goUpSprite;
	LPSPRITE shootingSprite;
	vector<LPGAMEOBJECT> * lstBullet;
	int direction;

	bool isGoingUp;
	bool isWalking;
	bool isShooting;
	bool isFireBallCreated;

	float savedX;
	float savedY;
	DWORD timeWaited;
public:
	Fish(float x, float y, int direction, Camera * camera, vector<LPGAMEOBJECT> * lstBullet);
	~Fish();

	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};

