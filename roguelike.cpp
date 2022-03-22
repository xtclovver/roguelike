#include <iostream>
#include <string>
#include <windows.h> // we need this header for the 'gotoxy' function.
#include <conio.h> // we need this header for the '_getch' function.
#include <cstdlib> // "system" is ambiguous.
#include <stdio.h>
#include <fstream>
#include <vector>
#include <fstream>
#include "colorfull.h" // full of huinya
#pragma warning(push, 0)
#include "colorfull.h"
#pragma warning(pop)
//-----------------------------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------------------------
Color::Modifier magenta(Color::FG_MAGENTA);// " << mag << "
Color::Modifier red(Color::FG_RED);// " << rou << "
Color::Modifier def(Color::FG_DEFAULT);// " << def << "
Color::Modifier yellow(Color::FG_YELLOW);// " << yel << "
Color::Modifier green(Color::FG_GREEN);// " << gre << "
Color::Modifier orange(Color::FG_ORANGE);// " << ora << "
Color::Modifier pink(Color::FG_PINK);// " << pin << "
Color::Modifier black(Color::FG_BLACK);// " << bla << "
Color::Modifier gray(Color::FG_GREY);// " << gry << "
Color::Modifier white(Color::FG_WHITE);// " << whi << "
Color::Modifier brwhite(Color::BG_BRWHITE);// " << big << "
Color::Modifier brcyan(Color::FG_BRCYAN);// " << bcc << "
Color::Modifier cyan(Color::FG_CYAN);// " << cya << "
Color::Modifier blue(Color::FG_BLUE);// " << blu << "
//-----------------------------------------------------------------------------------------------
string* MenuItems(); // a function that returns the name of a menu item.

void gotoxy(int, int); // by this function you can goto any position on the cmd line screen.

void ChangeCursorStatus(bool);

void MenuStart(); // every menu item needs a seperate function, so this is for the first item.

void MenuSettings(); //    and the second item etc...

void MenuAchievements(); 

void Gameplay(int map[35][93]);

void GenerateMap();

void difficultyIncrease();

void InitializationLeftMenu();

void ShowMap();

void MenuStartTutorial(); // TODO

bool IsNothingDisturbingThePlayer(int x, int y, char Where);

bool CanYouHitAEnemy(int x, int y);

void InitializationEnemyStats(int count);

void CheckItem();

void actionOnTheEnemy(int x, int y, int count, bool attack);

int WhereIsChestX(int x, int y);

int WhereIsChestX(int x, int y);

void OpenChest(int x, int y);

int xEnemy(int x, int y);

int yEnemy(int x, int y);

void ExitOption(); // this is also an item function but i named it like this coz every menu must
				   //    have an exit item.
