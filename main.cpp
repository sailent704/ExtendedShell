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
	try
	{
		std::error_code ec;

		auto path = std::filesystem::current_path(ec);
		if (ec.value() != 0)
		{
			std::cout << "[ExtendedShell] Failed to query the current directory: " << Helpers::GetErrorMessage(ec) << std::endl;
		}
		else
		{
			sDir = path.wstring();
		}
	}
	catch (std::system_error& e)
	{
		std::cout << "[catchExtended] Failed to query the current directory. Error: " << e.what() << std::endl;
	}
	
	string userName = getenv("username");
	string pcName = getenv("computername");

	Helpers::SetPrintCol(Helpers::Color::GREEN);
	std::cout << userName << "@" << pcName;
	Helpers::SetPrintCol(Helpers::Color::DEFAULT);
	std::cout << ':';
	Helpers::SetPrintCol(Helpers::Color::DARKBLUE);
	std::cout << std::string(sDir.begin(), sDir.end()); //a hack-around for patching a crash
	Helpers::SetPrintCol(Helpers::Color::DEFAULT);

	if (Helpers::IsElevated())
	{
		std::cout << "# ";
	}
	else
	{
		std::cout << "$ ";
	}
}

int main(int arg_count, char** arg_vector)
{
	InitFuncMap(gFuncMap);
	//Do stuff with args here
	Helpers::SetConsoleTitleS("eXtended Shell");

	while (1)
	{
		string sInput;
	
		PrintPrefix();

		std::getline(std::cin, sInput);

		ParseCommand(Helpers::delimstr(' ', sInput));
	}

	return 0;
}