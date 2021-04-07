#include "Commands.hpp"
#include <iostream>

/*
File: pwd.cpp
Purpose: Prints the working directory for the process.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::pwd(vector<wstring> args)
{
	std::error_code ec;
	auto path = fs::current_path(ec);

	std::wcout << path.native() << std::endl;

	return S_OK;
}