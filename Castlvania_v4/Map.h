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
public:
	void draw();
	TileMap(float x, float y,LPSPRITE sprite);
	~TileMap();
};

class Map
{
	TileMap ** mapMatrix;
	int mapWidth, mapHeight, tileID;
	float x, y;
public:
	void draw();
	Map(LPCWSTR mapDesFilePath,LPCWSTR objDesFilePath,float x, float y);
	~Map();
};

class MapManager
{
	Map * map;
	std::vector<LPCWSTR> mapDescriptionList;
	std::vector<LPCWSTR> objectDescriptionList;
public:
	static MapManager * __instance;
	static MapManager * getInstance();
	void setMap(WorldID id);
	void drawMap();
	std::vector<LPGAMEOBJECT> getObjectFromMap();
	MapManager();
	~MapManager();
};

