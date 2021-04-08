#include <iostream>
#include <filesystem>
#include <Windows.h>

#include <cstdio>

#include <io.h>
#include <fcntl.h>

#include "Helpers/Helpers.hpp"
#include "Parser/FuncMap.hpp"
#include "Parser/Parser.hpp"

#pragma warning(disable : 4996)

/*
File: main.cpp
Purpose: Holds the main entry point of the program, responsible for printing the pretty prefix.
Author: Pin (https://github.com/sailent704)
*/

class OutBuffer: public std::stringbuf
{
	public:
		int sync() {
			fputs( str().c_str(), stdout );
			str( "" );
			return 0;
		}
};

void PrintPrefix()
{
	wstring sDir = L"\\\\Unknown\\Path";

	std::error_code ec;

	auto path = std::filesystem::current_path(ec);
	if (ec.value() != 0)
	{
		std::wcout << L"[ExtendedShell] Failed to query the current directory: " << Helpers::GetErrorMessage(ec) << std::endl;
	}
	else
	{
		sDir = path.native();

		//Change 'D:\Test' to 'D:/Test' - looks better IMO
		//std::replace(sDir.begin(), sDir.end(), '\\', '/');
	}
	
	wstring userName = Helpers::ToWString(getenv("username"));
	wstring pcName = Helpers::ToWString(getenv("computername"));

	Helpers::SetPrintCol(Helpers::Color::GREEN);
	std::wcout << userName << "@" << pcName;

	Helpers::SetPrintCol(Helpers::Color::WHITE);
	std::wcout << ':';

	Helpers::SetPrintCol(Helpers::Color::BLUE);
	std::wcout << sDir;

	Helpers::SetPrintCol(Helpers::Color::DEFAULT);
	if (Helpers::IsElevated())
	{
		std::wcout << "# ";
	}
	else
	{
		std::wcout << "$ ";
	}
}

void SetFont(std::wstring font) // Supported on Vista and newer iirc
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfie;
	ZeroMemory(&cfie, sizeof(cfie));
	cfie.cbSize = sizeof(cfie);
	lstrcpyW(cfie.FaceName, font.c_str());
	SetCurrentConsoleFontEx(hStdOut, false, &cfie);
}

int main(int arg_count, char *arg_vector[])
{
	Helpers::SetConsoleTitleS("ExtendedShell Cutting Edge");
	InitFuncMap(&gFuncMap);
	//Do stuff with args here
	

	setlocale(LC_ALL, "en_US.UTF-8");
	setvbuf( stdout, nullptr, _IONBF, 0 );

	SetConsoleCP(65001);
	SetConsoleOutputCP( 65001 );
	SetFont(L"Lucida Console");

	OutBuffer buf;
	std::cout.rdbuf( &buf );

	while (true)
	{
		PrintPrefix();

		wstring sInput;
		std::getline(std::wcin, sInput);
		ParseCommand(Helpers::delimstr(' ', sInput));
	}

	return 0;
}