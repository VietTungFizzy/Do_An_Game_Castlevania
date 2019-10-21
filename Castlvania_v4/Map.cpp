#include "Map.h"
MapManager * MapManager::__instance = NULL;
void Map::Render(Camera * camera)
{
	int frameHeight = CTextures::GetInstance()->Get(tileID)->getFrameHeight();
	int franeWidth = CTextures::GetInstance()->Get(tileID)->getFrameWidth();
	int currentCamRow = camera->getY() / frameHeight;
	int currentCamColumn = camera->getX() / franeWidth;
	for (int i = currentCamRow; i < currentCamRow + (int)ceil(SCREEN_HEIGHT / frameHeight); i++)
	{
		for (int j = currentCamColumn; j < currentCamColumn + (int)ceil(SCREEN_WIDTH / franeWidth); j++)
		{
			if (i < 0 || i >= mapHeight || j < 0 || j >= mapWidth) continue;
			if (mapMatrix[i][j]->getID() == -1) continue;
			D3DXVECTOR2 pos = camera->translateWorldToScreen(j * franeWidth, i * frameHeight);
			mapMatrix[i][j]->draw(pos.x,pos.y);
		}
	}
}

int Map::getMapWidth()
{
	return mapWidth * CTextures::GetInstance()->Get(tileID)->getFrameWidth();
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
			if(spriteID != -1)
				mapMatrix[i][j] = new TileMap(spriteID, CSprites::GetInstance()->Get(tileID, spriteID));
			else
				mapMatrix[i][j] = new TileMap(spriteID, NULL);
		}
	}
	input.close();
}

Map::~Map()
{
}

void TileMap::draw(float x,float y)
{
	sprite->Draw(x, y, false);
}

TileMap::TileMap( int spriteID, LPSPRITE sprite)
{
	this->spriteID = spriteID;
	this->sprite = sprite;
}

TileMap::~TileMap()
{
}

MapManager * MapManager::GetInstance()
{
	if (__instance == NULL) __instance = new MapManager();
	return __instance;
}

void MapManager::setMap(WorldID id)
{
	LPCWSTR filePath = mapDescriptionList[id].c_str();
	if (map != NULL) delete map;
	map = new Map(filePath);
	DebugOut(L"Load success map with id= %d\n", id);
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
		
		mapDescriptionList.push_back(wTemp);
	}
	input.close();
}

MapManager::~MapManager()
{
}
