#include "Commands.hpp"
/*
File: clear.cpp
Purpose: Responsible for clearing the screen upon the 'clear' command.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::clear(vector<wstring> args)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csInfo;
	GetConsoleScreenBufferInfo(hConsole, &csInfo);

	DWORD dwWritten;
	
	if (FillConsoleOutputCharacterA(hConsole, ' ', csInfo.dwSize.X * csInfo.dwSize.Y, { 0, 0 }, &dwWritten))
	{
		SetConsoleCursorPosition(hConsole, { 0, 0 });
		return S_OK;
	}

	return E_FAIL;
}