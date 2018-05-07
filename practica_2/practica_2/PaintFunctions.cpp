#include "stdafx.h"
#include "PaintFunctions.h"

void gotoxy(short x, short y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}