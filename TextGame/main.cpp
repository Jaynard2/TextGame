#include <iostream>
#include <vector>
#include <Windows.h>
#include "Entity.h"
#include "Map.h"
#include "Messages.h"

enum class ControlState { PLAYER_CONTROL, COMPUTER_CONTROL };

int main(int arg, char** argc)
{

	SetConsoleTitle(TEXT("Text Game"));

	std::string gameOverScreen =
		"               ##############        #               ###             ###        ###########\n"
		"               ##############       ###             ## ##           ## ##       ###########\n"
		"               ###                 ## ##           ##   ##         ##   ##      ##         \n"
		"               ###                ##   ##         ##     ##       ##     ##     ###########\n"
		"               ###      #####    #########       ##       ##     ##       ##    ###########\n"
		"               ###        ###   ##       ##     ##         ##   ##         ##   ##         \n"
		"               ##############  ##         ##   ##           ## ##           ##  ###########\n"
		"               ############## ##           ## ##             ###             ## ###########\n"
		"                                                    OVER                                   \n";
	std::string gameWonScreen = "You won!\n";

	std::vector<Entity> entities;
	entities.push_back(Entity("DefaultPlayer.txt"));
	for(int i = 0; i < 2; ++i)
		entities.push_back(Entity("DefaultEnemy.txt"));

	Map map("DefaultMap.txt", entities);
	std::vector<Messages> gameMessages;
	bool gameWon = false;

	while(true)
	{
		ControlState controlState = ControlState::PLAYER_CONTROL;
		system("CLS");
		map.draw();
		entities[0].displayEntStats();

		while (controlState == ControlState::PLAYER_CONTROL)
		{
			static int timesMoved = 0;

			if (GetKeyState('W') & 0x8000)
			{
				entities[0].moveInY(1);
				system("CLS");
				map.update(entities);
				map.draw();
				entities[0].displayEntStats();
				++timesMoved;
			}
			if (GetKeyState('S') & 0x8000)
			{
				entities[0].moveInY(-1);
				system("CLS");
				map.update(entities);
				map.draw();
				entities[0].displayEntStats();
				++timesMoved;
			}
			if (GetKeyState('A') & 0x8000)
			{
				entities[0].moveInX(-1);
				system("CLS");
				map.update(entities);
				map.draw();
				entities[0].displayEntStats();
				++timesMoved;
			}
			if (GetKeyState('D') & 0x8000)
			{
				entities[0].moveInX(1);
				system("CLS");
				map.update(entities);
				map.draw();
				entities[0].displayEntStats();
				++timesMoved;
			}
			if (GetKeyState('F') & 0x8000)
			{
				for (int i = 1; i < entities.size(); ++i)
				{
					if (abs(entities[0].getLocation().first - entities[i].getLocation().first) == 1)
					{
						if (abs(entities[0].getLocation().second - entities[i].getLocation().second) == 0)
						{
							entities[0].attack(gameMessages, &entities[i]);
							system("CLS");
							map.update(entities);
							map.draw();
							++timesMoved;
						}
					}
					if (abs(entities[0].getLocation().first - entities[i].getLocation().first) == 0)
					{
						if (abs(entities[0].getLocation().second - entities[i].getLocation().second) == 1)
						{
							entities[0].attack(gameMessages, &entities[i]);
							system("CLS");
							map.update(entities);
							map.draw();
							++timesMoved;
						}
					}
				}
			}
			if (timesMoved >= entities[0].getSpeed())
			{
				timesMoved = 0;
				controlState = ControlState::COMPUTER_CONTROL;
			}
		}

		while (controlState == ControlState::COMPUTER_CONTROL)
		{
			for (int i = 1; i < entities.size(); ++i)
			{
				if (entities[i].getHealth() <= 0)
					continue;

				while (true)
				{
					static int timesMoved = 0;

					if (abs(entities[0].getLocation().first - entities[i].getLocation().first) == 1)
					{
						if (abs(entities[0].getLocation().second - entities[i].getLocation().second) == 0)
						{
							entities[i].attack(gameMessages, &entities[0]);
							++timesMoved;
						}
					}
					if (abs(entities[0].getLocation().first - entities[i].getLocation().first) == 0)
					{
						if (abs(entities[0].getLocation().second - entities[i].getLocation().second) == 1)
						{
							entities[i].attack(gameMessages, &entities[0]);
							++timesMoved;
						}
					}

					if (abs(entities[0].getLocation().first - entities[i].getLocation().first) >= abs(entities[0].getLocation().second - entities[i].getLocation().second))
					{
						if (entities[0].getLocation().first - entities[i].getLocation().first >= 1)
						{
							entities[i].moveInX(1);
							map.update(entities);
							++timesMoved;
						}
						else if(entities[0].getLocation().first - entities[i].getLocation().first <= -1)
						{
							entities[i].moveInX(-1);
							map.update(entities);
							++timesMoved;
						}
					}
					else
					{
						if (entities[0].getLocation().second - entities[i].getLocation().second >= 1)
						{
							entities[i].moveInY(-1);
							map.update(entities);
							++timesMoved;
						}
						else if(entities[0].getLocation().second - entities[i].getLocation().second <= -1)
						{
							entities[i].moveInY(1);
							map.update(entities);
							++timesMoved;
						}
					}

					if (timesMoved >= entities[i].getSpeed())
					{
						timesMoved = 0;
						break;
					}
				}
			}
			
			controlState = ControlState::PLAYER_CONTROL;
		}

		for (int i = 0; i < entities.size(); ++i)
		{
			entities[i].update(gameMessages);
		}

		if (entities[0].getHealth() <= 0)
		{
			system("CLS");
			std::cout << gameOverScreen;
			break;
		}

		for (int i = 1; i < entities.size(); ++i)
		{
			if ((i == entities.size() - 1) && (entities[i].getHealth() <= 0))
				gameWon = true;

			if (entities[i].getHealth() <= 0)
				continue;
			else
				break;
		}

		if (gameWon)
		{
			system("CLS");
			std::cout << gameWonScreen;
			break;
		}

		map.update(entities);

	}
	

#if _DEBUG
	std::cin.ignore();
#endif // _DEBUG

}
