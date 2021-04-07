#include "Commands.hpp"
#include <fstream>
#include <iostream>
/*
File: cat.cpp
Purpose: Manages the 'cat' command, responsible for displaying a file's contents.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::cat(vector<wstring> args)
{
	//I can't replicate the echo-back behavior
	if (args.size() < 2)
	{
		std::wcout << "cat: Missing operand" << std::endl;
		return E_INVALIDARG;
	}

	//The full file name
	wstring strSum = Helpers::vecsum(1, args, true);

	std::error_code ec;
	if (!fs::exists(strSum, ec))
	{
		std::wcout << "cat: No such file or directory" << std::endl;
		return ERROR_FILE_NOT_FOUND;
	}

	std::wifstream file(strSum.c_str());

	if (!file.good())
	{
		std::wcout << "cat: Cannot open file." << std::endl;
		return E_FAIL;
	}

	std::wstringstream wStream; wStream << file.rdbuf();

	std::wcout << wStream.str() << std::endl;

	file.close();

	return S_OK;
}
