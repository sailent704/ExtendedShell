#include "Commands.hpp"
#include <iostream>
#include <fstream>

/*
	File: echo.cpp
	Purpose: Hold echo function
	Function: Writes wstring to stdout or file
	Author: MousieDev (https://github.com/MousieDev)
	10.10.2020 15:30
*/

HRESULT Commands::echo(vector<wstring> args)
{
	if(args.size() <= 1 || args.at(1).compare(L"") == 0)
	{
		std::wcout << L"Usage: (f [filename]) [text]" << std::endl;
		std::wcout << L"[text]: Text to write" << std::endl;
		std::wcout << L"(f [filename]): Write output to file. Example: echo f text.txt hello -> writes hello to file text.txt" << std::endl;
		std::wcout << L"(argument) is optional; [argument] is required." << std::endl;
		std::wcout << L"If no (f [filename]) argument provided, output will be written into console." << std::endl << std::endl;
		return E_INVALIDARG;
	}

	if(args.at(1).compare(L"f") == 0 && args.size() >= 3)
	{
		std::wofstream wStream(args.at(2).c_str(), std::ios::out | std::ios::app | std::ios::binary);
		if (wStream.good())
		{
			wStream << Helpers::vecsum(3, args, true) << std::endl;
			wStream.close();

			return S_OK;
		}

		return E_FAIL;
	}

	wstring text = Helpers::vecsum(1, args, true);
	std::wcout << text << std::endl;
	return S_OK;
}