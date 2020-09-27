#include "Commands.hpp"
#include <fstream>
#include <iostream>

/*
File: touch.cpp
Purpose: Responsible for creating new files.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::touch(vector<string> args)
{
	string sCompleteName = Helpers::vecsum(1, args, true);
	std::ofstream file(sCompleteName);

	if (file.good())
	{
		file << "";
		file.close();

		return S_OK;
	}

	std::cout << "touch: Failed to create file" << std::endl;
	return E_FAIL;
}