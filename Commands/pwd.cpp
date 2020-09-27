#include "Commands.hpp"
#include <iostream>

/*
File: pwd.cpp
Purpose: Prints the working directory for the process.
Author: Pin (https://github.com/sailent704)
*/

HRESULT Commands::pwd(vector<string> args)
{
	std::cout << fs::current_path().string() << std::endl;

	return S_OK;
}