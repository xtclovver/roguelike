#pragma once
#include <iostream>
#include <string>

namespace variableKeeper {
	int map[35][93]; // map \\ level
	bool softExit = false;
	bool IsTeleportOn = false;
	bool IsMusicOn = true;
	bool PlayerGotCrown = false;
	int StageMusic = 0;
	int BossMusic = 0;
	unsigned int xTP, yTP;
	char WallSymbol = '#';
	char FloorSymbol = ' ';
	char ChestSymbol = '*';
	char EnemySymbol = 'E';
	char PlayerSymbol = 'P';
	char ShopSymbol = '$';
	char EventTeleporterSymbol = '@';
	int NeedsForTPCharge = 75;
	int TPCharge = -1;
	int Score = 0;
	int HealAfterKill = 0;
	int NumberOfEnemy = 0;
	float difficulty = 1;
	int Stage = 1;
	int MinStage;
	int EnemyDefaultStats[4] = { 20,10,15,5 }; // [0] = dmg, [1] = hp, [2] = how many gold drops, [3] = armor
	struct EnemyStats
	{
		int x;
		int y;
		int damage;
		int hp; // health point
		int gold; // how many drop
		int armor;
		int toTurn;
	};
	EnemyStats Enemy[100];
	std::string CurrentState = "", CurrentState2 = "";
	unsigned int MapSeed = 0;
	int ShopItemsIDs[3];
	int ItemSlotID[6] = { 0,-1,-1,-1,-1,-1 }; // [0] is sword, another is items
	bool IsBought = false;
	struct ItemsSpecifications {
		std::string Name;
		int damage = 0;
		int ID = 0;
		int StageReq = 0;
		int LvlToEqp = 0;
		int cost = 0;
		float special = 0;
		std::string Desc; // Description
	};
	ItemsSpecifications ShopItems[20];

}
