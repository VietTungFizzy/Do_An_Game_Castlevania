#pragma once
#include "Define.h"
#include "Game.h"
using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, bool isFlipVertical,int alpha = 255);
	void Draw(float x, float y, bool isFlipVertical, int r, int g, int b);
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int,unordered_map<int, LPSPRITE>> sprites;

public:
	void Add(int tileID,int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int tileID, int id);

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int tileID, int spriteId, DWORD time =0);
	void Render(float x, float y,bool isFlipVertical ,int alpha = 255);
	int getCurrentFrame() { return currentFrame; }
	void setCurrentFrame(int newFrame) { currentFrame = newFrame; }
	LPANIMATION_FRAME getCurrentAnimationFrame() { return frames[currentFrame]; }
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(AnimationID id);

	static CAnimations * GetInstance();
};
