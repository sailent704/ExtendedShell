#include "Helpers/Helpers.hpp"
#include <iostream>
#include "Parser/FuncMap.hpp"
#include "Parser/Parser.hpp"
#include <filesystem>

#pragma warning(disable : 4996)

void PrintPrefix()
{
	string sDir = std::filesystem::current_path().string();
	string userName = getenv("username");
	string pcName = getenv("computername");

	Helpers::SetPrintCol(Helpers::Color::GREEN);
	std::cout << userName << "@" << pcName;
	Helpers::SetPrintCol(Helpers::Color::DEFAULT);
	std::cout << ':';
	Helpers::SetPrintCol(Helpers::Color::DARKBLUE);
	std::cout << sDir;
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

	//Main loop
	while (1)
	{
		string sInput;
	
		PrintPrefix();

		std::getline(std::cin, sInput);

		ParseCommand(Helpers::delimstr(' ', sInput));
	}
}