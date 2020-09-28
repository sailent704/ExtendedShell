#include "Commands.hpp"
#include <iostream>
#include <fstream>

/*
File: rm.cpp
Purpose: Responsible for removing files
Author: Pin (https://github.com/sailent704)

Known bugs:
	rm can't remove files that are in-use (make them unlinked)
*/

HRESULT Commands::rm(vector<wstring> args)
{
	return S_OK;
}