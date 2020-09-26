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
	HRESULT ls(vector<string> args);
}