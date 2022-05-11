#pragma once
#include <windows.h>
namespace systems {
	void gotoxy(int xpos, int ypos)  // just take this function as it is.
	{
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
		scrn.X = xpos; scrn.Y = ypos;
		SetConsoleCursorPosition(hOuput, scrn);
	}
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
	void ShowMap(int map[35][93])
	{
		int Symbol = 0;
		for (int j = 0; j < 35; j++)
		{
			systems::gotoxy(31, 0 + j);
			for (int i = 0; i < 93; i++) // 0 = normal, 1 = wall, 2 = chest, 3 = Enemy, 4 = Player.
			{
				Symbol++;
				systems::gotoxy(31 + Symbol, 0);
				if (map[j][i] == 0)
				{
					std::cout << FloorSymbol;
				}
				else if (map[j][i] == 1)
				{
					std::cout << WallSymbol;
				}
				else if (map[j][i] == 2)
				{
					std::cout << Color::yellow << ChestSymbol << Color::def;
				}
				else if (map[j][i] == 4)
				{
					std::cout << Color::green << PlayerSymbol << Color::def;
				}
				else if (map[j][i] == 5)
				{
					std::cout << Color::orange << ShopSymbol << Color::def;
				}
				else if (map[j][i] == 6)
				{
					std::cout << FloorSymbol;
				}
				else if (map[j][i] >= 7)
				{
					for (int g = 0; g < 2; g++)
					{
						actionOnTheEnemy(i, j, g, false);
						std::cout << Color::red << EnemySymbol << Color::def;
						break;
					}
				}
			}

		}
	}
}
