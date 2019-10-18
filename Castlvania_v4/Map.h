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
typedef TileMap * LPTILEMAP;
class Map
{
	LPTILEMAP ** mapMatrix;
	int mapWidth, mapHeight, tileID;
public:
	void Render(Camera * camera);
	Map(LPCWSTR mapDesFilePath);
	~Map();
};

class MapManager
{
	Map * map;
	std::vector<LPCWSTR> mapDescriptionList;
public:
	static MapManager * __instance;
	static MapManager * getInstance();
	void setMap(WorldID id);
	void drawMap(Camera * camera);
	MapManager();
	~MapManager();
};

