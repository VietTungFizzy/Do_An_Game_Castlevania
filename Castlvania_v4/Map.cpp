#include "Map.h"

void Map::Render(Camera * camera)
{
	int currentCamRow = camera->getY() / CTextures::GetInstance()->Get(tileID)->getFrameHeight();
	int currentCamColumn = camera->getX() / CTextures::GetInstance()->Get(tileID)->getFrameWidth();

}

Map::Map(LPCWSTR mapDesFilePath)
{
	std::ifstream input(mapDesFilePath);
	if (!input.is_open()) DebugOut(L"Khong mo duoc file\n");
	input >> tileID >> mapWidth >> mapHeight;
	mapMatrix = new LPTILEMAP*[mapHeight];
	for (int i = 0; i < mapHeight; i++)
	{
		mapMatrix[i] = new LPTILEMAP[mapWidth];
	}
	int frameWidth = CTextures::GetInstance()->Get(tileID)->getFrameWidth();
	int frameHeight = CTextures::GetInstance()->Get(tileID)->getFrameHeight();
	int spriteID;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			input >> spriteID;
			mapMatrix[i][j] = new TileMap(j*frameWidth, i*frameHeight, CSprites::GetInstance()->Get(tileID, spriteID));
		}
	}
	input.close();
}

Map::~Map()
{
}

void TileMap::draw()
{
	sprite->Draw(x, y, false);
}

TileMap::TileMap(float x, float y, LPSPRITE sprite)
{
	this->x = x;
	this->y = y;
	this->sprite = sprite;
}

TileMap::~TileMap()
{
}

MapManager * MapManager::getInstance()
{
	if (__instance == NULL) __instance = new MapManager();
	return __instance;
}

void MapManager::setMap(WorldID id)
{
	map = new Map(mapDescriptionList[id]);
	DebugOut(L"Load success map with id= %d\n", id);
}

void MapManager::drawMap(Camera * camera)
{
	map->Render(camera);
}

MapManager::MapManager()
{
	std::ifstream input(L"Resources/Map_Information.txt");
	if(!input.is_open()) DebugOut(L"Khong mo duoc file\n");
	int n, id;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		std::string temp;
		input >> temp;
		std::wstring wTemp = std::wstring(temp.begin(), temp.end());
		LPCWSTR filePath = wTemp.c_str();
		mapDescriptionList.push_back(filePath);
	}
	input.close();
}

MapManager::~MapManager()
{
}
