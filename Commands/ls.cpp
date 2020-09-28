#include "Commands.hpp"
#include <iostream>

/*
File: ls.cpp
Purpose: Responsible for listing the files in a given directory.
Author: Pin (https://github.com/sailent704)

Known bugs: 
	Completely breaks when displaying a folder like TestFolder\* (created through WSL)
*/

HRESULT Commands::ls(vector<wstring> args)
{
	return S_OK;
}