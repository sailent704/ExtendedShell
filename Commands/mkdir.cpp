#include "Commands.hpp"
#include <iostream>

/*
File: mkdir.cpp
Purpose: Responsible for making directories.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::mkdir(vector<string> args)
{
	string sDirectoryName = Helpers::vecsum(1, args, true, ' ');
	string sPath = fs::current_path().string();


	if (sDirectoryName.empty())
	{
		std::cout << "mkdir: Missing operand" << std::endl;
		return E_INVALIDARG;
	}

	if (!Helpers::StringFind(sDirectoryName, "\\"))
	{
		sDirectoryName = sPath + "\\" + sDirectoryName;
	}

	std::error_code ecCreateDir;

	if (fs::create_directory(sDirectoryName, ecCreateDir))
	{
		return S_OK;
	}
	else
	{
		std::cout << "mkdir: cannot create directory '" << sDirectoryName << "': " << Helpers::GetErrorMessage(ecCreateDir) << std::endl;
	}

	return E_FAIL;
}