#pragma once
#include "Sprite.h"
#include "Define.h"
#include "DebugOut.h"
#include "Texture.h"
#include "GameObject.h"
class TileMap
{
private:
	LPSPRITE sprite;
	float x, y;
	int spriteID;
public:
	void draw();
	int getID() { return spriteID; }
	TileMap(float x, float y,int spriteID,LPSPRITE sprite);
	~TileMap();
};
typedef TileMap * LPTILEMAP;
class Map
{
	LPTILEMAP ** mapMatrix;
	int mapWidth, mapHeight, tileID;
public:
	void Render(Camera * camera);
	int getMapWidth();
	Map(LPCWSTR mapDesFilePath);
	~Map();
};

class MapManager
{
	Map * map;
	std::vector<std::wstring> mapDescriptionList;
public:
	static MapManager * __instance;
	static MapManager * GetInstance();
	void setMap(WorldID id);
	Map * getMap() { return map; }
	MapManager();
	~MapManager();
};

