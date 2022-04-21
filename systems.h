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
}
