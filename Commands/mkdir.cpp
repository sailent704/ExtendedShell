#include "Commands.hpp"
#include <iostream>

/*
File: mkdir.cpp
Purpose: Responsible for making directories.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::mkdir(vector<wstring> args)
{
	if (args.size() < 2)
	{
		std::wcout << "mkdir: Missing operand" << std::endl;
		return E_INVALIDARG;
	}

	wstring wsPath = Helpers::vecsum(1, args, true);

	std::error_code ec;

	if (!fs::create_directory(wsPath, ec))
	{
		std::wcout << "mkdir: " << Helpers::GetErrorMessage(ec) << std::endl;
		return E_FAIL;
	}

	return S_OK;
}