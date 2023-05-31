#pragma once
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
	void CheckItem() {
		int attemptsToCatch = 0;
		for (int i = 0; i < 6; i++)
		{
			switch (variableKeeper::ItemSlotID[i])
			{
			case -1:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << "Empty.";
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 0:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::grey << "Dao." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[0].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[0].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[0].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 1:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::white << "Quelling Blade." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[1].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[1].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[1].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 2:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::white << "Ogre Axe." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[2].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[2].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[2].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 3:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::green << "Katana." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[3].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[3].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[3].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 4:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::green << "Desolator." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[4].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[4].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[4].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 5:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::blue << "Skull Basher." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[5].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[5].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[5].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 6:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::pink << "Heavens Halberd." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[6].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[6].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[6].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 7:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::magenta << "Sacred Relic." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[7].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[7].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[7].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 8:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::cyan << "Ethereal blade." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[8].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[8].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[8].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 9:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::brcyan << "Divine Rapier." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << variableKeeper::ShopItems[9].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[9].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[9].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
				// Items
			case 12:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::pink << "Morbid Mask." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::green << "Heals: " << variableKeeper::ShopItems[12].special << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[12].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[12].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 13:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::magenta << "Chainmail." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::blue << "armor: " << variableKeeper::ShopItems[13].special << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[13].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[13].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 14:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::cyan << "Ring of Regen." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::green << "Heals: " << variableKeeper::ShopItems[14].special << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[14].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[14].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 15:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::brcyan << "Focused Convergence." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::yellow << "Turns: " << variableKeeper::ShopItems[15].special << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[15].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[15].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			case 16:
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::cyan << "Cyan crown." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::magenta << "exp%: " << variableKeeper::ShopItems[16].special << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << variableKeeper::ShopItems[16].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << variableKeeper::ShopItems[16].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
				break;
			default:
				break;
			}
		}
		attemptsToCatch = 0;
	}
	void InitializationLeftMenu()
	{
		for (int j = 1; j < 34; j++)
		{
			systems::gotoxy(0, 0 + j);
			std::cout << "|" << "\n";
			systems::gotoxy(30, 0 + j);
			std::cout << "|" << "\n";
		}
		for (int i = 0; i < 31; i++)
		{
			systems::gotoxy(0 + i, 0);
			std::cout << "-";
		}
		for (int i = 0; i < 31; i++)
		{
			systems::gotoxy(0 + i, 34);
			std::cout << "-";
		}
		systems::gotoxy(1, 1);
		std::cout << Color::red << "hp: " << player::Player.hp << " / " << player::Player.MaxHP << Color::def;
		if (player::Player.hp < 10)
		{
			systems::gotoxy(5, 1);
			std::cout << Color::red << Player.hp << Color::def;
			systems::gotoxy(6, 1);
			std::cout << " ";
			systems::gotoxy(7, 1);
			std::cout << Color::red << "/" << Color::def;
			systems::gotoxy(8, 1);
			std::cout << " ";
			systems::gotoxy(9, 1);
			std::cout << Color::red << player::Player.MaxHP << Color::def;
			systems::gotoxy(12, 1);
			std::cout << " ";
		}
		else if (player::Player.hp < 100)
		{
			systems::gotoxy(7, 1);
			std::cout << " ";
			systems::gotoxy(13, 1);
			std::cout << " ";
		}


		systems::gotoxy(15, 1);
		std::cout << Color::magenta << "xp: " << player::Player.exp << " / " << player::Player.forNextlvl << Color::def;
		systems::gotoxy(15, 2);
		std::cout << Color::brcyan << "lv: " << player::Player.lvl << Color::def;
		systems::gotoxy(1, 2);
		std::cout << Color::green << "Coins: " << player::Player.coins << Color::def;
		systems::gotoxy(1, 3);
		std::cout << Color::orange << "Difficulty: " << variableKeeper::difficulty << Color::def;
		systems::gotoxy(15, 3);
		std::cout << Color::blue << "Stage: " << variableKeeper::Stage << Color::def;
		systems::gotoxy(1, 4);
		std::cout << "-----------------------------";
		systems::gotoxy(1, 5);
		std::cout << "Items:";
		systems::gotoxy(1, 6);
		std::cout << "-----------------------------";
		CheckItem();
		systems::gotoxy(1, 25);
		std::cout << Color::brwhite << "Last action: " << variableKeeper::CurrentState << Color::def;
		systems::gotoxy(1, 26);
		std::cout << Color::brwhite << variableKeeper::CurrentState2 << Color::def;
		systems::gotoxy(1, 28);
		std::cout << Color::brwhite << "seed: " << variableKeeper::MapSeed << Color::def;
		if (DebugMode == 1)
		{
			//systems::gotoxy(1, 29);
			//std::cout << "up: '" << variableKeeper::map[Player.y - 1][Player.x] << "'";
			//systems::gotoxy(1, 30);
			//std::cout << "down: '" << variableKeeper::map[Player.y + 1][Player.x] << "'";
			//systems::gotoxy(1, 31);
			//std::cout << "left: '" << variableKeeper::map[Player.y][Player.x - 1] << "'";
			//systems::gotoxy(1, 32);
			//std::cout << "right: '" << variableKeeper::map[Player.y][Player.x + 1] << "'";
			systems::gotoxy(1, 33);
			std::cout << Color::red << "// DEBUG // DEBUG // DEBUG //" << Color::def;
		}
	}
	bool IsNothingDisturbingThePlayer(int x, int y, char Where, int map[35][93]) // ���� ����� U - UP; D - DOWN; L - LEFT; R - RIGHT
	{
		if (Where == 'U')
		{
			// up
			if (y <= 1)
			{
				return false;
			}
			if (map[y - 1][x] == 0 || map[y - 1][x] == 600)
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
			if (map[y + 1][x] == 0 || map[y + 1][x] == 600)
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
			if (map[y][x - 1] == 0 || map[y][x - 1] == 600)
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
			if (map[y][x + 1] == 0 || map[y][x + 1] == 600)
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
	void actionOnTheEnemy(int x, int y, int count, bool attack, bool TpPool = false) //attack = false - check enemy, attack = true - attack enemy
	{
		if (attack == false)
		{
			if (variableKeeper::Enemy[count].hp <= 0)
			{
				variableKeeper::map[y][x] = 0;
				systems::gotoxy(31 + x, y);
				std::cout << " ";
			}
			else if (variableKeeper::Enemy[count].hp > 0)
			{
				variableKeeper::map[y][x] = 7 + count;
			}
		}
		else if (attack == true)
		{
			variableKeeper::Enemy[count].hp -= variableKeeper::ShopItems[variableKeeper::ItemSlotID[0]].damage - variableKeeper::EnemyDefaultStats[3];
			if (variableKeeper::Enemy[count].hp <= 0)
			{
				if (TpPool == true)
				{
					variableKeeper::map[y][x] = 600;
					systems::gotoxy(31 + x, y);
					std::cout << Color::redBG << ' ' << Color::defBG;
				}
				else {
					variableKeeper::map[y][x] = 0;
					systems::gotoxy(31 + x, y);
					std::cout << " ";
				}
#pragma warning(suppress: 4244)
				Player.coins += 10 + (5 * variableKeeper::difficulty);
#pragma warning(suppress: 4244)
				Player.exp += 2.5 + (2.5 * variableKeeper::difficulty);
				if (variableKeeper::PlayerGotCrown == true) {
#pragma warning(suppress: 4244)
					player::Player.exp += (2.5 + (2.5 * variableKeeper::difficulty)) * (25 + variableKeeper::Stage / 100);
				}
				variableKeeper::CurrentState = "You killed a en";
				variableKeeper::CurrentState2 = "emy and got money & exp";
				variableKeeper::Score += 50;
			}
			player::Player.hp -= variableKeeper::EnemyDefaultStats[0] - player::Player.armor;
			player::Player.hp += variableKeeper::HealAfterKill;
			InitializationLeftMenu();
		}
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
				switch (map[j][i])
				{
				case 0:
					std::cout << variableKeeper::FloorSymbol;
					break;
				case 1:
					std::cout << variableKeeper::WallSymbol;
					break;
				case 2:
					std::cout << Color::yellow << variableKeeper::ChestSymbol << Color::def;
					break;
				case 4:
					std::cout << Color::green << variableKeeper::PlayerSymbol << Color::def;
					break;
				case 5:
					std::cout << Color::orange << variableKeeper::ShopSymbol << Color::def;
					break;
				case 6:
					std::cout << Color::magenta << variableKeeper::EventTeleporterSymbol << Color::def;
					break;
				case 600:
					std::cout << Color::redBG << variableKeeper::FloorSymbol << Color::defBG;
					break;
				case 601:
					std::cout << Color::redBG << variableKeeper::WallSymbol << Color::defBG;
					break;
				case 602:
					std::cout << Color::redBG << Color::yellow << variableKeeper::ChestSymbol << Color::def << Color::defBG;
					break;
				case 604:
					std::cout << Color::redBG << Color::green << variableKeeper::PlayerSymbol << Color::def << Color::defBG;
					break;
				case 605:
					std::cout << Color::redBG << Color::orange << variableKeeper::ShopSymbol << Color::def << Color::defBG;
					break;
				case 606:
					std::cout << Color::redBG << Color::magenta << variableKeeper::EventTeleporterSymbol << Color::def << Color::defBG;
					break;
				default:
					break;
				}
				if (map[j][i] < 500 && map[j][i] >= 7)
				{
					for (int g = 0; g < 2; g++)
					{
						actionOnTheEnemy(i, j, g, false);
						std::cout << Color::red << variableKeeper::EnemySymbol << Color::def;
						break;
					}
				}
				else if (map[j][i] >= 607)
				{
					for (int g = 0; g < 2; g++)
					{
						actionOnTheEnemy(i, j, g, false);
						std::cout << Color::redBG << Color::red << variableKeeper::EnemySymbol << Color::def << Color::defBG;
						break;
					}
				}
			}

		}
	}

	std::string* ShopMenuItems() // this function returns a pointer to a std::string.
	{
		std::string* item = new std::string[5];
		item[0] = variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].Name;
		item[1] = variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].Name;
		item[2] = variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].Name;
		return item;
	}
	std::string* ShopMenuItemsSpecs(bool cost, bool dmg, bool desc, bool lv) // this function returns a pointer to a std::string.
	{
		if (cost == true)
		{
			std::string* item = new std::string[5];
			item[0] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].cost);
			item[1] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].cost);
			item[2] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].cost);
			return item;
		}
		else if (dmg == true)
		{
			std::string* item = new std::string[5];
			item[0] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].damage);
			item[1] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].damage);
			item[2] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].damage);
			return item;
		}
		else if (desc == true)
		{
			std::string* item = new std::string[5];
			item[0] = variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].Desc;
			item[1] = variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].Desc;
			item[2] = variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].Desc;
			return item;
		}
		else if (lv == true)
		{
			std::string* item = new std::string[5];
			item[0] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].LvlToEqp);
			item[1] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].LvlToEqp);
			item[2] = std::to_string(variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].LvlToEqp);
			return item;
		}
