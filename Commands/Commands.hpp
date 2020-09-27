#pragma once
#include "../Helpers/Helpers.hpp"
#include <Windows.h>

namespace Commands
{
	//Args unused:
	HRESULT pwd(vector<string> args);
	HRESULT clear(vector<string> args);

	//Args used:
	HRESULT cd(vector<string> args);
	HRESULT cat(vector<string> args);
	HRESULT ls(vector<string> args);
	HRESULT mkdir(vector<string> args);
	HRESULT touch(vector<string> args);
	HRESULT rm(vector<string> args);

	HRESULT RunFile(vector<string> args);
}