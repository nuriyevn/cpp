#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

enum FieldContent
{
	EMPTY = 0,
	WALL,
	APPLE,
	ENEMY
};

enum ConsoleColors
{
	black = 0,
	blue = 1,
	green = 2,
	cyan = 3,
	red = 4,
	magenta = 5,
	brown = 6,
	light_gray = 7,
	dark_gray = 8,
	light_blue = 9,
	light_green = 10,
	light_cyan = 11,
	light_red = 12,
	light_magenta = 13,
	yellow = 14,
	white = 15
};


void main()
{
	srand(time(0));
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = true;
	cci.dwSize = 50;
	SetConsoleCursorInfo(h, &cci);
	system("mode con cols=50 lines=25");
	system("title PAC MAN");
	
	int collected_apples = 0;
	int all_apples = 0;

	const int cols = 24, lines = 24;
	int field[lines][cols];
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == 0 || j == 0 || i == lines - 1 || j == cols - 1)
			{
				field[i][j] = 1;
			}
			else
			{
				int temp = rand() % 100;
				if (temp >= 0 && temp <= 20)
					field[i][j] = 1;
				else if (temp > 20 && temp < 30)
				{
					field[i][j] = 2;
					all_apples++;
				}
				else if (temp == 35)
				{//	field[i][j] = 3;
				}
				else
					field[i][j] = 0;
			}
			if (field[i][j] == 1)
			{
				SetConsoleTextAttribute(h, light_gray);
				cout << char(177);
			}
			else if (field[i][j] == 2)
			{
				SetConsoleTextAttribute(h, yellow);
				cout << ".";
			}
			else if (field[i][j] == 3)
			{
				SetConsoleTextAttribute(h, light_red);
				cout << char(2);
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	COORD score;
	score.X = 26;
	score.Y = 2;
	SetConsoleCursorPosition(h, score);
	SetConsoleTextAttribute(h, light_magenta);
	cout << "Apples ( " << collected_apples << "/" << all_apples << " )";


	COORD player;
	player.X = 1;
	player.Y = 1;
	SetConsoleCursorPosition(h, player);
	SetConsoleTextAttribute(h, light_blue);
	cout << char(1);

	const int ene_count = 5;
	COORD enemies[ene_count];
	for (int i = 0; i < ene_count; i++)
	{
		enemies[i].X = rand() % (cols - 2) + 1;
		enemies[i].Y = rand() % (lines - 2) + 1;
		if (field[enemies[i].Y][enemies[i].X] != 0)
		{
			i--;
			continue;
		}
		field[enemies[i].Y][enemies[i].X] = 3;
		SetConsoleCursorPosition(h, enemies[i]);
		SetConsoleTextAttribute(h, light_red);
		cout << char(2);
	}


	while (1)
	{
		int code = _getch(); // conio.h
		SetConsoleCursorPosition(h, player);
		cout << " ";
		switch (code)
		{
		case 72: // up
			if (field[player.Y - 1][player.X] != 1)
				player.Y--;
			break;
		case 75: // left
			if (field[player.Y][player.X - 1] != 1)
				player.X--;
			break;
		case 77: // right
			if (field[player.Y][player.X + 1] != 1)
				player.X++;
			break;
		case 80: // down
			if (field[player.Y + 1][player.X] != 1)
				player.Y++;
			break;
		case 27:
			exit(0);
			break;
		}
		SetConsoleCursorPosition(h, player);
		SetConsoleTextAttribute(h, light_blue);
		cout << char(1);

		if (field[player.Y][player.X] == FieldContent::APPLE) // 
		{
			collected_apples++;
			field[player.Y][player.X] = FieldContent::EMPTY;
			SetConsoleCursorPosition(h, score);
			cout << "\t\t\t";
			SetConsoleTextAttribute(h, light_magenta);
			SetConsoleCursorPosition(h, score);
			cout << "Apples ( " << collected_apples << "/" << all_apples << " )";
		}
		// new_code
		else if (field[player.Y][player.X] == FieldContent::ENEMY)
		{
			//field[player.Y][player.X] = FieldContent::EMPTY;
			for (int i = 0; i < ene_count; i++)
			{
				if (enemies[i].X == -1)
					continue;
				if (player.Y == enemies[i].Y && player.X == enemies[i].X)
					enemies[i].X = -1;
			}
			//SetConsoleTextAttribute(h, light_magenta);
		}
		
//
		if (collected_apples >= all_apples *0.95)
		{
			system("cls");
			cout << "You win" << endl;
			break;
		}




		for (int i = 0; i < ene_count; i++)
		{
			SetConsoleCursorPosition(h, enemies[i]);
			cout << " ";
			field[enemies[i].Y][enemies[i].X] = 0;
			if (enemies[i].X == -1)
				continue;
			int direction = rand() % 4;
			switch (direction)
			{
			case 0: // up
				if (field[enemies[i].Y - 1][enemies[i].X] == 0)
					enemies[i].Y--;
				break;
			case 1: // left
				if (field[enemies[i].Y][enemies[i].X - 1] == 0)
					enemies[i].X--;
				break;
			case 2: // right
				if (field[enemies[i].Y][enemies[i].X + 1] == 0)
					enemies[i].X++;
				break;
			case 3: // down
				if (field[enemies[i].Y + 1][enemies[i].X] == 0)
					enemies[i].Y++;
				break;
			}
			SetConsoleCursorPosition(h, enemies[i]);

			if (enemies[i].X != -1)
			{
				field[enemies[i].Y][enemies[i].X] = 3;
				SetConsoleTextAttribute(h, light_red);
				cout << char(2);
			}
		}



	}
	
	system("pause");

}