#pragma warning(suppress: 4244)
	}
	//
	void ShopBuyWeapon()
	{
		if (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].cost <= player::Player.coins && variableKeeper::ShopItemsIDs[0] != 19 && variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].LvlToEqp <= player::Player.lvl)
		{
			player::Player.coins -= variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].cost;
			variableKeeper::ItemSlotID[0] = variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[0]].ID;
			variableKeeper::ShopItemsIDs[0] = 19;
			system("cls");
			InitializationLeftMenu();
			ShowMap(variableKeeper::map);
			variableKeeper::IsBought = true;
			variableKeeper::Score += 75;
			return;
		}
		else {
			variableKeeper::IsBought = false;
			return;
		}
	}
	void ShopBuyItem()
	{
		if (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].cost <= player::Player.coins && variableKeeper::ShopItemsIDs[1] != 19 && variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].LvlToEqp <= player::Player.lvl)
		{
			int availableSlot = -1;
			for (int i = 0; i < 6; i++)
			{
				if (variableKeeper::ItemSlotID[i] == -1)
				{
					availableSlot = i;
					break;
				}
			}
			if (availableSlot == -1)
			{
				variableKeeper::IsBought = false;
				return;
			}
			player::Player.coins -= variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].cost;
			variableKeeper::ItemSlotID[availableSlot] = variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].ID;
			if (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].ID == 12)
			{
				variableKeeper::HealAfterKill += variableKeeper::ShopItems[12].special;
			}
			else if (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].ID == 13)
			{
				player::Player.armor += variableKeeper::ShopItems[13].special;
			}
			else if (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].ID == 14)
			{
				player::Player.armor += variableKeeper::ShopItems[14].special;
			}
			else if (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].ID == 15)
			{
				variableKeeper::NeedsForTPCharge -= variableKeeper::ShopItems[15].special;
			}
			else if (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[1]].ID == 16)
			{
				variableKeeper::PlayerGotCrown = true;
			}
			variableKeeper::ShopItemsIDs[1] = 19;
			system("cls");
			InitializationLeftMenu();
			ShowMap(variableKeeper::map);
			variableKeeper::IsBought = true;
			variableKeeper::Score += 50;
			return;
		}
		else {
			variableKeeper::IsBought = false;
			return;
		}
	}
	void ShopBuyConsume()
	{
		if (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].cost <= player::Player.coins && variableKeeper::ShopItemsIDs[2] != 19 && variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].LvlToEqp <= player::Player.lvl)
		{
			switch (variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].ID)
			{
			case 10:
				Player.hp = Player.MaxHP;
				break;
			case 11:
				Player.exp += 10 + (Player.lvl * 2);
				break;
			default:
				break;
			}
			player::Player.coins -= variableKeeper::ShopItems[variableKeeper::ShopItemsIDs[2]].cost;
			variableKeeper::ShopItemsIDs[2] = 19;
			variableKeeper::Score += 25;
			system("cls");
			InitializationLeftMenu();
			ShowMap(variableKeeper::map);
			variableKeeper::IsBought = true;
			return;
		}
		else {
			variableKeeper::IsBought = false;
			return;
		}
	}
	void OpenShop()
	{ //int map[35][93]
		system("cls");
		typedef void (*TMenuShop)(); // typedef for defining a 'pointer to function' type.
		int ShopItemsCount = 3; // This variable holds the number of menu items.
		int ShopMenuChoice = 1; // This variable holds the position of the cursor. 
		char key; //for entering the key (up arrow,down arrow,etc...);
		TMenuShop* MenuShopOption = new TMenuShop[ShopItemsCount];//array of pointers to functions (dynamic).
		MenuShopOption[0] = ShopBuyWeapon; //filling the array with the functions.
		MenuShopOption[1] = ShopBuyItem;
		MenuShopOption[2] = ShopBuyConsume;
		//	PlaySound(TEXT("C:\\Dont_talk_with_me.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		while (1) //infinite loop. (this loop will not break that's why we need an exit function).
		{
			int ItemsCount = 5;
			if (DebugMode == 1)
			{
				systems::gotoxy(47, -1 + ItemsCount);
				std::cout << "ShopMenuChoise: " << ShopMenuChoice;
				systems::gotoxy(47, 0 + ItemsCount);
				std::cout << "ShopItemsIDs[0]: " << variableKeeper::ShopItemsIDs[0];
				systems::gotoxy(47, 1 + ItemsCount);
				std::cout << "ShopItemsIDs[1]: " << variableKeeper::ShopItemsIDs[1];
				systems::gotoxy(47, 2 + ItemsCount);
				std::cout << "ShopItemsIDs[2]: " << variableKeeper::ShopItemsIDs[2];
			}
			systems::gotoxy(47, 3 + ItemsCount);
			std::cout << Color::green << "Coins: " << Color::yellow << Player.coins << Color::def;
			systems::gotoxy(47, 5 + ItemsCount);
			std::cout << "------------------------------";
			for (int i = 0; i < ShopItemsCount; i++) // Draw the menu.
			{
				bool skippedDamage = false;
				systems::gotoxy(47, 6 + i + ItemsCount);
				ShopMenuChoice == i + 1 ? std::cout << " -> " : std::cout << "    "; // if (i+1) == the cursor then
				//    print ' -> ' else print '    '.
				//    by the way i call '->' the cursor
				std::cout << ShopMenuItems()[i] << std::endl; // print the name of the item.
				if (ShopMenuItemsSpecs(false, true, false, false)[i] != "0")
				{
					systems::gotoxy(50, 8 + i + ItemsCount);
					std::cout << Color::red << "Damage: " << ShopMenuItemsSpecs(false, true, false, false)[i] << Color::def << std::endl;

				}
				else { skippedDamage = true; }
				if (ShopMenuItemsSpecs(true, false, false, false)[i] != "0")
				{
					if (skippedDamage == true)
					{
						systems::gotoxy(50, 8 + i + ItemsCount);
						std::cout << Color::green << "Cost:  " << ShopMenuItemsSpecs(true, false, false, false)[i] << Color::def << std::endl;
						if (ShopMenuItemsSpecs(false, false, false, true)[i] != "0") {
							systems::gotoxy(62, 8 + i + ItemsCount);
							std::cout << Color::cyan << "lv:  " << ShopMenuItemsSpecs(false, false, false, true)[i] << Color::def << std::endl;
						}
					}
					else {
						systems::gotoxy(63, 8 + i + ItemsCount);
						std::cout << Color::green << "Cost:  " << ShopMenuItemsSpecs(true, false, false, false)[i] << Color::def << std::endl;
						if (ShopMenuItemsSpecs(false, false, false, true)[i] != "0") {
							systems::gotoxy(75, 8 + i + ItemsCount);
							std::cout << Color::cyan << "lv:  " << ShopMenuItemsSpecs(false, false, false, true)[i] << Color::def << std::endl;
						}
					}
				}
				systems::gotoxy(50, 9 + i + ItemsCount);
				std::cout << Color::grey << ShopMenuItemsSpecs(false, false, true, false)[i] << Color::def << std::endl;
				systems::gotoxy(47, 11 + i + ItemsCount);
				std::cout << "------------------------------";
				ItemsCount += 5;
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
					if (ShopMenuChoice == 1)
					{
						ShopBuyWeapon();
					}
					else if (ShopMenuChoice == 2)
					{
						ShopBuyItem();
					}
					else if (ShopMenuChoice == 3)
					{
						ShopBuyConsume();
					}

					if (variableKeeper::IsBought == true)
						return;
					else {}
				}
				catch (...)
				{
				}  // we have to use try and catch coz if we did'nt fill that index with a function.
				   //                     a runtime error will appear.
				break;
			case 'P': // if the entered key is the 'up arrow' notice that its equal to 'P' (capital)
				ShopMenuChoice++; //then we will increment the cursor by one.
				if (ShopMenuChoice > ShopItemsCount) // if the cursor value is more than the items count.
					ShopMenuChoice = 1;         //    then it will return back to the first item.
				break;
			case 'H': // same but with 'down arrow' and decrement the cursor.
				ShopMenuChoice--;
				if (ShopMenuChoice < 1)
					ShopMenuChoice = ShopItemsCount;
				break;
			case 27: // 27 is the asscii to the escape key (Esc)
				try { /*(*MenuShopOption[ShopItemsCount - 1])(); break;*/system("cls"); InitializationLeftMenu(); ShowMap(variableKeeper::map); return; } // useually when the 'Esc' key is pressed the last
				//     item will be called (executed). but you can
				//     change it to whatever you want.
				catch (...) {}
				break;
			default:// any another key.
				if (key >= '1' && key <= char(ShopItemsCount + '0'))//check if the pressed key is in the range
					//    of (1,2,3,...,#of items) [all char(s)]
				{
					try { (*MenuShopOption[int(key) - '0' - 1])(); } //call the function of the pressed number.
					//  you can make the cursor move to that item instead of calling (executing)
					//  it by replacing all the code between 'if (bla){' and '}' with this
					//  statement MenuChooice=int(key)-'0'
					catch (...) {}
				}
			}
		}

		delete[] MenuShopOption;
	}
}