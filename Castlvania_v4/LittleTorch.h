#pragma once
#include "GameObject.h"
#define LITTLE_TORCH_BBOX_WIDTH 8
#define LITTLE_TORCH_BBOX_HEIGHT 14
#define LITTLE_TORCH_OFFSET_X 5
#define LITTLE_TORCH_OFFSET_Y 10
class LittleTorch :
	public CGameObject
{
private:
	LPANIMATION animation;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Render(Camera * camera);
	LittleTorch(float x, float y);
	~LittleTorch();
};

