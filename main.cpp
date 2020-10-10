#include "Helpers/Helpers.hpp"
#include <iostream>
#include "Parser/FuncMap.hpp"
#include "Parser/Parser.hpp"
#include <filesystem>
#include <Windows.h>
#pragma warning(disable : 4996)

/*
File: main.cpp
Purpose: Holds the main entry point of the program, responsible for printing the pretty prefix.
Author: Pin (https://github.com/sailent704)
*/

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

int main(int arg_count, char** arg_vector)
{
	Helpers::SetConsoleTitleS("ExtendedShell Nightly");

	InitFuncMap(&gFuncMap);
	//Do stuff with args here

	setlocale(LC_ALL, "en_US.UTF-8");

	while (1)
	{
		wstring sInput;
	
		PrintPrefix();

		std::getline(std::wcin, sInput);

		ParseCommand(Helpers::delimstr(' ', sInput));
	}

	return 0;
}