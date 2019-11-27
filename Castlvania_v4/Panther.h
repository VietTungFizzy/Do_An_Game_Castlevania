#pragma once
#include "GameObject.h"
#include "Simon.h"

#define PANTHER_BBOX_WIDTH 32
#define PANTHER_BBOX_HEIGHT 16
#define PANTHER_GRAVITY 0.00055f
#define PANTHER_RUNNING_SPEED 0.18f
#define PANTHER_JUMPING_SPEED_X -0.3f
#define PANTHER_JUMPING_SPEED_Y 0.2f
#define PANTHER_BBOX_WIDTH_EXTEND SCREEN_WIDTH
#define PANTHER_SITTING_SPRITE_ID 0
#define PANTHER_JUMPING_SPRITE_ID 3
#define SIMON_DETECTION_RANGE 50
class Panther :
	public CGameObject
{
private:
	int direction;
	LPANIMATION runAni;
	LPSPRITE jumpingSprite;
	LPSPRITE sittingSprite;

	bool isJumping;
	bool isRunning;
	bool isSitting;
	bool isActive;

	Camera * camera;
	Simon* simon;
public:
	Panther(float x, float y,Simon * simon,Camera * camera);
	~Panther();

	
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	bool isSimonReachable();
	void jump();
	void run();
};

