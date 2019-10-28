#pragma once
#include "GameObject.h"
#define BIG_TORCH_BBOX_WIDTH 15
#define BIG_TORCH_BBOX_HEIGHT 32
#define BIG_TORCH_SPRITE_OFFSET_X 2
class BigTorch :
	public CGameObject
{
private:
	LPANIMATION animation;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	BigTorch(float x, float y);
	~BigTorch();
};

