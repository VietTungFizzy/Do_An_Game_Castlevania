#pragma once
#include"GameObject.h"
#include"Camera.h"
#include"MorningStar.h"
//spriteID
#define SIMON_STANDING_SPRITE_ID 0
#define SIMON_SITTING_SPRITE_ID 1

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

class Simon :
	public CGameObject
{
public:
	bool isAttacking;
	bool isSitting;
	bool isFreazing;
	bool isWalking;
	bool isHurt;
	bool isInAir;

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
	int direction;
	int heart;
	std::vector<LPANIMATION> lstAnimation;
	std::vector<LPSPRITE> lstSprite;
	unordered_map<WeaponType, Weapon*> lstWeapon;
	Camera * camera;
	WeaponType currentSecondaryWeaponType;

public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	void setDirection(int direction) { this->direction = direction; }
	void collisionWithGround(vector<LPGAMEOBJECT> *coObjects = NULL);

	void Jump();
	void Sit();
	void Attack(WeaponType weaponType);
	Simon(Camera * camera);
	~Simon();
};

