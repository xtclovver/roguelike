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

void InitializationLeftMenu();

void ShowMap();

void MenuStartTutorial(); // TODO

bool IsNothingDisturbingThePlayer(int x, int y, char Where);

void ExitOption(); // this is also an item function but i named it like this coz every menu must
				   //    have an exit item.
//-----------------------------------------------------------------------------------------------
const string title = "Roguelike v0.1.0 by rizze//hakerhd93";
//
int map[35][93]; // map \\ level
int xPlayer, yPlayer, playerCoins = 15, playerHP = 100, playerXP = 0, playerLVL = 1;
int difficulty = 1;
int ItemSlotID[6] = {1,0,0,0,0,0}, DefaultSword[3] = {15,1,0}; // DefaultSword {15 is dmg, 1 is lvl to need to equip, 0 sell cost
int EnemyStats[4] = {15,10,10,5}; // [0] = dmg, [1] = hp, [2] = how many gold drops, [3] = armor?
char WallSymbol = '#';
char FloorSymbol = ' ';
char ChestSymbol = '*';
char EnemySymbol = 'E';
char PlayerSymbol = 'P';
char MagazineSymbol = '$';
char BossTeleporterSymbol = '@';
//-----------------------------------------------------------------------------------------------
int main()
{
//	setlocale(LC_ALL, "Russian");
	system("title Roguelike v0.1.0 by rizze//hakerhd93");
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
void CheckItem()
{
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
		else if (ItemSlotID[i] == 1)
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
	}
	attemptsToCatch = 0;
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
	cout << "-----------------------------";
	gotoxy(1, 5);
	cout << "Items:";
	gotoxy(1, 6);
	cout << "-----------------------------";
	CheckItem();
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
void GenerateMap() // 0 = normal, 1 = wall, 2 = chest, 3 = Enemy, 4 = Player, 5 = Magazine, 6 = bossTP
{
	xPlayer = rand() % 93;
	yPlayer = rand() % 35;
	int WallCount = 0,ChestCount = 140, EnemyCount = 250, MagazineCount = 0, BossTPCount = 0;
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
			int rNum = 0;
			if (j == yPlayer && i == xPlayer)
			{
				map[j][i] = 4;
				continue;
			}
			if (ChestCount <= 0)
			{
				ChestCount = 140;
				map[j][i] = 2;
				continue;
			}
			ChestCount--;
			if (EnemyCount <= 0)
			{
				map[j][i] = 3;
				EnemyCount = 250;
			}
			EnemyCount--;
			do {
				rNum = rand() % 6;
			} while (rNum == 4);
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
					ChestCount = 140;
				}
				else
				{
					ChestCount--;
				}
			}
			else if (rNum == 3)
			{
				if (EnemyCount <= 0)
				{
					map[j][i] = 3;
					EnemyCount = 250;
				}
				else
				{
					map[j][i] = 0;
					EnemyCount--;
				}
			}
			else if (rNum == 5)
			{
				if (MagazineCount == 0)
				{
					cout << orange << MagazineSymbol << def;
					MagazineCount++;
				}
				else if (MagazineCount == 1) {
					map[j][i] = 0;
					continue;
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
			if (map[j][i] == 0)
			{
				cout << FloorSymbol;
			}
			else if (map[j][i] == 1)
			{
				cout << WallSymbol;
			}
			else if (map[j][i] == 2)
			{
				cout << yellow << ChestSymbol << def;
			}
			else if (map[j][i] == 3)
			{
				cout << red << EnemySymbol << def;
			}
			else if (map[j][i] == 4)
			{
				cout << green << PlayerSymbol << def;
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
	InitializationLeftMenu();
	while (1)
	{
		ShowMap();
		key = _getch();
		switch (key) //check the entered key.
		{
		case '\r': // if the entered key is 'Enter'.
			try
			{
				//
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
				if (yPlayer == 0)
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
				}

			}
			else if (IsNothingDisturbing == false) {}
			break;

		case 'H': // up arrow key
			IsNothingDisturbing = IsNothingDisturbingThePlayer(xPlayer, yPlayer, 'U');
			if (IsNothingDisturbing == true)
			{
				if (yPlayer == 1)
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
	system("cls");

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
	system("cls"); //clear the screen.
	gotoxy(50, 14);
	cout << "There is no game (Will be)" << endl;
	cin.ignore(); 
	system("cls");
}
//-----------------------------------------------------------------------------------------------
void MenuStartTutorial()
{
	InitializationLeftMenu();
	GenerateMap();
	Gameplay(map);
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
