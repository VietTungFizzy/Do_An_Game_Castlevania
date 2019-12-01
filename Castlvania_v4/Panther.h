#pragma once
#include "GameObject.h"
#include "Simon.h"

//General Attribute
#define PANTHER_BBOX_WIDTH 32
#define PANTHER_BBOX_HEIGHT 16
#define PANTHER_GRAVITY 0.00055f
#define PANTHER_RUNNING_SPEED 0.1f
#define PANTHER_JUMPING_SPEED_X 0.3f
#define PANTHER_JUMPING_SPEED_Y -0.2f
#define PANTHER_BBOX_WIDTH_EXTEND SCREEN_WIDTH
#define PANTHER_SITTING_SPRITE_ID 0
#define PANTHER_JUMPING_SPRITE_ID 3
#define SIMON_DETECTION_RANGE 75

//Panther type 1
#define PANTHER_1_POSITION_X 690.0f
#define PANTHER_1_POSITION_Y 79.0f
#define PANTHER_1_AUTO_GO_POSITION_LEFT 682.0f
#define PANTHER_1_AUTO_GO_POSITION_RIGHT 738.0f

//Panther type 2
#define PANTHER_2_POSITION_X 875.0f 
#define PANTHER_2_POSITION_Y 30.0f
#define PANTHER_2_AUTO_GO_POSITION_LEFT 752.0f
#define PANTHER_2_AUTO_GO_POSITION_RIGHT_1 914.0f
#define PANTHER_2_AUTO_GO_POSITION_RIGHT_2 930.0f

//Panther type 3
#define PANTHER_3_POSITION_X 938.0f
#define PANTHER_3_POSITION_Y 75.0f
#define PANTHER_3_AUTO_GO_POSITION_LEFT 930.0f
#define PANTHER_3_AUTO_GO_POSITION_RIGHT 1005.0f

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
	bool isAutoGo;

	Camera * camera;
	Simon* simon;
	int type;
	float savedX;
	float posToGo;

	//Support Function
	bool isSimonReachable();
	void jump();
	void run();

public:
	Panther(int type,Simon * simon,Camera * camera);
	~Panther();

	
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	void Render(Camera * camera);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};

