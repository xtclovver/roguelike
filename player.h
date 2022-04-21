#pragma once
#include "shopNitems.h"
namespace player {
	struct PlayerStats {
		int x;
		int y;
		int coins;
		int hp;
		int exp;
		int forNextlvl;
		int lvl;
		int armor;
		int MaxHP;
	};
	PlayerStats Player;
	bool IsNothingDisturbingThePlayer(int x, int y, char Where, int map[35][93]) // если вхере U - UP; D - DOWN; L - LEFT; R - RIGHT
	{
		if (Where == 'U')
		{
			// up
			if (y <= 1)
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
			if (x <= 0)
			{
				return false;
			}
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
			if (x > 91 + 1)
			{
				return false;
			}
#pragma warning(suppress: 6385)
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
}