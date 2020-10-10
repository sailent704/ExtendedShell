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
	if(args.at(1).compare(L"") == 0)
	{
		std::cout << "Usage: (f [filename]) [text]" << std::endl;
		std::cout << "(f [filename]): Optional; write output to file. Example: echo f text.txt hello -> writes hello to file text.txt" << std::endl;
		std::cout << "[text]: Required. Text to write" << std::endl;
		return E_FAIL;
	}

	if(args.at(1).compare(L"f") == 0)
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