#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y,bool isFlipVertical, int alpha)
{
	Game * game = Game::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, isFlipVertical,alpha);
}

void CSprite::Draw(float x, float y, bool isFlipVertical, int r, int g, int b)
{
	Game * game = Game::GetInstance();
	D3DXCOLOR color;
	color.r = r;
	color.g = g;
	color.b = b;
	game->Draw(x, y, texture, left, top, right, bottom, isFlipVertical, color);
}

void CSprites::Add(int tileID, int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[tileID][id] = s;
}

LPSPRITE CSprites::Get(int tileID, int id)
{
	return sprites[tileID][id];
}



void CAnimation::Add(int tileID,int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(tileID,spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, bool isFlipVertical, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, isFlipVertical,alpha);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(AnimationID id)
{
	return animations[id];
}