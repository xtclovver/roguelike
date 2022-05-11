#pragma once
#include <iostream>
#include <string>
#include "colorfull.h"
#include "systems.h"
#include "player.h"
namespace shopNitems {
	bool IsBought = false;
	int ShopItemsIDs[3];
	int ItemSlotID[6] = { 0,-1,-1,-1,-1,-1 }; // [0] is sword, another is items
	struct ItemsSpecifications {
		std::string Name;
		int damage = 0;
		int ID = 0;
		int StageReq = 0;
		int LvlToEqp = 0;
		int cost = 0;
		std::string Desc; // Description
	};
	ItemsSpecifications ShopItems[20];

	void CheckItem() {
		int attemptsToCatch = 0;
		for (int i = 0; i < 6; i++)
		{
			switch (ItemSlotID[i])
			{
			case 0:
			default:
				break;
			}

			if (ItemSlotID[i] == -1)
			{
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << "Empty.";
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
			}
			else if (ItemSlotID[0] == 0)
			{
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::grey << "Dao." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << ShopItems[0].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << ShopItems[0].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << ShopItems[0].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
			}
			else if (ItemSlotID[0] == 1)
			{
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::grey << "Quelling Blade." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << ShopItems[1].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << ShopItems[1].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << ShopItems[1].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
			}
			else if (ItemSlotID[0] == 2)
			{
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::grey << "Ogre Axe." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << ShopItems[2].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << ShopItems[2].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << ShopItems[2].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
			}
			else if (ItemSlotID[0] == 3)
			{
				systems::gotoxy(1, 7 + attemptsToCatch);
				std::cout << Color::grey << "Katana." << Color::def;
				systems::gotoxy(1, 8 + attemptsToCatch);
				std::cout << Color::red << "dmg: " << ShopItems[3].damage << Color::def;
				systems::gotoxy(10, 8 + attemptsToCatch);
				std::cout << Color::brcyan << "lv: " << ShopItems[3].LvlToEqp << Color::def;
				systems::gotoxy(17, 8 + attemptsToCatch);
				std::cout << Color::green << "cost: " << ShopItems[3].cost << Color::def;
				systems::gotoxy(1, 9 + attemptsToCatch);
				std::cout << "-----------------------------";
				attemptsToCatch += 3;
			}
		}
		attemptsToCatch = 0;
	}
	std::string* ShopMenuItems() // this function returns a pointer to a std::string.
	{
		std::string* item = new std::string[5];
		item[0] = ShopItems[ShopItemsIDs[0]].Name;
		item[1] = ShopItems[ShopItemsIDs[1]].Name;
		item[2] = ShopItems[ShopItemsIDs[2]].Name;
		return item;
	}
	std::string* ShopMenuItemsSpecs(bool cost, bool dmg, bool desc) // this function returns a pointer to a std::string.
	{
		if (cost == true)
		{
			std::string* item = new std::string[5];
			item[0] = std::to_string(ShopItems[ShopItemsIDs[0]].cost);
			item[1] = std::to_string(ShopItems[ShopItemsIDs[1]].cost);
			item[2] = std::to_string(ShopItems[ShopItemsIDs[2]].cost);
			return item;
		}
		else if (dmg == true)
		{
			std::string* item = new std::string[5];
			item[0] = std::to_string(ShopItems[ShopItemsIDs[0]].damage);
			item[1] = std::to_string(ShopItems[ShopItemsIDs[1]].damage);
			item[2] = std::to_string(ShopItems[ShopItemsIDs[2]].damage);
			return item;
		}
		else if (desc == true)
		{
			std::string* item = new std::string[5];
			item[0] = ShopItems[ShopItemsIDs[0]].Desc;
			item[1] = ShopItems[ShopItemsIDs[1]].Desc;
			item[2] = ShopItems[ShopItemsIDs[2]].Desc;
			return item;
		}
	}
	//
	void ShopBuy0()
	{
		if (ShopItems[ShopItemsIDs[0]].cost <= player::Player.coins)
		{
			player::Player.coins -= ShopItems[ShopItemsIDs[0]].cost;
			ItemSlotID[0] = ShopItems[ShopItemsIDs[0]].ID;
			system("cls");
			InitializationLeftMenu();
			systems::ShowMap(map);
			IsBought = true;
			return;
		}
		else {
			IsBought = false;
			return;
		}
	}
	void ShopBuy1()
	{

	}
	void ShopBuy2()
	{

	}
	void OpenShop()
	{ //int map[35][93]
		system("cls");
		typedef void (*TMenuShop)(); // typedef for defining a 'pointer to function' type.
		int ShopItemsCount = 3; // This variable holds the number of menu items.
		int ShopMenuChoice = 1; // This variable holds the position of the cursor. 
		char key; //for entering the key (up arrow,down arrow,etc...);
		TMenuShop* MenuShopOption = new TMenuShop[ShopItemsCount];//array of pointers to functions (dynamic).
		MenuShopOption[0] = ShopBuy0; //filling the array with the functions.
		MenuShopOption[1] = ShopBuy1;
		MenuShopOption[2] = ShopBuy2;
		//	PlaySound(TEXT("C:\\Dont_talk_with_me.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		while (1) //infinite loop. (this loop will not break that's why we need an exit function).
		{
			int ItemsCount = 5;
			if (DEBUG == 1)
			{
				systems::gotoxy(47, 1 + ItemsCount);
				std::cout << "ShopItemsIDs[0]: " << ShopItemsIDs[0];
				systems::gotoxy(47, 2 + ItemsCount);
				std::cout << "ShopItemsIDs[1]: " << ShopItemsIDs[1];
				systems::gotoxy(47, 3 + ItemsCount);
				std::cout << "ShopItemsIDs[2]: " << ShopItemsIDs[2];
			}
			systems::gotoxy(47, 5 + ItemsCount);
			std::cout << "------------------------------";
			for (int i = 0; i < ShopItemsCount; i++) // Draw the menu.
			{
				systems::gotoxy(47, 6 + i + ItemsCount);
				ShopMenuChoice == i + 1 ? std::cout << " -> " : std::cout << "    "; // if (i+1) == the cursor then
															   //    print ' -> ' else print '    '.
															   //    by the way i call '->' the cursor
				std::cout << ShopMenuItems()[i] << std::endl; // print the name of the item.
				systems::gotoxy(50, 8 + i + ItemsCount);
				std::cout << Color::red << "Damage: " << ShopMenuItemsSpecs(false, true, false)[i] << Color::def << std::endl;
				systems::gotoxy(62, 8 + i + ItemsCount);
				std::cout << Color::green << "Cost:  " << ShopMenuItemsSpecs(true, false, false)[i] << Color::def << std::endl;
				systems::gotoxy(50, 9 + i + ItemsCount);
				std::cout << Color::grey << ShopMenuItemsSpecs(false, false, true)[i] << Color::def << std::endl;
				systems::gotoxy(47, 11 + i + ItemsCount);
				std::cout << "------------------------------";
				ItemsCount += 5;
				//ShopItems[i]
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
					//(*MenuShopOption[ShopMenuChoice - 1])(); // call the function of the index 'cursor-1' in
					//							   //     the 'pointer to function' array.
					ShopBuy0();
					if (IsBought == true)
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
				try { 
					system("cls");
					InitializationLeftMenu();
					systems::ShowMap(map);
					return;
				} // useually when the 'Esc' key is pressed the last
													//     item will be called (executed). but you can									//     change it to whatever you want.
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
	//

}
