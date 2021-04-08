#include "Commands.hpp"
#include <iostream>

/*
File: cd.cpp
Purpose: Responsible for changing the working directory of the process.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::cd(vector<wstring> args)
{
	if (args.size() < 2)
	{
		std::wcout << "cd: Missing operand" << std::endl;
		return E_INVALIDARG;
	}

	wstring wsPath = Helpers::vecsum(1, args, true);

	std::error_code ec;
	fs::current_path(wsPath, ec);

	if (ec.value() != 0)
		std::wcout << "cd: " << Helpers::GetErrorMessage(ec) << std::endl;

	return S_OK;
}