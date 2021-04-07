#include "Commands.hpp"
#include <iostream>
#include <fstream>

/*
	File: echo.cpp
	Purpose: Hold echo function
	Function: Writes wstring to stdout or file
	Author: MousieDev (https://github.com/MousieDev)
	Created: 10.10.2020 15:30
	Revision 1: 11.10.2020 7:30
*/

HRESULT PrintUsage()
{
	std::wcout << L"echo: Missing operand" << std::endl;
	std::wcout << L"Usage: <text> [> FILENAME]" << std::endl;
	std::wcout << L"[text]: Text to write." << std::endl;
	std::wcout << L"[> FILENAME]: Write output to file." << std::endl << std::endl;
	return E_INVALIDARG;
}

HRESULT Commands::echo(vector<wstring> args)
{
	if(args.empty() || args.size() <= 1 || args.at(1).compare(L"") == 0) return PrintUsage();

	wstring text = Helpers::vecsum(1, args, true);
	if(args.size() >= 4 && text.find(L">") != std::string::npos)
	{
		std::vector<wstring> words;

		int i = 0;
		while(i < args.size() && !args.at(i).compare(L">") == 0)
		{
			words.push_back(args.at(i));
			i++;
		}

		int toFileIndex = text.find(L">");
		wstring filename;

		if(text.length() < toFileIndex +2) goto justPrint;
		else filename = text.substr(toFileIndex +2, text.length());

		wstring actualText = text.substr(0, toFileIndex -1);
		std::wcout << actualText << std::endl << std::endl;

		std::wofstream wStream(filename.c_str(), std::ios::out | std::ios::app | std::ios::binary);
		if (wStream.good())
		{
			wStream << actualText << std::endl;
			wStream.close();

			return S_OK;
		} else {
			std::wcout << L"echo: Failed to open file for writing." << std::endl;
			return E_FAIL;
		}
	} else {
		justPrint:
		std::wcout << text << std::endl << std::endl;
	}

	return S_OK;
}