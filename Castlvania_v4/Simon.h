#pragma once
#include"GameObject.h"
#include"Camera.h"
#include"MorningStar.h"
//spriteID
#define SIMON_STANDING_SPRITE_ID 0
#define SIMON_SITTING_SPRITE_ID 1
#define SIMON_ON_STAIR_GOING_UP_SPRITE_ID 2
#define SIMON_ON_STAIR_GOING_DOWN_SPRITE_ID 3

//BBox
#define SIMON_DIRECTION_RIGHT_OFFSET_X 10
#define SIMON_DIRECTION_LEFT_OFFSET_X 6
#define SIMON_STANDING_OFFSET_Y 2
#define SIMON_STANDING_BBOX_WIDTH 16
#define SIMON_STANDING_BBOX_HEIGHT 30
#define SIMON_SITTING_BBOX_WIDTH 16
#define SIMON_SITTING_BBOX_HEIGHT 24
#define SIMON_SITTING_OFFSET_Y 12
#define SIMON_SITTING_LEFT_OFFSET_X 6
#define SIMON_SITTING_RIGHT_OFFSET_X 10
#define SIMON_JUMPING_BBOX_HEIGHT 24
#define SIMON_JUMPING_BBOX_OFFSET_Y 9

//Simon's attribute
#define SIMON_GRAVITY 0.0005f
#define SIMON_WALKING_SPEED 0.12f
#define SIMON_JUMPING_SPEED -0.2f
#define SIMON_FREEZE_TIME_MAX 500
#define SIMON_STEP_ON_STAIR_SPEED 0.025f

//Direction
#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1

//Miscellaneous

class Simon :
	public CGameObject
{
public:
	//State
	bool isAttacking;
	bool isSitting;
	bool isFreezing;
	bool isWalking;
	bool isHurt;
	bool isInAir;
	bool isAutoGo;
	bool isOnStair;

	enum WeaponType
	{
		MORNING_STAR,
		KNIFE,
		AXE,
		HOLY_WATER,
		BOOMERANG,
		STOP_WATCH,
		NO_SECONDARY_WEAPON
	};
private:
	//Attribute
	int directionX;
	int directionY;
	int heart;

	//Graphic
	std::vector<LPANIMATION> lstAnimation;
	std::vector<LPSPRITE> lstSprite;
	
	//Sub-Objects
	unordered_map<WeaponType, Weapon*> lstWeapon;
	Camera * camera;
	
	//Parameters for calculation
	WeaponType currentSecondaryWeaponType;
	DWORD timeFreezed;


	//Auto Go
	int directionAfterAutoGo;
	int autoGoDirection;
	float posToGo;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void setDirectionX(int directionX) { this->directionX = directionX; }
	void setDirectionY(int directionY) { this->directionY = directionY; }
	
	void collisionWithGround(vector<LPGAMEOBJECT> *coObjects = NULL);
	void collisionWhenSimonOnStair(vector<LPGAMEOBJECT> *coObjects = NULL);

	void Jump();
	void Sit();
	void StandUp();
	void StepUp();
	void StepDown();
	void Attack(WeaponType weaponType);
	

	void setAutoWalk(float positionToGo, int directionAfterAutoGo);
	void upgradeWhip();
	void setSecondaryWeapon(WeaponType weaponType);
	WeaponType getSecondaryWeapon();
	void collectHeart(int amount) { heart += amount;}
	Simon(Camera * camera);
	~Simon();
};

