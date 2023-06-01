#define DebugMode 0
//-----------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <windows.h> // we need this header for the 'systems::gotoxy' function.
#include <conio.h> // we need this header for the '_getch' function.
#include <cstdlib> // "system" is ambiguous.
#include <stdio.h>
#include <chrono>
#include <thread>
#include <random>
#include "variableKeeper.h"
#include "colorfull.h" // ты вчера мне приподнёс
#include "systems.h"
#include "player.h"
#include <tlhelp32.h>
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
	Player.forNextlvl += 5;
#pragma warning(suppress: 4244)
	ShopItems[0].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[1].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[2].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[3].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[4].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[5].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[6].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[7].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[8].damage += Player.lvl * 1.2;
	//
#pragma warning(suppress: 4244)
	ShopItems[9].damage += Player.lvl * 1.2;
	//
	if (HealAfterKill >= 25)
	{
		HealAfterKill += 2;
	}
	Player.MaxHP += Player.lvl * 2;
	bool HaveStim = false;
	for (int i = 0; i < 6; i++)
	{
		if (variableKeeper::ItemSlotID[i] == 13)
			Player.armor += 1;
		else if (variableKeeper::ItemSlotID[i] == 14)
			HaveStim = true;
	}
	if (HaveStim == true) {
		Player.MaxHP = (Player.MaxHP - (Player.MaxHP / 10)) + Player.lvl * 2;
		Player.MaxHP += (Player.MaxHP / 10);
	}
	else
		Player.MaxHP += Player.lvl * 2;
	if (variableKeeper::ItemSlotID[0] == 9)
		ShopItems[9].damage += Player.lvl * 2;
#pragma warning(suppress: 4244)
	Player.hp += Player.lvl * 4;
