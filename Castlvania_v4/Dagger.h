#pragma once
#include "Weapon.h"
#define DAGGER_SPRITE_ID 2
#define DAGGER_BBOX_WIDTH 17
#define DAGGER_BBOX_HEIGHT 9
#define DAGGER_SPEED 0.45f
class Dagger :
	public Weapon
{
private:
	LPSPRITE sprite;
	Camera * camera;
public:
	virtual void InitialAttack(float x, float y, int direction);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	Dagger(Camera * camera);
	~Dagger();
};

