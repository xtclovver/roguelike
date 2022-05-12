#define DEBUG 1
//-----------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <windows.h> // we need this header for the 'systems::gotoxy' function.
#include <conio.h> // we need this header for the '_getch' function.
#include <cstdlib> // "system" is ambiguous.
#include <stdio.h>
#include <chrono>
#include <thread>
#include "variableKeeper.h"
#include "colorfull.h" // ты вчера мне приподнёс
#include "systems.h"
#include "player.h"
//-----------------------------------------------------------------------------------------------
using namespace std;
using namespace Color;
using namespace variableKeeper;
using namespace player;
using namespace systems;
#pragma comment(lib, "winmm")
//-----------------------------------------------------------------------------------------------
void UpgradeLvl()
{
	Player.lvl += 1;
	Player.exp = 0;
	ShopItems[0].damage += 15 + ((Player.lvl / 10) * 15);
	//
	ShopItems[1].damage = 20 + ((Player.lvl / 10) * 20);
	//
	ShopItems[2].damage = 25 + ((Player.lvl / 10) * 25);
	//
	ShopItems[3].damage = 30 + ((Player.lvl / 10) * 30);
	//
	ShopItems[4].damage = 35 + ((Player.lvl / 10) * 35);
	//
	ShopItems[5].damage = 40 + ((Player.lvl / 10) * 40);
	//
	ShopItems[6].damage = 45 + ((Player.lvl / 10) * 45);
	//
	ShopItems[7].damage = 50 + ((Player.lvl / 10) * 50);
	//
	ShopItems[8].damage = 55 + ((Player.lvl / 10) * 55);
	//
	ShopItems[9].damage = 70 + ((Player.lvl / 10) * 70);
	//
	Player.MaxHP += (Player.lvl / 50) * 100;
	Player.hp += (Player.lvl / 50) * 100;
	Player.armor += (Player.lvl / 75) * 100;
	InitializationLeftMenu();
}
//-----------------------------------------------------------------------------------------------
int enemyCount(int xEnemy, int yEnemy)
{
	return map[yEnemy][xEnemy] - 7;
}
//-----------------------------------------------------------------------------------------------
void MenuSettings()
{
	system("cls");
	systems::gotoxy(50, 14);
	cout << "No settings there, maybe later" << endl;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void MenuAchievements()
{
	system("cls");
	systems::gotoxy(50, 14);
	cout << "There is nothing" << endl;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void InitializationEnemyStats(int count) // [0] = dmg, [1] = hp, [2] = how many gold drops, [3] = armor
{
	Enemy[count].damage = EnemyDefaultStats[0];
	Enemy[count].hp = EnemyDefaultStats[1];
	Enemy[count].gold = EnemyDefaultStats[2];
	Enemy[count].armor = EnemyDefaultStats[3];
}
//-----------------------------------------------------------------------------------------------
void GenerateMap() // 0 = normal, 1 = wall, 2 = chest, 3 = Enemy, 4 = Player, 5 = Shop, 6 = bossTP
{
	Player.x = rand() % 92;
	Player.y = rand() % 34;
#pragma warning(suppress: 4244)
	int WallCount = 0, ChestCount = 220 + (20 * difficulty), EnemyCountCD = 270 - (20 * difficulty), ShopCount = 0, ShopCD;//, BossTPCount = 0;
	for (int j = 0; j < 35; j++)
	{
		for (int i = 0; i < 93; i++)
		{
			map[j][i] = 0;
		}
	}
	ShopCD = 350 + (unsigned int)rand() % 350;
	for (int j = 0; j < 35; j++)
	{
		for (int i = 0; i < 93; i++)
		{
			int rNum;
			if (j == Player.y && i == Player.x)
			{
				map[j][i] = 4;
				continue;
			}
			if (ChestCount <= 0)
			{
#pragma warning(suppress: 4244)
				ChestCount = 220 + (20 * difficulty);
				map[j][i] = 2;
				continue;
			}
			ChestCount--;
			if (EnemyCountCD <= 0)
			{
				if (EnemyCountCD <= 2 * difficulty)
				{
					map[j][i] = 7 + NumberOfEnemy;
					InitializationEnemyStats(NumberOfEnemy);
#pragma warning(suppress: 4244)
					EnemyCountCD = 270 - (20 * difficulty);
					Enemy[NumberOfEnemy].x = i;
					Enemy[NumberOfEnemy].y = j;
					NumberOfEnemy++;
					continue;
				}
				else
				{
					EnemyCountCD--;
				}
			}
			do {
				rNum = rand() % 6;
			} while (rNum == 4);
			if (j == 0)
			{
				map[j][i] = 1;
				continue;
			}
			if (rNum == 0)
			{
				map[j][i] = 0;
			}
			else if (rNum == 1)
			{
				map[j][i] = 1;
				WallCount++;
				if (WallCount >= 2)
				{
					WallCount = 0;
					map[j][i] = 0;
					continue;
				}
			}
			else if (rNum == 2)
			{
				if (ChestCount <= 0)
				{
					map[j][i] = 2;
#pragma warning(suppress: 4244)
					ChestCount = 220 + (20 * difficulty);
				}
				else
				{
					ChestCount--;
				}
			}
			else if (rNum == 3)
			{
#pragma warning(suppress: 4244)
				if (EnemyCountCD <= 2 * difficulty)
				{
					map[j][i] = 7 + NumberOfEnemy;
					InitializationEnemyStats(NumberOfEnemy);
#pragma warning(suppress: 4244)
					EnemyCountCD = 270 - (20 * difficulty);
					Enemy[NumberOfEnemy].x = i;
					Enemy[NumberOfEnemy].y = j;
					NumberOfEnemy++;
				}
				else
				{
					map[j][i] = 0;
					EnemyCountCD--;
				}
			}
			else if (rNum == 5)
			{
				if (ShopCD <= 0)
				{
					if (ShopCount == 0)
					{
						map[j][i] = 5;
						ShopCount++;
					}
					else if (ShopCount == 1) {}
				}
			}
			ShopCD--;
		}
	}
}
//-----------------------------------------------------------------------------------------------
void MenuStartTutorial()
{
	system("cls"); //clear the screen.
	systems::gotoxy(50, 14);
	cout << "There is no game (Will be)" << endl;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void OpenChest(int x, int y)
{
	if (map[y][x] == 2)
	{
		Player.coins += 5;
		CurrentState = "You got 5 coins";
		map[y][x] = 0;
		systems::gotoxy(31 + x, y);
		cout << " ";
		InitializationLeftMenu();
	}
}
//-----------------------------------------------------------------------------------------------
void EnemyAI(int i) // 1 is YOU attaked, 2 is just made a move
{
	if (WhereX(Enemy[i].x, Enemy[i].y, 0, false) != -1 && WhereY(Enemy[i].x, Enemy[i].y, 0, false) != -1)
	{
		if (Enemy[i].toTurn < 5)
		{
			Enemy[i].toTurn++;
			return;
		}
		int randNum = 0;
		/*randNum = 1 + rand() % 3;*/ // 1 - left, 2 - up, 3 - right, 4 - down
		if (Player.x > Enemy[i].x)
		{
			if (IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'R', map) == true)
			{
				randNum = 3;
			}
			else { randNum = 1 + rand() % 3; }
		}
		else if (Player.x < Enemy[i].x)
		{
			if (IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'L', map) == true)
			{
				randNum = 1;
			}
			else { randNum = 1 + rand() % 3; }
		}
		else if (Player.y > Enemy[i].y)
		{
			if (IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'D', map) == true)
			{
				randNum = 4;
			}
			else { randNum = 1 + rand() % 3; }
		}
		else if (Player.y < Enemy[i].y)
		{
			if (IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'U', map) == true)
			{
				randNum = 2;
			}
			else { randNum = 1 + rand() % 3; }
		}		switch (randNum)
		{
		case 1: //1 - left
			if (map[Enemy[i].y][Enemy[i].x - 1] == 0 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'L', map) == true)
			{
				map[Enemy[i].y][Enemy[i].x - 1] = 7 + i;
				systems::gotoxy(31 + (Enemy[i].x - 1), 0 + Enemy[i].y);
				cout << red << EnemySymbol << def;
				systems::gotoxy(31 + Enemy[i].x, 0 + Enemy[i].y);
				map[Enemy[i].y][Enemy[i].x] = 0;
				cout << FloorSymbol;
				Enemy[i].x--;
				Enemy[i].toTurn = 0;
			}
			break;
		case 2://2 - up
			if (map[Enemy[i].y - 1][Enemy[i].x] == 0 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'U', map) == true)
			{
				map[Enemy[i].y - 1][Enemy[i].x] = 7 + i;
				systems::gotoxy(31 + Enemy[i].x, 0 + (Enemy[i].y - 1));
				cout << red << EnemySymbol << def;
				systems::gotoxy(31 + Enemy[i].x, 0 + Enemy[i].y);
				map[Enemy[i].y][Enemy[i].x] = 0;
				cout << FloorSymbol;
				Enemy[i].y--;
				Enemy[i].toTurn = 0;
			}
			break;
		case 3: // 3 - right
			if (map[Enemy[i].y][Enemy[i].x + 1] == 0 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'R', map) == true)
			{
				map[Enemy[i].y][Enemy[i].x + 1] = 7 + i;
				systems::gotoxy(31 + (Enemy[i].x + 1), 0 + Enemy[i].y);
				cout << red << EnemySymbol << def;
				systems::gotoxy(31 + Enemy[i].x, 0 + Enemy[i].y);
				map[Enemy[i].y][Enemy[i].x] = 0;
				cout << FloorSymbol;
				Enemy[i].x++;
				Enemy[i].toTurn = 0;
			}
			break;
		case 4: // 4 - down
			if (map[Enemy[i].y + 1][Enemy[i].x] == 0 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'D', map) == true)
			{
				map[Enemy[i].y + 1][Enemy[i].x] = 7 + i;
				systems::gotoxy(31 + Enemy[i].x, 0 + (Enemy[i].y + 1));
				cout << red << EnemySymbol << def;
				systems::gotoxy(31 + Enemy[i].x, 0 + Enemy[i].y);
				map[Enemy[i].y][Enemy[i].x] = 0;
				cout << FloorSymbol;
				Enemy[i].y++;
				Enemy[i].toTurn = 0;
			}
			break;
		default:
			break;

		}
		return;
	}
	else if (WhereX(Enemy[i].x, Enemy[i].y, 4, false) == 0 && WhereY(Enemy[i].x, Enemy[i].y, 4, false) == 0)
	{
		if (Enemy[i].toTurn < 5)
		{
			Enemy[i].toTurn++;
			return;
		}
		Player.hp -= EnemyDefaultStats[0] - Player.armor;
		Enemy[i].toTurn = 0;
		return;
	}
}
//-----------------------------------------------------------------------------------------------
void Gameplay(int map[35][93])
{
	char key;
	bool IsNothingDisturbing;
	system("cls"); //clear the screen.
	GenerateMap();
	NumberOfEnemy = 0;
	InitializationLeftMenu();
	ShowMap(map);
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			do {
				ShopItemsIDs[0] = systems::getRandomNumber(0, 9);
			} while (ShopItems[ShopItemsIDs[0]].StageReq != Stage && ShopItems[ShopItemsIDs[0]].LvlToEqp != Player.lvl);
		}
		else if (i == 1) {
			do {
				ShopItemsIDs[1] = systems::getRandomNumber(12, 16);
			} while (ShopItems[ShopItemsIDs[2]].StageReq != Stage && ShopItems[ShopItemsIDs[2]].LvlToEqp != Player.lvl);
		}
		else if (i == 2) {
			do {
				ShopItemsIDs[2] = systems::getRandomNumber(10, 11);
			} while (ShopItems[ShopItemsIDs[1]].StageReq != Stage && ShopItems[ShopItemsIDs[1]].LvlToEqp != Player.lvl);
		}
	}
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (Player.exp >= Player.forNextlvl)
		{
			UpgradeLvl();
		}
		systems::gotoxy(1, 27);
		cout << brwhite << "x: " << Player.x << def;
		systems::gotoxy(10, 27);
		cout << brwhite << "y: " << Player.y << def;
		if (Player.y < 10)
		{
			systems::gotoxy(14, 26);
			cout << " ";
		}
		key = _getch();
		if (key == '\r' || (key >= 1 && key <= 26))
		{
		}
		else {
			key = _getch();   // Я ЕБАЛ МЕЛКОМЯГКИХ КАКОГО ХУЯ Я ДОЛЖЕН ПИСАТЬ ДВА РАЗА ГЕТЧ ЧТО БЫ ВСЁ НОРМАЛЬНО РАБОТАЛО СУ КА, FIX BRAIN MICROSOFT
		}
		switch (key) //check the entered key.
		{
		case '<': // f2 mb
			if (DEBUG == 1)
			{
				OpenShop();
			}
			else {}
			break;
			// https://adventuregamestudio.github.io/ags-manual/ASCIIcodes.html
		case 1: // Ctrl + A
			if (DEBUG == 1)
			{
				Gameplay(map);
			}
			else {}
			break;
		case 2: // Ctrl + B
			if (DEBUG == 1)
			{
				for (int i = 0; i < 3; i++)
				{
					if (i == 0)
					{
						do {
							ShopItemsIDs[0] = systems::getRandomNumber(0, 9);
						} while (ShopItems[ShopItemsIDs[0]].StageReq != Stage && ShopItems[ShopItemsIDs[0]].LvlToEqp != Player.lvl);
					}
					else if (i == 1) {
						do {
							ShopItemsIDs[1] = systems::getRandomNumber(12, 16);
						} while (ShopItems[ShopItemsIDs[2]].StageReq != Stage && ShopItems[ShopItemsIDs[2]].LvlToEqp != Player.lvl);
					}
					else if (i == 2) {
						do {
							ShopItemsIDs[2] = systems::getRandomNumber(10, 11);
						} while (ShopItems[ShopItemsIDs[1]].StageReq != Stage && ShopItems[ShopItemsIDs[1]].LvlToEqp != Player.lvl);
					}
				}
			}
			else {}
			break;
		case 3: // Ctrl + C
			if (DEBUG == 1)
			{
				Player.coins += 150;
			}
			else {}
			break;
		case 4: // Ctrl + D
			if (DEBUG == 1)
			{
				Player.exp += 5;
			}
			else {}
			break;
		case 5: // Ctrl + E
			if (DEBUG == 1)
			{
				Player.lvl += 1;
			}
			else {}
			break;
		case 6: // Ctrl + F
			if (DEBUG == 1)
			{
				Player.hp = Player.MaxHP;
			}
			else {}
			break;
		case '\r': // if the entered key is 'Enter'.
			try
			{
				if (WhereX(Player.x, Player.y, 0, true) == -1 && WhereY(Player.x, Player.y, 0, true) == -1)
				{
					if (WhereX(Player.x, Player.y, 5, false) != -1 && WhereY(Player.x, Player.y, 5, false) != -1)
					{
						OpenShop();
					}
					else if (WhereX(Player.x, Player.y, 2, false) != -1 && WhereY(Player.x, Player.y, 2, false) != -1)
					{
						OpenChest(WhereX(Player.x, Player.y, 2, false), WhereY(Player.x, Player.y, 2, false));
					}
				}
				else if (WhereX(Player.x, Player.y, 0, true) != -1 && WhereY(Player.x, Player.y, 0, true) != -1)
				{
					actionOnTheEnemy(WhereX(Player.x, Player.y, 0, true), WhereY(Player.x, Player.y, 0, true), enemyCount(WhereX(Player.x, Player.y, 0, true), WhereY(Player.x, Player.y, 0, true)), true);
				}
			}
			catch (...)
			{
			}  // we have to use try and catch coz if we did'nt fill that index with a function.
			   //                     a runtime error will appear.
			break;

		case 'P': // down arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(Player.x, Player.y, 'D', map);
			if (IsNothingDisturbing == true)
			{
				if (Player.y < 1)
				{
					continue;
				}
				else {
					map[Player.y + 1][Player.x] = 4;
					systems::gotoxy(31 + Player.x, 0 + (Player.y + 1));
					cout << green << PlayerSymbol << def;
					systems::gotoxy(31 + Player.x, 0 + Player.y);
					map[Player.y][Player.x] = 0;
					cout << FloorSymbol;
					Player.y++;
				}

			}
			else if (IsNothingDisturbing == false) {}
			break;

		case 'H': // up arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(Player.x, Player.y, 'U', map);
			if (IsNothingDisturbing == true)
			{
				if (Player.y <= 1)
				{
					continue;
				}
				else {
					map[Player.y - 1][Player.x] = 4;
					systems::gotoxy(31 + Player.x, 0 + (Player.y - 1));
					cout << green << PlayerSymbol << def;
					systems::gotoxy(31 + Player.x, 0 + Player.y);
					map[Player.y][Player.x] = 0;
					cout << FloorSymbol;
					Player.y--;
				}

			}
			else if (IsNothingDisturbing == false) {}
			break;
		case 'K': // left arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(Player.x, Player.y, 'L', map);
			if (IsNothingDisturbing == true)
			{
				map[Player.y][Player.x - 1] = 4;
				systems::gotoxy(31 + (Player.x - 1), 0 + Player.y);
				cout << green << PlayerSymbol << def;
				systems::gotoxy(31 + Player.x, 0 + Player.y);
				map[Player.y][Player.x] = 0;
				cout << FloorSymbol;
				Player.x--;
			}
			else if (IsNothingDisturbing == false) {}
			break;
		case 'M': // right arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(Player.x, Player.y, 'R', map);
			if (IsNothingDisturbing == true)
			{
				map[Player.y][Player.x + 1] = 4;
				systems::gotoxy(31 + (Player.x + 1), 0 + Player.y);
				cout << green << PlayerSymbol << def;
				systems::gotoxy(31 + Player.x, 0 + Player.y);
				map[Player.y][Player.x] = 0;
				cout << FloorSymbol;
				Player.x++;
			}
			else if (IsNothingDisturbing == false) {}
			break;
		case 27: // Esc
			try {
			}
			catch (...) {}
			break;
		default:
		{
			try {}
			catch (...) {}
		}
		break;
		}
		for (int i = 0; i < 2; i++)
		{
			if (Enemy[i].hp > 0)
			{
				EnemyAI(i);
			}
		}
	}
	cin.ignore();
}
//-----------------------------------------------------------------------------------------------
void MenuStart()
{
	system("cls");
	std::this_thread::sleep_for(std::chrono::milliseconds(250));
	Gameplay(map);
}
//-----------------------------------------------------------------------------------------------
void GoToTheNextStage() // TODO
{
	Stage += 1;
	Player.coins = 0;
	difficultyIncrease();
	Gameplay(map);
}
//-----------------------------------------------------------------------------------------------
void ExitOption()
{
	system("cls");
	systems::gotoxy(50, 14);
	cout << "Exitting..." << endl;
	exit(0);
}
//-----------------------------------------------------------------------------------------------
void DebugHelp()
{
	system("cls");
	systems::gotoxy(50, 10);
	cout << Color::red << "F2 - Open shop" << Color::def;
	systems::gotoxy(50, 11);
	cout << Color::red << "Ctrl + A - reGenerate map" << Color::def;
	systems::gotoxy(50, 12);
	cout << Color::red << "Ctrl + B - Refresh shop items" << Color::def;
	systems::gotoxy(50, 13);
	cout << Color::red << "Ctrl + C - +150 coins" << Color::def;
	systems::gotoxy(50, 14);
	cout << Color::red << "Ctrl + D - +5 exp" << Color::def;
	systems::gotoxy(50, 15);
	cout << Color::red << "Ctrl + E - +1 lvl" << Color::def;
	systems::gotoxy(50, 16);
	cout << Color::red << "Ctrl + F - Full health" << Color::def;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
string* MenuItems() // this function returns a pointer to a string.
{
	string* item = new string[5];
	item[0] = "Start new game.";
	if (DEBUG == 1)
		item[1] = "Debug help.";
	else
		item[1] = "Tutorial.";
	item[2] = "Settings.";
	item[3] = "Achivments.";
	item[4] = "Exit.";
	return item;
}
//-----------------------------------------------------------------------------------------------
int main()
{
	// Swords // Swords // Swords // Swords // Swords // Swords
	ShopItems[19].Name = "You alredy bought this.";
	ShopItems[19].damage = 0;
	ShopItems[19].cost = 0;
	ShopItems[19].LvlToEqp = 1;
	ShopItems[19].ID = 19;
	ShopItems[19].StageReq = 0;
	ShopItems[19].Desc = "Thanks for buying. See ya!";
	//
	ShopItems[0].Name = "Dao";
	ShopItems[0].damage = 15;
	ShopItems[0].cost = 5;
	ShopItems[0].LvlToEqp = 1;
	ShopItems[0].ID = 0;
	ShopItems[0].StageReq = 1;
	ShopItems[0].Desc = "Starting sword";
	//
	ShopItems[1].Name = "Quelling Blade";
	ShopItems[1].cost = 25;
	ShopItems[1].damage = 20;
	ShopItems[1].LvlToEqp = 2;
	ShopItems[1].ID = 1;
	ShopItems[1].StageReq = 1;
	ShopItems[1].Desc = "Low cost, good perfomace";
	//
	ShopItems[2].Name = "Ogre Axe";
	ShopItems[2].cost = 50;
	ShopItems[2].damage = 25;
	ShopItems[2].LvlToEqp = 4;
	ShopItems[2].ID = 2;
	ShopItems[2].StageReq = 2;
	ShopItems[2].Desc = "Stolen axe from ogre lair";
	//
	ShopItems[3].Name = "Katana";
	ShopItems[3].cost = 75;
	ShopItems[3].damage = 30;
	ShopItems[3].LvlToEqp = 6;
	ShopItems[3].ID = 3;
	ShopItems[3].StageReq = 2;
	ShopItems[3].Desc = "A samurai should always be prepared for death – whether his own or someone else's";
	//
	ShopItems[4].Name = "Desolator";
	ShopItems[4].cost = 100;
	ShopItems[4].damage = 35;
	ShopItems[4].LvlToEqp = 8;
	ShopItems[4].ID = 4;
	ShopItems[4].StageReq = 3;
	ShopItems[4].Desc = "A wicked weapon";
	//
	ShopItems[5].Name = "Skull Basher";
	ShopItems[5].cost = 125;
	ShopItems[5].damage = 40;
	ShopItems[5].LvlToEqp = 10;
	ShopItems[5].ID = 5;
	ShopItems[5].StageReq = 3;
	ShopItems[5].Desc = "A feared weapon in the right hands, this maul's ability to shatter the defenses of its opponents should not be underestimated.";
	//
	ShopItems[6].Name = "Heavens Halberd";
	ShopItems[6].cost = 125;
	ShopItems[6].damage = 45;
	ShopItems[6].LvlToEqp = 12;
	ShopItems[6].ID = 6;
	ShopItems[6].StageReq = 4;
	ShopItems[6].Desc = "This halberd moves with the speed of a smaller weapon, allowing the bearer to win duels that a heavy edge would not.";
	//
	ShopItems[7].Name = "Sacred Relic";
	ShopItems[7].cost = 150;
	ShopItems[7].damage = 50;
	ShopItems[7].LvlToEqp = 14;
	ShopItems[7].ID = 7;
	ShopItems[7].StageReq = 4;
	ShopItems[7].Desc = "An ancient weapon that often turns the tides of war.";
	//
	ShopItems[8].Name = "Ethereal blade";
	ShopItems[8].cost = 175;
	ShopItems[8].damage = 55;
	ShopItems[8].LvlToEqp = 16;
	ShopItems[8].ID = 8;
	ShopItems[8].StageReq = 5;
	ShopItems[8].Desc = "A flickering blade of a ghastly nature, it is capable of crushing damage to the enemy.";
	//
	ShopItems[9].Name = "Divine Rapier";
	ShopItems[9].cost = 293;
	ShopItems[9].damage = 70;
	ShopItems[9].LvlToEqp = 20;
	ShopItems[9].ID = 9;
	ShopItems[9].StageReq = 5;
	ShopItems[9].Desc = "He is so powerful that even God cannot control him.";
	// Swords // Swords // Swords // Swords // Swords // Swords

	// ITEMS // ITEMS // ITEMS // ITEMS // ITEMS // ITEMS // ITEMS 
	//  Consumables
	ShopItems[10].Name = "Healing Flask";
	ShopItems[10].cost = 50;
	ShopItems[10].LvlToEqp = 1;
	ShopItems[10].ID = 10;
	ShopItems[10].StageReq = 1;
	ShopItems[10].Desc = "Healing you";
	//
	ShopItems[11].Name = "Tome of Knowledge";
	ShopItems[11].cost = 100;
	ShopItems[11].LvlToEqp = 1;
	ShopItems[11].ID = 11;
	ShopItems[11].StageReq = 2;
	ShopItems[11].Desc = "Gives you exp";
	//  Consumables
	// Items
	ShopItems[12].Name = "Test Item 12";
	ShopItems[12].cost = 5;
	ShopItems[12].ID = 13;
	ShopItems[12].StageReq = 1;
	ShopItems[12].Desc = "Healing you";
	//
	ShopItems[13].Name = "Test Item 13";
	ShopItems[13].cost = 5;
	ShopItems[13].ID = 14;
	ShopItems[13].StageReq = 1;
	ShopItems[13].Desc = "Healing you";
	//
	ShopItems[14].Name = "Test Item 14";
	ShopItems[14].cost = 50;
	ShopItems[14].ID = 15;
	ShopItems[14].StageReq = 1;
	ShopItems[14].Desc = "Healing you";
	//
	ShopItems[15].Name = "Test Item 15";
	ShopItems[15].cost = 5;
	ShopItems[15].ID = 16;
	ShopItems[15].StageReq = 1;
	ShopItems[15].Desc = "Healing you";
	//
	ShopItems[16].Name = "Test Item 16";
	ShopItems[16].cost = 5;
	ShopItems[16].ID = 16;
	ShopItems[16].StageReq = 1;
	ShopItems[16].Desc = "Healing you";
	// Items
	// ITEMS // ITEMS // ITEMS // ITEMS // ITEMS // ITEMS // ITEMS 
	// PlayerStats // PlayerStats // PlayerStats // PlayerStats 
	Player.coins = 15;
	Player.hp = 100;
	Player.exp = 0;
	Player.forNextlvl = 10;
	Player.lvl = 1;
	Player.armor = 0;
	Player.MaxHP = 100;
	// PlayerStats // PlayerStats // PlayerStats // PlayerStats 
	if (DEBUG == 1)
		system("title Roguelike v0.3.8 by shiro // hakerhd93 // DEBUG");
	else if (DEBUG == 0)
		system("title Roguelike v0.3.8 by shiro // hakerhd93 // Beta");
	srand((unsigned int)time(NULL));
	ChangeCursorStatus(false);
	////////////////////меняем размер консоли 
	system("mode con cols=125 lines=35"); //размер окна, вывод нужного количества строк в консоль
	HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  size{ 100,100 };//символов строки, строк
	SetConsoleScreenBufferSize(hout, size);//размер буфера
	///////////////////////////////////Меняем шрифт для отображения символов Unicode, можно пропустить - если у вас установлен такой
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 12;
	cfi.dwFontSize.Y = 18;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(hout, false, &cfi);
	///////////////////////////////////Меняем шрифт
	typedef void (*TMenuOption)(); // typedef for defining a 'pointer to function' type.
	int ItemCount = 5; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //for entering the key (up arrow,down arrow,etc...);

	TMenuOption* MenuOption = new TMenuOption[ItemCount];//array of pointers to functions (dynamic).
	MenuOption[0] = MenuStart; //filling the array with the functions.
	MenuOption[1] = MenuStartTutorial;
	MenuOption[2] = MenuSettings;
	MenuOption[3] = MenuAchievements;
	MenuOption[4] = ExitOption;
	if (DEBUG == 1)
	{
		MenuOption[1] = DebugHelp;
	}
	//	PlaySound(TEXT("C:\\Dont_talk_with_me.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (1) //infinite loop. (this loop will not break that's why we need an exit function).
	{
		for (int i = 0; i < ItemCount; i++) // Draw the menu.
		{
			systems::gotoxy(50, 14 + i);
			MenuChoice == i + 1 ? cout << " -> " : cout << "    "; // if (i+1) == the cursor then
														   //    print ' -> ' else print '    '.
														   //    by the way i call '->' the cursor
			cout << MenuItems()[i] << endl; // print the name of the item.
		} // finish the drawing.

		key = _getch(); //get the key.
		/*
		   _getch() is like cin>>bla;
		   but the differance is that by 'cin' you can enter char,double,int,etc...
		   with more than one digit and the value you entered is printed on the screen
		   but with _getch you can only enter ONE CHARACTER and will not be printed on
		   the sceen and return the entered key to the variable 'key' in this case.
		*/
		switch (key) //check the entered key.
		{
		case '\r': // if the entered key is 'Enter'.
			try
			{
				(*MenuOption[MenuChoice - 1])(); // call the function of the index 'cursor-1' in
											   //     the 'pointer to function' array.
			}
			catch (...)
			{
			}  // we have to use try and catch coz if we did'nt fill that index with a function.
			   //                     a runtime error will appear.

			break;

		case 'P': // if the entered key is the 'up arrow' notice that its equal to 'P' (capital)
			MenuChoice++; //then we will increment the cursor by one.
			if (MenuChoice > ItemCount) // if the cursor value is more than the items count.
				MenuChoice = 1;         //    then it will return back to the first item.
			break;

		case 'H': // same but with 'down arrow' and decrement the cursor.
			MenuChoice--;
			if (MenuChoice < 1)
				MenuChoice = ItemCount;
			break;

		case 27: // 27 is the asscii to the escape key (Esc)
			try { (*MenuOption[ItemCount - 1])(); } // useually when the 'Esc' key is pressed the last
												//     item will be called (executed). but you can
												//     change it to whatever you want.
			catch (...) {}
			break;
		default:// any another key.
			if (key >= '1' && key <= char(ItemCount + '0'))//check if the pressed key is in the range
													  //    of (1,2,3,...,#of items) [all char(s)]
			{
				try { (*MenuOption[int(key) - '0' - 1])(); } //call the function of the pressed number.
					 //  you can make the cursor move to that item instead of calling (executing)
					 //  it by replacing all the code between 'if (bla){' and '}' with this
					 //  statement MenuChooice=int(key)-'0'
				catch (...) {}
			}
		}
	}

	delete[] MenuOption;
	return 0;
}
//-----------------------------------------------------------------------------------------------