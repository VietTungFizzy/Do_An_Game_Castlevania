#include "Map.h"

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
