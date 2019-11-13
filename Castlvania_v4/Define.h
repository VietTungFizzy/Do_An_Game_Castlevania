#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <algorithm>
#include "DebugOut.h"


#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

enum TileSetID
{
	BBOX =-100,
	ITEM = 1,
	CANDLE = 2,
	EFFECT =3,
	SIMON_TILESET =4,
	PROLOGUE_TILESET = 5,
	BRICK = 6,
	MORNING_START = 7
};
enum AnimationID
{
	SIMON_WALKING,
	SIMON_ATTACKING_STANDING,
	SIMON_ATTACKING_SITTING,
	SIMON_ATTACKING_GO_UP_STAIR,
	SIMON_ATTACKING_GO_DOWN_STAIR,
	SIMON_GO_UP_STAIR,
	SIMON_GO_DOWN_STAIR,
	BIG_TORCH,
	LITTLE_TORCH,
	EFFECT_SPARK,
	HAMMER,
	BOOMMERANG,
	HOLY_WATER,
	MONEY_BAG,
	MORNING_STAR_1,
	MORNING_STAR_2,
	MORNING_STAR_3
};
enum WorldID
{
	INTRO =-1,
	PROLOGUE,
	WORLD_1
};

enum ObjectType
{
	SIMON = 4,
	BRICK_OBJ = 5,
	BIG_TORCH_OBJ =6,
	HIDDEN_OBJ =7,
	LITTLE_TORCH_OBJ = 8,
	BREAKABLE_BRICK_OBJ =9
};
enum ItemType
{
	WHIP_UPGRADE,
	BIG_HEART,
	LITTLE_HEART,
	DAGGER,
	SPECIAL_MONEY_BAG,
	MONEY_BAG_1,
	MONEY_BAG_2,
	MONEY_BAG_3,
	HAMMER_ITEM,
	HOLY_WATER_ITEM,
	INVICIBLE_POTION,
	DOUBLE_SHOT,
	MAGICAL_CRYSTAL,
	POT_CHOP
};