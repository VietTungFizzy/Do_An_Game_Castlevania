#pragma once
#include"Define.h"
#include"GameObject.h"
#include"Item.h"

#define CELL_WIDTH 64
#define CELL_HEIGHT 64
class Grid
{
private:
	int previousBeginColumn;
	int previousBeginRow;
	int row, column;
	vector<LPGAMEOBJECT> ** lstObject;
	unordered_map<int, Item*> lstItem;
	std::vector<std::wstring> objectFilePaths;
	std::vector<std::wstring> itemFilePaths;

private:
	void loadObject(WorldID id);
	void loadItem(WorldID id);
public:
	static Grid *  __instance;
	static Grid * GetInstance();
	void setMap(WorldID id);
	void getList(vector<LPGAMEOBJECT> & lstObject, unordered_map<int,Item*> & lstItem ,Camera * camera);
	Grid();
	~Grid();
};

