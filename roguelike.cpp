void MenuStart(); // every menu item needs a seperate function, so this is for the first item.
void MenuSettings(); //    and the second item etc...
void MenuAchievements();
void Gameplay(int map[35][93]);
void GenerateMap();
void difficultyIncrease();
void MenuStartTutorial(); // TODO
int getRandomNumber(int min, int max);
int WhereX(int x, int y, int fiend, bool IsEnemy);
int WhereY(int x, int y, int fiend, bool IsEnemy);
void OpenChest(int x, int y);
void EnemyAI(int i);
void ExitOption(); // this is also an item function but i named it like this coz every menu must have an exit item
void InitializationLeftMenu();
void actionOnTheEnemy(int x, int y, int count, bool attack);
void InitializationEnemyStats(int count);
void DebugHelp();
int map[35][93]; // map \\ level
#define WallSymbol '#'
#define FloorSymbol ' '
#define ChestSymbol '*'
#define EnemySymbol 'E'
#define PlayerSymbol 'P'
#define ShopSymbol '$' // TODO
#define BossTeleporterSymbol '@' // TODO
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
#include "colorfull.h" // ты вчера мне приподнёс
#include "systems.h"
#include "shopNitems.h"
#include "player.h"
//-----------------------------------------------------------------------------------------------
using namespace std;
using namespace systems;
using namespace Color;
using namespace shopNitems;
using namespace player;
#pragma comment(lib, "winmm")
//-----------------------------------------------------------------------------------------------
int NumberOfEnemy = 0;
float difficulty = 1;
int Stage = 1;
int EnemyDefaultStats[4] = { 15,10,20,5 }; // [0] = dmg, [1] = hp, [2] = how many gold drops, [3] = armor
string* MenuItems(); // a function that returns the name of a menu item.
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
string CurrentState = "", CurrentState2 = "";
//-----------------------------------------------------------------------------------------------
int main()
{
	// Swords // Swords // Swords // Swords // Swords // Swords
	ShopItems[0].Name = "Dao";
	ShopItems[0].damage = 15;
	ShopItems[0].cost = 5;
	ShopItems[0].LvlToEqp = 1;
	ShopItems[0].ID = 1;
	ShopItems[0].StageReq = 1;
	ShopItems[0].Desc = "Starting sword";
	//
	ShopItems[1].Name = "Quelling Blade";
	ShopItems[1].cost = 25;
	ShopItems[1].damage = 20;
	ShopItems[1].LvlToEqp = 2;
	ShopItems[1].ID = 2;
	ShopItems[1].StageReq = 1;
	ShopItems[1].Desc = "Low cost, good perfomace";
	//
	ShopItems[2].Name = "Ogre Axe";
	ShopItems[2].cost = 50;
	ShopItems[2].damage = 25;
	ShopItems[2].LvlToEqp = 4;
	ShopItems[2].ID = 3;
	ShopItems[2].StageReq = 2;
	ShopItems[2].Desc = "Stolen axe from ogre lair";
	//
	ShopItems[3].Name = "Katana";
	ShopItems[3].cost = 75;
	ShopItems[3].damage = 30;
	ShopItems[3].LvlToEqp = 6;
	ShopItems[3].ID = 4;
	ShopItems[3].StageReq = 2;
	ShopItems[3].Desc = "A samurai should always be prepared for death – whether his own or someone else's";
	//
	ShopItems[4].Name = "Desolator";
	ShopItems[4].cost = 100;
	ShopItems[4].damage = 35;
	ShopItems[4].LvlToEqp = 8;
	ShopItems[4].ID = 5;
	ShopItems[4].StageReq = 3;
	ShopItems[4].Desc = "A wicked weapon";
	//
	ShopItems[5].Name = "Skull Basher";
	ShopItems[5].cost = 125;
	ShopItems[5].damage = 40;
	ShopItems[5].LvlToEqp = 10;
	ShopItems[5].ID = 6;
	ShopItems[5].StageReq = 3;
	ShopItems[5].Desc = "A feared weapon in the right hands, this maul's ability to shatter the defenses of its opponents should not be underestimated.";
	//
	ShopItems[6].Name = "Heavens Halberd";
	ShopItems[6].cost = 125;
	ShopItems[6].damage = 45;
	ShopItems[6].LvlToEqp = 12;
	ShopItems[6].ID = 7;
	ShopItems[6].StageReq = 4;
	ShopItems[6].Desc = "This halberd moves with the speed of a smaller weapon, allowing the bearer to win duels that a heavy edge would not.";
	//
	ShopItems[7].Name = "Sacred Relic";
	ShopItems[7].cost = 150;
	ShopItems[7].damage = 50;
	ShopItems[7].LvlToEqp = 14;
	ShopItems[7].ID = 8;
	ShopItems[7].StageReq = 4;
	ShopItems[7].Desc = "An ancient weapon that often turns the tides of war.";
	//
	ShopItems[8].Name = "Ethereal blade";
	ShopItems[8].cost = 175;
	ShopItems[8].damage = 55;
	ShopItems[8].LvlToEqp = 16;
	ShopItems[8].ID = 9;
	ShopItems[8].StageReq = 5;
	ShopItems[8].Desc = "A flickering blade of a ghastly nature, it is capable of crushing damage to the enemy.";
	//
	ShopItems[9].Name = "Divine Rapier";
	ShopItems[9].cost = 293;
	ShopItems[9].damage = 70;
	ShopItems[9].LvlToEqp = 20;
	ShopItems[9].ID = 10;
	ShopItems[9].StageReq = 5;
	ShopItems[9].Desc = "He is so powerful that even God cannot control him.";
	// Swords // Swords // Swords // Swords // Swords // Swords

	// ITEMS // ITEMS // ITEMS // ITEMS // ITEMS // ITEMS // ITEMS 
	//  Consumables
	ShopItems[11].Name = "Healing Flask";
	ShopItems[11].cost = 50;
	ShopItems[11].ID = 11;
	ShopItems[11].StageReq = 1;
	ShopItems[11].Desc = "Healing you";
	//
	ShopItems[12].Name = "Tome of Knowledge";
	ShopItems[12].cost = 100;
	ShopItems[12].ID = 12;
	ShopItems[12].StageReq = 1;
	ShopItems[12].Desc = "Gives you exp";
	//  Consumables
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
		system("title Roguelike v0.3.7 by shiro // hakerhd93 // DEBUG");
	else if (DEBUG == 0)
		system("title Roguelike v0.3.7 by shiro // hakerhd93 // Beta");
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
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// Равномерно распределяем рандомное число в нашем диапазоне
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}
//
void difficultyIncrease() // TODO
{
	difficulty += 0.2f;
#pragma warning(suppress: 4244)
	EnemyDefaultStats[0] += EnemyDefaultStats[0] * difficulty;
#pragma warning(suppress: 4244)
	EnemyDefaultStats[1] += EnemyDefaultStats[1] * difficulty;
#pragma warning(suppress: 4244)
	EnemyDefaultStats[2] += EnemyDefaultStats[2] * difficulty;
#pragma warning(suppress: 4244)
	EnemyDefaultStats[3] += EnemyDefaultStats[3] * difficulty;
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
void InitializationLeftMenu()
{
	for (int j = 1; j < 34; j++)
	{
		systems::gotoxy(0, 0 + j);
		cout << "|" << "\n";
		systems::gotoxy(30, 0 + j);
		cout << "|" << "\n";
	}
	for (int i = 0; i < 31; i++)
	{
		systems::gotoxy(0 + i, 0);
		cout << "-";
	}
	for (int i = 0; i < 31; i++)
	{
		systems::gotoxy(0 + i, 34);
		cout << "-";
	}
	systems::gotoxy(1, 1);
	cout << red << "hp: " << Player.hp << " / " << Player.MaxHP << def;
	if (Player.hp < 100)
	{
		systems::gotoxy(7, 1);
		cout << " ";
		systems::gotoxy(13, 1);
		cout << " ";
	}

	systems::gotoxy(15, 1);
	cout << magenta << "xp: " << Player.exp << " / " << Player.forNextlvl << def;
	systems::gotoxy(15, 2);
	cout << brcyan << "lv: " << Player.lvl << def;
	systems::gotoxy(1, 2);
	cout << green << "Coins: " << Player.coins << def;
	systems::gotoxy(1, 3);
	cout << orange << "Difficulty: " << difficulty << def;
	systems::gotoxy(15, 3);
	cout << blue << "Stage: " << Stage << def;
	systems::gotoxy(1, 4);
	cout << "-----------------------------";
	systems::gotoxy(1, 5);
	cout << "Items:";
	systems::gotoxy(1, 6);
	cout << "-----------------------------";
	CheckItem();
	systems::gotoxy(1, 25);
	cout << brwhite << "Curret state: " << CurrentState << def;
	systems::gotoxy(1, 26);
	cout << brwhite << CurrentState2 << def;
	if (DEBUG == 1)
	{
		systems::gotoxy(1, 29);
		cout << Color::red << "// DEBUG // DEBUG // DEBUG //" << Color::def;
		systems::gotoxy(1, 30);
		cout << Color::red << "// DEBUG // DEBUG // DEBUG //" << Color::def;
		systems::gotoxy(1, 31);
		cout << Color::red << "// DEBUG // DEBUG // DEBUG //" << Color::def;
		systems::gotoxy(1, 32);
		cout << Color::red << "// DEBUG // DEBUG // DEBUG //" << Color::def;
		systems::gotoxy(1, 33);
		cout << Color::red << "// DEBUG // DEBUG // DEBUG //" << Color::def;
	}
}
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
//
int enemyCount(int xEnemy, int yEnemy)
{
	return map[yEnemy][xEnemy] - 7;
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
int WhereX(int x, int y, int fiend, bool IsEnemy)
{
	if (IsEnemy == false)
	{
		if (map[y + 1][x] == fiend)
		{
			return x;
		}
		else if (map[y - 1][x] == fiend)
		{
			return x;
		}
		else if (map[y][x + 1] == fiend)
		{
			return x + 1;
		}
		else if (map[y][x - 1] == fiend)
		{
			return x - 1;
		}
		else if (map[y + 1][x + 1] == fiend)
		{
			return x + 1;
		}
		else if (map[y + 1][x - 1] == fiend)
		{
			return x - 1;
		}
		else if (map[y - 1][x + 1] == fiend)
		{
			return x + 1;
		}
		else if (map[y - 1][x - 1] == fiend)
		{
			return x - 1;
		}
		else
		{
			return -1;
		}
	}
	if (IsEnemy == true)
	{
		for (int i = 0; i < 20; i++)
		{
			if (map[y][x - 1] == 7 + i) // left
			{
				return x - 1;
			}
			else if (map[y][x + 1] == 7 + i) // right
			{
				return x + 1;
			}
			else if (map[y + 1][x] == 7 + i) // up
			{
				return x;
			}
			else if (map[y - 1][x] == 7 + i) // down
			{
				return x;
			}
			else if (map[y - 1][x - 1] == 7 + i) // left up
			{
				return x - 1;
			}
			else if (map[y - 1][x + 1] == 7 + i) // right up
			{
				return x + 1;
			}
			else if (map[y + 1][x - 1] == 7 + i) // left down
			{
				return x - 1;
			}
			else if (map[y + 1][x + 1] == 7 + i) // right down
			{
				return x + 1;
			}
		}
	}
	return -1;
}
//
int WhereY(int x, int y, int fiend, bool IsEnemy) //fiend = whatneedtofind
{
	if (IsEnemy == false)
	{
		if (map[y + 1][x] == fiend)
		{
			return y + 1;
		}
		else if (map[y - 1][x] == fiend)
		{
			return y - 1;
		}
		else if (map[y][x + 1] == fiend)
		{
			return y;
		}
		else if (map[y][x - 1] == fiend)
		{
			return y;
		}
		else if (map[y + 1][x + 1] == fiend)
		{
			return y + 1;
		}
		else if (map[y + 1][x - 1] == fiend)
		{
			return y + 1;
		}
		else if (map[y - 1][x + 1] == fiend)
		{
			return y - 1;
		}
		else if (map[y - 1][x - 1] == fiend)
		{
			return y - 1;
		}
		else
		{
			return -1;
		}
	}
	if (IsEnemy == true)
	{
		for (int i = 0; i < 20; i++)
		{
			if (map[y - 1][x] == 7 + i)	//up
			{
				return y - 1;
			}
			else if (map[y + 1][x] == 7 + i) // down
			{
				return y + 1;
			}
			else if (map[y][x - 1] == 7 + i) //left
			{
				return y;
			}
			else if (map[y][x + 1] == 7 + i) // right
			{
				return y;
			}
			else if (map[y - 1][x - 1] == 7 + i) // left up
			{
				return y - 1;
			}
			else if (map[y - 1][x + 1] == 7 + i) // right up
			{
				return y - 1;
			}
			else if (map[y + 1][x - 1] == 7 + i) // left down
			{
				return y + 1;
			}
			else if (map[y + 1][x + 1] == 7 + i) // right down
			{
				return y + 1;
			}
		}
		return -1;
	}
	return -1;
}
//
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
void actionOnTheEnemy(int x, int y, int count, bool attack) //attack = false - check enemy, attack = true - attack enemy
{
	if (attack == false)
	{
		if (Enemy[count].hp <= 0)
		{
			map[y][x] = 0;
			systems::gotoxy(31 + x, y);
			cout << " ";
		}
		else if (Enemy[count].hp > 0)
		{
			map[y][x] = 7 + count;
		}
	}
	else if (attack == true)
	{
		if (ItemSlotID[0] == 0)
		{
			Enemy[count].hp -= ShopItems[0].damage - EnemyDefaultStats[3];
		}
		else if (ItemSlotID[0] == 1)
		{
			Enemy[count].hp -= ShopItems[1].damage - EnemyDefaultStats[3];
		}
		else if (ItemSlotID[0] == 2)
		{
			Enemy[count].hp -= ShopItems[2].damage - EnemyDefaultStats[3];
		}
		else if (ItemSlotID[0] == 3)
		{
			Enemy[count].hp -= ShopItems[3].damage - EnemyDefaultStats[3];
		}
		if (Enemy[count].hp <= 0)
		{
			map[y][x] = 0;
			systems::gotoxy(31 + x, y);
			cout << " ";
#pragma warning(suppress: 4244)
			Player.coins += 10 + (5 * difficulty);
#pragma warning(suppress: 4244)
			Player.exp += 2.5 + (2.5 * difficulty);
			CurrentState = "You killed a en";
			CurrentState2 = "emy and got money & exp";
		}
		Player.hp -= EnemyDefaultStats[0] - Player.armor;
		InitializationLeftMenu();
	}
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
		if (key == '\r' || key == 1)
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
				for (int i = 0; i < 3; i++)
				{
					if (i == 0)
					{
						do {
							ShopItemsIDs[0] = getRandomNumber(0, 9);
						} while (ShopItems[ShopItemsIDs[0]].StageReq != Stage && ShopItems[ShopItemsIDs[0]].LvlToEqp != Player.lvl);
					}
					else {
						ShopItemsIDs[i] = getRandomNumber(11, 12);
					}
				}
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
void MenuStartTutorial()
{
	system("cls"); //clear the screen.
	systems::gotoxy(50, 14);
	cout << "There is no game (Will be)" << endl;
	cin.ignore();
	system("cls");
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
void ExitOption()
{
	system("cls");
	systems::gotoxy(50, 14);
	cout << "Exitting..." << endl;
	exit(0);
}
void DebugHelp()
{
	system("cls");
	systems::gotoxy(50, 13);
	cout << Color::red << "F2 - Open shop" << Color::def;
	systems::gotoxy(50, 14);
	cout << Color::red << "Ctrl + A - reGenerate map" << Color::def;
	cin.ignore();
}