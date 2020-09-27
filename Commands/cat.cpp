#include "Commands.hpp"
#include <fstream>
#include <iostream>

/*
File: cat.cpp
Purpose: Manages the 'cat' command, responsible for displaying a file's contents.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::cat(vector<string> args)
{
	if (args.size() < 2)
		return E_INVALIDARG;

	string sFileName = Helpers::vecsum(1, args, true, ' ');

	if (!fs::exists(sFileName))
	{
		printf("cat: %s: No such file or directory\n", sFileName.c_str());
		return E_INVALIDARG;
	}

	std::ifstream file(sFileName);

	if (!file.good())
	{
		std::cout << "cat: Failed to open file" << std::endl;
		return E_FAIL;
	}

	std::stringstream sStream; sStream << file.rdbuf();

	std::cout << sStream.str() << std::endl;

	return S_OK;
}
