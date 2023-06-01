#pragma once
namespace systems {
	int getRandomNumber(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		// Равномерно распределяем рандомное число в нашем диапазоне
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}
	unsigned GetNumberOfDigits(unsigned i)
	{
		return i > 0 ? (int)log10((double)i) + 1 : 1;
	}
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
	bool IsEven(int x)
	{
		switch (x % 2)
		{
		case 0:
			return true;
			break;
		case 1:
			return false;
			break;
		default:
			break;
		}
	}
	int WhereX(int x, int y, int fiend, bool IsEnemy, bool TpPool = false)
	{
		if (IsEnemy == false)
		{
			if (variableKeeper::map[y + 1][x] == fiend)
			{
				return x;
			}
			else if (variableKeeper::map[y - 1][x] == fiend)
			{
				return x;
			}
			else if (variableKeeper::map[y][x + 1] == fiend)
			{
				return x + 1;
			}
			else if (variableKeeper::map[y][x - 1] == fiend)
			{
				return x - 1;
			}
			else if (variableKeeper::map[y + 1][x + 1] == fiend)
			{
				return x + 1;
			}
			else if (variableKeeper::map[y + 1][x - 1] == fiend)
			{
				return x - 1;
			}
			else if (variableKeeper::map[y - 1][x + 1] == fiend)
			{
				return x + 1;
			}
			else if (variableKeeper::map[y - 1][x - 1] == fiend)
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
			if (TpPool == false)
			{
				for (int i = 0; i < variableKeeper::NumberOfEnemy; i++)
				{
					if (variableKeeper::map[y][x - 1] == 7 + i) // left
					{
						return x - 1;
					}
					else if (variableKeeper::map[y][x + 1] == 7 + i) // right
					{
						return x + 1;
					}
					else if (variableKeeper::map[y + 1][x] == 7 + i) // up
					{
						return x;
					}
					else if (variableKeeper::map[y - 1][x] == 7 + i) // down
					{
						return x;
					}
					else if (variableKeeper::map[y - 1][x - 1] == 7 + i) // left up
					{
						return x - 1;
					}
					else if (variableKeeper::map[y - 1][x + 1] == 7 + i) // right up
					{
						return x + 1;
					}
					else if (variableKeeper::map[y + 1][x - 1] == 7 + i) // left down
					{
						return x - 1;
					}
					else if (variableKeeper::map[y + 1][x + 1] == 7 + i) // right down
					{
						return x + 1;
					}
				}
			}
			else if (TpPool == true)
			{
				for (int i = 0; i < variableKeeper::NumberOfEnemy; i++)
				{
					if (variableKeeper::map[y][x - 1] == 607 + i) // left
					{
						return x - 1;
					}
					else if (variableKeeper::map[y][x + 1] == 607 + i) // right
					{
						return x + 1;
					}
					else if (variableKeeper::map[y + 1][x] == 607 + i) // up
					{
						return x;
					}
					else if (variableKeeper::map[y - 1][x] == 607 + i) // down
					{
						return x;
					}
					else if (variableKeeper::map[y - 1][x - 1] == 607 + i) // left up
					{
						return x - 1;
					}
					else if (variableKeeper::map[y - 1][x + 1] == 607 + i) // right up
					{
						return x + 1;
					}
					else if (variableKeeper::map[y + 1][x - 1] == 607 + i) // left down
					{
						return x - 1;
					}
					else if (variableKeeper::map[y + 1][x + 1] == 607 + i) // right down
					{
						return x + 1;
					}
				}
			}
		}
		return -1;
	}
	//
	int WhereY(int x, int y, int fiend, bool IsEnemy, bool TpPool = false) //fiend = whatneedtofind
	{
		if (IsEnemy == false)
		{
			if (variableKeeper::map[y + 1][x] == fiend)
			{
				return y + 1;
			}
			else if (variableKeeper::map[y - 1][x] == fiend)
			{
				return y - 1;
			}
			else if (variableKeeper::map[y][x + 1] == fiend)
			{
				return y;
			}
			else if (variableKeeper::map[y][x - 1] == fiend)
			{
				return y;
			}
			else if (variableKeeper::map[y + 1][x + 1] == fiend)
			{
				return y + 1;
			}
			else if (variableKeeper::map[y + 1][x - 1] == fiend)
			{
				return y + 1;
			}
			else if (variableKeeper::map[y - 1][x + 1] == fiend)
			{
				return y - 1;
			}
			else if (variableKeeper::map[y - 1][x - 1] == fiend)
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
			if (TpPool == true)
			{
				for (int i = 0; i < variableKeeper::NumberOfEnemy; i++)
				{
					if (variableKeeper::map[y - 1][x] == 607 + i)	//up
					{
						return y - 1;
					}
					else if (variableKeeper::map[y + 1][x] == 607 + i) // down
					{
						return y + 1;
					}
					else if (variableKeeper::map[y][x - 1] == 607 + i) //left
					{
						return y;
					}
					else if (variableKeeper::map[y][x + 1] == 607 + i) // right
					{
						return y;
					}
					else if (variableKeeper::map[y - 1][x - 1] == 607 + i) // left up
					{
						return y - 1;
					}
					else if (variableKeeper::map[y - 1][x + 1] == 607 + i) // right up
					{
						return y - 1;
					}
					else if (variableKeeper::map[y + 1][x - 1] == 607 + i) // left down
					{
						return y + 1;
					}
					else if (variableKeeper::map[y + 1][x + 1] == 607 + i) // right down
					{
						return y + 1;
					}
				}
			}
			else if (TpPool == false)
			{
				for (int i = 0; i < variableKeeper::NumberOfEnemy; i++)
				{
					if (variableKeeper::map[y - 1][x] == 7 + i)	//up
					{
						return y - 1;
					}
					else if (variableKeeper::map[y + 1][x] == 7 + i) // down
					{
						return y + 1;
					}
					else if (variableKeeper::map[y][x - 1] == 7 + i) //left
					{
						return y;
					}
					else if (variableKeeper::map[y][x + 1] == 7 + i) // right
					{
						return y;
					}
					else if (variableKeeper::map[y - 1][x - 1] == 7 + i) // left up
					{
						return y - 1;
					}
					else if (variableKeeper::map[y - 1][x + 1] == 7 + i) // right up
					{
						return y - 1;
					}
					else if (variableKeeper::map[y + 1][x - 1] == 7 + i) // left down
					{
						return y + 1;
					}
					else if (variableKeeper::map[y + 1][x + 1] == 7 + i) // right down
					{
						return y + 1;
					}
				}
			}
			return -1;
		}
		return -1;
	}
	void difficultyIncrease() // TODO
	{
		variableKeeper::difficulty += 0.25f;
#pragma warning(suppress: 4244)
		variableKeeper::EnemyDefaultStats[0] += variableKeeper::EnemyDefaultStats[0] * (variableKeeper::difficulty * 0.4);
#pragma warning(suppress: 4244)
		variableKeeper::EnemyDefaultStats[1] += variableKeeper::EnemyDefaultStats[1] * (variableKeeper::difficulty * 0.4);
#pragma warning(suppress: 4244)
		variableKeeper::EnemyDefaultStats[2] += variableKeeper::EnemyDefaultStats[2] * (variableKeeper::difficulty * 0.4);
#pragma warning(suppress: 4244)
		variableKeeper::EnemyDefaultStats[3] += variableKeeper::EnemyDefaultStats[3] * (variableKeeper::difficulty * 0.4);
	}
}
