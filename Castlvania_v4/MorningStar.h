#pragma once
#include "Weapon.h"
#define MORNING_STAR_1_BBOX_WIDTH 26
#define MORNING_STAR_1_BBOX_HEIGHT 7
#define MORNING_STAR_2_BBOX_WIDTH 25
#define MORNING_STAR_2_BBOX_HEIGHT 6
#define MORNING_STAR_3_BBOX_WIDTH 39
#define MORNING_STAR_3_BBOX_HEIGHT 6
#define ANIMATION_LAST_FRAME 3
#define ANIMATION_FRAME_TO_CHECK_COLLSION 2
#define ADJUST_BBOX_POSITION_X_SIMON_STAND_RIGHT 43
#define ADJUST_BBOX_POSITION_Y_SIMON_STAND_RIGHT 7
#define ADJUST_BBOX_POSITION_X_SIMON_STAND_LEFT 28
#define ADJUST_BBOX_POSITION_Y_SIMON_STAND_LEFT 7
#define ADJUST_POSITION_X_SIMON_STAND_RIGHT 12
#define ADJUST_POSITION_X_SIMON_STAND_LEFT 52
#define ADJUST_POSITION_Y_SIMON_STAND 3
#define ADJUST_POSITION_Y_SIMON_SIT 13
class MorningStar :
	public Weapon
{
private:
	vector<LPANIMATION> lstAnimation;
	int level;
public:
	void InitialAttack(float x, float y,int directionX);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) ;
	void Render(Camera * camera);
	void Upgrade();
	MorningStar();
	~MorningStar();
};