#pragma warning(suppress: 4244)
	Player.armor += Player.lvl * 1.3;
	InitializationLeftMenu();
}
//
void PlayerDeath()
{
	system("cls");
	gotoxy(50, 15);
	cout << red << "You died! At stage " << Stage << def;
	gotoxy(52, 16);
	cout << cyan << "Overall score: " << black << redBG << Score << def << defBG;
	if (IsMusicOn == true)
		PlaySound(TEXT("audio\\death sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound(NULL, NULL, SND_PURGE);
	cin.ignore();
	ItemSlotID[0] = 0;
	ItemSlotID[1] = -1;
	ItemSlotID[2] = -1;
	ItemSlotID[3] = -1;
	ItemSlotID[4] = -1;
	ItemSlotID[5] = -1;
	PlayerGotCrown = false;
	IsTeleportOn = false;
	StageMusic = 0;
	BossMusic = 0;
	NeedsForTPCharge = 75;
	TPCharge = -1;
	Score = 0;
	HealAfterKill = 0;
	NumberOfEnemy = 0;
	difficulty = 1;
	Stage = 1;
	MapSeed = 0;
	Player.coins = 15;
	Player.hp = 100;
	Player.exp = 0;
	Player.forNextlvl = 10;
	Player.lvl = 1;
	Player.armor = 2;
	Player.MaxHP = 100;
	system("cls");
	return;
}
//-----------------------------------------------------------------------------------------------
int enemyCount(int xEnemy, int yEnemy, bool TpPool = false)
{
	if (TpPool == true)
	{
		return map[yEnemy][xEnemy] - 607;
	}
	else {
		return map[yEnemy][xEnemy] - 7;
	}
}
//-----------------------------------------------------------------------------------------------
string* SettingsMenuItems() // this function returns a pointer to a string.
{
	string* item = new string[3];
	item[0] = "Music: ";
	item[1] = "Seed run.";
	item[2] = "Exit. (Esc)";
	return item;
}
//-----------------------------------------------------------------------------------------------
void SoftExitOption()
{
	softExit = true;
	system("cls");
	return;
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
void MenuMusic()
{
	if (IsMusicOn == true) {
		IsMusicOn = false; PlaySound(NULL, NULL, SND_PURGE);;
	}
	else if (IsMusicOn == false) { IsMusicOn = true; PlaySound(TEXT("audio\\main menu.wav"), NULL, SND_FILENAME | SND_ASYNC); }
	return;
}
//-----------------------------------------------------------------------------------------------
void MenuSeedRun()
{
	do {
		system("cls"); //clear the screen.
		cout << "Enter the seed, it must be 9 digits, for example 293610234 (enter 0 for exit): ";
		cin >> MapSeed;
		if (MapSeed == 0)
			return;
	} while (GetNumberOfDigits(MapSeed) != 9);
	system("cls");
	return;
}
//-----------------------------------------------------------------------------------------------
void MenuSettings()	//	cfi.dwFontSize.Y = 18;
{
	system("cls");
	typedef void (*TMenuOption)(); // typedef for defining a 'pointer to function' type.
	int ItemCount = 3; // This variable holds the number of menu items.
	int MenuChoice = 1; // This variable holds the position of the cursor. 
	char key; //for entering the key (up arrow,down arrow,etc...);
	TMenuOption* MenuOption = new TMenuOption[ItemCount];//array of pointers to functions (dynamic).
	MenuOption[0] = MenuMusic; //filling the array with the functions.
	MenuOption[1] = MenuSeedRun;
	MenuOption[2] = SoftExitOption;
	while (1) //infinite loop. (this loop will not break that's why we need an exit function).
	{
		for (int i = 0; i < ItemCount; i++) // Draw the menu.
		{
			systems::gotoxy(50, 14 + i);
			MenuChoice == i + 1 ? cout << " -> " : cout << "    "; // if (i+1) == the cursor then
			//    print ' -> ' else print '    '.
			//    by the way i call '->' the cursor
			if (i == 0)
			{
				cout << SettingsMenuItems()[i] << std::boolalpha << IsMusicOn << endl; // print the name of the item.
			}
			cout << SettingsMenuItems()[i] << endl; // print the name of the item.
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
				system("cls");
				if (softExit == true)
				{
					softExit = false;
					return;
				}
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
	return;
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void MenuCredits()
{
	if (IsMusicOn == true)
		PlaySound(TEXT("audio\\credits theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else
		PlaySound(NULL, NULL, SND_PURGE);
	system("cls");
	system("mode con: cols=99 lines=39");
	systems::gotoxy(0, 0);
	cout << R"(
                  __.;=====;.__
              _.=+==++=++=+=+===;.
               -=+++=+===+=+=+++++=_
          .     -=:``     `--==+=++==.
         _vi,    `            --+=++++:
        .uvnvi.       _._       -==+==+.
       .vvnvnI`    .;==|==;.     :|=||=|.
  +QmQQmpvvnv; _yYsyQQWUUQQQm #QmQ#:QQQWUV$QQm.
   -QQWQWpvvowZ?.wQQQE==<QWWQ/QWQW.QQWW(: jQWQE
    -$QQQQmmU\'  jQQQ\@+=<QWQQ)mQQQ.mQQQC+;jWQQ\@'
     -$WQ8YnI:   QWQQwgQQWV`mWQQ.jQWQQgyyWW\@!
       -1vvnvv.     `~+++`        ++|+++
        +vnvnnv,                 `-|===
         +vnvnvns.           .      :=-
          -Invnvvnsi..___..=sv=.     `
            +Invnvnvnnnnnnnnvvnn;.
              ~|Invnvnvvnvvvnnv}+`
                  -~|{*l}*|~)";
	//systems::gotoxy(50, 0);
	//cout << R"(           __        __                     )";
	//systems::gotoxy(50, 1);
	//cout << R"(          |  \      |  \                    )";
	//systems::gotoxy(50, 2);
	//cout << R"(  _______ | $$____   \$$  ______    ______  )";
	//systems::gotoxy(50, 3);
	//cout << R"( /       \| $$    \ |  \ /      \  /      \ )";
	//systems::gotoxy(50, 4);
	//cout << R"(|  $$$$$$$| $$$$$$$\| $$|  $$$$$$\|  $$$$$$\)";
	//systems::gotoxy(50, 5);
	//cout << R"( \$$    \ | $$  | $$| $$| $$   \$$| $$  | $$)";
	//systems::gotoxy(50, 6);
	//cout << R"( _\$$$$$$\| $$  | $$| $$| $$      | $$__/ $$)";
	//systems::gotoxy(50, 7);
	//cout << R"(|       $$| $$  | $$| $$| $$       \$$    $$)";
	//systems::gotoxy(50, 8);
	//cout << R"( \$$$$$$$  \$$   \$$ \$$ \$$        \$$$$$$ )";
	systems::gotoxy(10, 20);
	cout << R"(             __                __                                                    )";
	systems::gotoxy(10, 21);
	cout << R"(            /  |              /  |                                                   )";
	systems::gotoxy(10, 22);
	cout << R"( __    __  _$$ |_     _______ $$ |  ______   __     __  __     __  ______    ______  )";
	systems::gotoxy(10, 23);
	cout << R"( __    __  _$$ |_     _______ $$ |  ______   __     __  __     __  ______    ______  )";
	systems::gotoxy(10, 24);
	cout << R"($$  \/$$/ $$$$$$/   /$$$$$$$/ $$ |/$$$$$$  |$$  \ /$$/ $$  \ /$$//$$$$$$  |/$$$$$$  |)";
	systems::gotoxy(10, 25);
	cout << R"( $$  $$<    $$ | __ $$ |      $$ |$$ |  $$ | $$  /$$/   $$  /$$/ $$    $$ |$$ |  $$/ )";
	systems::gotoxy(10, 26);
	cout << R"( $$  $$<    $$ | __ $$ |      $$ |$$ |  $$ | $$  /$$/   $$  /$$/ $$    $$ |$$ |  $$/ )";
	systems::gotoxy(10, 27);
	cout << R"(/$$/ $$  |  $$  $$/ $$       |$$ |$$    $$/    $$$/       $$$/   $$       |$$ |      )";
	systems::gotoxy(10, 28);
	cout << R"($$/   $$/    $$$$/   $$$$$$$/ $$/  $$$$$$/      $/         $/     $$$$$$$/ $$/       )";

	//             __                __                                                    
	//            /  |              /  |                                                   
	// __    __  _$$ |_     _______ $$ |  ______   __     __  __     __  ______    ______  
	///  \  /  |/ $$   |   /       |$$ | /      \ /  \   /  |/  \   /  |/      \  /      \ 
	//$$  \/$$/ $$$$$$/   /$$$$$$$/ $$ |/$$$$$$  |$$  \ /$$/ $$  \ /$$//$$$$$$  |/$$$$$$  |
	// $$  $$<    $$ | __ $$ |      $$ |$$ |  $$ | $$  /$$/   $$  /$$/ $$    $$ |$$ |  $$/ 
	// /$$$$  \   $$ |/  |$$ \_____ $$ |$$ \__$$ |  $$ $$/     $$ $$/  $$$$$$$$/ $$ |      
	///$$/ $$  |  $$  $$/ $$       |$$ |$$    $$/    $$$/       $$$/   $$       |$$ |      
	//$$/   $$/    $$$$/   $$$$$$$/ $$/  $$$$$$/      $/         $/     $$$$$$$/ $$/       



	systems::gotoxy(60, 10);
	cout << brcyan << "Hey!" << def;
	systems::gotoxy(47, 12);
	cout << brcyan << "This game was made by xtclovver," << def;
	systems::gotoxy(44, 13);
	cout << brcyan << "please do not criticize this game strictly," << def;
	systems::gotoxy(43, 14);
	cout << brcyan << "I'm still learning c++." << def;
	systems::gotoxy(41, 15);
	cout << magenta << "I would be grateful if you play my game. <3" << def;
	cin.ignore();
	system("cls");
	system("mode con cols=125 lines=35"); //размер окна, вывод нужного количества строк в консоль
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
int CheckTPZone(int x, int y)
{
	if (map[y][x] == 0)
	{
		return 600;
	}
	else if (map[y][x] == 1)
	{
		return 601;
	}
	else if (map[y][x] == 2)
	{
		return 602;
	}
	else if (map[y][x] == 4)
	{
		return 604;
	}
	else if (map[y][x] == 5)
	{
		return 605;
	}
	else if (map[y][x] == 6)
	{
		return 606;
	}
	else if (map[y][x] == 600)
	{
		return 600;
	}
	else if (map[y][x] == 601)
	{
		return 601;
	}
	else if (map[y][x] == 602)
	{
		return 602;
	}
	else if (map[y][x] == 604)
	{
		return 604;
	}
	else if (map[y][x] == 605)
	{
		return 605;
	}
	else if (map[y][x] == 606)
	{
		return 606;
	}
	else if (map[y][x] >= 607)
	{
		return 607 + NumberOfEnemy;
	}
	return -1;
}
//-----------------------------------------------------------------------------------------------
void StartTeleportEvent() {
	std::mt19937 gen(MapSeed);
	std::uniform_int_distribution<> j(yTP - 7, yTP + 7);
	std::uniform_int_distribution<> i(xTP - 7, xTP + 7);
	TPCharge = NeedsForTPCharge;
	IsTeleportOn = true;
	if (BossMusic == 1)
	{
		if (IsMusicOn == true)
			PlaySound(TEXT("audio\\boss theme 1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else
			PlaySound(NULL, NULL, SND_PURGE);
	}
	else if (BossMusic == 2)
	{
		if (IsMusicOn == true)
			PlaySound(TEXT("audio\\boss theme 2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else
			PlaySound(NULL, NULL, SND_PURGE);
	}
	else if (BossMusic == 3)
	{
		if (IsMusicOn == true)
			PlaySound(TEXT("audio\\boss theme 3.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else
			PlaySound(NULL, NULL, SND_PURGE);
	}
	for (int g = 0; g < Stage; g++)
	{
		int xEnemy = i(gen);
		int	yEnemy = j(gen);
		do {
			xEnemy = i(gen);
			yEnemy = j(gen);
		} while (map[yEnemy][xEnemy] == 600 || map[yEnemy][xEnemy] == 0);
		map[yEnemy][xEnemy] = 607 + NumberOfEnemy;
		InitializationEnemyStats(NumberOfEnemy);
		Enemy[NumberOfEnemy].x = xEnemy;
		Enemy[NumberOfEnemy].y = yEnemy;
		NumberOfEnemy++;
	}
	for (int o = -9; o < 9; o++)
	{
		for (int p = -5; p < 6; p++)
		{
			gotoxy(xTP + 31, yTP + p);
			map[yTP + p][xTP + o] = CheckTPZone(xTP + o, yTP + p);
			//cout << redBG << ' ' << defBG;
			gotoxy(xTP + 31, yTP - p);
			map[yTP - p][xTP - o] = CheckTPZone(xTP - o, yTP - p);
			//cout << redBG << ' ' << defBG;
		}
	}
	system("cls");
	InitializationLeftMenu();
	ShowMap(map);
}


//-----------------------------------------------------------------------------------------------
void GenerateMap() // 0 = normal, 1 = wall, 2 = chest, 3 = Enemy, 4 = Player, 5 = Shop, 6 = bossTP
{
	std::mt19937 gen(MapSeed);
	std::uniform_int_distribution<> x(0, 92);
	std::uniform_int_distribution<> y(1, 34);
	std::uniform_int_distribution<> randNum(0, 6);
	std::uniform_int_distribution<> cdShop(1, 350);
	Player.x = x(gen);
	Player.y = y(gen);
#pragma warning(suppress: 4244)
	int WallCount = 0, ChestCount = 253 + (20 * difficulty), EnemyCountCD = 470 - (10 * difficulty), ShopCount = 0, ShopCD, BossTPCount = 0, BossCD = 775;
	for (int j = 0; j < 35; j++)
	{
		for (int i = 0; i < 93; i++)
		{
			map[j][i] = 0;
		}
	}
	ShopCD = 350 + cdShop(gen);
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
				if (NumberOfEnemy < 2 * difficulty)
				{
					map[j][i] = 7 + NumberOfEnemy;
					InitializationEnemyStats(NumberOfEnemy);
#pragma warning(suppress: 4244)
					EnemyCountCD = 370 - (10 * difficulty);
					Enemy[NumberOfEnemy].x = i;
					Enemy[NumberOfEnemy].y = j;
					NumberOfEnemy++;
					continue;
				}
			}
			else
			{
				EnemyCountCD--;
			}
			do {
				rNum = randNum(gen);
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
				if (NumberOfEnemy < 2 * difficulty && EnemyCountCD <= 0)
				{
					map[j][i] = 7 + NumberOfEnemy;
					InitializationEnemyStats(NumberOfEnemy);
#pragma warning(suppress: 4244)
					EnemyCountCD = 370 - (10 * difficulty);
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
			else if (rNum == 6 && BossTPCount != 1 && BossCD <= 0 && i > 20 && j > 10 && i < 50 && j < 20)
			{
				map[j][i] = 6;
				BossTPCount = 1;
				xTP = i;
				yTP = j;
			}
			BossCD--;
			ShopCD--;
		}
	}
}
//-----------------------------------------------------------------------------------------------
void MenuStartTutorial()
{
	system("cls"); //clear the screen.
	systems::gotoxy(1, 0);
	cout << red << "hp - This your health point, if hp < 0 - you died" << def;
	systems::gotoxy(1, 1);
	cout << green << "coins - For coins you can buy weapons, items and all sorts of consumables" << def;
	systems::gotoxy(1, 2);
	cout << yellow << "Difficulty - The higher the difficulty, the stronger the enemies, and, accordingly, the greater the reward." << def;
	systems::gotoxy(1, 3);
	cout << magenta << "xp - For killing enemies you get experience, experience is needed to level up" << def;
	systems::gotoxy(1, 4);
	cout << cyan << "lv (level, lvl) - For each level up, you heal and raise maximum hp, and the weapon starts to hit harder." << def;
	systems::gotoxy(1, 5);
	cout << blue << "Stage - After completing the teleport event, you move on to the next stage. With each stage, the game becomes more and more difficult." << def;
	systems::gotoxy(1, 7);
	cout << white << "The first item slot can ONLY have weapons, items in the rest of the slots. You cannot have more than 1 weapon." << def;
	systems::gotoxy(4, 10);
	cout << green << "P - It's you, the player! You can move them using the arrows on the keyboard, press Enter to interact with the enemy, store, teleport, etc." << def;
	systems::gotoxy(4, 12);
	cout << white << "The empty space - is the floor, both the player and the enemy can walk on it" << def;
	systems::gotoxy(4, 13);
	cout << yellow << "* - This is a chest, by pressing Enter, you will open the chest and get some coins " << def;
	systems::gotoxy(4, 14);
	cout << white << "# - It's a wall, you can't go through it." << def;
	systems::gotoxy(4, 15);
	cout << red << "E - This is an enemy, if you approach him, he will start to fight with you, you can hit him and he will die ;(" << def;
	systems::gotoxy(4, 16);
	cout << orange << "$ - This is a store, you can open it on Enter and buy something in it, unless of course you have coins. Stores are updated once per stage" << def;
	systems::gotoxy(4, 18);
	cout << magenta << "@ - This is an event teleport, you will need to stay in it for some time in order to take you to the next stage " << def;
	systems::gotoxy(4, 22);
	cout << brcyan << "Map generation seed (seed) - if you like your run and want to transfer the generation of a map, items, etc. to someone or just play again on the same map, then write down this seed and enter it in the settings" << def;
	systems::gotoxy(4, 22);
	cout << brcyan << "	Last Action - this line will tell you what happened last time(For example, killing an enemy or opening a chest)" << def;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void OpenChest(int x, int y)
{
	if (map[y][x] == 2)
	{
		Score += 10;
		Player.coins += 3 + (Stage * 3);
		CurrentState = "You open a chest!";
		map[y][x] = 0;
		systems::gotoxy(31 + x, y);
		cout << " ";
		InitializationLeftMenu();
	}
}
//-----------------------------------------------------------------------------------------------
void EnemyAI(int i) // 1 is YOU attaked, 2 is just made a move
{
	if ((WhereX(Enemy[i].x, Enemy[i].y, 0, false) != -1 && WhereY(Enemy[i].x, Enemy[i].y, 0, false) != -1) || (WhereX(Enemy[i].x, Enemy[i].y, 600, false) != -1 && WhereY(Enemy[i].x, Enemy[i].y, 600, false) != -1))
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
		}
		if (((WhereX(Enemy[i].x, Enemy[i].y, 4, false) <= Enemy[i].x + 1 && WhereX(Enemy[i].x, Enemy[i].y, 4, false) >= Enemy[i].x - 1) && (WhereY(Enemy[i].x, Enemy[i].y, 4, false) <= Enemy[i].y + 1 && WhereY(Enemy[i].x, Enemy[i].y, 4, false) >= Enemy[i].y - 1)) || (WhereX(Enemy[i].x, Enemy[i].y, 604, false) <= Enemy[i].x + 1 && WhereX(Enemy[i].x, Enemy[i].y, 604, false) >= Enemy[i].x - 1) && (WhereY(Enemy[i].x, Enemy[i].y, 604, false) <= Enemy[i].y + 1 && WhereY(Enemy[i].x, Enemy[i].y, 604, false) >= Enemy[i].y - 1))
		{
			Player.hp -= EnemyDefaultStats[0] - (Player.armor * 3); // offencive поощираю 
			InitializationLeftMenu();
			Enemy[i].toTurn = 0;
			return;
		}
		switch (randNum)
		{
		case 1: //1 - left
			if ((map[Enemy[i].y][Enemy[i].x - 1] == 0 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'L', map) == true) || (map[Enemy[i].y][Enemy[i].x - 1] == 600 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'L', map) == true))
			{
				if (map[Enemy[i].y][Enemy[i].x - 1] == 600)
					map[Enemy[i].y][Enemy[i].x - 1] = 607 + i;
				else
					map[Enemy[i].y][Enemy[i].x - 1] = 7 + i;
				systems::gotoxy(31 + (Enemy[i].x - 1), 0 + Enemy[i].y);
				if (map[Enemy[i].y][Enemy[i].x - 1] == 607 + i)
					cout << redBG << magenta << EnemySymbol << def << defBG;
				else
					cout << red << EnemySymbol << def;
				systems::gotoxy(31 + Enemy[i].x, 0 + Enemy[i].y);
				if (map[Enemy[i].y][Enemy[i].x] == 607 + i) {
					map[Enemy[i].y][Enemy[i].x] = 600;
					cout << redBG << FloorSymbol << defBG;
				}
				else {
					map[Enemy[i].y][Enemy[i].x] = 0;
					cout << FloorSymbol;
				}
				Enemy[i].x--;
				Enemy[i].toTurn = 0;
			}
			break;
		case 2://2 - up
			if ((map[Enemy[i].y - 1][Enemy[i].x] == 0 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'U', map) == true) || (map[Enemy[i].y - 1][Enemy[i].x] == 600 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'U', map) == true))
			{
				if (map[Enemy[i].y - 1][Enemy[i].x] == 600)
					map[Enemy[i].y - 1][Enemy[i].x] = 607 + i;
				else
					map[Enemy[i].y - 1][Enemy[i].x] = 7 + i;
				systems::gotoxy(31 + Enemy[i].x, 0 + (Enemy[i].y - 1));
				if (map[Enemy[i].y - 1][Enemy[i].x] == 607 + i)
					cout << redBG << magenta << EnemySymbol << def << defBG;
				else
					cout << red << EnemySymbol << def;
				systems::gotoxy(31 + Enemy[i].x, 0 + Enemy[i].y);
				if (map[Enemy[i].y][Enemy[i].x] == 607 + i) {
					map[Enemy[i].y][Enemy[i].x] = 600;
					cout << redBG << FloorSymbol << defBG;
				}
				else {
					map[Enemy[i].y][Enemy[i].x] = 0;
					cout << FloorSymbol;
				}
				Enemy[i].y--;
				Enemy[i].toTurn = 0;
			}
			break;
		case 3: // 3 - right
			if ((map[Enemy[i].y][Enemy[i].x + 1] == 0 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'R', map) == true) || (map[Enemy[i].y][Enemy[i].x + 1] == 600 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'R', map) == true))
			{
				if (map[Enemy[i].y][Enemy[i].x + 1] == 600)
					map[Enemy[i].y][Enemy[i].x + 1] = 607 + i;
				else
					map[Enemy[i].y][Enemy[i].x + 1] = 7 + i;
				systems::gotoxy(31 + (Enemy[i].x + 1), 0 + Enemy[i].y);
				if (map[Enemy[i].y][Enemy[i].x + 1] == 607 + i)
					cout << redBG << magenta << EnemySymbol << def << defBG;
				else
					cout << red << EnemySymbol << def;
				systems::gotoxy(31 + Enemy[i].x, 0 + Enemy[i].y);
				if (map[Enemy[i].y][Enemy[i].x] == 607 + i) {
					map[Enemy[i].y][Enemy[i].x] = 600;
					cout << redBG << FloorSymbol << defBG;
				}
				else {
					map[Enemy[i].y][Enemy[i].x] = 0;
					cout << FloorSymbol;
				}
				Enemy[i].x++;
				Enemy[i].toTurn = 0;
			}
			break;
		case 4: // 4 - down
			if ((map[Enemy[i].y + 1][Enemy[i].x] == 0 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'D', map) == true) || (map[Enemy[i].y + 1][Enemy[i].x] == 600 && IsNothingDisturbingThePlayer(Enemy[i].x, Enemy[i].y, 'D', map) == true))
			{
				if (map[Enemy[i].y + 1][Enemy[i].x] == 600)
					map[Enemy[i].y + 1][Enemy[i].x] = 607 + i;
				else
					map[Enemy[i].y + 1][Enemy[i].x] = 7 + i;
				systems::gotoxy(31 + Enemy[i].x, 0 + (Enemy[i].y + 1));
				if (map[Enemy[i].y + 1][Enemy[i].x] == 607 + i)
					cout << redBG << magenta << EnemySymbol << def << defBG;
				else
					cout << red << EnemySymbol << def;
				systems::gotoxy(31 + Enemy[i].x, 0 + Enemy[i].y);
				if (map[Enemy[i].y][Enemy[i].x] == 607 + i) {
					map[Enemy[i].y][Enemy[i].x] = 600;
					cout << redBG << FloorSymbol << defBG;
				}
				else {
					map[Enemy[i].y][Enemy[i].x] = 0;
					cout << FloorSymbol;
				}
				Enemy[i].y++;
				Enemy[i].toTurn = 0;
			}
			break;
		default:
			break;

		}
		return;
	}
}
//-----------------------------------------------------------------------------------------------
void GoToTheNextStage();
//-----------------------------------------------------------------------------------------------
void Gameplay(int map[35][93])
{
	char key;
	bool IsNothingDisturbing;
	system("cls"); //clear the screen.
	gotoxy(1, 1);
	if (MapSeed == 0)
	{
		do {
			std::random_device rd;
			std::mt19937::result_type seed = rd() ^ (
				(std::mt19937::result_type)
				std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now().time_since_epoch()
				).count() +
				(std::mt19937::result_type)
				std::chrono::duration_cast<std::chrono::microseconds>(
					std::chrono::high_resolution_clock::now().time_since_epoch()
				).count());
			MapSeed = seed;
		} while (GetNumberOfDigits(MapSeed) != 9);
	}
	std::mt19937 gen(MapSeed);
	std::mt19937::result_type seed = MapSeed;
	system("cls");
	GenerateMap();
	InitializationLeftMenu();
	ShowMap(map);
	std::uniform_int_distribution<> WeaponRand(0, 9);
	std::uniform_int_distribution<> ItemRand(12, 16);
	std::uniform_int_distribution<> ConsumableRand(10, 11);
	std::uniform_int_distribution<> StageRand(1, 4);
	std::uniform_int_distribution<> BossRand(1, 3);
	StageMusic = StageRand(gen);
	BossMusic = BossRand(gen);
	if (StageMusic == 1)
	{
		if (IsMusicOn == true)
			PlaySound(TEXT("audio\\stage theme 1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else
			PlaySound(NULL, NULL, SND_PURGE);
	}
	else if (StageMusic == 2)
	{
		if (IsMusicOn == true)
			PlaySound(TEXT("audio\\stage theme 2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else
			PlaySound(NULL, NULL, SND_PURGE);
	}
	else if (StageMusic == 3)
	{
		if (IsMusicOn == true)
			PlaySound(TEXT("audio\\stage theme 3.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else
			PlaySound(NULL, NULL, SND_PURGE);
	}
	else if (StageMusic == 4)
	{
		if (IsMusicOn == true)
			PlaySound(TEXT("audio\\stage theme 4.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		else
			PlaySound(NULL, NULL, SND_PURGE);
	}
	MinStage = Stage - 1;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			do {
				ShopItemsIDs[0] = WeaponRand(gen);
			} while (ShopItems[ShopItemsIDs[0]].StageReq > Stage || ShopItems[ShopItemsIDs[0]].StageReq <= MinStage);
		}
		else if (i == 1) {
			do {
				ShopItemsIDs[1] = ItemRand(gen);
			} while (ShopItems[ShopItemsIDs[1]].StageReq > Stage);
		}
		else if (i == 2) {
			do {
				ShopItemsIDs[2] = ConsumableRand(gen);
			} while (ShopItems[ShopItemsIDs[2]].LvlToEqp > Player.lvl);
		}
	}
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if (Player.hp <= 0)
		{
			PlayerDeath();
			return;
		}
		if (Player.exp >= Player.forNextlvl)
		{
			UpgradeLvl();
			if (Player.lvl >= 19)
			{
				gotoxy(27, 1);
				cout << ' ';
			}
			else {
				gotoxy(25, 1);
				cout << ' ';
			}
		}
		gotoxy(1, 29);
		cout << brcyan << "Score: " << Score << def;
		if (IsTeleportOn == true)
		{
			gotoxy(13, 27);
			cout << brcyan << "TP Charge: " << TPCharge << def;
			if (TPCharge < 10)
			{
				gotoxy(25, 27);
				cout << ' ';
			}
		}
		if (TPCharge == 0)
			GoToTheNextStage();
		if (Player.y < 10)
		{
			gotoxy(14, 26);
			cout << " ";
		}
		if (DebugMode == 1)
		{
			systems::gotoxy(1, 27);
			std::cout << Color::brwhite << "x: " << player::Player.x << Color::def;
			systems::gotoxy(10, 27);
			std::cout << Color::brwhite << "y: " << player::Player.y << Color::def;
			systems::gotoxy(1, 29);
			std::cout << "up: '" << variableKeeper::map[Player.y - 1][Player.x] << "'";
			systems::gotoxy(1, 30);
			std::cout << "down: '" << variableKeeper::map[Player.y + 1][Player.x] << "'";
			systems::gotoxy(1, 31);
			std::cout << "left: '" << variableKeeper::map[Player.y][Player.x - 1] << "'";
			systems::gotoxy(1, 32);
			std::cout << "right: '" << variableKeeper::map[Player.y][Player.x + 1] << "'";
		}
		key = _getch();
		if (key == '\r' || (key >= 1 && key <= 26)) {}
		else {
			key = _getch();   // FIX BRAIN MICROSOFT 
		}
		switch (key) //check the entered key.
		{
		case '<': // f2 mb
			if (DebugMode == 1)
			{
				OpenShop();
			}
			else {}
			break;
			// https://adventuregamestudio.github.io/ags-manual/ASCIIcodes.html
		case 1: // Ctrl + A
			if (DebugMode == 1)
			{
				do {
					std::random_device rd;
					std::mt19937::result_type seed = rd() ^ (
						(std::mt19937::result_type)
						std::chrono::duration_cast<std::chrono::seconds>(
							std::chrono::system_clock::now().time_since_epoch()
						).count() +
						(std::mt19937::result_type)
						std::chrono::duration_cast<std::chrono::microseconds>(
							std::chrono::high_resolution_clock::now().time_since_epoch()
						).count());
					MapSeed = seed;
				} while (GetNumberOfDigits(MapSeed) != 9);
				NumberOfEnemy = 0;
				Score = 0;
				IsTeleportOn = false;
				PlayerGotCrown = false;
				TPCharge = -1;
				HealAfterKill = 0;
				difficulty = 1;
				Stage = 1;
				Gameplay(map);
				continue;
			}
			else {}
			break;
		case 2: // Ctrl + B
			if (DebugMode == 1)
			{
				for (int i = 0; i < 3; i++)
				{
					if (i == 0)
					{
						do {
							ShopItemsIDs[0] = WeaponRand(gen);
						} while (ShopItems[ShopItemsIDs[0]].StageReq > Stage);
					}
					else if (i == 1) {
						do {
							ShopItemsIDs[1] = ItemRand(gen);
						} while (ShopItems[ShopItemsIDs[2]].StageReq > Stage);
					}
					else if (i == 2) {
						do {
							ShopItemsIDs[2] = ConsumableRand(gen);
						} while (ShopItems[ShopItemsIDs[1]].StageReq > Stage);
					}
				}
				continue;
			}
			else {}
			break;
		case 3: // Ctrl + C
			if (DebugMode == 1)
			{
				Player.coins += 150;
				InitializationLeftMenu();
				continue;
			}
			else {}
			break;
		case 4: // Ctrl + D
			if (DebugMode == 1)
			{
				Player.exp += 5;
				InitializationLeftMenu();
				continue;
			}
			else {}
			break;
		case 5: // Ctrl + E
			if (DebugMode == 1)
			{
				Player.lvl += 1;
				InitializationLeftMenu();
				continue;
			}
			else {}
			break;
		case 6: // Ctrl + F
			if (DebugMode == 1)
			{
				Player.hp = Player.MaxHP;
				InitializationLeftMenu();
				continue;
			}
			else {}
			break;
		case 7: // Ctrl + G
			if (DebugMode == 1)
			{
				StartTeleportEvent();
				continue;
			}
			else {}
			break;
		case 8: // Ctrl + H
			if (DebugMode == 1)
			{
				system("cls");
				ShowMap(map);
				InitializationLeftMenu();
				continue;
			}
			else {}
			break;
		case 9: // Ctrl + i
			if (DebugMode == 1)
			{
				GoToTheNextStage();
				continue;
			}
			else {}
			break;
		case '\r': // if the entered key is 'Enter'.
			try
			{
				if ((WhereX(Player.x, Player.y, 0, true, false) == -1 && WhereY(Player.x, Player.y, 0, true, false) == -1) && (WhereX(Player.x, Player.y, 0, true, true) == -1 && WhereY(Player.x, Player.y, 0, true, true) == -1))
				{
					if (WhereX(Player.x, Player.y, 5, false) != -1 && WhereY(Player.x, Player.y, 5, false) != -1)
					{
						OpenShop();
					}
					else if (WhereX(Player.x, Player.y, 2, false) != -1 && WhereY(Player.x, Player.y, 2, false) != -1)
					{
						OpenChest(WhereX(Player.x, Player.y, 2, false), WhereY(Player.x, Player.y, 2, false));
					}
					else if (WhereX(Player.x, Player.y, 6, false) != -1 && WhereY(Player.x, Player.y, 6, false) != -1)
					{
						StartTeleportEvent();
					}
				}
				else if (WhereX(Player.x, Player.y, 0, true, false) != -1 && WhereY(Player.x, Player.y, 0, true, false) != -1)
				{
					actionOnTheEnemy(WhereX(Player.x, Player.y, 0, true), WhereY(Player.x, Player.y, 0, true), enemyCount(WhereX(Player.x, Player.y, 0, true), WhereY(Player.x, Player.y, 0, true), false), true);
				}
				else if (WhereX(Player.x, Player.y, 0, true, true) != -1 && WhereY(Player.x, Player.y, 0, true, true) != -1)
				{
					actionOnTheEnemy(WhereX(Player.x, Player.y, 0, true, true), WhereY(Player.x, Player.y, 0, true, true), enemyCount(WhereX(Player.x, Player.y, 0, true, true), WhereY(Player.x, Player.y, 0, true, true), true), true, true);
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
					if (map[Player.y + 1][Player.x] == 600)
						map[Player.y + 1][Player.x] = 604;
					else
						map[Player.y + 1][Player.x] = 4;
					systems::gotoxy(31 + Player.x, 0 + (Player.y + 1));
					if (map[Player.y + 1][Player.x] == 604)
						cout << redBG << green << PlayerSymbol << defBG << def;
					else
						cout << green << PlayerSymbol << def;
					systems::gotoxy(31 + Player.x, 0 + Player.y);
					if (map[Player.y][Player.x] == 604) {
						map[Player.y][Player.x] = 600;
						cout << redBG << FloorSymbol << defBG;
						if (TPCharge != -1 && TPCharge != 0)
						{
							TPCharge--;
						}
					}
					else {
						map[Player.y][Player.x] = 0;
						cout << FloorSymbol;
					}
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
					if (map[Player.y - 1][Player.x] == 600)
						map[Player.y - 1][Player.x] = 604;
					else
						map[Player.y - 1][Player.x] = 4;
					systems::gotoxy(31 + Player.x, 0 + (Player.y - 1));
					if (map[Player.y - 1][Player.x] == 604)
						cout << redBG << green << PlayerSymbol << defBG << def;
					else
						cout << green << PlayerSymbol << def;
					systems::gotoxy(31 + Player.x, 0 + Player.y);
					if (map[Player.y][Player.x] == 604) {
						map[Player.y][Player.x] = 600;
						cout << redBG << FloorSymbol << defBG;
						if (TPCharge != -1 && TPCharge != 0)
						{
							TPCharge--;
						}
					}
					else {
						map[Player.y][Player.x] = 0;
						cout << FloorSymbol;
					}
					Player.y--;
				}
			}
			else if (IsNothingDisturbing == false) {}
			break;
		case 'K': // left arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(Player.x, Player.y, 'L', map);
			if (IsNothingDisturbing == true)
			{
				if (map[Player.y][Player.x - 1] == 600)
					map[Player.y][Player.x - 1] = 604;
				else
					map[Player.y][Player.x - 1] = 4;
				systems::gotoxy(31 + (Player.x - 1), 0 + Player.y);
				if (map[Player.y][Player.x - 1] == 604)
					cout << redBG << green << PlayerSymbol << defBG << def;
				else
					cout << green << PlayerSymbol << def;
				systems::gotoxy(31 + Player.x, 0 + Player.y);
				if (map[Player.y][Player.x] == 604) {
					map[Player.y][Player.x] = 600;
					cout << redBG << FloorSymbol << defBG;
					if (TPCharge != -1 && TPCharge != 0)
					{
						TPCharge--;
					}
				}
				else {
					map[Player.y][Player.x] = 0;
					cout << FloorSymbol;
				}
				Player.x--;
			}
			else if (IsNothingDisturbing == false) {}
			break;
		case 'M': // right arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(Player.x, Player.y, 'R', map);
			if (IsNothingDisturbing == true)
			{
				if (map[Player.y][Player.x + 1] == 600)
					map[Player.y][Player.x + 1] = 604;
				else
					map[Player.y][Player.x + 1] = 4;
				systems::gotoxy(31 + (Player.x + 1), 0 + Player.y);
				if (map[Player.y][Player.x + 1] == 604)
					cout << redBG << green << PlayerSymbol << defBG << def;
				else
					cout << green << PlayerSymbol << def;
				systems::gotoxy(31 + Player.x, 0 + Player.y);
				if (map[Player.y][Player.x] == 604) {
					if (TPCharge != -1 && TPCharge != 0)
					{
						TPCharge--;
					}
					map[Player.y][Player.x] = 600;
					cout << redBG << FloorSymbol << defBG;
				}
				else {
					map[Player.y][Player.x] = 0;
					cout << FloorSymbol;
				}
				Player.x++;
			}
			else if (IsNothingDisturbing == false) {}
			break;
		case 27: // Esc
			try {
				system("cls");
				return;

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
		for (int i = 0; i < NumberOfEnemy; i++)
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
void GoToTheNextStage() // TODO
{
	TPCharge = -1;
	Score += 100;
	IsTeleportOn = false;
	NumberOfEnemy = 0;
#pragma warning(suppress: 4244)
	MapSeed = 1 + (MapSeed / Stage) * (Stage * 0.93); // 333826495
	do {
		if (GetNumberOfDigits(MapSeed) == 8)
			MapSeed *= (Stage * 0.15) + 1;
		else if (GetNumberOfDigits(MapSeed) >= 10)
			MapSeed /= (Stage * 0.15) + 1;
		else if (MapSeed <= 200000000)
			MapSeed *= 2;
	} while (GetNumberOfDigits(MapSeed) != 9);
	Stage += 1;
#pragma warning(suppress: 4244)
	Score += Player.coins;
	Player.coins = 0;
	if (IsMusicOn == true)
		PlaySound(TEXT("audio\\stage complited.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else
		PlaySound(NULL, NULL, SND_PURGE);
	system("cls");
	gotoxy(58, 15);
	cout << red << "Stage " << Stage << def;
	gotoxy(51, 16);
	cout << redBG << black << "it will only get worse" << def << defBG;
	std::this_thread::sleep_for(std::chrono::milliseconds(3500));
	system("cls");
	difficultyIncrease();
	Gameplay(map);
}
//-----------------------------------------------------------------------------------------------
void MenuStart()
{
	system("cls");
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
	Gameplay(map);
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
	systems::gotoxy(50, 17);
	cout << Color::red << "Ctrl + G - Force start teleport event" << Color::def;
	systems::gotoxy(50, 18);
	cout << Color::red << "Ctrl + H - Force re-render map & interface" << Color::def;
	systems::gotoxy(50, 19);
	cout << Color::red << "Ctrl + i - Next stage" << Color::def;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
string* MenuItems() // this function returns a pointer to a string.
{
	string* item = new string[5];
	item[0] = "Start new game.";
	if (DebugMode == 1)
		item[1] = "Debug help.";
	else
		item[1] = "Tutorial.";
	item[2] = "Settings.";
	item[3] = "Credits.";
	item[4] = "Exit.";
	return item;
}
//-----------------------------------------------------------------------------------------------
int main()
{
	//system("cmd /K conhost C:\\Users\\fetis\\source\\repos\\roguelike\\x64\\Release\\roguelike.exe");
	/*system("taskkill /IM WindowsTerminal.exe /F");*/
	//}
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
	ShopItems[1].damage = 20;
	ShopItems[1].cost = 40;
	ShopItems[1].LvlToEqp = 1;
	ShopItems[1].ID = 1;
	ShopItems[1].StageReq = 1;
	ShopItems[1].Desc = "Low cost, good perfomace";
	//
	ShopItems[2].Name = "Ogre Axe";
	ShopItems[2].cost = 60;
	ShopItems[2].damage = 25;
	ShopItems[2].LvlToEqp = 2;
	ShopItems[2].ID = 2;
	ShopItems[2].StageReq = 2;
	ShopItems[2].Desc = "Stolen axe from ogre lair";
	//
	ShopItems[3].Name = "Katana";
	ShopItems[3].cost = 95;
	ShopItems[3].damage = 30;
	ShopItems[3].LvlToEqp = 2;
	ShopItems[3].ID = 3;
	ShopItems[3].StageReq = 3;
	ShopItems[3].Desc = "A samurai should always be prepared for death – whether his own or someone else's";
	//
	ShopItems[4].Name = "Desolator";
	ShopItems[4].cost = 120;
	ShopItems[4].damage = 40;
	ShopItems[4].LvlToEqp = 4;
	ShopItems[4].ID = 4;
	ShopItems[4].StageReq = 4;
	ShopItems[4].Desc = "A wicked weapon";
	//
	ShopItems[5].Name = "Skull Basher";
	ShopItems[5].cost = 125;
	ShopItems[5].damage = 50;
	ShopItems[5].LvlToEqp = 5;
	ShopItems[5].ID = 5;
	ShopItems[5].StageReq = 5;
	ShopItems[5].Desc = "A feared weapon in the right hands, this maul's ability to shatter the defenses of its opponents should not be underestimated.";
	//
	ShopItems[6].Name = "Heavens Halberd";
	ShopItems[6].cost = 180;
	ShopItems[6].damage = 60;
	ShopItems[6].LvlToEqp = 7;
	ShopItems[6].ID = 6;
	ShopItems[6].StageReq = 6;
	ShopItems[6].Desc = "This halberd moves with the speed of a smaller weapon, allowing the bearer to win duels that a heavy edge would not.";
	//
	ShopItems[7].Name = "Sacred Relic";
	ShopItems[7].cost = 200;
	ShopItems[7].damage = 85;
	ShopItems[7].LvlToEqp = 8;
	ShopItems[7].ID = 7;
	ShopItems[7].StageReq = 7;
	ShopItems[7].Desc = "An ancient weapon that often turns the tides of war.";
	//
	ShopItems[8].Name = "Ethereal blade";
	ShopItems[8].cost = 300;
	ShopItems[8].damage = 135;
	ShopItems[8].LvlToEqp = 10;
	ShopItems[8].ID = 8;
	ShopItems[8].StageReq = 8;
	ShopItems[8].Desc = "A flickering blade of a ghastly nature, it is capable of crushing damage to the enemy.";
	//
	ShopItems[9].Name = "Divine Rapier";
	ShopItems[9].cost = 450;
	ShopItems[9].damage = 325;
	ShopItems[9].LvlToEqp = 12;
	ShopItems[9].ID = 9;
	ShopItems[9].StageReq = 10;
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
	ShopItems[11].LvlToEqp = 2;
	ShopItems[11].ID = 11;
	ShopItems[11].StageReq = 2;
	ShopItems[11].Desc = "Gives you exp";
	//  Consumables
	// Items
	ShopItems[12].Name = "Morbid Mask";
	ShopItems[12].cost = 35;
	ShopItems[12].ID = 12;
	ShopItems[12].special = 15;
	ShopItems[12].StageReq = 2;
	ShopItems[12].Desc = "After killing a enemy, gives you 15 hp (+2 per level)";
	//
	ShopItems[13].Name = "Chainmail";
	ShopItems[13].cost = 50;
	ShopItems[13].ID = 13;
	ShopItems[13].special = 3;
	ShopItems[13].StageReq = 2;
	ShopItems[13].Desc = "Gives you 3 armor (scales w/ lvl)";
	//
	ShopItems[14].Name = "Combat Implant";
	ShopItems[14].cost = 75;
	ShopItems[14].ID = 14;
	ShopItems[14].special = 0;
	ShopItems[14].StageReq = 3;
	ShopItems[14].Desc = "Permanently grants an additional 10% to your health";
	//
	ShopItems[15].Name = "Focused Convergence";
	ShopItems[15].cost = 150;
	ShopItems[15].ID = 15;
	ShopItems[15].special = 25;
	ShopItems[15].StageReq = 3;
	ShopItems[15].Desc = "Required time to charge the teleporter -25 turns";
	//
	ShopItems[16].Name = "Cyan crown";
	ShopItems[16].cost = 50;
	ShopItems[16].ID = 16;
	ShopItems[16].special = 25;
	ShopItems[16].StageReq = 1;
	ShopItems[16].Desc = "Enemies give 25% more exp";
	// Items
	// ITEMS // ITEMS // ITEMS // ITEMS // ITEMS // ITEMS // ITEMS 
	// PlayerStats // PlayerStats // PlayerStats // PlayerStats 
	Player.coins = 25;
	Player.hp = 100;
	Player.exp = 0;
	Player.forNextlvl = 10;
	Player.lvl = 1;
	Player.armor = 2;
	Player.MaxHP = 100;
	// PlayerStats // PlayerStats // PlayerStats // PlayerStats 
	if (DebugMode == 1)
		IsMusicOn = false;
	if (DebugMode == 1)
		system("title Roguelike v1.0.3 by xtclovver // DEBUG");
	else if (DebugMode == 0)
		system("title Roguelike v1.0.3 by xtclovver");
	ChangeCursorStatus(false);
	////////////////////меняем размер консоли 
	system("mode con cols=125 lines=35"); //размер окна, вывод нужного количества строк в консоль
	HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD  size{ 100,100 };//символов строки, строк
	COORD  size{ 120,30 };//символов строки, строк
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
	//if (DebugMode == 1)
	//	IsMusicOn = false;
	if (IsMusicOn == true)
		PlaySound(TEXT("audio\\main menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else
		PlaySound(NULL, NULL, SND_PURGE);
	TMenuOption* MenuOption = new TMenuOption[ItemCount];//array of pointers to functions (dynamic).
	MenuOption[0] = MenuStart; //filling the array with the functions.
	MenuOption[1] = MenuStartTutorial;
	MenuOption[2] = MenuSettings;
	MenuOption[3] = MenuCredits;
	MenuOption[4] = ExitOption;
	if (DebugMode == 1)
	{
		MenuOption[1] = DebugHelp;
	}
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
//if (IsMusicOn == true)
//	PlaySound(TEXT("audio\\main menu.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
//else
//	PlaySound(NULL, NULL, SND_PURGE);
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