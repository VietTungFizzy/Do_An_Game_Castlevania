#pragma once
#include "Weapon.h"
#define MORNING_STAR_1_BBOX_WIDTH 24
#define MORNING_STAR_1_BBOX_HEIGHT 8
#define MORNING_STAR_2_BBOX_WIDTH 24
#define MORNING_STAR_2_BBOX_HEIGHT 7
#define MORNING_STAR_3_BBOX_WIDTH 39
#define MORNING_STAR_3_BBOX_HEIGHT 7
#define ANIMATION_LAST_FRAME 2

class MorningStar :
	public Weapon
{
private:
	vector<LPANIMATION> lstAnimation;
	int level,
		direction;
public:
	void InitialAttack(float x, float y,int direction);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) ;
	void Render(Camera * camera);
	void Upgrade();
	MorningStar();
	~MorningStar();
};

