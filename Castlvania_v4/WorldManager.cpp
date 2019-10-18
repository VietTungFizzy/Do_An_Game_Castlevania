#include "WorldManager.h"


WorldManager * WorldManager::__instance = NULL;

void WorldManager::setWorld(GameWorld * newWorld)
{
	GameWorld * temp = world;
	world = newWorld;
	if (temp != NULL) delete temp;
}

WorldManager::WorldManager()
{
}


WorldManager::~WorldManager()
{
}

WorldManager * WorldManager::GetInstance()
{
	if (__instance == NULL) __instance = new WorldManager();
	return __instance;
}

void WorldManager::KeyState(BYTE * states)
{
	world->KeyState(states);
}

void WorldManager::OnKeyDown(int KeyCode)
{
	world->OnKeyDown(KeyCode);
}

void WorldManager::OnKeyUp(int KeyCode)
{
	world->OnKeyUp(KeyCode);
}

void WorldManager::LoadResources()
{
	CTextures * textureManager = CTextures::GetInstance();
	CSprites *spriteManager = CSprites::GetInstance();
	CAnimations * animationManager = CAnimations::GetInstance();

	std::ifstream input1(L"Resources/TileSet_Description.txt");

	if (!input1.is_open())DebugOut(L"Khong mo duoc file\n");

	int n,id,totalColumn,totalRow,r,g,b, frameHeight,frameWidth;
	std::string strfilePath;
	input1 >> n;
	
	for (int i = 0; i < n; i++)
	{
		input1 >> strfilePath;
		std::wstring stemp = std::wstring(strfilePath.begin(), strfilePath.end());
		LPCWSTR filePath = stemp.c_str();
		input1 >> id >> totalColumn >> totalRow >> r >> g >> b;
		textureManager->Add(id, filePath, totalColumn, totalRow, D3DCOLOR_XRGB(r, g, b));
		frameHeight = textureManager->Get(id)->getFrameHeight();
		frameWidth = textureManager->Get(id)->getFrameWidth();
		for (int j = 0;  j < totalRow;  j++)
		{
			for (int k = 0; k < totalColumn; k++)
			{
				spriteManager->Add(id,
									i * totalColumn + k,
									k * frameWidth, 
									i*frameHeight, 
									k * frameWidth + frameWidth, 
									i*frameHeight + frameHeight, 
									textureManager->Get(id)->getTexture());
			}
		}
	}
	input1.close();

	input1.open(L"Resources/Animation_Description.txt");

	if (!input1.is_open())DebugOut(L"Khong mo duoc file\n");
	input1 >> n;
	int tileID,animationID, beginSpriteID, endSpriteID, time;
	for (int i = 0; i < n; i++)
	{
		input1 >> tileID >> animationID >> beginSpriteID >> endSpriteID >> time;
		LPANIMATION temp = new CAnimation(time);
		for (int j = beginSpriteID; j <= endSpriteID; j++)
		{
			temp->Add(tileID, j, time);
		}
		animationManager->Add(animationID, temp);
	}
	input1.close();
}

void WorldManager::Render()
{
	world->Render();
}

void WorldManager::Update(DWORD dt)
{
	world->Update(dt);
}
