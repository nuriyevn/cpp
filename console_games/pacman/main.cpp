#include <iostream>
#include <Windows.h>
#include <time.h>
#include <cctype>

int HandleKeyEvent( const KEY_EVENT_RECORD &key_event );
//void HandleMouseEvent( const MOUSE_EVENT_RECORD &mouse_event );

using namespace std;
// Wrapper
class CriticalSectionContainer
{
public:
	CriticalSectionContainer(CRITICAL_SECTION* pCS)
		: m_pCS(pCS)
	{
		EnterCriticalSection(m_pCS);
	}

	~CriticalSectionContainer()
	{
		LeaveCriticalSection(m_pCS);
	}

	operator bool()
	{
		return true;
	}

private:
	CRITICAL_SECTION* m_pCS;
};

#define CSBLOCK(x) if (CriticalSectionContainer __csc = x)

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

enum FieldContent
{
	EMPTY = 0,
	WALL = 1,
	APPLE = 2,
	ENEMY = 3
};

enum KeyboardKeys{
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,
	ESCAPE = 27
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

int ENEMY_COLOR = light_red;
int PLAYER_COLOR = light_blue;
int APPLE_COLOR = yellow;
int WALL_COLOR = light_gray;
int SCORE_COLOR = light_magenta;

const int ene_count = 5;
COORD enemies[ene_count];

// We have field matrix 24x24
const int cols = 24, lines = 24;
int field[lines][cols];


DWORD moveEnemies(CriticalSectionContainer* pcsc);
bool gameOver = false;

void main()
{
	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);

	CriticalSectionContainer csc(&cs);

	// Setting the width of caret
	srand((unsigned int)time(0));
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = true;
	cci.dwSize = 50;
	SetConsoleCursorInfo(h, &cci);

	// Setting the frame of the console window
	system("mode con cols=50 lines=25");
	system("title PAC MAN");
	
	int collected_apples = 0;
	int all_apples = 0;


	

	// outer loop
	for (int i = 0; i < lines; i++)
	{
		// inner loop
		for (int j = 0; j < cols; j++)
		{
			// filling boundaries of the game field with walls
			if (i == 0 || j == 0 || i == lines - 1 || j == cols - 1)
			{
				field[i][j] = WALL; // WALL
			}
			// Filling non-boundary cells with either WALLs - 20% or Apples = 10%, Empty space = 70%
			else
			{
				int temp = rand() % 100;
				if (temp >= 0 && temp <= 20)
					field[i][j] = WALL;
				else if (temp > 20 && temp < 30)
				{
					field[i][j] = APPLE;
					all_apples++;
				}
				else
					field[i][j] = EMPTY;
			}

			if (field[i][j] == WALL)
			{
				SetConsoleTextAttribute(h, WALL_COLOR);
				cout << char(177);
			}
			else if (field[i][j] == APPLE)
			{
				SetConsoleTextAttribute(h, APPLE_COLOR);
				cout << ".";
			}
			else if (field[i][j] == EMPTY)
			{
				cout << " ";
			}
			else
			{

			}
		}
		cout << endl;
	}

	// LEGEND PART: Details of game
	
	// Output information about score
	COORD score;
	score.X = 26;
	score.Y = 2;
	SetConsoleCursorPosition(h, score);
	SetConsoleTextAttribute(h, SCORE_COLOR);
	cout << "Apples ( " << collected_apples << "/" << all_apples << " )";

	// Initializa player position at start and draw player
	// @todo check that initial position is logically correct
	COORD player;
	player.X = 1;
	player.Y = 1;
	SetConsoleCursorPosition(h, player);
	SetConsoleTextAttribute(h, PLAYER_COLOR);
	cout << char(1);

	// Generating inital positin of enemies and draw them all
	for (int i = 0; i < ene_count; i++)
	{
		enemies[i].X = rand() % (cols - 2) + 1;
		enemies[i].Y = rand() % (lines - 2) + 1;
		if (field[enemies[i].Y][enemies[i].X] != EMPTY)
		{
			// revert transaction, try to generate enemy again
			i--;
			continue;
		}

		// Drawing enemies
		field[enemies[i].Y][enemies[i].X] = ENEMY;
		SetConsoleCursorPosition(h, enemies[i]);
		SetConsoleTextAttribute(h, ENEMY_COLOR);
		cout << char(2);
	}


