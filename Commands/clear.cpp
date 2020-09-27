#include "Commands.hpp"
/*
File: clear.cpp
Purpose: Responsible for clearing the screen upon the 'clear' command.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::clear(vector<string> args)
{
	COORD coOrigin = { 0, 0 };
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	GetConsoleScreenBufferInfo(hConsole, &csbInfo);

	DWORD dwNumWritten;

	if (FillConsoleOutputCharacterA(hConsole, ' ', csbInfo.dwSize.X * csbInfo.dwSize.Y, coOrigin, &dwNumWritten))
	{
		//FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE indicates white text on a black background.
		if (FillConsoleOutputAttribute(
			hConsole,
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			dwNumWritten,
			coOrigin,
			&dwNumWritten))
		{
			SetConsoleCursorPosition(hConsole, coOrigin);
			return S_OK;
		}

	}

	return E_FAIL;
}
