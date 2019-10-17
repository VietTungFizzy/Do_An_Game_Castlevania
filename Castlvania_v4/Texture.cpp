#include "Texture.h"
#include"Game.h"

CTextures * CTextures::__instance = NULL;

CTextures::CTextures()
{
}

void CTextures::Add(int id, LPCWSTR filePath,int totalColumn,int totalRow ,D3DCOLOR transparentColor)
{
	LPTEXTURE temp;
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	temp = new CTexture(texture, totalColumn, totalRow, info.Height / totalRow, info.Width / totalColumn);
	textures[id] = temp;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

LPTEXTURE CTextures::Get(unsigned int id)
{
	return textures[id];
}

CTextures * CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}


CTexture::CTexture(LPDIRECT3DTEXTURE9 tex, int totalColumn, int totalRow, int frameHeight, int frameWidth)
{
	this->tex = tex;
	this->totalColumn = totalColumn;
	this->totalRow = totalRow;
	this->frameHeight = frameHeight;
	this->frameWidth = frameWidth;
}

CTexture::~CTexture()
{
}
