#include "Commands.hpp"
#include <iostream>

/*
File: cd.cpp
Purpose: Responsible for changing the working directory of the process.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::cd(vector<string> args)
{
	string sPath = Helpers::vecsum(1, args, true, ' ');

	//Replicate the behavior of cd in UNIX-like systems.
	if (sPath.empty())
		return E_INVALIDARG;

	std::error_code e;
	if (fs::is_directory(sPath, e) && fs::exists(sPath, e))
	{
		fs::current_path(sPath, e);

		if (e.value() != 0)
		{
			std::cout << "cd: '" << sPath << "': " << Helpers::GetErrorMessage(e) << std::endl;
			return E_FAIL;
		}
	}
	else
	{
		std::cout << "cd: '" << sPath << "': " << Helpers::GetErrorMessage(e) << std::endl;
	}

	return S_OK;
}
