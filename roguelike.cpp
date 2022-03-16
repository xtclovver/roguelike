#include <iostream>
#include <string>
#include <windows.h> // we need this header for the 'gotoxy' function.
#include <conio.h> // we need this header for the '_getch' function.
#include <cstdlib> // "system" is ambiguous.
#include <stdio.h>
#include <fstream>
#include <vector>
#include <fstream>
//-----------------------------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------------------------
string* MenuItems(); // a function that returns the name of a menu item.

void gotoxy(int, int); // by this function you can goto any position on the cmd line screen.

void ChangeCursorStatus(bool);

void MenuStart(); // every menu item needs a seperate function, so this is for the first item.

void MenuSettings(); //    and the second item etc...

void MenuAchievements(); 

void Gameplay(int map[35][93]);

void GenerateMap();

void MenuStartTutorial(); // TODO

void ExitOption(); // this is also an item function but i named it like this coz every menu must
				   //    have an exit item.
/* Красим текст в консоли // POTOM
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hOUTPUT,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<"GREEN TEXT\n";
    SetConsoleTextAttribute(hOUTPUT,FOREGROUND_RED   | FOREGROUND_INTENSITY);
    cout<<"RED TEXT\n";
    SetConsoleTextAttribute(hOUTPUT,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );*/
//-----------------------------------------------------------------------------------------------
int map[35][93]; // map \\ level
int leftMenu[35][30]; // lest menu with stats, hp and etc.
int xPlayer, yPlayer, playerCoins = 15, playerHP = 100, playerXP = 0, playerLVL = 1;
int ItemSlotID[6] = {1,0,0,0,0,0}, DefaultSword[3] = {15,1,0}; // DefaultSword {15 is dmg, 1 is lvl to need to equip, 0 sell cost
//-----------------------------------------------------------------------------------------------
int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
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
			cout << "Default Sword.";
			gotoxy(1, 8 + attemptsToCatch);
			cout << "dmg: " << DefaultSword[0];
			gotoxy(10, 8 + attemptsToCatch);
			cout << "lv: " << DefaultSword[1];
			gotoxy(17, 8 + attemptsToCatch);
			cout << "cost: " << DefaultSword[2];
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
	cout << "hp: " << playerHP;
	gotoxy(15, 1);
	cout << "xp: " << playerXP;
	gotoxy(15, 2);
	cout << "lv: " << playerLVL;
	gotoxy(1, 2);
	cout << "Coins: " << playerCoins;
	gotoxy(1, 3);
	cout << "-----------------------------";
	gotoxy(1, 5);
	cout << "Items:";
	gotoxy(1, 6);
	cout << "-----------------------------";
	CheckItem();
	cin.ignore();
}
//
void GenerateMap() // 0 = normal, 1 = wall, 2 = chest, 3 = Enemy, 4 = Player.
{
	xPlayer = rand() % 93;
	yPlayer = rand() % 35;
	for (int j = 0; j < 35; j++)
	{
		for (int i = 0; i < 93; i++)
		{
			if (j == yPlayer && i == xPlayer)
			{
				map[j][i] = 4;
				continue;
			}
			map[j][i] = rand() % 3;
		}
	}
}
//-----------------------------------------------------------------------------------------------
void Gameplay(int map[35][93])
{
	char key;
	system("cls"); //clear the screen.
	InitializationLeftMenu();
	while (1)
	{
		for (int j = 0; j < 35; j++)
		{
			gotoxy(31, 0 + j);
			for (int i = 0; i < 93; i++)
			{
				gotoxy(31 + i, 0);
				if (map[j][i] == 0)
				{
					cout << " ";
				}
				else if (map[j][i] == 1)
				{
					cout << " ";
				}
				else if (map[j][i] == 2)
				{
					cout << " ";
				}
				else if (map[j][i] == 3)
				{
					cout << " ";
				}
				else if (map[j][i] == 4)
				{
					cout << " ";
				}
			}
		}
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

		case 'P': // if the entered key is the 'up arrow' notice that its equal to 'P' (capital)
			 //then we will increment the cursor by one.
			 // if the cursor value is more than the items count.
				       //    then it will return back to the first item.
			break;

		case 'H': // same but with 'down arrow' and decrement the cursor.

			break;

		case 27: // 27 is the asscii to the escape key (Esc)
			try { } // useually when the 'Esc' key is pressed the last
												//     item will be called (executed). but you can
												//     change it to whatever you want.
			catch (...) {}
			break;
		default:// any another key.
			//check if the pressed key is in the range
			//    of (1,2,3,...,#of items) [all char(s)]
			{
				try { } //call the function of the pressed number.
					 //  you can make the cursor move to that item instead of calling (executing)
					 //  it by replacing all the code between 'if (bla){' and '}' with this
					 //  statement MenuChooice=int(key)-'0'
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
//	GenerateMap();
//	Gameplay(map);
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
