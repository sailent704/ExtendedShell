#pragma once
#include "../Helpers/Helpers.hpp"
#include <Windows.h>
#include <filesystem>
/*
File: Commands.hpp
Purpose: Contains declarations of all Commmand functions.
Author: Pin (https://github.com/sailent704)
*/

namespace fs = std::filesystem;

namespace Commands
{
	//Args unused:
	HRESULT pwd(vector<wstring> args);
	HRESULT clear(vector<wstring> args);
	HRESULT exit(vector<wstring> args);

	//Args used:
	HRESULT cd(vector<wstring> args);
	HRESULT cat(vector<wstring> args);
	HRESULT ls(vector<wstring> args);
	HRESULT mkdir(vector<wstring> args);
	HRESULT touch(vector<wstring> args);
	HRESULT rm(vector<wstring> args);

	HRESULT _execute(vector<wstring> args);
	std::error_code _iteratefolder(wstring wsPath, bool bRecursive, function<void(fs::directory_entry&, bool)> onIterator);
}