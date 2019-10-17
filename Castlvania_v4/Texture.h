#pragma once
#include "Define.h"

using namespace std;
class CTexture
{
private:
	LPDIRECT3DTEXTURE9 tex;
	int totalColumn, totalRow, frameHeight, frameWidth;
public:
	int getTotalColumn()			{ return totalColumn; }
	int getTotalRow()				{ return totalRow; }
	int getFrameHeight()			{ return frameHeight; }
	int getFrameWidth()				{ return frameWidth; }
	LPDIRECT3DTEXTURE9 getTexture() { return tex; }
	CTexture(LPDIRECT3DTEXTURE9 tex, int totalColumn, int totalRow,int frameHeight,int frameWidth);
	~CTexture();


};
typedef CTexture * LPTEXTURE;
class CTextures
{
	static CTextures * __instance;

	unordered_map<int, LPTEXTURE> textures;

public:
	CTextures();
	void Add(int id, LPCWSTR filePath, int totalColumn, int totalRow, D3DCOLOR transparentColor);
	LPTEXTURE Get(unsigned int id);

	static CTextures * GetInstance();
};