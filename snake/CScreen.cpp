#include "CScreen.h"

#include <conio.h>

const char *msgs[] = 
{
	"",
	"Failed GetStdHandle(): INVALID_HANDLE_VALUE",
	"Failed GetConsoleCursorInfo()",
	"Failed SetConsoleCursorInfo()",
	"Failed SetConsoleCursorPosition()"
};

const char *CSScreenException::what() 
{
	return msgs[err];
}

CScreen::CScreen()
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOutput == INVALID_HANDLE_VALUE)
		throw CSScreenException(1);
	if (!GetConsoleCursorInfo(hConsoleOutput, &oldCursorInfo))
		throw CSScreenException(2);
	curCursorInfo.dwSize = oldCursorInfo.dwSize;
	curCursorInfo.bVisible =oldCursorInfo.bVisible;
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
	oldTextAttr = csbi.wAttributes;
}

CScreen::~CScreen()
{
	SetConsoleCursorInfo(hConsoleOutput, &oldCursorInfo);
	SetConsoleTextAttribute(hConsoleOutput, oldTextAttr);
}

void CScreen::cursor_show(bool visible)
{
	curCursorInfo.bVisible = visible;
	if (!SetConsoleCursorInfo(hConsoleOutput, &curCursorInfo))
		throw CSScreenException(3);
}

void CScreen::text_attr(short attr)
{
	SetConsoleTextAttribute(hConsoleOutput, attr);
}
