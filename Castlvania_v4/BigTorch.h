#pragma once
#include "GameObject.h"
#define BIG_TORCH_BBOX_WIDTH 16
#define BIG_TORCH_BBOX_HEIGHT 32
#define BIG_TORCH_SPRITE_OFFSET_X 1
class BigTorch :
	public CGameObject
{
private:
	int health;
	LPANIMATION animation;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	BigTorch(float x, float y);
	~BigTorch();
};