	HANDLE hThread = 0;
	DWORD threadId = 0;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)moveEnemies, &csc, 0, &threadId);

	while (1)
	{

		// MOVING THE PLAYER

		// Handling keyboard key code
		
		int code;

		HANDLE hStdin;
		INPUT_RECORD input[128];
		DWORD num_input;

		hStdin = GetStdHandle( STD_INPUT_HANDLE );

		if (ReadConsoleInput( hStdin, input, sizeof input / sizeof *input, &num_input ))
		{
			for ( DWORD i = 0; i < num_input; i++ )
			{
				if ( input[i].EventType == KEY_EVENT )
				{
					code = HandleKeyEvent( input[i].Event.KeyEvent );
					
				}
			}
		}


		CSBLOCK(csc)
		{
			// updating position of cursor to the old position
			SetConsoleCursorPosition(h, player);
			// Remove the image of player
			cout << " ";
		}

		// Handling keyboard events
		switch (code)
		{
		case UP: 
			if (field[player.Y - 1][player.X] != WALL)
				player.Y--;
			break;
		case LEFT:
			if (field[player.Y][player.X - 1] != WALL)
				player.X--;
			break;
		case RIGHT:
			if (field[player.Y][player.X + 1] != WALL)
				player.X++;
			break;
		case DOWN:
			if (field[player.Y + 1][player.X] != WALL)
				player.Y++;
			break;
		case ESCAPE:
			exit(0);
			break;
		}

		CSBLOCK(csc)
		{
			// Set the new position of the player
			SetConsoleCursorPosition(h, player);
			// Set color of the player
			SetConsoleTextAttribute(h, PLAYER_COLOR);
			// Draw the player
			cout << char(1);
		}


		// Where are we?
		if (field[player.Y][player.X] == FieldContent::APPLE) // 
		{
			collected_apples++;
			field[player.Y][player.X] = FieldContent::EMPTY;
			CSBLOCK(csc)
			{
				// Erase the score board
				SetConsoleCursorPosition(h, score);
				cout << "\t\t\t";

				// Update score
				SetConsoleTextAttribute(h, SCORE_COLOR);
				SetConsoleCursorPosition(h, score);
				cout << "Apples ( " << collected_apples << "/" << all_apples << " )";
			}
		}
		else if (field[player.Y][player.X] == FieldContent::ENEMY)
		{
			CSBLOCK(csc)
			{
				SetConsoleCursorPosition(h, player);
				SetConsoleTextAttribute(h, ENEMY_COLOR);
				cout << char(2);

				// Loosing information
				SetConsoleCursorPosition(h, score);
				cout << "\t\t\t";
				SetConsoleTextAttribute(h, SCORE_COLOR);
				SetConsoleCursorPosition(h, score);
				cout << "You loose!" << endl;
			}
			break;
		}
		else if (field[player.Y][player.X] == FieldContent::EMPTY)
		{
		}

		// Checking whether we win
		if (collected_apples >= all_apples *0.95)
		{
			CSBLOCK(csc)
			{
				system("cls");
				cout << "You win" << endl;
			}
			break;
		}
	}

	
	gameOver = true;
	WaitForSingleObject(hThread, 1000);
	CloseHandle(hThread);
	system("pause");

}



DWORD moveEnemies(CriticalSectionContainer* pcss)
{

	while (!gameOver)
	{
		Sleep(10);
		for (int i = 0; i < ene_count; i++)
		{
			CSBLOCK(*pcss)
			{
				// Remove enemies[i]
				SetConsoleCursorPosition(h, enemies[i]);
				cout << " ";
			}
			field[enemies[i].Y][enemies[i].X] = EMPTY;

			// Generate next move direction
			// We can only move to empty position
			int direction = rand() % 4;
			switch (direction)
			{
			case 0: // up
				if (field[enemies[i].Y - 1][enemies[i].X] == EMPTY)
					enemies[i].Y--;
				break;
			case 1: // left
				if (field[enemies[i].Y][enemies[i].X - 1] == EMPTY)
					enemies[i].X--;
				break;
			case 2: // right
				if (field[enemies[i].Y][enemies[i].X + 1] == EMPTY)
					enemies[i].X++;
				break;
			case 3: // down
				if (field[enemies[i].Y + 1][enemies[i].X] == EMPTY)
					enemies[i].Y++;
				break;
			}

			CSBLOCK(*pcss)
			{
				// Put enemy and draw him
				SetConsoleCursorPosition(h, enemies[i]);
				field[enemies[i].Y][enemies[i].X] = ENEMY;
				SetConsoleTextAttribute(h, ENEMY_COLOR);
				cout << char(2);
			}
		}
	}
	return 0;
}

int HandleKeyEvent( const KEY_EVENT_RECORD &key_event )
{
    std::cout << "Key ";
    if ( std::isprint( static_cast<unsigned char>(key_event.uChar.AsciiChar) ) )
        std::cout << (char)std::toupper( static_cast<unsigned char>(key_event.uChar.AsciiChar) );
    else
        std::cout << "<unprintable>";

	
    if ( key_event.bKeyDown)
    {
        //std::cout << " down!\n";
		switch (key_event.wVirtualKeyCode)
		{
			case VK_UP:
				return UP;
			case VK_RIGHT:
				return RIGHT;
			case VK_LEFT:
				return LEFT;
			case VK_DOWN:
				return DOWN; 
			case VK_ESCAPE:
				return ESCAPE; 
		}
    }
    else
    {
        std::cout << " up!\n";
    }
	return 0;
}