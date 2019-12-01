#pragma once
#include "GameWorld.h"
#include"Map.h"
#include"Camera.h"
#include"Simon.h"
#include"Item.h"
#include"Define.h"

//General
#define AMOUNT_ENEMY_MAX_AT_1_TIME 3
#define TIME_BETWEEN_SPAWN_2_ENEMY 1000
#define TIME_BETWEEN_2_WAVE 3000
//Stage 1
#define CAMERA_CONSTRAINT_FOR_STAGE_1_LEFT 0.0f
#define CAMERA_CONSTRAINT_FOR_STAGE_1_RIGHT 1553.0f
#define OBJECT_HIDDEN_ID_FOR_GO_TO_STAGE_2 31
#define CAMERA_POSITION_1_WHEN_SIMON_GO_TO_STAGE_2 1410.0f
#define SIMON_POSITION_WHEN_GO_TO_STAGE_2 1578.0f
#define AREA_ENEMY_SPAWN_1_BOUNDARY_LEFT 0.0f
#define AREA_ENEMY_SPAWN_1_BOUNDARY_RIGHT 356.0f
#define AREA_ENEMY_SPAWN_2_BOUNDARY_LEFT 529.0f
#define AREA_ENEMY_SPAWN_2_BOUNDARY_RIGHT 1089.0f
#define AREA_ENEMY_SPAWN_3_BOUNDARY_LEFT 1138.0f
#define AREA_ENEMY_SPAWN_3_BOUNDARY_RIGHT 1553.0f

//Stage 2
#define CAMERA_CONSTRAINT_FOR_STAGE_2_RIGHT 2050.0f
#define CAMERA_CONSTRAINT_FOR_STAGE_2_LEFT 1530.0f

//Stage 3
#define CAMERA_CONSTRAINT_FOR_STAGE_3_RIGHT 2818.0f
#define CAMERA_CONSTRAINT_FOR_STAGE_3_LEFT 2050.0f


class World_1 :
	public GameWorld
{
private:
	//Property
	Camera * camera;
	vector<LPGAMEOBJECT> lstObject;
	unordered_map<int, Item*> lstItem;
	vector<LPGAMEOBJECT> lstEnemy;
	Simon * simon;
	int stage;

	//Process Stage
	bool isSimonGoNextStage;
	bool isSimonGoThroughDoor;

	//Spawn Enemy
	int amountEnemy;
	DWORD timeEnemyCreated;
	bool isInWave;
	DWORD timeWaveEnded;
public:
	void KeyState(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void Update(DWORD dt);
	void LoadResources();
	void Render();

	void processSimonCollideWithObjectHidden();
	void processWeaponWithEnemy();
	void spawnEnemy();
	World_1();
	~World_1();
};