//-----------------------------------------------------------------------------------------------
//
int map[35][93]; // map \\ level
int xPlayer, yPlayer, playerCoins = 15, playerHP = 100, playerXP = 0, playerLVL = 1;
int difficulty = 1, Stage = 1;
int ItemSlotID[6] = {1,0,0,0,0,0}, DefaultSword[3] = {15,1,5}, FireSword[3] = {25,3,75}, IchorSword[3] = {35,4,150}, Katana[3] = {50,6,300}; // DefaultSword {15 is dmg, 1 is lvl to need to equip, 0 sell n buy cost
int EnemyStats[4] = {15,10,20,5}; // [0] = dmg, [1] = hp, [2] = how many gold drops, [3] = armor
int EnemyOne[4] = {15,10,20,5}, EnemyTwo[4] = { 15,10,20,5 }, EnemyThree[4] = { 15,10,20,5 }, EnemyFour[4], EnemyFive[4], EnemySix[4], EnemySeven[4], EnemyEight[4], EnemyNine[4], EnemyTen[4], EnemyEleven[4], EnemyTwelve[4], EnemyThirty[4], EnemyFourty[4], EnemyFifty[4], EnemySixteen[4], EnemySeventeen[4], EnemyEighteen[4], EnemyNineteen[4], EnemyTwenty[4];
int EnemyAssociationToMap[20]; // example 7 is first enemy = 7
string CurrentState = "";
char WallSymbol = '#'; 
char FloorSymbol = ' ';
char ChestSymbol = '*';
char EnemySymbol = 'E';
int NumberOfEnemy = 0;
char PlayerSymbol = 'P';
char MagazineSymbol = '$'; // TODO
char BossTeleporterSymbol = '@'; // TODO
//-----------------------------------------------------------------------------------------------
int main()
{
//	setlocale(LC_ALL, "Russian");
	system("title Roguelike v0.2.9 by rizze//hakerhd93 // Beta");
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

	while (1) //infinite loop. (this loop will not break that's why we need an exit function).
	{
		for (int i = 0; i < ItemCount; i++) // Draw the menu.
		{
			gotoxy(50, 14 + i);
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
	item[1] = "Tutorial.";
	item[2] = "Settings.";
	item[3] = "Achivments.";
	item[4] = "Exit.";

	return item;
}
//-----------------------------------------------------------------------------------------------
void CheckItem() {
	int attemptsToCatch = 0;
	for (int i = 0; i < 6; i++)
	{
		if (ItemSlotID[i] == 0)
		{
			gotoxy(1, 7 + attemptsToCatch);
			cout << "Empty.";
			gotoxy(1, 9 + attemptsToCatch);
			cout << "-----------------------------";
			attemptsToCatch += 3;
		}
		else if (ItemSlotID[0] == 1) // DefaultSword[3] = {15,1,5}
		{
			gotoxy(1, 7 + attemptsToCatch);
			cout << gray << "Default Sword." << def;
			gotoxy(1, 8 + attemptsToCatch);
			cout << red << "dmg: " << DefaultSword[0] << def;
			gotoxy(10, 8 + attemptsToCatch);
			cout << brcyan << "lv: " << DefaultSword[1] << def;
			gotoxy(17, 8 + attemptsToCatch);
			cout << green << "cost: " << DefaultSword[2] << def;
			gotoxy(1, 9 + attemptsToCatch);
			cout << "-----------------------------";
			attemptsToCatch += 3;
		}
		else if (ItemSlotID[0] == 2) // FireSword[3] = {25,3,75}
		{
			gotoxy(1, 7 + attemptsToCatch);
			cout << gray << "Default Sword." << def;
			gotoxy(1, 8 + attemptsToCatch);
			cout << red << "dmg: " << FireSword[0] << def;
			gotoxy(10, 8 + attemptsToCatch);
			cout << brcyan << "lv: " << FireSword[1] << def;
			gotoxy(17, 8 + attemptsToCatch);
			cout << green << "cost: " << FireSword[2] << def;
			gotoxy(1, 9 + attemptsToCatch);
			cout << "-----------------------------";
			attemptsToCatch += 3;
		}
		else if (ItemSlotID[0] == 3) // IchorSword[3] = {35,4,150}
		{
			gotoxy(1, 7 + attemptsToCatch);
			cout << gray << "Default Sword." << def;
			gotoxy(1, 8 + attemptsToCatch);
			cout << red << "dmg: " << IchorSword[0] << def;
			gotoxy(10, 8 + attemptsToCatch);
			cout << brcyan << "lv: " << IchorSword[1] << def;
			gotoxy(17, 8 + attemptsToCatch);
			cout << green << "cost: " << IchorSword[2] << def;
			gotoxy(1, 9 + attemptsToCatch);
			cout << "-----------------------------";
			attemptsToCatch += 3;
		}
		else if (ItemSlotID[0] == 4) // Katana[3] = {50,6,300}
		{
			gotoxy(1, 7 + attemptsToCatch);
			cout << gray << "Katana." << def;
			gotoxy(1, 8 + attemptsToCatch);
			cout << red << "dmg: " << Katana[0] << def;
			gotoxy(10, 8 + attemptsToCatch);
			cout << brcyan << "lv: " << Katana[1] << def;
			gotoxy(17, 8 + attemptsToCatch);
			cout << green << "cost: " << Katana[2] << def;
			gotoxy(1, 9 + attemptsToCatch);
			cout << "-----------------------------";
			attemptsToCatch += 3;
		}
	}
	attemptsToCatch = 0;
}
//-----------------------------------------------------------------------------------------------
void difficultyIncrease() // TODO
{

}
//
void GoToTheNextStage() // TODO
{

}
//-----------------------------------------------------------------------------------------------
void InitializationLeftMenu()
{
	system("cls");
	for (int j = 1; j < 34; j++)
	{
		gotoxy(0, 0 + j);
		cout << "|" << "\n";
		gotoxy(30, 0 + j);
		cout << "|" << "\n";
	}
	for (int i = 0; i < 31; i++)
	{
		gotoxy(0 + i, 0);
		cout << "-";
	}
	for (int i = 0; i < 31; i++)
	{
		gotoxy(0 + i, 34);
		cout << "-";
	}
	gotoxy(1, 1);
	cout << red << "hp: " << playerHP << def;
	gotoxy(15, 1);
	cout << magenta << "xp: " << playerXP << def;
	gotoxy(15, 2);
	cout << brcyan << "lv: " << playerLVL << def;
	gotoxy(1, 2);
	cout << green << "Coins: " << playerCoins << def;
	gotoxy(1, 3);
	cout << orange << "Difficulty: " << difficulty << def;
	gotoxy(15, 3);
	cout << blue << "Stage: " << Stage << def;
	gotoxy(1, 4);
	cout << "-----------------------------";
	gotoxy(1, 5);
	cout << "Items:";
	gotoxy(1, 6);
	cout << "-----------------------------";
	CheckItem();
	gotoxy(1, 25);
	cout << brwhite << "Curret state: " << CurrentState << def;
}
//-----------------------------------------------------------------------------------------------
int enemyCount(int xEnemy, int yEnemy)
{
	return map[yEnemy][xEnemy] - 6;
}
//-----------------------------------------------------------------------------------------------
bool IsNothingDisturbingThePlayer(int x, int y, char Where) // если вхере U - UP; D - DOWN; L - LEFT; R - RIGHT
{
	if (Where == 'U')
	{
		// up
		if (y < 1)
		{
			return false;
		}
		if (map[y - 1][x] == 0)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else if (Where == 'D')
	{
		// down
		if (y > 33)
		{
			return false;
		}
		if (map[y + 1][x] == 0)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else if (Where == 'L')
	{
		// left
		if (map[y][x - 1] == 0)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else if (Where == 'R')
	{
		// right
		if (map[y][x + 1] == 0)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else
	{
		exit(-1);
	}
}
//-----------------------------------------------------------------------------------------------
bool CanYouHitAEnemy(int x, int y)
{
	for (int i = 0; i < 20; i++)
	{
	if (map[y - 1][x] == 7 + i)	//up
	{
		return true;
	} else if (map[y + 1][x] == 7 + i) // down
	{
		return true;
	} else if (map[y][x - 1] == 7 + i) // left
	{
		return true;
	} else if (map[y][x + 1] == 7 + i) // right
	{
		return true;
	} else if (map[y - 1][x - 1] == 7 + i) // left up
	{
		return true;
	} else if (map[y - 1][x + 1] == 7 + i) // right up
	{
		return true;
	} else if (map[y + 1][x - 1] == 7 + i) // left down
	{
		return true;
	} else if (map[y + 1][x + 1] == 7 + i) // right down
	{
		return true;
	}
	}
	return false;
}
//-----------------------------------------------------------------------------------------------
void InitializationEnemyStats(int count) // [0] = dmg, [1] = hp, [2] = how many gold drops, [3] = armor
{
	switch (count)
	{
	case 1:
		for (int i = 0; i < 4; i++)
		{
			EnemyOne[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[0] = 6 + count;
		break;
	case 2:
		for (int i = 0; i < 4; i++)
		{
			EnemyTwo[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[1] = 6 + count;
		break;
	case 3:
		for (int i = 0; i < 4; i++)
		{
			EnemyThree[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[2] = 6 + count;
		break;
	case 4:
		for (int i = 0; i < 4; i++)
		{
			EnemyFour[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[3] = 6 + count;
		break;
	case 5:
		for (int i = 0; i < 4; i++)
		{
			EnemyFive[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[4] = 6 + count;
		break;
	case 6:
		for (int i = 0; i < 4; i++)
		{
			EnemySix[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[5] = 6 + count;
		break;
	case 7:
		for (int i = 0; i < 4; i++)
		{
			EnemySeven[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[6] = 6 + count;
		break;
	case 8:
		for (int i = 0; i < 4; i++)
		{
			EnemyEight[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[7] = 6 + count;
		break;
	case 9:
		for (int i = 0; i < 4; i++)
		{
			EnemyNine[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[8] = 6 + count;
		break;
	case 10:
		for (int i = 0; i < 4; i++)
		{
			EnemyTen[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[9] = 6 + count;
		break;
	case 11:
		for (int i = 0; i < 4; i++)
		{
			EnemyEleven[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[10] = 6 + count;
		break;
	case 12:
		for (int i = 0; i < 4; i++)
		{
			EnemyTwelve[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[11] = 6 + count;
		break;
	case 13:
		for (int i = 0; i < 4; i++)
		{
			EnemyThirty[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[12] = 6 + count;
		break;
	case 14:
		for (int i = 0; i < 4; i++)
		{
			EnemyFourty[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[13] = 6 + count;
		break;
	case 15:
		for (int i = 0; i < 4; i++)
		{
			EnemyFifty[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[14] = 6 + count;
		break;
	case 16:
		for (int i = 0; i < 4; i++)
		{
			EnemySixteen[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[15] = 6 + count;
		break;
	case 17:
		for (int i = 0; i < 4; i++)
		{
			EnemySeventeen[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[16] = 6 + count;
		break;
	case 18:
		for (int i = 0; i < 4; i++)
		{
			EnemyEighteen[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[17] = 6 + count;
		break;
	case 19:
		for (int i = 0; i < 4; i++)
		{
			EnemyNineteen[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[18] = 6 + count;
		break;
	case 20:
		for (int i = 0; i < 4; i++)
		{
			EnemyTwenty[i] = EnemyStats[i];
		}
		EnemyAssociationToMap[19] = 6 + count;
		break;
	default:
		break;
	}
}
//-----------------------------------------------------------------------------------------------
int WhereIsChestX(int x, int y)
{
	if (map[y + 1][x] == 2)
	{
		return x;
	}
	else if (map[y - 1][x] == 2)
	{
		return x;
	}
	else if (map[y][x + 1] == 2)
	{
		return x + 1;
	} 
	else if (map[y][x - 1] == 2)
	{
		return x - 1;
	}
	else if(map[y + 1][x + 1] == 2)
	{
		return x + 1;
	}
	else if(map[y + 1][x - 1] == 2)
	{
		return x - 1;
	}
	else if (map[y - 1][x + 1] == 2)
	{
		return x + 1;
	}
	else if (map[y - 1][x - 1] == 2)
	{
		return x - 1;
	}
	else
	{
		return -1;
	}
}
//
int WhereIsChestY(int x, int y)
{
	if (map[y + 1][x] == 2)
	{
		return y + 1;
	}
	else if (map[y - 1][x] == 2)
	{
		return y - 1;
	}
	else if (map[y][x + 1] == 2)
	{
		return y;
	}
	else if (map[y][x - 1] == 2)
	{
		return y;
	}
	else if (map[y + 1][x + 1] == 2)
	{
		return y + 1;
	}
	else if (map[y + 1][x - 1] == 2)
	{
		return y + 1;
	}
	else if (map[y - 1][x + 1] == 2)
	{
		return y - 1;
	}
	else if (map[y - 1][x - 1] == 2)
	{
		return y - 1;
	}
	else
	{
		return -1;
	}
}
//
void OpenChest(int x, int y)
{
	if (map[y][x] == 2)
	{
		playerCoins += 15;
		CurrentState = "You got 15 coins";
		map[y][x] = 0;
		gotoxy(31 + x, 0 + y);
		cout << " ";
		InitializationLeftMenu();
		ShowMap();
	}
}
//-----------------------------------------------------------------------------------------------
int yEnemy(int x, int y)
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
//
int xEnemy(int x, int y)
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
	return -1;
}
//
void actionOnTheEnemy(int x, int y, int count, bool attack) //attack = false - check enemy, attack = true - attack enemy
{
	if (attack == false)
	{
		switch (count)
		{
		case 1:
			if (EnemyOne[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyOne[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 2: 
			if (EnemyTwo[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyTwo[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 3:
			if (EnemyThree[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyThree[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 4:
			if (EnemyFour[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyFour[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 5:
			if (EnemyFive[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyFive[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 6:
			if (EnemySix[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemySix[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 7:
			if (EnemySeven[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemySeven[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 8:
			if (EnemyEight[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyEight[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 9:
			if (EnemyNine[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyNine[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 10:
			if (EnemyTen[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyTen[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 11:
			if (EnemyEleven[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyEleven[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 12:
			if (EnemyTwelve[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyTwelve[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 13:
			if (EnemyThirty[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyThirty[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 14:
			if (EnemyFourty[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyFourty[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 15:
			if (EnemyFifty[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyFifty[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 16:
			if (EnemySixteen[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemySixteen[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 17:
			if (EnemySeventeen[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemySeventeen[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 18:
			if (EnemyEighteen[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyEighteen[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 19:
			if (EnemyNineteen[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyNineteen[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		case 20:
			if (EnemyTwenty[1] <= 0)
			{
				map[y][x] = 0;
			}
			else if (EnemyTwenty[1] > 0)
			{
				map[y][x] = 6 + count;
			}
			break;
		default:
			break;
		}
	}
	else if (attack == true)
	{
		switch (count)
		{
		case 1:
			if (ItemSlotID[0] == 1)
			{
				EnemyOne[1] -= DefaultSword[0];
			}
			else if (ItemSlotID[0] == 2)
			{
				EnemyOne[1] -= FireSword[0];
			}
			else if (ItemSlotID[0] == 3)
			{
				EnemyOne[1] -= IchorSword[0];
			}
			else if (ItemSlotID[0] == 4)
			{
				EnemyOne[1] -= Katana[0];
			}
			if (EnemyOne[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 2:
			if (EnemyTwo[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 3:
			if (EnemyThree[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 4:
			if (EnemyFour[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 5:
			if (EnemyFive[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 6:
			if (EnemySix[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 7:
			if (EnemySeven[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 8:
			if (EnemyEight[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 9:
			if (EnemyNine[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 10:
			if (EnemyTen[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 11:
			if (EnemyEleven[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 12:
			if (EnemyTwelve[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 13:
			if (EnemyThirty[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 14:
			if (EnemyFourty[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 15:
			if (EnemyFifty[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 16:
			if (EnemySixteen[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 17:
			if (EnemySeventeen[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 18:
			if (EnemyEighteen[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 19:
			if (EnemyNineteen[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		case 20:
			if (EnemyTwenty[1] <= 0)
			{
				map[y][x] = 0;
			}
			break;
		default:
			break; 
		}
	}
}
//-----------------------------------------------------------------------------------------------
void GenerateMap() // 0 = normal, 1 = wall, 2 = chest, 3 = Enemy, 4 = Player, 5 = Magazine, 6 = bossTP
{
	xPlayer = rand() % 92;
	yPlayer = rand() % 34;
	int WallCount = 0, ChestCount = 120 + (20 * difficulty), EnemyCount = 270 - (20 * difficulty);//, MagazineCount = 0, BossTPCount = 0;
	for (int j = 0; j < 35; j++)
	{
		for (int i = 0; i < 93; i++)
		{
			map[j][i] = 0;
		}
	}
	for (int j = 0; j < 35; j++)
	{
		for (int i = 0; i < 93; i++)
		{
			int rNum;
			if (j == yPlayer && i == xPlayer)
			{
				map[j][i] = 4;
				continue;
			}
			if (ChestCount <= 0)
			{
				ChestCount = 120 + (20 * difficulty);
				map[j][i] = 2;
				continue;
			}
			ChestCount--;
			if (EnemyCount <= 0)
			{
				if (EnemyCount <= 2 * difficulty)
				{
					NumberOfEnemy++;
					map[j][i] = 6 + NumberOfEnemy;
					InitializationEnemyStats(NumberOfEnemy);
					EnemyCount = 270 - (20 * difficulty);
					continue;
				}
				else
				{
					EnemyCount--;
				}
			}
			do {
				rNum = rand() % 6;
			} while (rNum == 4);
			/*if (rNum == 5)
			{
				if (MagazineCount == 0)
				{
					cout << orange << MagazineSymbol << def;
					MagazineCount++;
				}
				else if (MagazineCount == 1) { }
			}*/
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
					ChestCount = 120 + (20 * difficulty);
				}
				else
				{
					ChestCount--;
				}
			}
			else if (rNum == 3)
			{
				if (EnemyCount <= 2 * difficulty)
				{
					NumberOfEnemy++;
					map[j][i] = 6 + NumberOfEnemy;
					InitializationEnemyStats(NumberOfEnemy);
					EnemyCount = 270 - (20 * difficulty);
				}
				else
				{
					map[j][i] = 0;
					EnemyCount--;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------
void ShowMap()
{
	int Symbol = 0;
	for (int j = 0; j < 35; j++)
	{
		gotoxy(31, 0 + j);
		for (int i = 0; i < 93; i++) // 0 = normal, 1 = wall, 2 = chest, 3 = Enemy, 4 = Player.
		{
			Symbol++;
			gotoxy(31 + Symbol, 0);
			switch (map[j][i])
			{
			case 0:
				cout << FloorSymbol;
				break;
			case 1:
				cout << WallSymbol;
				break;
			case 2:
				cout << yellow << ChestSymbol << def;
				break;
			case 4:
				cout << green << PlayerSymbol << def;
				break;
			case 5:
				cout << FloorSymbol;
				break;
			case 6:
				cout << FloorSymbol;
				break;
			case 7:
				actionOnTheEnemy(i, j, 1, false);
				cout << red << EnemySymbol << def;
				break;
			case 8:
				actionOnTheEnemy(i, j, 2, false);
				cout << red << EnemySymbol << def;
				break;
			case 9:
				actionOnTheEnemy(i, j, 3, false);
				cout << red << EnemySymbol << def;
				break;
			case 10:
				actionOnTheEnemy(i, j, 4, false);
				cout << red << EnemySymbol << def;
				break;
			case 11:
				actionOnTheEnemy(i, j, 5, false);
				cout << red << EnemySymbol << def;
				break;
			case 12:
				actionOnTheEnemy(i, j, 6, false);
				cout << red << EnemySymbol << def;
				break;
			case 13:
				actionOnTheEnemy(i, j, 7, false);
				cout << red << EnemySymbol << def;
				break;
			case 14:
				actionOnTheEnemy(i, j, 8, false);
				cout << red << EnemySymbol << def;
				break;
			case 15:
				actionOnTheEnemy(i, j, 9, false);
				cout << red << EnemySymbol << def;
				break;
			case 16:
				actionOnTheEnemy(i, j, 10, false);
				cout << red << EnemySymbol << def;
				break;
			case 17:
				actionOnTheEnemy(i, j, 11, false);
				cout << red << EnemySymbol << def;
				break;
			case 18:
				actionOnTheEnemy(i, j, 12, false);
				cout << red << EnemySymbol << def;
				break;
			case 19:
				actionOnTheEnemy(i, j, 13, false);
				cout << red << EnemySymbol << def;
				break;
			case 20:
				actionOnTheEnemy(i, j, 14, false);
				cout << red << EnemySymbol << def;
				break;
			case 21:
				actionOnTheEnemy(i, j, 15, false);
				cout << red << EnemySymbol << def;
				break;
			case 22:
				actionOnTheEnemy(i, j, 16, false);
				cout << red << EnemySymbol << def;
				break;
			case 23:
				actionOnTheEnemy(i, j, 17, false);
				cout << red << EnemySymbol << def;
				break;
			case 24:
				actionOnTheEnemy(i, j, 18, false);
				cout << red << EnemySymbol << def;
				break;
			case 25:
				actionOnTheEnemy(i, j, 19, false);
				cout << red << EnemySymbol << def;
				break;
			case 26:
				actionOnTheEnemy(i, j, 20, false);
				cout << red << EnemySymbol << def;
				break;
			default:
				break;
			}
		}

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
	gotoxy(1, 26);
	cout << brwhite << "x: " << xPlayer << def;
	gotoxy(10, 26);
	cout << brwhite << "y: " << yPlayer << def;
	if (yPlayer < 10)
	{
		gotoxy(1, 26);
		cout << brwhite << "x: " << xPlayer << def;
		gotoxy(14, 26);
		cout << " ";
	}
	ShowMap();
	while (1)
	{

		gotoxy(1, 26);
		cout << brwhite << "x: " << xPlayer << def;
		gotoxy(10, 26);
		cout << brwhite << "y: " << yPlayer << def;
		if (yPlayer < 10)
		{
			gotoxy(14, 26);
			cout << " ";
		}
		key = _getch();
		switch (key) //check the entered key.
		{
		case '\r': // if the entered key is 'Enter'.
			try
			{
				if (CanYouHitAEnemy(xPlayer, yPlayer) == false)
				{
					if (WhereIsChestX(xPlayer, yPlayer) != -1 && WhereIsChestY(xPlayer, yPlayer) != -1)
					{
						OpenChest(WhereIsChestX(xPlayer, yPlayer), WhereIsChestY(xPlayer, yPlayer));
					}
				}
				else if (CanYouHitAEnemy(xPlayer, yPlayer) == true)
				{
					actionOnTheEnemy(xEnemy(xPlayer, yPlayer), yEnemy(xPlayer, yPlayer), enemyCount(xEnemy(xPlayer, yPlayer), yEnemy(xPlayer, yPlayer)), true);
				}
			}
			catch (...)
			{
			}  // we have to use try and catch coz if we did'nt fill that index with a function.
			   //                     a runtime error will appear.
			break;

		case 'P': // down arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(xPlayer, yPlayer, 'D');
			if (IsNothingDisturbing == true)
			{
				if (yPlayer < 1)
				{
					continue;
				}
				else {

					map[yPlayer + 1][xPlayer] = 4;
					gotoxy(31 + xPlayer, 0 + (yPlayer + 1));
					cout << green << PlayerSymbol << def;
					gotoxy(31 + xPlayer, 0 + yPlayer);
					map[yPlayer][xPlayer] = 0;
					cout << FloorSymbol;
					yPlayer++;
					float delay = 0.35;
					delay *= CLOCKS_PER_SEC;
					clock_t now = clock();
					while (clock() - now < delay);
				}

			}
			else if (IsNothingDisturbing == false) {}
			break;

		case 'H': // up arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(xPlayer, yPlayer, 'U');
			if (IsNothingDisturbing == true)
			{
				if (yPlayer <= 1)
				{
					continue;
				}
				else {
					map[yPlayer - 1][xPlayer] = 4;
					gotoxy(31 + xPlayer, 0 + (yPlayer - 1));
					cout << green << PlayerSymbol << def;
					gotoxy(31 + xPlayer, 0 + yPlayer);
					map[yPlayer][xPlayer] = 0;
					cout << FloorSymbol;
					yPlayer--;
				}

			}
			else if (IsNothingDisturbing == false) {}
			break;
		case 'K': // left arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(xPlayer, yPlayer, 'L');
			if (IsNothingDisturbing == true)
			{
				map[yPlayer][xPlayer - 1] = 4;
				gotoxy(31 + (xPlayer - 1), 0 + yPlayer);
				cout << green << PlayerSymbol << def;
				gotoxy(31 + xPlayer, 0 + yPlayer);
				map[yPlayer][xPlayer] = 0;
				cout << FloorSymbol;
				xPlayer--;
			}
			else if (IsNothingDisturbing == false) {}
			break;
		case 'M': // right arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(xPlayer, yPlayer, 'R');
			if (IsNothingDisturbing == true)
			{
				map[yPlayer][xPlayer + 1] = 4;
				gotoxy(31 + (xPlayer + 1), 0 + yPlayer);
				cout << green << PlayerSymbol << def;
				gotoxy(31 + xPlayer, 0 + yPlayer);
				map[yPlayer][xPlayer] = 0;
				cout << FloorSymbol;
				xPlayer++;
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
				try { }
				catch (...) {}
			}
		}
	}
	cin.ignore();
//	system("cls");
}
//-----------------------------------------------------------------------------------------------
void gotoxy(int xpos, int ypos)  // just take this function as it is.
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
//-----------------------------------------------------------------------------------------------
void MenuStart()
{
	system("cls");
	int delay = 1;
	delay *= CLOCKS_PER_SEC;
	clock_t now = clock();
	while (clock() - now < delay);
	Gameplay(map);
}
//-----------------------------------------------------------------------------------------------
void MenuStartTutorial()
{
	system("cls"); //clear the screen.
	gotoxy(50, 14);
	cout << "There is no game (Will be)" << endl;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void MenuSettings()
{
	system("cls");
	gotoxy(50, 14);
	cout << "No settings there, maybe later" << endl;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void MenuAchievements()
{
	system("cls");
	gotoxy(50, 14);
	cout << "There is nothing" << endl;
	cin.ignore();
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void ExitOption()
{
	system("cls");
	gotoxy(50, 14);
	cout << "Exitting..." << endl;
	exit(0);
}
//-----------------------------------------------------------------------------------------------
void ChangeCursorStatus(bool Visible)
{
	CONSOLE_CURSOR_INFO* c = new CONSOLE_CURSOR_INFO;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (Visible)
	{
		c->bVisible = TRUE;
		c->dwSize = 0;//(0) is invild so the default value is set
	}
	else
	{
		c->bVisible = FALSE;
		c->dwSize = 1;//it must be assigned to a valid value
	}

	SetConsoleCursorInfo(h, c);
}
//-----------------------------------------------------------------------------------------------
