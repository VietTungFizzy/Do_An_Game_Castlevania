#include "Grid.h"
#include"Map.h"
#include "Brick.h"
#include "BigTorch.h"
#include "LittleTorch.h"
#include "InitialStairEvent.h"
#include "ObjectHidden.h"
#include "BreakableBrick.h"
#include "WhipUpgrade.h"
#include "Dagger_Item.h"
#include "BigHeart.h"
#include "SpecialMoneyBag.h"
#include "Door.h"
Grid * Grid::__instance = NULL;
Grid * Grid::GetInstance()
{
	if (__instance == NULL) __instance = new Grid();
	return __instance;
}
void Grid::loadObject(WorldID id)
{
	LPCWSTR temp = objectFilePaths[(int)id].c_str();
	ifstream input(temp);
	if (!input.is_open()) DebugOut(L"Khong load duoc file Object\n");
	int n, objectId, w, h, type;
	float x, y;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> objectId >> x >> y >> w >> h >> type;
		LPGAMEOBJECT tempObj = NULL;
		switch ((ObjectType)objectId)
		{
		case BRICK_OBJ:
			tempObj = new Brick(x, y, w, h, type);
			break;
		case BIG_TORCH_OBJ:
			tempObj = new BigTorch(x, y);
			break;
		case HIDDEN_OBJ:
			tempObj = new ObjectHidden(x, y, w, h);
			break;
		case LITTLE_TORCH_OBJ:
			tempObj = new LittleTorch(x, y);
			break;
		case BREAKABLE_BRICK_OBJ:
			tempObj = new BreakableBrick(x, y, w, h, type);
			break;
		case GO_UP_STAIR_OBJ:
		{
			float stairPosX, stairPosY;
			input >> stairPosX >> stairPosY;
			tempObj = new InitialStairEvent(x, y, w, h, -1, type, stairPosX, stairPosY);
		}
		break;
		case GO_DOWN_STAIR_OBJ:
		{
			float stairPosX, stairPosY;
			input >> stairPosX >> stairPosY;
			tempObj = new InitialStairEvent(x, y, w, h, 1, type, stairPosX, stairPosY);
		}
		break;
		case DOOR_OBJ:
			tempObj = new Door(x, y);
			break;
		default:
			break;
		}
		tempObj->setID(i);

		int beginColumn = x / CELL_WIDTH;
		int beginRow = y / CELL_HEIGHT;
		int endColumn = (x + w) / CELL_WIDTH;
		int endRow = (y + h) / CELL_HEIGHT;
		for (int j = beginRow; j<= endRow; j++)
		{
			for (int k = beginColumn; k <= endColumn; k++)
			{
				lstObject[j][k].push_back(tempObj);
			}
		}
	}


}
void Grid::loadItem(WorldID id)
{
	LPCWSTR temp = itemFilePaths[(int)id].c_str();
	ifstream input(temp);
	if (!input.is_open()) DebugOut(L"Khong load duoc file Item\n");
	int n, objectID, itemID, x, y, type;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		input >> objectID >> itemID >> x >> y >> type;
		Item * item = NULL;
		switch ((ItemType) itemID)
		{
		case WHIP_UPGRADE:
			item = new WhipUpgrade(x, y);
			break;
		case BIG_HEART:
			item = new BigHeart(x, y);
			break;
		case DAGGER:
			item = new Dagger_Item(x, y);
			break;
		case SPECIAL_MONEY_BAG:
			item = new SpecialMoneyBag(x, y);
		default:
			break;
		}
		lstItem[objectID] = item;
	}
}
void Grid::setMap(WorldID id)
{
	lstItem.clear();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			lstObject[i][j].clear();
		}
		delete[] lstObject[i];
	}
	delete[] lstObject;
	previousBeginColumn = -1;
	previousBeginRow = -1;
	column = MapManager::GetInstance()->getMap()->getMapWidth() / CELL_WIDTH + 1;
	row = MapManager::GetInstance()->getMap()->getMapHeight() / CELL_HEIGHT + 1;

	lstObject = new vector<LPGAMEOBJECT>*[row];
	for (int i = 0; i < row; i++)
	{
		lstObject[i] = new vector<LPGAMEOBJECT>[column];
	}
	loadObject(id);
	loadItem(id);
}

void Grid::getList(vector<LPGAMEOBJECT>& lstObject, unordered_map<int, Item*>& lstItem, Camera * camera)
{
	
	int beginColumn = (int)(camera->getX() / CELL_WIDTH);
	int beginRow = (int)(camera->getY() / CELL_HEIGHT);
	int endColumn = (int)((camera->getX() + SCREEN_WIDTH) / CELL_WIDTH + 1);
	int endRow = (int)((camera->getY() + SCREEN_HEIGHT) / CELL_HEIGHT + 1);

	if (beginColumn == previousBeginColumn && beginRow == previousBeginRow) return;

	previousBeginColumn = beginColumn;
	previousBeginRow = beginRow;

	lstObject.clear();
	lstItem.clear();

	for (int i = beginRow; i < endRow; i++)
	{
		for (int j = beginColumn; j < endColumn; j++)
		{
			if (i < 0 || j < 0 || i >= row || j >= column) continue;
			if (this->lstObject[i][j].size() == 0) continue;

			for (int k = 0; k < this->lstObject[i][j].size(); k++)
			{
				/*int t = this->lstObject[i][j].at(k)->getID();
				DebugOut(L"t = %d\n", t);*/
				lstObject.push_back(this->lstObject[i][j].at(k));
				if(this->lstObject[i][j].at(k)->getHealth() != 999)
					lstItem[this->lstObject[i][j].at(k)->getID()] = this->lstItem[this->lstObject[i][j].at(k)->getID()];
			}
		}
	}
}

Grid::Grid()
{
	std::ifstream input(L"Resources/Loader/Map_Object.txt");
	if (!input.is_open()) DebugOut(L"Khong mo duoc file\n");
	int n;
	input >> n;
	for (int i = 0; i < n; i++)
	{
		std::string temp;
		input >> temp;
		std::wstring wTemp = std::wstring(temp.begin(), temp.end());

		objectFilePaths.push_back(wTemp);
	}
	input.close();

	input.open(L"Resources/Loader/Map_Item.txt");
	if (!input.is_open()) DebugOut(L"Khong mo duoc file\n");
	input >> n;
	for (int i = 0; i < n; i++)
	{
		std::string temp;
		input >> temp;
		std::wstring wTemp = std::wstring(temp.begin(), temp.end());

		itemFilePaths.push_back(wTemp);
	}
	input.close();
}


Grid::~Grid()
{
}
