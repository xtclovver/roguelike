#pragma once
#include <iostream>
#include <string>

namespace variableKeeper {
	int map[35][93]; // map \\ level
	char WallSymbol = '#';
	char FloorSymbol = ' ';
	char ChestSymbol = '*';
	char EnemySymbol = 'E';
	char PlayerSymbol = 'P';
	char ShopSymbol = '$'; // TODO
	char BossTeleporterSymbol = '@'; // TODO
	int NumberOfEnemy = 0;
	float difficulty = 1;
	int Stage = 1;
	int EnemyDefaultStats[4] = { 15,10,20,5 }; // [0] = dmg, [1] = hp, [2] = how many gold drops, [3] = armor
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
	EnemyStats Enemy[2];
	std::string CurrentState = "", CurrentState2 = "";
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
		std::string Desc; // Description
	};
	ItemsSpecifications ShopItems[20];

}
